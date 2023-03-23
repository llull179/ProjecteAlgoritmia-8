#include <vector> 
#include <iostream>
#include <queue>


using namespace std;

class IC_difussionGraph {

    private:

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
        // constructor
        IC_difussionGraph(int n){
            this-> n = n;
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
        void readStartingSubset(){
                // subset of nodes
            cout << "Introduce initial subset of nodes: "  << endl;
            cout << "(end subset with a -1)" << endl;
            int x;
            while(cin >> x and x!=-1){
                nodesToSpread.push(x);
                spreadedNodes[x] = true;
            }   
                // spreading probability
            cout << "Introduce the spreading probability: ";
            cin >> this-> p; 
        }

        // propagation
        void propagate(){
            while(not nodesToSpread.empty()){
                // get next element to propagate
                int tmp = nodesToSpread.front();

                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        if(not spreadedNodes[i]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p > this-> p){
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }
        }

        // print graph
        void printGraph(){
            cout << "Displaying graph ..." << endl;
            for(int i = 0; i < this->n; i++){
                cout << "node " << i << " : ";
                cout << "{";
                for (int j = 0; j < g[i].size(); j++){
                    if(j == 0) cout << g[i][j];
                    else cout << ", " << g[i][j];
                }
                cout << "}" << endl;
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