#include "LT_difussionGraph.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>


typedef pair<double,int> ppair;


class SA: private LT_difussionGraph {

    public:

        // constructor and parametrized constructor ------------------------
        SA(){}

        SA(int n, double r){
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

        vector<bool> form(const vector<int>& v) {
            int n = v.size();
            vector<bool> s(g.size(),false);
            for (int i = 0; i < n; ++i) {
                s[v[i]] == true;                //cal mirar si va de 0 a n -1 o de 0 a n !!
            }
            return s;
        }

        bool es_solucio(const vector<bool>& S) {

        }  

        vector<bool> simulated_annealing(const vector<bool> & ini, int temp) {
            int r;
            vector<bool> sol,aux = ini;
            while(temp > 0) {
                for (int i = 0; i < 100; ++i) {
                    aux = sol;
                    r = rand()%g.size();
                    //forma part de S (veiem si el podem treure)
                    if (ini[r]) {
                        aux[r] = false;
                        if(es_solucio(aux)) sol[r] = false;
                        else --i; //no volem comptar les iteracions que surten de l'espai de solucions
                    }
                    //no forma part de S (veiem si el podem afegir)
                    else {
                        double prob = pow(10, -1/temp);
                        int bound = rand()%100;
                        if (prob*100 <= bound) sol[r] = true;
                    }
                }
                --temp;
            }
            return sol;
        }

        vector<int> getMinDominantSet() {
            vector<bool> uncovered(n, true);
            queue<int> q;
            vector<int> scores;

            //Initialize scores in function of how nodes could influence one node
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < g[i].size(); j++) {
                    if (g[i][j] != i) {
                        scores[i]++;
                    }
                }
            }

            // Minimum dominant set
            bool mdsFind = false;
            while(!mdsFind) {
                int maxScore = -1;
                int maxNode = -1;
                
                for(int i = 0; i<n;++i) {
                    if (uncovered[i] && scores[i] > maxScore) {
                    maxScore = scores[i];
                    maxNode = i;
                    }
                }

                if(maxNode != -1) {
                    q.push(maxNode);
                    uncovered[maxNode] = false;
                    for ( int i = 0; i < g[maxNode].size(); i++)
                    {
                       int neighbor = g[maxNode][i];
                       if(neighbor != maxNode && uncovered[neighbor]) {
                            uncovered[neighbor] = false;
                            for(int j = 0; j < g[neighbor][j]; ++j) {
                                if(g[neighbor][j] != neighbor) {
                                    scores[g[neighbor][j]]--;
                                }
                            }
                       }
                       
                    }
                    
                }else {
                    mdsFind = true;
                }

            }
            vector<int> result;
            while(!q.empty()) {
                result.push_back(q.front());
                q.pop();
            }
            return result;
        }

        void beginDifusionLTInit(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            priority_queue < ppair, vector<ppair>, less<ppair> > Q;
            for (int i = 0; i < this -> n; ++i) {
                int p = computeNodeInfluence(i,inSubset);
                Q.push(make_pair(p,i));
            }

            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            while(propagatedNodes != this->n){

                int idx = Q.top().second;
                Q.pop();
                // add node to subset
                if (not inStartingSubset(idx)) {
                    inSubset[idx] = true;
                    subset.push_back(idx);
                    list<int> l;
                    l.push_back(idx);
                    modStartingSubset(l);
                    newPropagatedNodes = propagate(); 
                    if (newPropagatedNodes == propagatedNodes) {
                        subset.pop_back();
                        //newSubset.pop_back();
                    }
                    else propagatedNodes = newPropagatedNodes;
                    iteration++;

                    // output to file current subset
                    file << "Iteration " << iteration << ", current subset of nodes:";
                    list<int>::const_iterator it=subset.begin();
                    while(it != subset.end()){
                        file << " " << (*it);
                        it++;
                    }file << endl << "--------------------" << endl << endl;
                }
            }                
            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }

        void beginDifusionLTAlways(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            priority_queue < ppair, vector<ppair>, less<ppair> > Q;
            

            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            while(propagatedNodes != this->n){
                int max = 0;
                int idx = -1;
                for (int i = 0; i < this -> n; ++i) {
                    int p = computeNodeInfluence(i,inSubset);
                    if (p > max) {
                        max = p;
                        idx = i;
                    }
                }
                // add node to subset
                if (not inStartingSubset(idx)) {
                    inSubset[idx] = true;
                    subset.push_back(idx);
                    list<int> l;
                    l.push_back(idx);
                    modStartingSubset(l);
                    newPropagatedNodes = propagate(); 
                    if (newPropagatedNodes == propagatedNodes) {
                        subset.pop_back();
                        //newSubset.pop_back();
                    }
                    else propagatedNodes = newPropagatedNodes;
                    iteration++;

                    // output to file current subset
                    file << "Iteration " << iteration << ", current subset of nodes:";
                    list<int>::const_iterator it=subset.begin();
                    while(it != subset.end()){
                        file << " " << (*it);
                        it++;
                    }file << endl << "--------------------" << endl << endl;
                }
            }                
            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }

        double computeNodeInfluence(int src, vector<bool> &S){
            // Priority queue for vertices that are being processed
            priority_queue < ppair, vector<ppair>, greater<ppair> > Q;
            Q.push(make_pair(0,src));

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
                        if(not S[v] and distances[v] < distances[u]+distances[u]*1/s){
                            distances[v] = distances[u] + distances[u]*1/s;
                            visited[v] = true;
                            Q.push(make_pair(-distances[v], v));
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