#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

void Student::listCourses(){
    cout << "Course for " << id << endl;
    for (vector<string>::iterator it = course_ids.begin(); it != course_ids.end(); ++it){
        cout << *it << endl;
    }
}