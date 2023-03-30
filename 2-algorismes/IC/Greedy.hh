#include "IC_difussionGraph.hh"
#include <cmath>
#include <list>
#include <fstream>


typedef pair<int,int> ppair;


class Greedy: private IC_difussionGraph{

    public:

        // constructor and parametrized constructor ------------------------
        Greedy(){}

        Greedy(int n){
            this-> n = n;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        // public methods --------------------------------------------------

        void readEdges(int m, double p){
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

        void readEdgesFromFile(double p, string filename){
            this-> m = 0;
            this->p = p;     

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
            list <int> subset;
            vector<bool> inSubset(n, false);

            // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();


            int iteration = 0;

            while(propagatedNodes != this->n){

                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not inSubset[i]){
                        double nodeInfluence = computeNodeInfluence(i);
                        if(nodeInfluence > maxInfluence){
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

            cout << "Difusion ended, check output-IC-difusion file to see benchmarks and the result" << endl;
        }

        double computeNodeInfluence(int src){
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