#include "LocalSearch.hh"
#include <string>
#define INPUT_PATH "../Utilities/input-graphs/"

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
        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else  cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
        
        LocalSearch g = LocalSearch(n,pr);
        cout << "Number of edges: " ;
        cin >> m;
        cout << "Introduce edges in the folllowing format : i j " << endl;
        g.readEdges(m);
        int mode = askMode();
        // begin difusion
        if(dmode == "IC")  g.beginDifusion(true,mode); 
        else g.beginDifusion(false,mode);

    }

    // graph input from file
    else if (argc == 2){
        string filename = argv[1];
        LocalSearch g = LocalSearch();
        double pr;

        if(dmode == "IC") cout << "Introduce Spreading probability: ";
        else cout << "Introduce Spreading ratio: ";
        cin >> pr; cout << endl;
    
        g.readEdgesFromFile(pr, INPUT_PATH + filename);
        // begin difusion
        int mode = askMode();  

        if(dmode == "IC")  g.beginDifusion(true,mode); 
        else g.beginDifusion(false,mode);   
    }
    else{
        cerr << "Invalid number of arguments." << endl;
        return -1;
    }

    return 0;

}