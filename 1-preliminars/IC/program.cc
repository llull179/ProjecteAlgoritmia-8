#include "IC_difussionGraph.hh"



int main(){
    // input reading
        // nodes and edges
    int n, m;
    cout << "Number of nodes: " ;
    cin >> n;
    IC_difussionGraph g = IC_difussionGraph(n);
    cout << "Number of vertices: " ;
    cin >> m;
    cout << "Introduce edges in the folllowing format : i j " << endl;
    g.readEdges(m);
    g.printGraph();

        // subset of vertices
    g.readStartingSubset();
    
    // tries diffusion
    g.propagate();


}