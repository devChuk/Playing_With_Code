/*
Brian Chuk
CS1124
bc1691
*/

#include <iostream>
#include <vector>
#include <string>
        using namespace std;


class TimeSlot {
	public:
		TimeSlot(const string& newDay, const int& newHour) 
		: day(newDay), hour(newHour) {}

		void display() {
			int time;
			string period;
			if (hour > 12) {
				time = hour - 12;
				period = "PM";
			}
			else {
				time = hour;
				period = "AM";
			}
			cout << day << " " << time << period << endl;
		}
		
	private:
		string day;
		unsigned int hour;
};

class Student {
	public:
		string name;

		Student(const string newName) {
			name = newName;
			for (int i = 0; i < 13; i++) {
				grades.push_back(-1);
			}
		}

		void display() {
			cout << name << "; Grades:";
			for (int i = 0; i < 13; i++) {
				cout << " " << grades[i];
			}
			cout << endl;
		}

		void addGrade(int grade, int week) {
			grades[week] = grade;
		}
	private:
		vector<int> grades;
};

class Section {
	public:
		Section(const string& newName, const string& day, const int& hour)
		: name(newName), timeslot(day, hour) {}

		void addStudent(const string& newName) {
			Student* pStud = new Student(newName);
			students.push_back(pStud);
		}

		void display() {
			cout << "Section: " << name << "; ";
			timeslot.display();
			for (Student* stud : students) {
				cout << "Student: ";
				stud->display();// << endl;
			}
			cout << "\n" << endl;
		}

		void addGrade(string newname, int grade, int week) {
			for (int i = 0; i < students.size(); i++) {
				if (students[i]->name == newname) {
					students[i]->addGrade(grade, week);
					break;
				}
			}
		}

		void reset() {
			for (int i = 0; i < students.size(); i++) {
				delete students[i];
				students[i] = NULL;
			}
			students.clear();
		}

	private:
		string name;
		vector<Student*> students;
		TimeSlot timeslot;
};

class LabWorker {
	public:
		LabWorker(const string& newName) 
		: name(newName) {}

		void addSection(Section& sec) {
			section = &sec;
		}

		void displayGrades() {
			cout << name << " has ";
			section->display();
		}

		void addGrade(string newname, int grade, int week) {
			section->addGrade(newname, grade, week);
		}

	private:
		string name;
		Section* section;
};


int main() {

   // lab workers
   LabWorker moe( "Moe" );
   LabWorker jane( "Jane" );
   
   // sections and setup and testing
   Section secA2( "A2", "Tuesday", 16 );
   //secA2.loadStudentsFromFile( "A2.txt" );
   
   secA2.addStudent("John");
   secA2.addStudent("George");
   secA2.addStudent("Paul");
   secA2.addStudent("Ringo");
   
   cout << "\ntest A2\n";    // here the modeler-programmer checks that load worked
   secA2.display();          // YOU'll DO THIS LATER AS: cout << secA2 << endl;
   moe.addSection( secA2 );
   moe.displayGrades();       // here the modeler-programmer checks that adding the Section worked
  
   Section secB3( "B3", "Thursday", 11 );
   //secB3.loadStudentsFromFile( "B3.txt" );
   secB3.addStudent("Thorin");
   secB3.addStudent("Dwalin");
   secB3.addStudent("Balin");
   secB3.addStudent("Kili");
   secB3.addStudent("Fili");
   secB3.addStudent("Dori");
   secB3.addStudent("Nori");
   secB3.addStudent("Ori");
   secB3.addStudent("Oin");
   secB3.addStudent("Gloin");
   secB3.addStudent("Bifur");
   secB3.addStudent("Bofur");
   secB3.addStudent("Bombur");

   cout << "\ntest B3\n";    // here the modeler-programmer checks that load worked
   secB3.display();          // YOU'll DO THIS LATER AS: cout << secB3 << endl;
   jane.addSection( secB3 );
   jane.displayGrades();      // here the modeler-programmer checks that adding Instructor worked


   // setup is complete, now a real world scenario can be written in the code
   // [NOTE: the modeler-programmer is only modeling joe's actions for the rest of the program]

   // week one activities  
   cout << "\nModeling week: 1\n";
   moe.addGrade( "John", 7, 1 );  
   moe.addGrade( "Paul", 9, 1 );  
   moe.addGrade( "George", 7, 1 );  
   moe.addGrade( "Ringo", 7, 1 );  
   cout << "End of week one\n";
   moe.displayGrades();

   // week two activities
   cout << "\nModeling week: 2\n";
   moe.addGrade( "John", 5, 2 );  
   moe.addGrade( "Paul", 10, 2 );  
   moe.addGrade( "Ringo", 0, 2 );  
   cout << "End of week two\n";
   moe.displayGrades();

   //test that reset works  // NOTE: can we check that the heap data was dealt with?
   cout << "\ntesting reset()\n";
   secA2.reset();
   secA2.display();
   moe.displayGrades();

} // main