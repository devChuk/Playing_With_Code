#include <iostream>
#include <vector>
#include <string>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

#include <fstream>

template <class Object>
Object sumVector(const std::vector<Object> & a, int left, int right) {
        
}

int runFunction(int one, int two) {
	std::cout << "ran" << std::endl;
	return one;
}

bool uniqueChars(std::string input) {
	// std::vector<std::string> chars;
	// for (int i = 0; i < input.length; i++) {
	// 	if (chars.indexOf(input.str(i,i+1))  == -1)
	// 		chars.push_back(input.str(i,i+1));
	// 	else
	// 		return false;
	// 	return true;
	// }
	//////////
	// std::vector<std::string> chars;
	// for (int i = 0; i < input.length(); i++) {
	// 	if (std::find(chars.begin(),chars.end(),input.substr(i,i+1))  == chars.end())
	// 		chars.push_back(input.substr(i,i+1));
	// 	else
	// 		return false;
	// }
	// return true;
	///////////
	for (int i = 0; i < input.length(); i++) {
		for (int j = i + 1; j < input.length(); j++) {
			if (input.substr(i,i+1) == input.substr(j,j+1))
				return false;
		}
	}
	return true;
}

void reverse(char* str) {
	// char* end = str;
	// char* ans;
	// if (*str) {
	// 	while (*end)
	// 		end++;
	// 	while (*end != *str) {
	// 		ans = end;
	// 		ans++;
	// 		*end--;
	// 	}
	// }
	// return ans;
	////////////
	char* end = str;
	char tmp;
	if (*str) {
		while (*end)
			end++;
		end--;
		while (end > str) {
			tmp = *str;
			*str++ = *end;
			*end-- = tmp;
		}
	}
}

bool permuCheck(std::string strA, std::string strB) {
	if (strA.length() == strB.length()) {
		std::sort(strA.begin(), strA.end());
		std::sort(strB.begin(), strB.end());
		for (int i = 0; i < strA.length(); i++)
			if (strA[i] != strB[i])
				return false;
		return true;
	} else
	return false;
	
	// OR, MAKE AN ARRAY THAT RECORDS THE FREQUENCY OF ALL POSSIBLE CHARS
	// THEN HAVE IT RECORD THE FREQ OF CHARS IN strA, then remove/compare with strB.
}


// "Mr|John|||Smith|"
void replaceTwenty(std::string& str, int length) {
	int count = 0, newLength;

	for (int i = 0; i < length; i++)
		if (str[i] == ' ')
			count++;

	newLength = length + 2 * count;
	str[newLength] = '\0';

	for (int i = length - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			str[newLength - 1] = '0';
			str[newLength - 2] = '2';
			str[newLength - 3] = '%';
			newLength = newLength -3;
		} else {
			str[newLength - 1] = str[i];
			newLength--;
		}
	}
}

void removeDupes(LLNode* head) {
	std::unordered_map<int, bool> record;
	record.insert({head->data, true});
	LLNode* current = head->next;
	LLNode* prev = head;

	while (current)
		if (record.count(current->data) > 0) {
			current = current->next;
			prev->next = current;
		} else {
			record.insert({current->data, true});
			current = current->next;
			prev = prev->next;
		}
}

int main() {
	
	while(false) {
	   int a = 4;
	}

	for (int i = 0; i < 10; i++) {
		std::cout << i << std::endl;
	}

	do {
	   int b = 2;
	} while( false );


	std::cout << "ay" << std::endl;

	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	first.push_back(5);
	std::cout << first.size() << std::endl;
	std::cout << first[0] << std::endl;
	std::cout << first.front() << std::endl;
	std::cout << first.back() << std::endl;

	first.pop_back();

	it = first.begin();
	first.insert(it,300);
	first.insert(it,2,300);

	first.erase(first.begin() + 5);
	first.swap(second);

	first.clear();



	/*
	char grade = 'D';

	switch(grade)
	{
	case 'A' :
		cout << "Excellent!" << endl; 
		break;
	case 'B' :
	case 'C' :
		cout << "Well done" << endl;
		break;
	case 'D' :
		cout << "You passed" << endl;
		break;
	case 'F' :
		cout << "Better try again" << endl;
		break;
	default :
		cout << "Invalid grade" << endl;
	}
	*/

	std::string s(5, 'a');
	string str1 = "Hello";
	string str2 = "World";
	string str3;
	int  len ;

	// copy str1 into str3
	str3 = str1;
	cout << "str3 : " << str3 << endl;

	// concatenates str1 and str2
	str3 = str1 + str2;
	cout << "str1 + str2 : " << str3 << endl;

	// total lenghth of str3 after concatenation
	len = str3.size();
	cout << "str3.size() :  " << len << endl;


	std::string str="We think in generalities, but we live in details.";
                                           // (quoting Alfred N. Whitehead)

	std::string str2 = str.substr (3,5);     // "think"


	runFunction(1,2);

	// char somebuffer[100] = "a string";
	// char* ptr = somebuffer;  // ptr now points to somebuffer
	// std::cout << ptr << std::endl; // prints "a string"
	// reverse(ptr);
	// std::cout << ptr << std::endl; // prints "a string"
	
	/*
	// 3
	// 1 5
	// 3 10
	// 999 -34343

	int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << a+b << "\n";
    }
    */


    
   char data[100];

   // open a file in write mode.
   ofstream outfile;
   outfile.open("afile.dat");

   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);

   // write inputted data into the file.
   outfile << data << endl;

   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // again write inputted data into the file.
   outfile << data << endl;

   // close the opened file.
   outfile.close();

   // open a file in read mode.
   ifstream infile; 
   infile.open("afile.dat"); 
 
   cout << "Reading from the file" << endl; 
   infile >> data; 

   // write the data at the screen.
   cout << data << endl;
   
   // again read the data from the file and display it.
   infile >> data; 
   cout << data << endl; 

   // close the opened file.
   infile.close();

	

   
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b)) { break; } // error

	// process pair (a,b)
	}

	

	vector<vector<bool>> isVisited(n, vector<bool>(n, false));
    vector<array<int, 2>> pD;   // possible directions

    vector<vector<int>> result;
    result.resize(n-1);
    for (int i = 0; i < result.size(); i++) {
        result[i].resize(n - 1);
    }

    return 0;
}

// std::sort O(nlogn)


std::sort(mMyClassVector.begin(), mMyClassVector.end(), 
    [](const MyClass & a, const MyClass & b) -> bool
{ 
    return a.mProperty > b.mProperty; 
});
