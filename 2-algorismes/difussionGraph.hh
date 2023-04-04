#include <vector> 
#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <list>


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
        int propagate(){
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
};