//Brian Chuk
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;


//PROBLEM 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//returns true if there is a duplicate item
template <class T>
bool duplicateCheck(vector<T>& v) {
	for (int i = 0; i < v.size(); i++) 
		for (int j = i + 1; j < v.size(); j++)
			if (v[i] == v[j])
				return true;
	return false;
}

//the problem is a bit vague on how I should do it. Am I supposed to make a function? Or is any solution fine?
class Node {
public: // These member variables are made public to simplify your coding.
		// Of course these member variables should be private!
	Node( char ch, Node * ptr = nullptr):data(ch),next(ptr){}
	char data;
	Node * next;
};

void memorylocationPrint(Node* head) {
	Node* nodePtr;
	nodePtr = head;
	while (nodePtr) {\
		printf("%p", nodePtr);
		nodePtr = nodePtr->next;
		cout << endl;
	}
	cout << "nodePtr address: ";
	printf("%p\n", nodePtr);
	cout << endl;
}
//PROBLEM 4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void fillwithRandomN(vector<int>& randomInts, int n) {
	for (int i = 0; i < n; i++) {
		randomInts.push_back((rand() % 2001) - 1000);
	}
}

class timer {
public:
    timer() : start(clock()) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};

template <class Comparable>
Comparable maxSubsequenceSum1( const vector<Comparable> & a, int & seqStart, int & seqEnd )
{
    int n = a.size( );
    Comparable maxSum = 0;
	
    for( int i = 0; i < n; i++ )
        for( int j = i; j < n; j++ )
        {
            Comparable thisSum = 0;
            for( int k = i; k <= j; k++ )
                thisSum += a[ k ];
			
            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }
	
    return maxSum;
}

template <class Comparable>
Comparable maxSubsequenceSum2( const vector<Comparable> & a,int & seqStart, int & seqEnd )
{
    int n = a.size( );
    Comparable maxSum = 0;
	
    for( int i = 0; i < n; i++ )
    {
        Comparable thisSum = 0;
        for( int j = i; j < n; j++ )
        {
            thisSum += a[ j ];
			
            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }
    }
	
    return maxSum;
}

template <class Comparable>
Comparable maxSubsequenceSum4( const vector<Comparable> & a, int & seqStart, int & seqEnd )
{
    int n = a.size( );
    Comparable thisSum = 0;
    Comparable maxSum = 0;
	
    for( int i = 0, j = 0; j < n; j++ )
    {
        thisSum += a[ j ];
		
        if( thisSum > maxSum )
        {
            maxSum = thisSum;
            seqStart = i;
            seqEnd = j;
        }
        else if( thisSum < 0 )
        {
            i = j + 1;
            thisSum = 0;
        }
    }
    return maxSum;
}

int main() {
	cout << "Problem 1" << endl;
	vector<string> nodupes;
	nodupes.push_back("hello");
	nodupes.push_back("world");
	cout << duplicateCheck(nodupes) << endl;
	vector<char> yesdupes;
	yesdupes.push_back('a');
	yesdupes.push_back('b');
	yesdupes.push_back('c');
	yesdupes.push_back('d');
	yesdupes.push_back('a');
	cout << duplicateCheck(yesdupes) << endl;
	vector<int> yesdupes2;
	yesdupes2.push_back(1);
	yesdupes2.push_back(1);
	yesdupes2.push_back(1);
	cout << duplicateCheck(yesdupes2) << endl;

	cout << "Problem 2" << endl;
	Node uno('C');
	Node dos('B');
	Node tres('D');
	uno.next = &dos;
	dos.next = &tres;

	Node front('A');
	front.next = &uno;

	Node* nodePtr;
	nodePtr = &front;
	while (nodePtr) {
		printf("%p", nodePtr);
		nodePtr = nodePtr->next;
		cout << endl;
	}
	cout << "nodePtr address: ";
	printf("%p\n", nodePtr);
	cout << endl;

	nodePtr = front.next;
	front.next = NULL;
	delete front.next;

//PROBLEM 3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cout << "Problem 3" << endl;
	int * intPtr = new int[5];
	for (int i = 2; i < 6; i++) {
		*intPtr = i; 
		intPtr++;
	}

	for (int i = 0; i < 5; i++) {
		*intPtr = *(intPtr - 1);
		--intPtr;
	}
	*++intPtr = 1;
	for (int j = 0; j < 5; j++) {
		cout << "Memory location of " << *intPtr++ << ": " << intPtr << endl;
		cout << "\n" << endl;
	}
	cout << intPtr << "\n\n\n" << "Problem 4" << endl;
	intPtr = NULL;
	delete intPtr;

//PROBLEM 4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	vector<int> items;
	int n = 4096, ss = 0, se = 0;
	timer t;
	double nuClicks;
	fillwithRandomN(items, n);
	t.reset();
	maxSubsequenceSum4( items, ss, se);
	nuClicks = t.elapsed();
	cout << nuClicks << endl;

}