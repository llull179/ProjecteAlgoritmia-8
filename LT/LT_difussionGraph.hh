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

        LT_difussionGraph(int n, int r){
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
        void readStartingSubset(const list<int>& l){
            // if list is empty asks user for nodes
            spreaded = 0;
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
            cout << "Initially spreaded nodes:";
            for (int i = 0; i < spreadedNodes.size(); ++i) {
                if (spreadedNodes[i]) cout << " " << i;
            }
            cout << "Propagation ratio is " << this->r << endl;
            cout << endl;
            int steps = 0;
            int numPropagatedNodes = spreaded;
            auto begin = std::chrono::high_resolution_clock::now();
            vector<bool> newSpreadedNodes;
            int newV = -1;
            while(numPropagatedNodes < n and newV != 0){
                newV = 0;
                newSpreadedNodes = spreadedNodes;
                steps++;
                for(int i = 0; i < n; i++){
                    if(not newSpreadedNodes[i]){
                        // tries propagation
                        double count = 0;
                        double s = g[i].size();
                        for (int j = 0; j < s; ++j) {
                            cout << g[i][j] << " adjacent a " << i << endl;
                            if (spreadedNodes[g[i][j]]) ++count;
                        }
                        cout << "node " << i << " influenciat per " << count << " nodes de " << s << " possibles" << endl;
                        cout << s*this->r << endl;
                        if (count >= s*this->r) {newSpreadedNodes[i] = true; cout << i << " ara actiu" << endl; ++newV;}
                    }
                }
                numPropagatedNodes += newV;
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