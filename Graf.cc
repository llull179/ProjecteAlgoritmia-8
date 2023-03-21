#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Graph {
    private:
        float prob;
        vector<vector<int>> adj_list;

    public:
        Graph() {}

        Graph(int n, vector<pair<int,int>> E,float p) {
            defineGraph(n, E, p);
        }
        void defineGraph(int n, vector<pair<int,int>> E,float p) {
            prob = p;
            vector<vector<int>> adj_list_temp(n);
            for (int i = 0; i < E.size(); ++i) {
                adj_list_temp[E[i].first-1].push_back(E[i].second);
                adj_list_temp[E[i].second-1].push_back(E[i].first);
            }
            adj_list = adj_list_temp;
        }

        void showGraph() {
            for(int i = 0; i < adj_list.size(); ++i) {
                cout << i+1 <<"--> ";
                for(int j = 0; j < adj_list[i].size(); ++j) {
                    cout << adj_list[i][j] << " ";
                }
                cout << endl;
            }

        }
};

int main() {
    Graph G;
   vector<pair<int, int>> vertexs {
        {2, 3},
        {1, 2},
        {1, 3},
        {1, 4}
    };

    G.defineGraph(4, vertexs, 0.5);
    G.showGraph();
    cout << "FIN"<<endl;
}