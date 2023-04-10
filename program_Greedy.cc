#include "Greedy.hh"
#include <string.h>
#define INPUT_PATH "./input-graphs/"

using namespace std;

int main(int argc, char * argv[]){

    // MODE 1: Read graph manually
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
        int n, m; double pr;
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of edges: " ;
        cin >> m;

        // spreading probability | propagating ratio
        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else  cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        if(pr > 1 || pr < 0){
            cerr << "Invalid probability/ratio" << endl;
            return -1;
        }

        // build graph
        Greedy g = Greedy(n,pr);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m);

        // begin difusion
        if(dmode == "IC") g.beginDifusion_IC_v2(); 
        else g.beginDifusion_LT_v3();

    }

    // MODE 2: graph input from file
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

        // begin difusion 
        if(dmode == "IC")  g.beginDifusion_IC_v2(); 
        else g.beginDifusion_LT_v1();   
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
        cerr << "   manual input:           $ ./program_Greedy " << endl;
        cerr << "   input from file:        $ ./program_Greedy graph_NAME " << endl;
        cerr << "   test propagation:       $ ./program_Greedy graph_NAME test " << endl;
        return -1;
    }

    return 0;

}