#include "IC_difussionGraph.hh"
#include <cmath>
#include <list>


typedef pair<int,int> ppair;


class Greedy: private IC_difussionGraph{

    public:

        Greedy(int n){
            this-> n = n;
            g.resize(n);
            cout << g.size() << endl;
            spreadedNodes.resize(n, false);
        }

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

        void beginDifusion(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list <int> subset;
            vector<bool> inSubset(n, false);


            int iteration = 0;

            while(propagatedNodes != this->n){

                cout << "Iteration " << iteration << endl;

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
            }

            cout << "Difusion ended, check output-IC file to see benchmarks and the result" << endl;
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