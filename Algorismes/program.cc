#include "Greedy.hh"
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

    // manual graph input
    if(argc == 1){
        int n, m; double pr;
        cout << "Number of nodes: " ;
        cin >> n;
        cout << "Number of edges: " ;
        cin >> m;

        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else  cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;

        Greedy g = Greedy(n,pr);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m);

        // begin difusion
        if(dmode == "IC")  g.beginDifusion_IC_v1(); 
        else g.beginDifusion_LT_v2();

    }

    // graph input from file
    else if (argc == 2){
        string filename = argv[1];
        Greedy g = Greedy();
        double pr;

        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;

        g.readEdgesFromFile2(pr, INPUT_PATH + filename);

        // begin difusion 
        if(dmode == "IC")  g.beginDifusion_IC_v2(); 
        else g.beginDifusion_LT_v1();   
    }
    else if(argc == 3){
        string filename = argv[1];
        Greedy g = Greedy();
        double pr;

        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;

        g.readEdgesFromFile2(pr, INPUT_PATH + filename);

        list<int> l;
        int x;
        int c = 0;
        while(cin >> x && x != -1){
            l.push_back(x);
            ++c;
        }
        // begin difusion 
        if(dmode == "LT")  cout << g.testDifusionLT(l)+c; 
        else cout << g.testDifusionIC(l);
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}