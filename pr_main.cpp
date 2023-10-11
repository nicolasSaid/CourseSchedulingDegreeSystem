#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "pr_check.cpp"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout<<"Incorrect number of parameters"<<endl;
        return 0;
    }
    string s(argv[1]);
    if(setup(s)){
        //testing
        // for (auto pair: adjacencyList){
        //     cout << pair.first << ": "<<flush;
        //     Node* stelle = pair.second;
        //     while (stelle != nullptr){
        //         for (unsigned int i = 0; i < stelle->classes.size(); i++){
        //             cout << stelle->classes.at(i) << " ";
        //         }
        //         stelle = stelle->next;
        //     }
        //     cout<<endl;
        // }
        if (DFS_loop_detection()){
            cout << "The prerequisites are viable" << endl;
        }
    }
    deleteNodes();
    
}