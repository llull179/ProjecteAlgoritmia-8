#include <vector> 
#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <list>


using namespace std;

class IC_difussionGraph {

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
        // degault and parametrized constructor
        IC_difussionGraph(){}

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
        void readStartingSubset(const list<int>& l){
            // if list is empty asks user for nodes
            if(l.size() ==0){
                // subset of nodes
                cout << "Introduce initial subset of nodes: "  << endl;
                cout << "(end subset with a -1)" << endl;
                int x;
                while(cin >> x and x!=-1){
                    nodesToSpread.push(x);
                    spreadedNodes[x] = true;
                }   
            }
            // otherwise reads nodes from the linked list
            else{
                list<int>::const_iterator it=l.begin();
                while(it != l.end()){
                    nodesToSpread.push(*it);
                    spreadedNodes[*it] = true;
                    it++;
                }
            }   
        }

        // propagation
        int propagate(){

            int steps = 0;
            auto begin = std::chrono::high_resolution_clock::now();

            while(not nodesToSpread.empty()){
                // get next element to propagate
                int tmp = nodesToSpread.front();

                // check neightbours
                for(int i = 0; i < g[tmp].size(); i++){
                        steps++;
                        if(not spreadedNodes[g[tmp][i]]){
                            // tries propagation
                            double shot_p = (rand()%100)/100.0;
                            if(shot_p > (1-this-> p)){
                                nodesToSpread.push(g[tmp][i]);
                                spreadedNodes[g[tmp][i]] = true;
                            }
                        }
                }
                // node tmp does not try propagation again
                nodesToSpread.pop();
            }
            
            // Prints output to a file
            ofstream file;
            file.open ("output-IC");           

            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << steps << " steps, " << elapsed.count() * 1e-9 << "s." << endl;

            file << "Propagated nodes:";
            int solSize = 0;
            for(int i = 0; i < this->n; i++){
                if(spreadedNodes[i]){
                    solSize ++;
                }
            }
            file << endl;
            file.close();

            // empty used data structures
            queue<int>empty;
            swap(this-> nodesToSpread, empty);
            spreadedNodes = vector<bool>(n, false);

            return solSize;
        }

        // print graph
        void printGraph(){
            
        }

        // print nodes belong to the diffusion subset
        void printDifusionSubstet(){
            for(int i = 0; i < spreadedNodes.size(); i++){
                if(spreadedNodes[i]) cout << i << " ";
            }
            cout << endl;
        }
};