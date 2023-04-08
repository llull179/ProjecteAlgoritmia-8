#include "SA.hh"
#include <string>
#define INPUT_PATH "../Utilities/input-graphs/"
using namespace std;


int main(int argc, char * argv[]){
    // manual graph input
    if(argc == 1){

        int n, m; double r;
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of vertices: " ;
        cin >> m;
        cout << "Introduce Spreading ratio or Spreading probability: ";
        cin >> r; cout << endl;
        SA G = SA(n,r);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        G.readEdges(m);
        vector<bool> sol_ini = G.getMinDominantSet();
        //definim la temperatura
        int temp = 100;
            // ask user for difussion model
        cout << "Select difusion model:" << endl;
        cout << "Type <IC> for independent cascade, or <LT> for Linear Threshold" << endl;
        string dmode;
        cin >> dmode;

        if (dmode != "LT" && dmode != "IC"){
            //invalid mode
            cerr << "Invalid difusion model" << endl;
            return -1;
        }
        bool modeIC;
        if (dmode == "IC") modeIC = true;
        else modeIC = false;
        double varEnergia = 50; //la variacio de lenergia sempre es la mateixa ja que afegim o treiem un node
        G.simulated_annealing(sol_ini,temp,modeIC,varEnergia);

    }
    // graph input from file
    else if (argc == 2){
                          
        string filename = argv[1];
        SA G = SA();
        
        cout << "Introduce Spreading ratio or Spreading probability: ";
        double r; cin >> r; cout << endl;
        

        G.readEdgesFromFile(r, INPUT_PATH + filename);

       vector<bool> sol_ini = G.getMinDominantSet();
        //definim la temperatura
        int temp = 100;
     // ask user for difussion model
        cout << "Select difusion model:" << endl;
        cout << "Type <IC> for independent cascade, or <LT> for Linear Threshold" << endl;
        string dmode;
        cin >> dmode;

        if (dmode != "LT" && dmode != "IC"){
            //invalid mode
            cerr << "Invalid difusion model" << endl;
            return -1;
        }
        bool modeIC;
        if (dmode == "IC") modeIC = true;
        else modeIC = false;
        double varEnergia = 50; //la variacio de lenergia sempre es la mateixa ja que afegim o treiem un node
        G.simulated_annealing(sol_ini,temp,modeIC,varEnergia);
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}

