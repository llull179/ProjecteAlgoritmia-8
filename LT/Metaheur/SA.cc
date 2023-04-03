#include "SA.hh"
#include <string>
#define INPUT_PATH "../input-graphs/"
using namespace std;


int main(int argc, char * argv[]){
    // manual graph input
    if(argc == 1){

        int n, m; double r;
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of vertices: " ;
        cin >> m;
        cout << "Introduce Spreading ratio: ";
        cin >> r; cout << endl;
        SA G = SA(n,r);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        G.readEdges(m);
        vector<int> llistat = G.getMinDominantSet();
        //passar llistat de nodes a vector de booleans
        vector<bool> sol_ini = G.form(llistat);
        //definim la temperatura
        int temp = 100;
        vector<bool> sol_fin = G.simulated_annealing(sol_ini,temp);

    }
    // graph input from file
    else if (argc == 2){
        string filename = argv[1];
        SA G = SA();
        
        cout << "Introduce Spreading probability: ";
        double r; cin >> r; cout << endl;
        G.readEdgesFromFile(r, INPUT_PATH + filename);

       vector<int> llistat = G.getMinDominantSet();
        //passar llistat de nodes a vector de booleans
        vector<bool> sol_ini = G.form(llistat);
        //definim la temperatura
        int temp = 100;
        vector<bool> sol_fin = G.simulated_annealing(sol_ini,temp);
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}

