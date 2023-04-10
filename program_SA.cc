#include "SA.hh"
#include <string.h>
#define INPUT_PATH "./input-graphs/"


using namespace std;


int askMode() {
    cout << "Select intial solution model:" << endl;
    cout << "Type <R> for select a random nodes solution"<<endl;
    cout << "Type <D> for select a Minimum Dominant Set solution"<<endl;
    cout << "Type <G> for select a LocalSearch implementation solution"<<endl;
    string dmode; 
    cin >> dmode;
    if(dmode == "R") return 0;
    else if(dmode=="D") return 1;
    else return 2;
}

int main(int argc, char * argv[]){

    // MODE 1:  manual graph input
    if(argc == 1){

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

        // graph order
        int n, m; double r;
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of vertices: " ;
        cin >> m;

        // spreading probability | propagating ratio
        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> r; cout << endl;
        if(r > 1 || r < 0){
            cerr << "Invalid probability/ratio" << endl;
            return -1;
        }

        // build graph
        SA G = SA(n,r);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        G.readEdges(m);

        // ask for method for subset computation 
        int mode = askMode();
        
        // set SA parameters
        int temp = 100;
        double varEnergia = 50;
        bool modeIC;
        if (dmode == "IC") modeIC = true;
        else modeIC = false;
        
        // run SA
        G.simulated_annealing(mode,temp,modeIC,varEnergia);

    }
    // graph input from file
    else if (argc == 2){

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

        // build graph                  
        string filename = argv[1];
        SA G = SA();
        
        // spreading probability | propagation ratio
        double r;
        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> r; cout << endl;
        if(r > 1 || r < 0){
            cerr << "Invalid probability/ratio" << endl;
            return -1;
        }
        
        // build graph
        G.readEdgesFromFile2(r, INPUT_PATH + filename);

        // ask for method for subset computation 
        int mode = askMode();

        // set SA parameters
        int temp = 50;
        double varEnergia = 75;

        bool modeIC;
        if (dmode == "IC") modeIC = true;
        else modeIC = false;
        
        // run SA
        G.simulated_annealing(mode,temp,modeIC,varEnergia);
    }

    // MODE 3: Test Graph propagation
    else if(argc == 3 && strcmp(argv[2], "test") == 0){

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

        // build graph
        string filename = argv[1];
        Greedy g = Greedy();
        double pr;

        // spreading probability | propagating ratio
        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid probability/ratio" << endl;
            return -1;
        }

        // read graph edges
        g.readEdgesFromFile2(pr, INPUT_PATH + filename);

        // read subset of nodes to propagate
        list<int> l;
        int x;
        int c = 0;
        while(cin >> x && x != -1){
            l.push_back(x);
            ++c;
        }
        // begin difusion 
        if(dmode == "LT")  cout << g.testDifusionLT(l)+c<<endl; 
        else cout << g.testDifusionIC(l)<<endl;
    }
    else{
        cerr << "Invalid arguments." << endl;
        cerr << "USAGE:" << endl;
        cerr << "   manual input:           $ ./program_SA" << endl;
        cerr << "   input from file:        $ ./program_SA graph_NAME " << endl;
        cerr << "   test propagation:       $ ./program_Greedy graph_NAME test " << endl;
        return -1;
    }
    return 0;

}

