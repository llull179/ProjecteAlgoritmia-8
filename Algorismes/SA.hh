#include "difussionGraph.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>


typedef pair<double,int> ppair;


class SA: public difussionGraph {

    public:

        // constructor and parametrized constructor ------------------------
        SA(){}

        SA(int n, double r){
            this -> n = n;
            this -> p = r;
            spreaded = 0;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        // public methods --------------------------------------------------

        vector<bool> simulated_annealing(const vector<bool> & ini, int temp) {
            int r;
            vector<bool> sol,aux = ini;
            while(temp > 0) {
                for (int i = 0; i < 100; ++i) {                   
                    r = rand()%g.size();
                    //forma part de S (veiem si el podem treure)
                    if (sol[r]) {
                        aux = sol;
                        aux[r] = false;
                        if(isSolution(aux)) sol[r] = false;//CAL CANVIAR
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

      

    

};