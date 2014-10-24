#include "Registrar.h"
#include <vector>
#include <iostream>
#include <string>
        using namespace std;

namespace BrooklynPoly {

	Course::Course(const string& aname) : name(aname) {}
	string Course::getName() {
		return name;
	}
	void Course::addStudent(Student* student) {
		students.push_back(student);
	}
	void Course::display() {
		for (int i = 0; i < students.size(); i++) {
			cout << students[i]->getName() << endl;
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////
	Student::Student(const string& aname) : name(aname) {}
	string Student::getName() {
		return name;
	}
	void Student::addCourse(Course* course) {
		courses.push_back(course);
	}
/////////////////////////////////////////////////////////////////////////////////////////////
	Registrar::Registrar() {}
	void Registrar::printReport() {
		for (int i = 0; i < courses.size(); i++) {
			cout << courses[i]->getName() << ": " << endl;
			courses[i]->display();
		}
	}
	void Registrar::addCourse(const string& name) {
		courses.push_back(new Course(name));
	}
	void Registrar::addStudent(const string& name) {
		students.push_back(new Student(name));
	 }

	Course* Registrar::getCourse(const string& name) {
		for (int i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == name) {
				return courses[i];
			}
		}
		return NULL;
	}
	Student* Registrar::getStudent(const string& name) {
		for (int i = 0; i < students.size(); i++) {
			if (students[i]->getName() == name) {
				return students[i];
			}
		}
		return NULL;
	}

	// // void Registrar::removeStudent(const string name) {}
	void Registrar::enrollStudentInCourse(const string& student, const string& course) {
		if (Registrar::getStudent(student) == NULL || Registrar::getCourse(course) == NULL) {
			return;
		}
		else {
			Registrar::getCourse(course)->addStudent(Registrar::getStudent(student));
			Registrar::getStudent(student)->addCourse(Registrar::getCourse(course));
		}
	}
	// //void Registrar::dropStudentFromCourse(const string student, const string course) {}
	void Registrar::cancelCourse(const string& course) {
		Course* Coursepnt = Registrar::getCourse(course);
		delete Coursepnt;
		Coursepnt = NULL;
		courses.pop_back();
	}
	void Registrar::purge() {
		for (int i = 0; i < students.size(); i++) {
			delete students[i];
			students[i] = NULL;
		}
		for (int j = -1; j < courses.size(); ++j) {
			if (courses[j]) {
				delete courses[j];
				courses[j] = NULL;
			}
		}
		students.clear();
		courses.clear();
	}


}