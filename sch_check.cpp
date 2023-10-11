#include "pr_check.cpp"
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

unordered_map<string, vector<string> > coursesPerSemester; // key = semester value = vector of courses
vector<int> yearsPresent;//ordered vector including the years of the semesters
set<string> courses;//set of all courses (cant be taken twice)


bool parse(string textfile){
    coursesPerSemester.clear();
    yearsPresent.clear();
    courses.clear();

    ifstream schedule(textfile);
    string line;
    while(getline(schedule, line)){
    size_t spaceLocation = line.find(" ");  
    if(spaceLocation == string::npos){
            cout<<"Bad formatting"<<endl;
            break;
        }
        string semester = line.substr(spaceLocation + 1);
        string course = line.substr(0, spaceLocation);
        string strYear = semester.substr(0, 4); //assume 4 digit year
        int year = stoi(strYear);
        if (coursesPerSemester.find(semester) == coursesPerSemester.end()){
            coursesPerSemester[semester] = vector<string>();
        }
        coursesPerSemester[semester].push_back(course);
        if(coursesPerSemester[semester].size() > 3){
            cout<<"more than three classes taken a semester"<<endl;
            return false;
        }
        if (courses.find(course) == courses.end()){
            courses.insert(course);
        }
        else{
            cout << "Schedule repeats classes" << endl;
            return false;
        }

        if(find(yearsPresent.begin(), yearsPresent.end(), year) == yearsPresent.end()) {
            yearsPresent.push_back(year);
        }

    }
    sort(yearsPresent.begin(), yearsPresent.end());
    schedule.close();
    return true;
}

bool sched_check(){
    vector<string> seasons = vector<string>();
    seasons.push_back("Fall");
    seasons.push_back("Summer");
    seasons.push_back("Spring");
    for(int i = yearsPresent.size() - 1; i >= 0; i--){ // loop through all years that we have taken semesters
        string year = to_string(yearsPresent[i]);
        for (unsigned int x = 0; x < seasons.size(); x++){ //loop through the three seasons (fall, summer, spring) in reverse order
            string firstQuery = year + seasons[x];

            if(coursesPerSemester.find(firstQuery) != coursesPerSemester.end()){
                vector<string> cours = coursesPerSemester[firstQuery];
                for(unsigned int j = 0; j < cours.size(); j++){ // through courses taken that semester
                    Node* adj = nullptr;
                    if(adjacencyList.find(cours[j]) != adjacencyList.end()){
                        adj = adjacencyList[cours[j]];
                    }                
                    

                    while(adj != nullptr){ //loop through the pre-req list for a given course
                        vector<string> co_reqs = adj->classes;
                        bool found = false;
                        for(unsigned int l = 0; l < co_reqs.size(); l++){//loop through the co-requirements for each node
                            for(unsigned int q = x + 1; q < seasons.size(); q++){ //see if the req is present in other semesters in the same year
                                string yearQuery = year + seasons[q];
                                if(coursesPerSemester.find(firstQuery) != coursesPerSemester.end()){
                                    vector<string> checkcheck = coursesPerSemester[yearQuery];
                                    for(unsigned int p = 0; p < checkcheck.size(); p++){ //go through the courses taken in one of the previous semesters
                                        //cout<<co_reqs[l]<<" : "<< checkcheck[p]<<" : year = "<<year<<endl;
                                        if(co_reqs[l] == checkcheck[p]){
                                            //cout << "Found PreReq - " << co_reqs[l] << endl;
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            for(int k = i - 1; k >= 0; k--){ //go through previous years
                                for(unsigned int m = 0; m < seasons.size(); m++){ //check all seasons in previous years
                                    string yearCheck = to_string(yearsPresent[k]);
                                    string yearQuery = yearCheck + seasons[m];
                                    if(coursesPerSemester.find(firstQuery) != coursesPerSemester.end()){
                                        vector<string> checkcheck = coursesPerSemester[yearQuery];
                                        for(unsigned int p = 0; p < checkcheck.size(); p++){ //go through the courses taken in one of the previous semesters
                                            //cout<<co_reqs[l]<<" : "<< checkcheck[p]<<" : year = "<<yearsPresent[k]<<endl;
                                            if(co_reqs[l] == checkcheck[p]){
                                                //cout << "Found PreReq - " << co_reqs[l] << endl;
                                                found = true;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(!found){ //if we didnt find the course anywhere, they did not take the required pre-requisite
                            cout<<"Error: the pre-requisites for "<<cours[j]<<": ";
                            vector<string> pre_reqs = adj->classes;
                            for(unsigned int g = 0; g < pre_reqs.size(); g++){
                                cout<<pre_reqs[g];
                                if(g != pre_reqs.size() - 1){
                                    cout<<", ";
                                }
                            }
                            cout<<" were not taken in time"<<endl;
                            //cout<<cours[j]<<endl;
                            return false;
                        }
                        found = false; //reset false for the next course
                        adj = adj->next;
                    }
                }
            }
        }
    }
    return true;
}
