#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"

using namespace std;

void School::addStudents(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail())
    {
      students.push_back(Student(uin, name));
    }
  }
}

void School::addCourses(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line); // gets the entire first line
    if (line == "")
    {
      break;
    }
    istringstream ss(line); // created a strin stream (divides the string and each string in it will become its own)
    string section;
    getline(ss, section, ','); // the first string in the string stream and before the first comma is stored in "section"

    string start_time_str;
    getline(ss, start_time_str, ',');
    istringstream ss_1(start_time_str); // this block creates the object start_time
    string hour_str;
    string minute_str;
    getline(ss_1, hour_str, ':');
    getline(ss_1, minute_str);
    int hour = stoi(hour_str);
    int minute = stoi(minute_str);
    Date start_time(hour, minute);

    string end_time_str;
    getline(ss, end_time_str, ',');
    istringstream ss_2(end_time_str); // this block creates the object end_time
    string hour_str_2;
    string minute_str_2;
    getline(ss_2, hour_str_2, ':');
    getline(ss_2, minute_str_2);
    int end_hour = stoi(hour_str_2);
    int end_minute = stoi(minute_str_2);
    Date end_time(end_hour, end_minute);
    string course;
    getline(ss, course);
    if (!ss.fail())
    {
      courses.push_back(Course(section, course, start_time, end_time));
      //getline(ss, course); // get the courses
      // if the next element is "and" that will be last element that needs to be stored
    }
  }
}

void School::listStudents()
{
  if (students.empty())
  {
    cout << "No Students" << endl;
  }
  else
  {
    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
    {
      cout << it->get_id() << "," << it->get_name() << endl;
    }
  }
}

void School::listCourses()
{
  if (courses.empty())
  {
    cout << "No Courses" << endl;
  }
  else
  {
    for (vector<Course>::iterator it = courses.begin(); it != courses.end(); ++it)
    {
      stringstream ssStartTime;
      ssStartTime << setw(2) << setfill('0') << it->getStartTime().getHour() << ":";
      ssStartTime << setw(2) << setfill('0') << it->getStartTime().getMin();

      stringstream ssEndTime;
      ssEndTime << setw(2) << setfill('0') << it->getEndTime().getHour() << ":";
      ssEndTime << setw(2) << setfill('0') << it->getEndTime().getMin();

      cout << it->getID() << "," << ssStartTime.str() << "," << ssEndTime.str() << "," << it->getTitle() << endl;
    }
  }
}

void School::addAttendanceData(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line);
    if (line == "")
    {
      break;
    }
    istringstream ss(line);
    string year;
    getline(ss, year, '-');
    string month;
    getline(ss, month, '-'); // windows sometimes converts / to - automatically
    string day;
    getline(ss, day, ' ');
    string hour;
    getline(ss, hour, ':');
    string minute;
    getline(ss, minute, ':');
    string second;
    getline(ss, second, ',');
    string section;
    getline(ss, section, ',');
    string uin;
    getline(ss, uin);
    Date time(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute), stoi(second));
    if (!ss.fail())
    {
      AttendanceRecord attendance(section, uin, time);
      for (vector<Course>::iterator it = courses.begin(); it != courses.end(); ++it)
      {
        if (it->getID() == section)
        {
          if (it->getStartTime() <= time && it->getEndTime() >= time)
          {
            it->addAttendanceRecord(attendance);
          }
        }
      }
    }
  }
}

void School::outputCourseAttendance(string course_id)
{
  /*for (vector<Course>::iterator it = courses.begin(); it != courses.end(); ++it){
    if(it->getID().compare(course_id) == 0){
      it->outputAttendance();
    }
  }*/
  for (int i = 0; i < courses.size(); i++)
  {
    if (course_id == courses.at(i).getID())
    {
      courses.at(i).outputAttendance();
    }
  }
}

void School::outputStudentAttendance(string student_id, string course_id)
{
  for (int i = 0; i < courses.size(); i++)
  {
    if (course_id == courses.at(i).getID())
    {
      courses.at(i).outputAttendance(student_id);
    }
  }
}