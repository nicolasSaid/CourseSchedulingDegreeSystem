#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "sch_check.cpp"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        cout<<"Incorrect number of parameters"<<endl;
        return 0;
    }
    string s(argv[1]);
    string t(argv[2]);
    if(setup(s)){
        //testing
        // for (auto pair: adjacencyList){
        //     cout << pair.first << ": ";
        //     Node* stelle = pair.second;
        //     while (stelle != nullptr){
        //         for (int i = 0; i < stelle->classes.size(); i++){
        //             cout << stelle->classes.at(i) << " ";
        //         }
        //         stelle = stelle->next;
        //     }
        //     cout<<endl;
        // }
        if(!DFS_loop_detection()){
            cout<<"The prerequisite list is unviable"<<endl;
        } else {
            if (parse(t)){
                if (sched_check()){
                    cout<<"the given schedule is valid"<<endl;
                }
            }
        }
    }
    deleteNodes();
}