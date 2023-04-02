#include "LT_Greedy.hh"
#include <string>
#define INPUT_PATH "../input-graphs/"



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
        LTGreedy g = LTGreedy(n,r);
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m);


        // begin difusion
        g.beginDifusion(); 
    }
    // graph input from file
    else if (argc == 2){
        string filename = argv[1];
        LTGreedy g = LTGreedy();
        
        cout << "Introduce Spreading probability: ";
        double r; cin >> r; cout << endl;
        g.readEdgesFromFile(r, INPUT_PATH + filename);

        // begin difusion
        g.beginDifusion(); 
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}

