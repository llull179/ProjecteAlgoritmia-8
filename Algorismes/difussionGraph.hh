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
        // spreading probability
        double p;

    public:
        // default and parametrized constructor
        difussionGraph(){}

        difussionGraph(int n){
            this-> n = n;
            g.resize(n);
            cout << g.size() << endl;
            spreadedNodes.resize(n, false);
        }

        // set edges
        virtual void readEdges(int m, double p){
            this-> m = m;

            for(int i = 0; i < m; i++){
                int a, b;
                cin >> a >> b;
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
            }
            this->p = p;     
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

        // propagation
        int propagateIC(){
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

        //Comprova si el conjunt de nodes 'sol' és una solució vàlida
        //Si checkIC es true comprova pel model de solució per IC, en cas contrari comprova la solució
        //pel model de difusió de LT
        bool isSolution(const vector<bool>& sol, bool checkIC) {
            for(int i = 0; i < sol.size(); ++i) {
                if(sol[i]) nodesToSpread.push(i);
            } 
            if(checkIC && propagateIC() == n) return true;
        // else if(!checkIC && propagateLT() == n) return true;
            else return false;
        
        }

        vector<bool> getRandomNodes() {
            vector<bool> nodes (n,false);
            return nodes;
        }
        vector<bool> getMinDominantSet() {
            vector<bool> uncovered(n, true);
            queue<int> q;
            vector<int> scores;

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
                            for(int j = 0; j < g[neighbor][j]; ++j) {
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

        double computeNodeInfluence_IC(int src){
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
};
#endif