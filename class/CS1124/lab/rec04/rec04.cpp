/*
Brian Chuk
CS1124
bc1691
*/
#include <iostream>
#include <vector>
#include <string>
        using namespace std;

int main() {
	int x;  
	x = 10;  
	cout << "x = " << x << endl;

	int* p;
	p = &x;  
	cout << "p = " << p << endl;

	cout << "p points to where " << *p << " is stored\n";  
	cout << "*p contains " << *p << endl;     


	cout << "\n";
	*p = -2763;  
	cout << "p points to where " << *p << " is      stored\n";  
	cout << "*p now contains " << *p << endl;  
	cout << "x now contains " << x << endl;

	cout << "\n";
	int y(13);      
	cout << "y contains " << y << endl;      
	p = &y;      
	cout << "p now points to where " << *p << " is stored\n";      
	cout << "*p now contains " << *p << endl;      
	*p = 980;      
	cout << "p points to where " << *p << " is stored\n";      
	cout << "*p now contains " << *p << endl;      
	cout << "y now contains " << y << endl;

	cout << "\n";
	int* q;      
	q = p;      
	cout << "q points to where " << *q << " is stored\n";      
	cout << "*q contains " << *q << endl;

	/*double d(33.44);      
	double* pD(&d);      
	*pD = *p;      
	*pD = 73.2343;      
	*p  = *pD;      
	*q  = *p;      
	pD  = p; */
	cout << "\n";
	int joe( 24 );  
	const int sal( 19 );    
	int*  pI;  
	//  pI = &joe;  
	// *pI = 234;  
	//  pI = &sal;  
	// *pI = 7623;    

	//const int* pcI;
	//  pcI = &joe;  
	// *pcI = 234;  
	//  pcI = &sal;  
	// *pcI = 7623;    

	//int* const cpI;
	//int* const cpI(&joe);
	//int* const cpI(&sal);
	//  cpI = &joe;  
	// *cpI = 234;  
	//  cpI = &sal;  
	// *cpI = 7623;    

	//const int* const cpcI;
	//const int* const cpcI(&joe);
	//const int* const cpcI(&sal);
	//  cpcI = &joe;  
	// *cpcI = 234;  
	//  cpcI = &sal;  
	// *cpcI = 7623;
}