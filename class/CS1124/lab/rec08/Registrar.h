#ifndef REGISTRAR_H
#define REGISTRAR_H

//#include "student.h"
//#include "course.h"
#include <vector>
#include <iostream>
#include <string>

namespace BrooklynPoly {

	class Student;

	class Course {
	public:
		Course(const std::string& name);
		std::string getName();
		void addStudent(Student* student);
		void display();
	private:
		std::string name;
		std::vector<Student*> students;
	};

	class Student{
	public:
		Student(const std::string& name);
		std::string getName();
		void addCourse(Course* course);
	private:
		std::string name;
		std::vector<Course*> courses;
	};

	class Registrar {
	public:
		Registrar();
		void printReport();
		void addCourse(const std::string& name);
	 	void addStudent(const std::string& name);
	// 	//void removeStudent(const string name);
		void enrollStudentInCourse(const std::string& student, const std::string& course);
	// 	//void dropStudentFromCourse(const string student, const string course);
		void cancelCourse(const std::string& course);
		void purge();
	 private:
		Course* getCourse(const std::string& name);
		Student* getStudent(const std:: string& name);
		std::vector<Student*> students;
		std::vector<Course*> courses;
	};


}
#endif