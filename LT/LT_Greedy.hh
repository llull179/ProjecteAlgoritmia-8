#include "LT_difussionGraph.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>


typedef pair<double,int> ppair;


class LTGreedy: private LT_difussionGraph {

    public:

        // constructor and parametrized constructor ------------------------
        LTGreedy(){}

        LTGreedy(int n, int r){
            this -> n = n;
            this -> r = r;
            spreaded = 0;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        // public methods --------------------------------------------------

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

        void readEdgesFromFile(double r, string filename) {
            this -> m = 0;     
            this -> r = r;
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

        void beginDifusion(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();


            int iteration = 0;

            while(propagatedNodes != this->n){

                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if( not inSubset[i]) {
                        double nodeInfluence = computeNodeInfluence(i);
                        cout << "Node " << i << " influència: " << nodeInfluence << endl;
                        if (nodeInfluence > maxInfluence) {
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                inSubset[idx] = true;
                subset.push_back(idx);
                readStartingSubset(subset);
                propagatedNodes = propagate();

                iteration++;

                // output to file current subset
                file << "Iteration " << iteration << ", current subset of nodes:";
                list<int>::const_iterator it=subset.begin();
                while(it != subset.end()){
                    file << " " << (*it);
                    it++;
                }file << endl << "--------------------" << endl << endl;
            }

                    

            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }

        double computeNodeInfluence(int src){
            // Priority queue for vertices that are being processed
            priority_queue < ppair, vector<ppair>, greater<ppair> > Q;
            Q.push(pair(0,src));

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
                            Q.push(pair(-distances[v], v));
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

};