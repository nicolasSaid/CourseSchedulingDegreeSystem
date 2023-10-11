#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
        Node(string value){
            classes = vector<string>();
            classes.push_back(value);
            next = nullptr;
        }
        Node(){
            classes = vector<string>();
            next = nullptr;
        }
        vector<string> classes;
        Node* next;
        ~Node(){}
};