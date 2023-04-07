#ifndef DIFUSSIONGRAPH_HH
#define DIFUSSIONGRAPH_HH
#include <vector> 
#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <list>
#include <cmath>


using namespace std;

class difussionGraph {

    protected:

        // graph dimension
        int n, m;
        // graph itself
        vector<vector<int>> g;
        // visited nodes
        vector <bool> spreadedNodes;
        // subset of nodes to spread
        queue <int> nodesToSpread;
        // double representing the spreading probability needed if modeling IC or the influence ratio used if modeling LT
        double p;
        // number of nodes already spreaded when modeling LT
        int spreaded;


    public:
        /***********************************************************************************************************
        DEFAULT AND PARAMETRIZED CONSTRUCTOR
        ***********************************************************************************************************/
        difussionGraph(){}

        difussionGraph(int n, double p){
            this -> p = p;
            this-> n = n;
            g.resize(n);
            cout << g.size() << endl;
            spreadedNodes.resize(n, false);
            spreaded = 0;
        }

        /***********************************************************************************************************
        GENERIC PUBLIC METHODS
        ***********************************************************************************************************/


        virtual void readEdges(int m){
            this-> m = m;

            for(int i = 0; i < m; i++){
                int a, b;
                cin >> a >> b;
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
            }
        }

        virtual void readEdgesFromFile(double pr, string filename){
            this-> m = 0;
            this->p = pr;     

            // read graph from file
            ifstream file(filename);

            // read graph dimension
            file >> this-> n;
            g.resize(n);
            spreadedNodes.resize(n, false);

            // read graph edges
            int a, b;
            while(file >> a >> b){
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
                this->m++;
            }
            file.close();
        }


        // read starting subset of nodes
        void enqueueStartingSet(){
            for(int i = 0; i < this->n; i++){
                if(spreadedNodes[i]) nodesToSpread.push(i);
            } 
        }

        double computeNodeInfluenceIC(int src){
            // Priority queue for vertices that are being processed
            queue <int> Q;
            Q.push(src);

            // Vector for disntances
            vector <int> distances(this->n, __INT_MAX__);
            distances[src] = 0;

            // Vector for visited nodes
            vector <bool> visited(n, false);
            visited[src] = true;

            while(not Q.empty()){
                // next node
                int u = Q.front();
                Q.pop();
                // visit all neightbours
                for(int i = 0; i < g[u].size(); i++){
                    // next neightbour
                    int v = g[u][i];
                    // if not visited, mark as visited and enqueue
                    if(not visited[v]){
                        distances[v] = distances[u] + 1;
                        visited[v] = true;
                        Q.push(v);
                    }
                }
            }
            // compute global influence as the sum of all influences
            double globalInfluence = 0.0;
            for(int i = 0; i < n; i++){
                globalInfluence += pow(this->p,distances[i]);
            }
            return globalInfluence;
        }

        // Computation of each nodes influence under the LT model using Djikstra's algorithm for navigating weighted graphs.
        double computeNodeInfluenceLT(int src){
            // Priority queue for vertices that are being processed
            priority_queue < pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > Q;
            Q.push(make_pair(0,src));

            // Vector for disntances
            vector <double> distances(this->n, 0);
            distances[src] = 1;

            // Vector for visited nodes
            vector <bool> visited(n, false);

            while(not Q.empty()){
                // next node
                int u = Q.top().second;
                Q.pop();
                if (not visited[u]) {
                    visited[u] = true;
                    // visit all neightbours
                    for(int i = 0; i < g[u].size(); i++){
                        // next neightbour
                        int v = g[u][i];
                        // modify distance if necesssary
                        double s = g[v].size();
                        if(distances[v] < distances[u]+distances[u]*1/s){
                            distances[v] = distances[u] + distances[u]*1/s;
                            visited[v] = true;
                            Q.push(make_pair(-distances[v], v));
                        }
                    }
                }
            }
            // compute global influence as the sum of all influences
            double globalInfluence = 0.0;
            for(int i = 0; i < n; i++){
                globalInfluence += distances[i];
            }
            return globalInfluence;
        }

        // print graph
        void printGraph(){
            for(int i = 0; i<n; i++){
                cout << "node " << i << " :";
                for(int j = 0; j< g[i].size(); j++){
                    cout << " " <<  g[i][j];
                }
                cout << endl;
            }
        }

        // print nodes belong to the diffusion subset
        void printDifusionSubstet(){
            for(int i = 0; i < spreadedNodes.size(); i++){
                if(spreadedNodes[i]) cout << i << " ";
            }
            cout << endl;
        }

        /***********************************************************************************************************
        INDEPENDENT CASCADE GREEDY METHODS
        ***********************************************************************************************************/
        void readStartingSubset(const list<int>& l){
            list<int>::const_iterator it=l.begin();
            while(it != l.end()){
                nodesToSpread.push(*it);
                spreadedNodes[*it] = true;
                it++;
            }
        }

