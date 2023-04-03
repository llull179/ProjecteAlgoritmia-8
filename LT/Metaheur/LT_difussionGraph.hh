#include <vector> 
#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <list>


using namespace std;

class LT_difussionGraph {

    protected:

        // graph dimension
        int n, m;
        // graph itself
        vector<vector<int>> g;
        // visited nodes
        vector <bool> spreadedNodes;
        // ratio needed to influence a node
        double r;
        // number of already spreaded nodes
        int spreaded;
        

    public:
        // degault and parametrized constructor
        LT_difussionGraph(){}

        LT_difussionGraph(int n, double r){
            this -> n = n;
            this -> r = r;
            spreaded = 0;
            g.resize(n);
            cout << g.size() << endl;
            spreadedNodes.resize(n, false);
        }

        // set edges
        void readEdges(int m){
            this-> m = m;

            for(int i = 0; i < m; i++){
                int a, b;
                cin >> a >> b;
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
            }
        }

        // read starting subset of nodes
        void modStartingSubset(const list<int>& l){
            // if list is empty asks user for nodes
            if(l.size() ==0){
                // subset of nodes
                int x;
                while(cin >> x and x!=-1){
                    if (not spreadedNodes[x]) {
                        spreadedNodes[x] = true;
                        spreaded++;
                    }
                }   
            }
            // otherwise reads nodes from the linked list
            else{
                list<int>::const_iterator it=l.begin();
                while(it != l.end()){
                    if (not spreadedNodes[*it]) { spreadedNodes[*it] = true; ++spreaded;}
                    it++;
                }
            }   
        }

        bool inStartingSubset (int i) {
            return spreadedNodes[i];
        }

        // propagation
        int propagate(){
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
                        if (count >= s*this->r) {newSpreadedNodes[i] = true; ++newV;}
                    }
                }
                spreaded += newV;
            }

            return spreaded;
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
};