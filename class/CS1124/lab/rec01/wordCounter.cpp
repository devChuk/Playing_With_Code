/*
	Brian Chuk
	bc1691
	rec01
	9/5/2014

	This program reads a file, displays it to the screen and reports how many "words" there are.
*/


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {

	cout << "PART 1\n======\n";
	//Read the file line-by-line, printing each line to the screen.
	ifstream ifs("file.txt"); //initialize a input file stream
	string i;				  //initialize a string	
	while (getline(ifs, i)) { //a while loop that prints out each line
		cout << i << endl;
	}
	ifs.close();              //whatever memory you take, remember to give it back

	



	cout << "PART 2\n======\n";
	//Read the file again, word-by-word, keeping a count of the words read and displaying the count when you are done.
	ifstream ifs2("file.txt");
	string s;
	int x;
	while (ifs2 >> s) {
		x++;
	}
	cout << x << endl;
	ifs2.close(); 
}