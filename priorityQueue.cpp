#include <iostream>
#include <stdlib.h>
#include "priorityQueue.h"

using namespace std;

priorityQueue::priorityQueue(){
    maxheap = vector<student*>(1);
    maxStudents = 1;
    numberOfStudents = 0;
    bnumbers = set<string>();
    accessStudentPointer = unordered_map<string, student*>();
}

bool priorityQueue::insertStudent(string BNum, int val){
    if(bnumbers.find(BNum) != bnumbers.end()){
        return false;
    }

    if(numberOfStudents == maxStudents){
        maxheap.resize(maxStudents * 2);
        maxStudents *= 2;
    }

    student* stud = new student(BNum,val);
    accessStudentPointer[BNum] = stud;
    bnumbers.insert(BNum);

    int index = numberOfStudents;
    maxheap[index] = stud;
    while(index > 0 && maxheap[(index - 1)/2]->prio < maxheap[index]->prio){
        //cout<<"entered"<<endl;
        student* parent = maxheap[(index - 1)/2];
        maxheap[(index - 1)/2] = maxheap[index];
        maxheap[index] = parent;

        index = (index - 1)/2;
    }
    numberOfStudents++;
    //printArray();
    return true;
}

void priorityQueue::heapifyHelper(int index){
    int start = index;


    if(((2*index+1) < numberOfStudents) && (maxheap[index]->prio < maxheap[2*index+1]->prio)){
        index = 2*index+1;
    }
    if(((2*index+2) < numberOfStudents) && (maxheap[index]->prio < maxheap[2*index+2]->prio)){
        index = 2*index+2;
    }

    if(index != start){
        student* swap = maxheap[start];
        maxheap[start] = maxheap[index];
        maxheap[index] = swap;

        heapifyHelper(index);
    }
}

void priorityQueue::reHeapify(){
    int nonLeaf = (numberOfStudents/2) - 1;
    for(int i = nonLeaf; i >= 0; i--){
        heapifyHelper(i);
    }
}

bool priorityQueue::promoteStudent(string BNum, int val){
    if(bnumbers.find(BNum) == bnumbers.end()){
        return false;
    }

    student* stud = accessStudentPointer[BNum];
    stud->prio+=val;

    reHeapify();
    //printArray();
    return true;
}

bool priorityQueue::reset(string BNum){
    if(bnumbers.find(BNum) == bnumbers.end()){
        return false;
    }
    accessStudentPointer[BNum]->prio = 0;
    reHeapify();
    return true;
}

student* priorityQueue::peek(){
    if(numberOfStudents < 1){
        return nullptr;
    }
    //cout << maxheap[0]->bNum << endl;
    return maxheap[0];
}

student* priorityQueue::pop(){
    if(numberOfStudents == 0){
        return nullptr;
    }

    student* toReturn = maxheap[0];

    maxheap[0] = maxheap[numberOfStudents - 1];
    numberOfStudents--;
    bnumbers.erase(toReturn->bNum);
    accessStudentPointer.erase(toReturn->bNum);
    heapifyHelper(0);
    return toReturn;
}
void priorityQueue::printArray(){
    cout<<"Max heap: ";
    for(int i = 0; i < numberOfStudents; i++){
        cout<<maxheap[i]->prio<< ", ";
    }

    cout<<endl;
}
void priorityQueue::destruct(){
    for(int i = 0; i < numberOfStudents; i++){
        //cout<<"i love freeing: "<<i<<" - "<<numberOfStudents<<endl;
        delete maxheap[i];
    }
}

// priorityQueue::~priorityQueue(){
//     for(int i = 0; i < numberOfStudents; i++){
//         cout<<"i love freeing: "<<i<<" - "<<numberOfStudents<<endl;
//         delete maxheap[i];
//     }
// }
