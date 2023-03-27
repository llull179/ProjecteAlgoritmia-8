#include "IC_difussionGraph.hh"

class IC_greedy: private IC_difussionGraph() {


    public:

        double valueShortestPath(int u, int v) {
            double influence = 0;

            return influence;
        }

        int getNodeMaxInfleunce() {
            int nodeMaxInlfuence, influence, maxInfluence;
            double tmpInfluence, maxInfluence;

            for(int i = 0; i < g.size(); ++i) {
                if(not spreadedNodes[i]) {
                    tmpInfluence = computeInfluence(i)
                    if(influence > maxInfluece) {
                        maxInfluence = tmpInfluence;
                        nodeMaxInfluence = i;
                    }
                }
            }
            return nodeMaxInfleunce;
        }

        double computeInfluence(int u) {
            double influence = 0;
            for(int i = 0; i < g.size()) {
                if(not spreadedNodes[i]) {
                    influence += valueShortestPath(i,j);
                }
            }
            return influence;
        }
};

