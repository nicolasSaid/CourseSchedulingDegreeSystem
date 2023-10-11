#include <stdlib.h>
#include <string>

using namespace std;

class student{
    public:
        student(string bnum, int priority){
            bNum = bnum;
            prio = priority;
        }
        student(){
            bNum = "";
            prio = 0;
        }
        bool operator<(const student& rhs){ //for max heap only!!
            return this->prio < rhs.prio;
        }
        bool operator==(const student& rhs){
            return this->bNum == rhs.bNum;
        }
        string bNum;
        int prio;
        ~student(){}
};