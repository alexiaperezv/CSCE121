#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
  std::string id;
  std::string name;
  std::vector<std::string> course_ids;
  
public:
  Student(std::string student_id, std::string name) : id(student_id), name(name) {}
  std::string get_id() {return id;}
  std::string get_name() {return name;}
  void addCourse(std::string course_id) {course_ids.push_back(course_id);}
  void listCourses();
};

#endif