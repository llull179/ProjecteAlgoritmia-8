
#include "Greedy.hh"
#include "LocalSearch.hh"

#include <string>

#define INPUT_PATH "../Utilities/input-graphs/"



int main(int argc, char * argv[]){

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

    //Intoduce propability for IC and wieght for LT
    double pr;
    if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else  cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;


    //Introduce which algorith execute
    int action;
    cout << "Select action:" << endl;
    cout << "Type 0 for just difusion" << endl;
    cout << "Type 1 for Greedy Algorithm" << endl;
    cout << "Type 2 for LocalSearch difusion" << endl;
    cout << "Type 3 for Metauristic Algorithm" << endl;
    cin >> action;

    //declarar el tipo de algoritmo
    LocalSearch g = LocalSearch();
    
    // manual graph input
    if(argc == 1){
        int n, m; 
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of edges: " ;
        cin >> m;

        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m, pr);
          
    }
    // graph input from file
    else if (argc == 2){
        string filename = argv[1];

        g.readEdgesFromFile(pr, INPUT_PATH + filename);
  
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    /*if(action ==1) {
        if(dmode == "IC")g.beginDifusion_IC();
        else LT difusion;
    }
    else if(action == 2) {*/
        if(dmode=="IC") g.beginDifusion(true);
        else g.beginDifusion(false);
    //}
    return 0;

}

