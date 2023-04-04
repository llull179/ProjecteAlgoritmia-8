#ifndef GREEDY_HH
#define GREEDY_HH
#include "difussionGraph.hh"
#include <list>
#include <fstream>
using namespace std;


typedef pair<int,int> ppair;

class Greedy: public difussionGraph{

    public:

        /***********************************************************************************************************
        DEFAULT AND PARAMETRIZED CONSTRUCTOR
        ***********************************************************************************************************/
        Greedy(){}

        Greedy(int n){
            this-> n = n;
            g.resize(n);
            spreadedNodes.resize(n, false);
        }

        /***********************************************************************************************************
        PUBLIC METHODS
        ***********************************************************************************************************/
        
        // ...

        /***********************************************************************************************************
        LINEAR THRESHOLD METHODS
        ***********************************************************************************************************/

        // ...

        /***********************************************************************************************************
        INDEPENDENT CASCADE METHODS
        ***********************************************************************************************************/

        void beginDifusion_IC_v1(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list <int> subset;
            vector<bool> inSubset(n, false);

            // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion-v1");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();


            int iteration = 0;

            while(propagatedNodes != this->n){
                iteration++;
                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not inSubset[i]){
                        double nodeInfluence = computeNodeInfluence(i);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                inSubset[idx] = true;
                subset.push_back(idx);
                readStartingSubset(subset);

                // output to file current subset
                file << "Iteration " << iteration << ", current subset of nodes:";
                list<int>::const_iterator it=subset.begin();
                while(it != subset.end()){
                    file << " " << (*it);
                    it++;
                }file << endl << "--------------------" << endl << endl;

                propagatedNodes = propagateIC_v1();                
            }

                    

            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-IC-difusion file to see benchmarks and the result" << endl;
        }

        void beginDifusion_IC_v2(){
            // initially no nodes propagated
            int propagatedNodes = 0;

            // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion-v2");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            int iteration = 0;

            while(propagatedNodes != this->n){
                iteration++;

                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not this->spreadedNodes[i]){
                        double nodeInfluence = computeNodeInfluence(i);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                this->spreadedNodes[idx] = true;
                this->enqueueStartingSet();

                // output to file actual subset of nodes
                file << "Iteration " << iteration << ", current subset of nodes:";
                for(int i = 0; i < this->n; i++){
                    if(spreadedNodes[i]) file << " " << i;
                } 
                file << endl << "--------------------" << endl << endl;
                propagatedNodes = propagateIC_v23();
            }

            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-IC-difusion file to see benchmarks and the result" << endl;
        }

        void beginDifusion_IC_v3(){
            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();

            // initially no nodes propagated
            int propagatedNodes = 0;

            // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion-v3");   

            priority_queue<pair<double,int>> Q;

            // computes all Influence one time only
            for(int i = 0; i < this->n; i++){
                // pick node not propagated yet
                double nodeInfluence = computeNodeInfluence(i);
                Q.push(make_pair(nodeInfluence, i));                
            }

            
            int iteration = 0;

            while(propagatedNodes != this->n){
                iteration++;

                // pick wich node to propagate
                int v = Q.top().second;
                Q.pop();

                // add node to subset
                this->spreadedNodes[v] = true;
                this->enqueueStartingSet();

                // output to file actual subset of nodes
                file << "Iteration " << iteration << ", current subset of nodes:";
                for(int i = 0; i < this->n; i++){
                    if(spreadedNodes[i]) file << " " << i;
                } 
                file << endl << "--------------------" << endl << endl;

                
                propagatedNodes = propagateIC_v23();
            }

                    

            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file.close();

            cout << "Difusion ended, check output-IC-difusion file to see benchmarks and the result" << endl;
        }
};
#endif