#include <stdlib.h>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include "student.h"

using namespace std;

class priorityQueue{
    public:
        priorityQueue();
        bool insertStudent(string BNum, int val);
        bool promoteStudent(string BNum, int val);
        bool reset(string BNum);
        void reHeapify();
        void heapifyHelper(int index);
        void printArray();
        void destruct();
        student* peek();
        student* pop();
        //~priorityQueue();
    private:
        int numberOfStudents;
        int maxStudents;
        vector<student*> maxheap;
        set<string> bnumbers;
        unordered_map<string, student*> accessStudentPointer;
};