#include "hashMap.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

int main() {

	std::cout << "\n\nTesting HashMap of ints...\nInitializing HashMap intTest of size 20" << std::endl;
	
	HashMap<int> intTest = HashMap<int>(20);
	std::cout << "load factor: " << intTest.loadFactor() << std::endl;

	std::cout << "\nInserting 123 at please\nInserting 10000 at accept\nInserting 1337 at my\nInserting 666 at app\nInserting 404 at app\n" << std::endl;
	int pls = 123;
	int accept = 10000;
	int my = 1337;
	int app = 666;
	int app2 = 404;

  	std::cout << (intTest.set("please", pls) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (intTest.set("accept", accept) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (intTest.set("my", my) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (intTest.set("app", app) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (intTest.set("app", app2) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;

  	std::cout << "load factor: " << intTest.loadFactor() << std::endl;

  	std::cout << "\nTesting get function..." << std::endl;
  	std::cout << "intTest[please]: " << intTest.get("please") << std::endl;
  	std::cout << "intTest[accept]: " << intTest.get("accept") << std::endl;
  	std::cout << "intTest[my]: " << intTest.get("my") << std::endl;
  	std::cout << "intTest[app]: " << intTest.get("app") << std::endl;
  	std::cout << "intTest[hacker] (does not exist): " << intTest.get("hacker") << std::endl;

  	std::cout << "\nTesting delete function..." << std::endl;
	std::cout << "load factor: " << intTest.loadFactor() << std::endl;
	intTest.del("please");
	intTest.del("accept");
	intTest.del("my");
	intTest.del("app");
	std::cout << "All keys have been deleted." << std::endl;
	std::cout << "load factor: " << intTest.loadFactor() << std::endl;


	std::cout << "\n\nTesting HashMap of strings...\nInitializing HashMap stringTest of size 200" << std::endl;
	
	HashMap<std::string> stringTest = HashMap<std::string>(200);
	std::cout << "load factor: " << stringTest.loadFactor() << std::endl;

	std::cout << "\nInserting hello at please\nInserting my at accept\nInserting name at my\nInserting is at app\nInserting Brian at app\n" << std::endl;
	std::string plsString = "hello";
	std::string acceptString = "my";
	std::string myString = "name";
	std::string appString = "is";
	std::string app2String = "Brian";

  	std::cout << (stringTest.set("please", plsString) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (stringTest.set("accept", acceptString) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (stringTest.set("my", myString) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (stringTest.set("app", appString) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;
  	std::cout << (stringTest.set("app", app2String) ? "SUCCESS" : "ERROR, ALEADY CONTAINS ANOTHER ELEMENT") << std::endl;

  	std::cout << "load factor: " << stringTest.loadFactor() << std::endl;

  	std::cout << "\nTesting get function..." << std::endl;
  	std::cout << "stringTest[please]: " << stringTest.get("please") << std::endl;
  	std::cout << "stringTest[accept]: " << stringTest.get("accept") << std::endl;
  	std::cout << "stringTest[my]: " << stringTest.get("my") << std::endl;
  	std::cout << "stringTest[app]: " << stringTest.get("app") << std::endl;

  	std::cout << "\nTesting delete function..." << std::endl;
	std::cout << "load factor: " << stringTest.loadFactor() << std::endl;
	stringTest.del("please");
	stringTest.del("accept");
	stringTest.del("my");
	stringTest.del("app");
	std::cout << "All keys have been deleted." << std::endl;
	std::cout << "load factor: " << intTest.loadFactor() << std::endl;

	std::cout << "\n\n\nTEST COMPLETE." << std::endl;
	
	return 0;
}