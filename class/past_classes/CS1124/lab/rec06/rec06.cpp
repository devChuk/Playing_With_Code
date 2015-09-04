/*
Brian Chuk
CS1124
bc1691
*/

#include <iostream>
#include <vector>
#include <string>
        using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned numPages) : numberofPages(numPages) {}
	virtual void displayNumPages() const = 0; //this pure function makes PrintedMaterial abstract. That means that no objects are allowed to be created from it unless it directly overrrides it.
protected:
private:
	unsigned numberofPages;
};

void PrintedMaterial::displayNumPages() const {
  cout << numberofPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned numPages) : PrintedMaterial(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned numPages) : PrintedMaterial(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndexPages) : Book(numPages), numOfIndexPages(numIndexPages) {}
	void displayNumPages() const {
		cout << "Pages: ";
		PrintedMaterial::displayNumPages();
		cout << "Index pages: ";
		cout << numOfIndexPages << endl;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned numPages) : Book(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};



// tester/modeler code
int main()
{	
	TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);

	// as direct method calls
	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	// Storing generic objects in a vector 
	cout << "\n\nNow we'll use a container. Yea!!!\n\n";
	vector< PrintedMaterial* > allThemPrinties;
	allThemPrinties.push_back(&t);
	allThemPrinties.push_back(&n);
	allThemPrinties.push_back(&m);
	for( size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx ) 
	{
		allThemPrinties[ndx]->displayNumPages();
		cout << endl;
	}
}
