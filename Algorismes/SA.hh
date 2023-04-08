#include "difussionGraph.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>


typedef pair<double,int> ppair;


class SA: public difussionGraph {

    public:

        // constructor and parametrized constructor ------------------------
        SA(){
            cout << "construct" << endl;
        }

        SA(int n, double r){
            this -> n = n;
            this -> p = r;
            spreaded = 0;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        // public methods --------------------------------------------------

        void simulated_annealing(const vector<bool> & ini, int temp) {
            int r;
            vector<bool> sol = ini;
            vector<int> espai_solucions;
            while(temp > 0) {
                for (int i = 0; i < 10; ++i) {   
                    espai_solucions.clear();
                    for(int i = 0; i < sol.size(); ++i) {
                        if (sol[i]) {
                            sol[i] = false;
                            if(isSolution(sol,false)) espai_solucions.push_back(i);
                            sol[i] = true;
                        }
                        else espai_solucions.push_back(i);
                    }             
                    r = rand()%espai_solucions.size();
                    //forma part de S 
                    if (sol[r]) sol[r] = false;  
                    //no forma part de S (veiem si el podem afegir)
                    else {
                        double prob = pow(10, -1/temp);
                        int bound = rand()%100;
                        if (prob*100 <= bound) sol[r] = true;
                    }
                    cout << temp << endl;
                }
      
                --temp;
            }
             cout << "he acabado" << endl;
             
             for(int i = 0; i < sol.size(); ++i) {
                if (sol[i]) cout << i << endl;
             }
           
        }

      

    

};