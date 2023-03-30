#include <iostream>
#include <vector>
using namespace std;


int main() {
    cout << "Introdueixi tamany del graf" << endl;
    int n;
    cin >> n;
    vector<bool> inf(n);
    int c = 0;
    int t = 0;
    vector<vector<int>> adjL(n);
    for (int i = 0; i < n; ++i) {
        cout << "Introdueixi adjacències del vèrtex " << i << endl;
        int aux;
        while (cin >> aux and aux != -1) {
            adjL[i].push_back(aux);
        }
    }
    cout << "Introdueixi vèrtexs d'S" <<endl;
    int aux;
    while (cin >> aux and aux != -1) {
        ++c;
        inf[aux] = true;
    }
    int prev = 0;
    vector<bool> auxV;
    while (c < n and c != prev) {
        auxV = inf;
        prev = c;
        for (int i = 0; i < n; ++i) {
            if (not auxV[i]) { 
                int count = 0;
                int s = adjL[i].size();
                for (int j = 0; j < s; ++j) {
                    if (inf[adjL[i][j]]) ++count;
                }
                if (2*count >= s) {auxV[i] = true; ++c;}
            }
        }
        ++t;
        cout << t << ": " << c << " nodes expandit en total, " << prev << " prèviament" << endl;
        inf = auxV;
    }
    cout << "Final: " << c << " nodes expandits en " << t << " passes." << endl;

}