        /*
        PROPAGATION FOR IC MODEL
            - v1: Propagation without saving previous iterations
            - v23: Optimized propagation, remembers past iterations
        */
        int propagateIC_v1(){

            int steps = 0;
            int numPropagatedNodes = nodesToSpread.size();
            auto begin = std::chrono::high_resolution_clock::now();

            while(not nodesToSpread.empty()){
                
                // get next element to propagate
                int tmp = nodesToSpread.front();
                steps++;
                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        
                        if(not spreadedNodes[g[tmp][i]]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p > (1-this-> p)){
                                // propagates to new node
                                numPropagatedNodes++;
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }

            // empty used data structures
            queue<int>empty;
            swap(this-> nodesToSpread, empty);
            spreadedNodes = vector<bool>(n, false);

            return numPropagatedNodes;
        }

        int propagateIC_v23(){
            int steps = 0;
            int numPropagatedNodes = nodesToSpread.size();

            while(not nodesToSpread.empty()){
                
                // get next element to propagate
                int tmp = nodesToSpread.front();
                steps++;
                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        
                        if(not spreadedNodes[g[tmp][i]]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p > (1-this-> p)){
                                // propagates to new node
                                numPropagatedNodes++;
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }
            return numPropagatedNodes;
        }

        

        /***********************************************************************************************************
        LINEAR THRESHOLD GREEDY METHODS
        ***********************************************************************************************************/

        // modify starting subset of nodes
        int modStartingSubset(const list<int>& l){
            // if list is empty asks user for nodes
            cout << spreaded << endl;
            int added = 0;
            if(l.size() ==0){
                // subset of nodes
                int x;
                while(cin >> x and x!=-1){
                    if (not spreadedNodes[x]) {
                        spreadedNodes[x] = true;
                        added++;
                    }
                }   
            }
            // otherwise reads nodes from the linked list
            else{
                list<int>::const_iterator it=l.begin();
                while(it != l.end()){
                    if (not spreadedNodes[*it]) { spreadedNodes[*it] = true; ++added;}
                    it++;
                }
            }
            spreaded += added;
            cout << "Added " << added << " nodes to the initial subset" << endl;
            return added; 
        }

        bool inStartingSubset(int i) {
            return spreadedNodes[i];
        }

        // propagation
        int propagateLT_v1(){
            int steps = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            vector<bool> newSpreadedNodes = spreadedNodes;
            int newV = -1;
            while(spreaded < n and newV != 0){
                newV = 0;
                spreadedNodes = newSpreadedNodes;
                steps++;
                for(int i = 0; i < n; i++){
                    if(not spreadedNodes[i]){
                        // tries propagation
                        double count = 0;
                        double s = g[i].size();
                        for (int j = 0; j < s; ++j) {
                            if (spreadedNodes[g[i][j]]) ++count;
                        }
                        if (count >= s*this->p) {newSpreadedNodes[i] = true; ++newV;}
                    }
                }
                spreaded += newV;
            }
            int result = spreaded;
            spreaded = 0;
            spreadedNodes = vector<bool>(n, false);
            return result;
        }

        int propagateLT_v23(){
            int steps = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            vector<bool> newSpreadedNodes = spreadedNodes;
            int newV = -1;
            while(spreaded < n and newV != 0){
                newV = 0;
                spreadedNodes = newSpreadedNodes;
                steps++;
                for(int i = 0; i < n; i++){
                    if(not spreadedNodes[i]){
                        // tries propagation
                        double count = 0;
                        double s = g[i].size();
                        for (int j = 0; j < s; ++j) {
                            if (spreadedNodes[g[i][j]]) ++count;
                        }
                        if (count >= s*this->p) {newSpreadedNodes[i] = true; ++newV;}
                    }
                }
                spreaded += newV;
            }

            return spreaded;
        }

        /***********************************************************************************************************
        LOCAL SEARCH METHODS 
        ***********************************************************************************************************/

        //Comprova si el conjunt de nodes 'sol' és una solució vàlida
        //Si checkIC es true comprova pel model de solució per IC, en cas contrari comprova la solució
        //pel model de difusió de LT
        bool isSolution(const vector<bool>& sol, bool checkIC) {
            for(int i = 0; i < sol.size(); ++i) {
                if(sol[i]) nodesToSpread.push(i);
            } 
            if(checkIC && propagateIC_v23() == n) return true;
        // else if(!checkIC && propagateLT() == n) return true;
            else return false;
        
        }

        vector<bool> getRandomNodes() {
            vector<bool> nodes (n,false);
            bool findSolution = false;
            while(!findSolution) {
                int rand_num = rand() % n;
                if(!nodes[rand_num]) nodes[rand_num] = true;
                findSolution = isSolution(nodes,true);
            } 
            return nodes;
        }
        vector<bool> getMinDominantSet() {
            vector<bool> uncovered(n, true);
            queue<int> q;
            vector<int> scores(n,0);
            //Initialize scores in function of how nodes could influence one node
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < g[i].size(); j++) {
                    if (g[i][j] != i) {
                        scores[i]++;
                    }
                }
            }
            // Minimum dominant set
            bool mdsFind = false;
            while(!mdsFind) {
                int maxScore = -1;
                int maxNode = -1;
                
                for(int i = 0; i<n;++i) {
                    if (uncovered[i] && scores[i] > maxScore) {
                    maxScore = scores[i];
                    maxNode = i;
                    }
                }
                if(maxNode != -1) {
                    q.push(maxNode);
                    uncovered[maxNode] = false;
                    for ( int i = 0; i < g[maxNode].size(); i++)
                    {
                       int neighbor = g[maxNode][i];
                       if(neighbor != maxNode && uncovered[neighbor]) {
                            uncovered[neighbor] = false;
                            for(int j = 0; j < g[neighbor].size(); ++j) {
                                if(g[neighbor][j] != neighbor) {
                                    scores[g[neighbor][j]]--;
                                }
                            }
                       }
                       
                    }
                    
                }else {
                    mdsFind = true;
                }

            }
            vector<bool> result(n,false);
            while(!q.empty()) {
                result[q.front()] = true;
                q.pop();
            }
            return result;
        }
};
#endif