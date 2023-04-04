#include <iostream>
#include <vector>
#include "difussionGraph.hh"
#include <queue>

using namespace std;

class LocalSearch: protected difussionGraph{
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

    vector<int> beginDifusion() {
        vector<int> sol = this->getDominantSet();
        vector<int> influence;
        vector<int> meanInfluence;
        bool converge = false;
        
        while(!converge) {
            //Calcular la mitjana de la influencia de tots els veis de cada node
            priority_queue<myPair> meanInfluence;
            myPair pair;
            for(auto i: sol) {
                int sum = 0;
                int count = 0;
                for(auto j: g[sol]) {
                    ++count;
                    sum += influence[j];
                }
                pair.first = i;
                pair.second = sum/count;
                meanInfluence.push(pair) ;
            }
            int minInfl = meanInfluence.front().second;
            int minNod = meanInfluence.front().first;;

            bool findSolution = false;
            int it = 0;
            while(it < meanInfluence.size() && !findSolution) {
                sol[minNod] = false;
                if(isSol(sol)) {
                    findSolution = true;
                }
                else {
                    sol[minNod] = true;
                }
                ++it;
            }
            if(findSolution == false) converge = true;
        }
    }
};