#include <iostream>
#include <stdexcept>
#include <fstream>  
#include <string>

using namespace std;
int main(int argc, char *argv[]){
    if(argc != 3) cerr << "Invalid number of arguments" << endl;
    else{
        // read args
        int n = atoi(argv[1]);
        double p = atof(argv[2]);

        // creates file with name graph-N-M
        string filename = "graph-" + to_string(n);
        
        fstream file;
        file.open(filename, ios::out);
        if (!file) {
            cerr << "File not created!";
        }
        else {
            cout << "File created successfully!";
            // generate graph
            int m = 0;
            for(int i = 0; i < n; i++){
                for(int j = i; j < n; j++){
                    double shot_p = (rand()%100)/100.0;
                    if(p > (1-shot_p)){
                        m++;
                        file << i << " " << j << endl;
                    }
                }
            }
            cout << "Graph generated with " + to_string(n) + " vertices and " + to_string(m) << " edges" << endl;
            file.close();
        }
        return 0;

    }    
}
