#include "difussionGraph.hh"
#include "Greedy.hh"
#include <cmath>
#include <list>
#include <queue>
#include <fstream>




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

        void simulated_annealing(int mode, int temp, bool IC, double varEn) {
            int r;
            vector<bool> sol;
             ofstream file;
            file.open("output_SA");   
            auto begin = std::chrono::high_resolution_clock::now();
            
            if(mode == 0) sol = getRandomNodes(IC);
            else if(mode == 1) sol = getMinDominantSet();
            else {
                Greedy gred = Greedy(g,p);
                if(IC){
                    gred.beginDifusion_startingSubset_IC(sol);
                }
                else gred.beginDifusion_startingSubset_LT(sol);
            }
            file << "----------SOLUCIÓ INICIAL:----------" << endl;
            for(int i = 0; i < sol.size();++i) if (sol[i]) file << i << ' ';
            file << endl;

            vector<int> espai_solucions;
            while(temp > 0) {
                for (int j = 0; j < 20; ++j) {   
                    espai_solucions.clear();
                    for(int i = 0; i < sol.size(); ++i) {
                        if (sol[i]) {
                            sol[i] = false;
                            if(isSolution(sol,IC))  espai_solucions.push_back(i);                     
                            sol[i] = true;
                        }
                        else espai_solucions.push_back(i);
                    }             
                    r = rand()%espai_solucions.size();
                    //forma part de S 
                    if (sol[espai_solucions[r]]) sol[espai_solucions[r]] = false;  
                    //no forma part de S (veiem si el podem afegir)
                    else {
                        double prob = pow(10.0, -varEn/temp);
                        cout << prob << endl;
                        int al = rand()%100;
                        if (al <= prob*100) sol[r] = true;
                    }
                }
                cout << temp << endl;
                --temp;
            }           
            auto end = std::chrono::high_resolution_clock::now();
            file << "----------SOLUCIÓ FINAL:----------" << endl;
            for(int i = 0; i < sol.size();++i) if (sol[i]) file << i << ' ';
            file << endl<< "----------------------------------" << endl;
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();
        }

      

    

};