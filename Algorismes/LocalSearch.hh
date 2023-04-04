#ifndef LOCALSEARCH_HH
#define LOCALSEARCH_HH
#include <iostream>
#include <vector>
#include "difussionGraph.hh"
#include <queue>

using namespace std;

class LocalSearch: public difussionGraph{
    private:
    struct myPair {
        int first;
        int second;

        bool operator<(const myPair& other) const {
            return second < other.second;
        }
    };
    public:
    LocalSearch() {

    }

    void beginDifusion(bool modeIC) {
        // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion");   

        // sets timer
        auto begin = std::chrono::high_resolution_clock::now();
        int iteration = 0;
        vector<bool> sol;
        if(modeIC) sol = getRandomNodes();
        else if(!modeIC) sol = getMinDominantSet();
        else /*/sol = //beginGreedy/*/;
        
        vector<double> influence(n,0);

        for(int i = 0; i< n; i++) {
            influence[i] = computeNodeInfluence_IC(i);
        }
        vector<int> meanInfluence;
        bool converge = false;
        
        while(!converge) {
            //Calcular la mitjana de la influencia de tots els veis de cada node
            priority_queue<myPair> meanInfluence;
            myPair pair;
            for(auto i: sol) {
                double sum = 0;
                double count = 0;
                for(auto j: g[i]) {
                    ++count;
                    sum += influence[j];
                }
                pair.first = i;
                pair.second = sum/count;
                meanInfluence.push(pair) ;
            }
            int minInfl = meanInfluence.top().second;
            int minNod = meanInfluence.top().first;;

            bool findSolution = false;
            int it = 0;
            while(it < meanInfluence.size() && !findSolution) {
                sol[minNod] = false;
                if(isSolution(sol,true)) {
                    findSolution = true;
                }
                else {
                    sol[minNod] = true;
                }
                ++it;
                // output to file actual subset of nodes
                file << "Iteration " << iteration << ", current subset of nodes:";
                for(int i = 0; i < this->n; i++){
                    if(sol[i]) file << " " << i;
                } 
                file << endl << "--------------------" << endl << endl;
            }
            if(findSolution == false) converge = true;

        }
        /// stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-IC-difusion file to see benchmarks and the result" << endl;
        }
};
#endif