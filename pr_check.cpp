#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "Node.h"
#include <fstream>

using namespace std;


unordered_map<string, Node*> adjacencyList; //adjacencylist of class name key to linkedlist value
unordered_map<string, string> nodeStatus; // white/grey/black

bool setup(string textfile){
    ifstream prereqs(textfile);

    string line;
    while (getline(prereqs, line)){
        size_t spaceLocation = line.find(" "); 
        if(spaceLocation == string::npos){
            cout<<"Bad formatting"<<endl;
            return false;
        }
        string courseName = line.substr(0, spaceLocation);
        Node* pre = new Node();
        line = line.substr(spaceLocation + 1);
        spaceLocation = line.find(" "); 
        while(spaceLocation != string::npos){
            string course1 = line.substr(0, spaceLocation);
            pre->classes.push_back(course1);
            line = line.substr(spaceLocation + 1);
            spaceLocation = line.find(" "); 
        }
        pre->classes.push_back(line);
        if (adjacencyList.find(courseName) == adjacencyList.end()){
            adjacencyList[courseName] = pre;
            nodeStatus[courseName] = "white";
        }else {
            Node* it = adjacencyList.find(courseName)->second;
            while(it->next != nullptr){
                it = it->next;
            }
            it->next = pre;
        }
    }
    prereqs.close();
    return true;
}

int DFS_helper(int depth, string key){
    if (depth > 6){
        cout << "not viable: sequence of necessary prerequisites that exceeds 6" << endl;
        return 1;
    }

    if(adjacencyList.find(key) != adjacencyList.end()){
        if(nodeStatus[key] == "gray"){
            cout << "not viable: loop beginning at class " << key << endl;
            return 2;
        } //else if(nodeStatus[key] == "black"){
        //     return 0; //might not want to return 0 here because if a class with depth 5 runs into a path already explored of depth 2, it would say its ok instead of outputting an error
        // }
        
        if(nodeStatus[key] != "black"){
            nodeStatus[key] = "gray"; //might want to add if its not currently black
        
            Node* stelle = adjacencyList[key];
            while (stelle != nullptr){
                for (unsigned int i = 0; i < stelle->classes.size(); i++){
                    int x = DFS_helper(depth + 1, stelle->classes.at(i));
                    if(x == 1 || x == 2){
                        return x;
                    }
                }
                stelle = stelle->next;
            }

            nodeStatus[key] = "black";
        }
    }
    return 0;
    
}

bool DFS_loop_detection(){
    for (auto pair : adjacencyList){
        int count = 1;
        int retVal = DFS_helper(count, pair.first);
        if(retVal == 1 || retVal == 2){
            //cout<<"Greater than 6 semesters"<<endl;
        //     return false;
        // } else if (retVal == 2){
            //cout<<"There is a loop in the requirements - Unable to be completed"<<endl;
            return false;
        }

        for (auto said: nodeStatus){
            nodeStatus[said.first] = "white";
        }
    }
    return true;
}

void deleteNodes(){
    for(auto x : adjacencyList){
        Node* next = x.second->next;
        Node* curr = x.second;
        while(next != nullptr){
            delete curr;
            curr = next;
            next = next->next;
        }
        delete curr;
    }
}
