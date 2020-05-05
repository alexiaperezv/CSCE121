#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"
#include <sstream>
#include <iomanip>

using namespace std;

Course::Course(string id, string title, Date startTime, Date endTime) : id(id), title(title), startTime(startTime), endTime(endTime) {}

void Course::addAttendanceRecord(AttendanceRecord ar)
{
    attendanceRecords.push_back(ar);
}

void Course::outputAttendance()
{
    if (attendanceRecords.empty())
    {
        cout << "No Records" << endl;
    }
    else
    {
        for (vector<AttendanceRecord>::iterator it = attendanceRecords.begin(); it != attendanceRecords.end(); ++it)
        {
            stringstream ss;
            ss << setw(2) << setfill('0') << it->getDate().getHour() << ":";
            ss << setw(2) << setfill('0') << it->getDate().getMin() << ":";
            ss << setw(2) << setfill('0') << it->getDate().getSec();
            cout << it->getDate().getMonth() << "/" << it->getDate().getDay() << "/" << it->getDate().getYear() << " ";
            cout << ss.str() << "," << it->getCourseID() << "," << it->getStudentID() << endl;
        }
    }
}

void Course::outputAttendance(std::string student_id)
{

    if(attendanceRecords.empty())
    {
        cout << "No Records" << endl;
    }
    else
    {
        bool student_found = false;
        for (vector<AttendanceRecord>::iterator it = attendanceRecords.begin(); it != attendanceRecords.end(); ++it)
        {
            if (it->getStudentID().compare(student_id) == 0)
            {
                student_found = true;
                stringstream ss;
                ss << setw(2) << setfill('0') << it->getDate().getHour() << ":";
                ss << setw(2) << setfill('0') << it->getDate().getMin() << ":";
                ss << setw(2) << setfill('0') << it->getDate().getSec();
                cout << it->getDate().getMonth() << "/" << it->getDate().getDay() << "/" << it->getDate().getYear() << " ";
                cout << ss.str() << "," << it->getCourseID() << "," << it->getStudentID() << endl;
            }

        }
        if(!student_found){
            cout << "No Records" << endl;
        }
    }
}