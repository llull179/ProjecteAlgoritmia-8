#include <iostream>
#include <vector>
#include <utility>
#include <queue>

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

        vector<bool> simulateDifusion( vector<int> S) {
            int n = adj_list.size();
            int randomNumber, visiting;
            int countVisited = 0;

            vector<bool> visited (n, false);
            queue<int> toVisit (deque<int>(S.begin(), S.end()));

            while(countVisited < n and not toVisit.empty()){

                visiting = toVisit.front(); 
                toVisit.pop();
                visited[visiting] = true;
                for(int i = 0; i < adj_list[visiting].size(); i++) {
                    randomNumber = int(rand() % 2);
                    if(randomNumber == 1 and not visited[i]) {
                        toVisit.push(i);
                    }
                }
            }
            return visited;
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
    vector<int> S {1,2};
    G.defineGraph(4, vertexs, 0.5);
    //G.showGraph();
    vector<bool> as = G.simulateDifusion(S);
    for(int k = 0; k< as.size();++k) {
        cout<<as[k]<<endl;
    }
    cout << "FIN"<<endl;
}