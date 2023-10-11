#include "sch_check.cpp"
#include "priorityQueue.h"

using namespace std;

unordered_map<string, priorityQueue> pqs;
unordered_map<string, string> stu2sch; //maps bnumber to their schedule file
unordered_map<string, int> stu2numEnrolled;

bool terminal(string semester, string prereqtxt, string schedtxt, string enrolltxt){
    //run prereq_checker
    setup(prereqtxt);
    if(!DFS_loop_detection()){
        cout<<"The prerequisites are unviable"<<endl;
        return false;
    }

    //process all student schedules
    ifstream schedules(schedtxt);
    string line;
    while(getline(schedules, line)){
        size_t spaceLocation = line.find(" ");  
        if(spaceLocation == string::npos){
            cout<<"Bad formatting in schedules.txt"<<endl;
            return false;
        }
        string sched = line.substr(spaceLocation + 1);
        string bnum = line.substr(0, spaceLocation);
        stu2sch[bnum] = sched;
    }
    schedules.close();

    //process enroll.txt
    ifstream enroll(enrolltxt);
    while(getline(enroll, line)){
        size_t spaceLocation = line.find(" ");
        if(spaceLocation == string::npos){
            cout<<"Bad formatting in enroll.txt"<<endl;
            return false;
        }
        string command = line.substr(0, spaceLocation);
        if (command == "newlist"){
            //cout<<"newlist called"<<endl;
            string course = line.substr(spaceLocation + 1);
            pqs[course] = priorityQueue();
        }
        else if (command == "add"){
            //cout<<"add called"<<endl;
            line += " ";
            string bnum, course, points = "";
            vector<string> fields = {bnum, course, points};
            for (string& x: fields){
                line = line.substr(spaceLocation + 1);
                spaceLocation = line.find(" ");
                x = line.substr(0, spaceLocation);
            }
            if (pqs.find(fields[1]) != pqs.end()){
                if (!(pqs[fields[1]].insertStudent(fields[0], stoi(fields[2])))){
                    cout << "Student " << fields[0] << "already exists in waitlist " << fields[1] << endl;
                    return false;
                }
            }
            else{
                cout << "Requested course not found: " << fields[1] << endl;
                return false;
            }
        }
        else if (command == "promote"){
            //cout<<"promote called"<<endl;
            line += " ";
            string bnum, course, points = "";
            vector<string> fields = {bnum, course, points};
            for (string& x: fields){ //parse line
                line = line.substr(spaceLocation + 1);
                spaceLocation = line.find(" ");
                x = line.substr(0, spaceLocation);
            }
            if (pqs.find(fields[1]) != pqs.end()){ 
                if(stu2sch.find(fields[0]) == stu2sch.end()){
                    cout<<"Student doesn't exist"<<endl;
                    return false;
                }
                //priorityQueue& prio = pqs[fields[1]];
                //bool found = false;
                if(!(pqs[fields[1]].promoteStudent(fields[0], stoi(fields[2])))){
                    //cout<<fields[0]<<"|"<<endl;
                    //prio.printArray();

                    cout<<"Student does not exist within this waitlist"<<endl;
                }
            }else{
                cout<<"Course does not exist"<<endl;
            }
        }
        else if (command == "enroll"){
            //cout<<"enroll called"<<endl;
            string course = line.substr(spaceLocation + 1);
            if (pqs.find(course) != pqs.end()){
                //pqs[course].printArray();
                student* s = pqs[course].peek();
                //pqs[course].printArray();
                bool enrolled = false;
                vector<string> seasons;
                seasons.push_back("Spring");
                seasons.push_back("Summer");
                seasons.push_back("Fall");
                unordered_map<string, int> map;
                map["Spring"] = 0;
                map["Summer"] = 1;
                map["Fall"] = 2;
                //pqs[course].printArray();
                while (s != nullptr){
                    //cout<<s->bNum<<endl;
                    if(parse(stu2sch[s->bNum])){
                        //remove "future" semesters
                        int target = stoi(semester.substr(0, 4));
                        int cutoff = 0;
                        for (unsigned int t = 0; t < yearsPresent.size(); t++){
                            if (yearsPresent[t] == target){
                                cutoff = t;
                                for (unsigned int b = map[semester.substr(4)] + 1; b < seasons.size(); b++){
                                    string sem = to_string(yearsPresent[t]) + seasons[b];
                                    if (coursesPerSemester.find(sem) != coursesPerSemester.end()){
                                        vector<string> cours = coursesPerSemester[sem];
                                        for(unsigned int j = 0; j < cours.size(); j++){
                                            courses.erase(cours[j]);
                                        }
                                        coursesPerSemester.erase(sem);
                                    }
                                }
                            }
                            else if (yearsPresent[t] > target){
                                for(unsigned int i = 0; i < seasons.size(); i++){
                                    string sem = to_string(yearsPresent[t]) + seasons[i];
                                    if (coursesPerSemester.find(sem) != coursesPerSemester.end()){
                                        vector<string> cours = coursesPerSemester[sem];
                                        for(unsigned int j = 0; j < cours.size(); j++){
                                            courses.erase(cours[j]);
                                        }
                                        coursesPerSemester.erase(sem);
                                    }
                                }
                            }
                        }
                        yearsPresent.resize(cutoff + 1);

                        if(sched_check()){
                            if (coursesPerSemester.find(semester) != coursesPerSemester.end()){
                                coursesPerSemester[semester].push_back(course);
                            }
                            else{
                                vector<string> c = {course};
                                coursesPerSemester[semester] = c;
                                yearsPresent.push_back(stoi(semester.substr(0, 4)));
                            }

                            bool cont = true;
                            if(courses.find(course) == courses.end()){
                                courses.insert(course);
                            }
                            else {
                                cont = false;
                                cout<<"Error: "<<s->bNum<<" has already taken "<<course<<endl;
                            }

                            if (sched_check() && cont){
                                int extrasem = 0;
                                if(stu2numEnrolled.find(s->bNum) != stu2numEnrolled.end()){
                                    extrasem = stu2numEnrolled[s->bNum];
                                }
                                if(coursesPerSemester[semester].size() + extrasem > 3){
                                    cout <<"Error: "<< s->bNum << " is already taking 3 classes in " << semester << endl;
                                    cout << s->bNum << " has a bad schedule after inserting, choosing next student" << endl;
                                    student* remove = pqs[course].pop(); //might reinsert with prio 0, 
                                    for (auto x: pqs){
                                        x.second.reset(remove->bNum);
                                    }
                                    delete remove;
                                    s = pqs[course].peek();
                                }else{
                                    if(stu2numEnrolled.find(s->bNum) == stu2numEnrolled.end()){
                                        stu2numEnrolled[s->bNum] = 1;
                                    } else {
                                        stu2numEnrolled[s->bNum]++;
                                    }
                                    cout << "Enrolling student " << s->bNum << " in course " << course << endl << endl;
                                    enrolled = true;
                                    pqs[course].pop();
                                    for (auto x: pqs){
                                        x.second.reset(s->bNum);
                                    }
                                    delete s;
                                    break;
                                }
                            }
                            else{
                                cout << s->bNum << " has a bad schedule after inserting, choosing next student" << endl;
                                student* remove = pqs[course].pop(); //might reinsert with prio 0, 
                                for (auto x: pqs){
                                    x.second.reset(remove->bNum);
                                }
                                delete remove;
                                s = pqs[course].peek();
                            }
                        }
                        else{                     //prints in the method so no need to do any here
                            cout<<"Student "<<s->bNum<<" does not have a valid schedule even befre adding classes"<<endl;
                            cout<<"Halting execution of program"<<endl;
                            return false;
                        }
                    }
                    else{                         //prints in the method so no need to do any here
                        return false;
                    }
                }
                if(!enrolled){
                    cout<<"No viable student in the "<<course<<" waitlist"<<endl << endl;
                }
            }
            else{
                cout << "Requested course not found: " << course << endl;
                return false;
            }
        }
        else{
            cout << "Invalid command" << endl;
            return false;
        }
    }
    enroll.close();
    return true;
}

void deleteMap(){
    for(auto x : pqs){
        x.second.destruct();
    }
    pqs.clear();
}

int main(int argc, char *argv[]){
    if(argc != 5){
        cout<<"Incorrect number of arguments"<<endl;
        return 0;
    }

    terminal(string(argv[1]), string(argv[2]), string(argv[3]), string(argv[4]));
    deleteMap();
    deleteNodes();
}