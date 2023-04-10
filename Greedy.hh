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

        Greedy(int n, double p){
            this-> n = n;
            this -> p = p;
            g.resize(n);
            spreadedNodes.resize(n, false);
            spreaded = 0;
        }

        Greedy(const vector<vector<int>>& graf, double prob){
            n = graf.size();
            g = graf;
            p = prob;
            spreadedNodes.resize(n, false);
            spreaded = 0;
        }
        /***********************************************************************************************************
        PUBLIC METHODS
        ***********************************************************************************************************/
        
        vector<bool> getGreedySolution(bool modeIC) {
            if(modeIC) beginDifusion_IC_v1();
            else beginDifusion_LT_v2();
            return spreadedNodes;
        }

        /***********************************************************************************************************
        LINEAR THRESHOLD METHODS
        ***********************************************************************************************************/

        void beginDifusion_LT_v1(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            while(propagatedNodes != this->n){
                int maxInfluence = 0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not inSubset[i]){
                        double nodeInfluence = computeNodeInfluenceLT(i, inSubset);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                if (not inStartingSubset(idx)) {
                    inSubset[idx] = true;
                    subset.push_back(idx);
                    modStartingSubset(subset);
                    newPropagatedNodes = propagateLT_v1(); 
                    if (newPropagatedNodes == propagatedNodes) {
                        subset.pop_back();
                    }
                    else propagatedNodes = newPropagatedNodes;
                    iteration++;

                    // output to file current subset
                    file << "Iteration " << iteration << ", current subset of nodes:";
                    list<int>::const_iterator it=subset.begin();
                    while(it != subset.end()){
                        file << " " << (*it);
                        it++;
                    }file << endl << "--------------------" << endl << endl;
                }
            }                
            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file << "Solution size: " << subset.size() << " nodes." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }
        
        void beginDifusion_LT_v2(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   
            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            
            while(propagatedNodes != this->n){
                int maxInfluence = 0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not inSubset[i]){
                        double nodeInfluence = computeNodeInfluenceLT(i, inSubset);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                inSubset[idx] = true;
                if (not inStartingSubset(idx)) {
                    subset.push_back(idx);
                    list<int> l;
                    l.push_back(idx);
                    if (modStartingSubset(l) > 0) {
                        newPropagatedNodes = propagateLT_v23(); 
                        if (newPropagatedNodes == propagatedNodes) {
                            subset.pop_back();
                        }
                        else propagatedNodes = newPropagatedNodes;
                        iteration++;

                        // output to file current subset
                        file << "Iteration " << iteration << ", current subset of nodes:";
                        list<int>::const_iterator it=subset.begin();
                        while(it != subset.end()){
                            file << " " << (*it);
                            it++;
                        }file << endl << "--------------------" << endl << endl;
                    }
                    else subset.pop_back();
                }
            }                
            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file << "Solution size: " << subset.size() << " nodes." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }
        
        
        void beginDifusion_LT_v3(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false);
            // Prints is redirected to a file
            ofstream file;
            file.open("output-LT-difusion");   

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();
            priority_queue < ppair, vector<ppair>, less<ppair> > Q;
            for (int i = 0; i < this -> n; ++i) {
                int ni = computeNodeInfluenceLT(i, inSubset);
                Q.push(make_pair(ni,i));
            }

            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            while(propagatedNodes != this->n){

                int idx = Q.top().second;
                Q.pop();
                // add node to subset
                if (not inStartingSubset(idx)) {
                    inSubset[idx] = true;
                    subset.push_back(idx);
                    list<int> l;
                    l.push_back(idx);
                    if (modStartingSubset(l) > 0) {
                        newPropagatedNodes = propagateLT_v23(); 
                        if (newPropagatedNodes == propagatedNodes) {
                            subset.pop_back();
                        }
                        else propagatedNodes = newPropagatedNodes;
                        iteration++;

                        // output to file current subset
                        file << "Iteration " << iteration << ", current subset of nodes:";
                        list<int>::const_iterator it=subset.begin();
                        while(it != subset.end()){
                            file << " " << (*it);
                            it++;
                        }file << endl << "--------------------" << endl << endl;
                    }
                    else subset.pop_back();
                }
            }                
            // stop elapsed timer
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            file << "Difusion completed in " << iteration << " steps, " << elapsed.count() * 1e-9 << "s." << endl;
            file << "Solution size: " << subset.size() << " nodes." << endl;
            file.close();

            cout << "Difusion ended, check output-LT-difusion file to see benchmarks and the result" << endl;
        }

        void beginDifusion_startingSubset_LT(vector <bool>& sol){
            sol.resize(n, false);

            // initially no nodes propagated
            int propagatedNodes = 0;
            list<int> subset;
            vector<bool> inSubset(n, false); 
            
            priority_queue < ppair, vector<ppair>, less<ppair> > Q;
            for (int i = 0; i < this -> n; ++i) {
                int ni = computeNodeInfluenceLT(i, inSubset);
                Q.push(make_pair(ni,i));
            }

            int iteration = 0;
            list<int> newSubset = subset;
            int newPropagatedNodes = propagatedNodes;
            while(propagatedNodes != this->n){

                int idx = Q.top().second;
                Q.pop();
                // add node to subset
                if (not inStartingSubset(idx)) {
                    inSubset[idx] = true;
                    subset.push_back(idx);
                    list<int> l;
                    l.push_back(idx);
                    if (modStartingSubset(l) > 0) {
                        newPropagatedNodes = propagateLT_v23(); 
                        if (newPropagatedNodes == propagatedNodes) {
                            subset.pop_back();
                        }
                        else propagatedNodes = newPropagatedNodes;
                    }
                    else subset.pop_back();
                }
            }    
            list<int>::const_iterator it=subset.begin();
            while(it != subset.end()){
                sol[*it] = true;
                it++;
            }     
        }



        /***********************************************************************************************************
        INDEPENDENT CASCADE METHODS
        ***********************************************************************************************************/




        void beginDifusion_IC_v1(){
            // initially no nodes propagated
            int propagatedNodes = 0;
            

            // Prints is redirected to a file
            ofstream file;
            file.open("output-IC-difusion-v1");   
            vector <bool> inMinimumSubset(n, false);

            // sets timer
            auto begin = std::chrono::high_resolution_clock::now();


            int iteration = 0;
            list<int> minimumSubset;

            while(propagatedNodes != this->n){
                iteration++;

                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not inMinimumSubset[i]){
                        double nodeInfluence = computeNodeInfluenceIC(i, inMinimumSubset);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                inMinimumSubset[idx] = true;
                minimumSubset.push_back(idx);
                readStartingSubset(minimumSubset);

                // output to file current subset
                file << "Iteration " << iteration << ", current subset of nodes:";
                list<int>::iterator it = minimumSubset.begin();
                while(it != minimumSubset.end()){
                    file <<  " " << (*it);
                    it++;
                }
                file << endl << "size: " <<  minimumSubset.size() << endl;
                file << endl << "--------------------" << endl << endl;

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

            list<int> minimumSubset;

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
                        double nodeInfluence = computeNodeInfluenceIC(i, spreadedNodes);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                this->spreadedNodes[idx] = true;
                minimumSubset.push_back(idx);
                this->enqueueStartingSet();

                // output to file actual subset of nodes
                file << "Iteration " << iteration << ", current subset of nodes:";
                list<int>::iterator it = minimumSubset.begin();
                while(it != minimumSubset.end()){
                    file <<  " " << (*it);
                    it++;
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

        void beginDifusion_startingSubset_IC(vector<bool>& sol){
            sol.resize(n, false);
            // initially no nodes propagated
            int propagatedNodes = 0;

            while(propagatedNodes != this->n){
                // pick wich node to propagate
                double maxInfluence = 0.0;
                int idx = 0;
                for(int i = 0; i < this->n; i++){
                    // pick node not propagated yet
                    if(not this->spreadedNodes[i]){
                        double nodeInfluence = computeNodeInfluenceIC(i, spreadedNodes);
                        if(nodeInfluence > maxInfluence){
                            maxInfluence = nodeInfluence;
                            idx = i;
                        }
                    }
                }
                // add node to subset
                this->spreadedNodes[idx] = true;
                sol[idx] = true;
                this->enqueueStartingSet();

                // output to file actual subset of nodes
                propagatedNodes = propagateIC_v23();
            }

            cout << "--------------------------------------" << endl;
            for(int i = 0; i < n; i++){
                if(sol[i]) cout << " " << i;
            }
        }

        /*
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
                double nodeInfluence = computeNodeInfluenceIC(i);
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
        */
};
#endif