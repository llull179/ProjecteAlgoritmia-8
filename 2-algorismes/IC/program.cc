#include "Greedy.hh"
#include <string>
#define INPUT_PATH "../input-graphs/"



int main(int argc, char * argv[]){
    // manual graph input
    if(argc == 1){
        int n, m; double p;
        cout << "Number of nodes: " ;
        cin >> n;
        Greedy g = Greedy(n);
        cout << "Number of vertices: " ;
        cin >> m;
        cout << "Introduce Spreading probability: ";
        cin >> p; cout << endl;
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m, p);


        // begin difusion
        g.beginDifusion(); 
    }
    // graph input from file
    else if (argc == 2){
        string filename = argv[1];
        Greedy g = Greedy();
        
        cout << "Introduce Spreading probability: ";
        double p; cin >> p; cout << endl;
        g.readEdgesFromFile(p, INPUT_PATH + filename);

        // begin difusion
        g.beginDifusion(); 
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}

