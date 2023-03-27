#include "IC_difussionGraph.hh"
#include <queue>
#include <vector>

class Greedy: private IC_difussionGraph{

    private:
        // <degree, vertexId>
        priority_queue <pair<int,int>> degree;
        
    public:


        Greedy(int n){
            this-> n = n;
            g.resize(n);
            cout << g.size() << endl;
            // O(n)
            spreadedNodes.resize(n, false);

        }

        void readEdges(int m){
            this-> m = m;

            // O(n)
            for(int i = 0; i < m; i++){
                int a, b;
                cin >> a >> b;
                // add edge
                g[a].push_back(b);
                g[b].push_back(a);
            }

            // fills the priority_queue -> O(n*lgn)
            for(int i = 0; i < n; i++){
                degree.push(make_pair(g[i].size(), i));
            }
        }


        void beginDifusion(){
            int spreaded = 0;
            double maxInfluence = 0.0;
            int maxInfluenceNode = 0;

            // compute influence of all nodes
            while(spreaded != n){
                for(int i = 0; i < this->n; i++){
                    if (not spreadedNodes[i]){
                        double tmpInfluence = computeGraphInfluence(i);
                    }
                }
            }
        }

        /*
        Given a node v, computes influence of u in the graph as the sum
        of influence to every other node in the graph */
        double computeGraphInfluence(int u){

            // distances array
            vector <int> distances = vector<int>(n, __INT_MAX__);
            // visited nodes
            vector <bool> visited = vector<bool>(n, false);

            // source node metrics
            double nodeInfluence = 0.0;
            distances[u] = 0;
            visited[u] = true;

            for(int i = 0; i < this-> n; i++){
                

                // checks if node has been spreaded and ignore it if so
                if(not spreadedNodes[i]){
                    
                }
            }
        }

        int minDistance(vector<int>& distances, vector<bool>& visited){
            int minimum=__INT_MAX__, idx; 
            for(int i = 0; i < this-> n; i++){
                if(not visited[i] && distances[i]<=minimum){
                    minimum = distances[i];
                    idx=i;
                }
            }
            return idx;
        }
};  