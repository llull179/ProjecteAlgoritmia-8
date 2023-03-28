#include "Greedy.hh"



int main(){
    // input reading
        // nodes and edges
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

