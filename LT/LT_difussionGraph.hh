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
        // number of already spreaded nodes
        int spreaded;
        

    public:
        // degault and parametrized constructor
        LT_difussionGraph(){}

        LT_difussionGraph(int n){
            this -> n = n;
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
        void readStartingSubset(const list<int>& l){
            // if list is empty asks user for nodes
            if(l.size() ==0){
                // subset of nodes
                cout << "Introduce initial subset of nodes: "  << endl;
                cout << "(end subset with a -1)" << endl;
                int x;
                while(cin >> x and x!=-1){
                    spreadedNodes[x] = true;
                    spreaded++;
                }   
            }
            // otherwise reads nodes from the linked list
            else{
                spreaded += l.size();
                list<int>::const_iterator it=l.begin();
                while(it != l.end()){
                    spreadedNodes[*it] = true;
                    it++;
                }
            }   
        }

        // propagation
        int propagate(){

            int steps = 0;
            int numPropagatedNodes = spreaded;
            auto begin = std::chrono::high_resolution_clock::now();
            vector<bool> newSpreadedNodes;
            while(numPropagatedNodes < n and numPropagatedNodes != spreaded){
                newSpreadedNodes = spreadedNodes;
                steps++;
                for(int i = 0; i < n; i++){
                    if(not newSpreadedNodes[i]){
                        // tries propagation
                        int count = 0;
                        int s = g[i].size();
                        for (int j = 0; j < s and 2*count < s; ++j) {
                            if (spreadedNodes[g[i][j]]) ++count;
                        }
                        if (2*count >= s) {newSpreadedNodes[i] = true; ++numPropagatedNodes;}
                    }
                }
            }
            cout << "Final: " << numPropagatedNodes << " nodes expanded in " << steps << " steps";
            // empty used data structures
            spreaded = 0;
            spreadedNodes = vector<bool>(n, false);

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
};