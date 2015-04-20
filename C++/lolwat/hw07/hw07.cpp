//Brian Chuk, Programming Part
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>
#include <exception>
using namespace std;
//PROBLEM 1///////////////////////////////////////////////////////////////////////////////////////////////////////////
void parseTrainData(map<string, int>& moo, vector<string>& int_to_stop_id) { //fills up moo & int_to_stop_id
	ifstream stopFile("MTA_train_stop_data.txt");
	if (!stopFile) {
		cerr << "Yo the train stop data file's missing.\n";
		exit(1);
	}
	string line;
	getline(stopFile, line);
	int count = 0;
	while (getline(stopFile, line)) {
		int comma = line.find(',');
		string stop_id = line.substr(0,comma);
		if (stop_id.substr(comma-1) != "S" && stop_id.substr(comma-1) != "N") {
			moo[stop_id] = count;
			int_to_stop_id.push_back(stop_id);
			count++;
		}
	}
}

void parseTransfersData(vector<list<int>>& adjacent, map<string, int>& moo, vector<string>& int_to_stop_id) { //fills up adjacent with lists of transferrable numbers
	ifstream stopFile("transfers.txt");
	if (!stopFile) {
		cerr << "Yo the transfers data file's missing.\n";
		exit(1);
	}
	string line;
	getline(stopFile, line);
	while (getline(stopFile, line)) { //adjacent index represents init transfer point
		string from = line.substr(0,line.find(','));
		string to = line.substr(4,3);
		// cout << from << "|" << to << "|" << moo[from] << "|" << moo[to] << endl;
		if (adjacent.size() == moo[from]) {
			list<int>* meow = new list<int>;
			meow->push_back(moo[to]);
			adjacent.push_back(*meow);//create new slot
		}
		else {
			adjacent[adjacent.size() - 1].push_back(moo[to]);
		}
	}
}
/*  TEST CODE
int main() {
	map<string, int> moo;
	vector<string> int_to_stop_id;
	parseTrainData(moo, int_to_stop_id);
	vector<list<int>> adjacent;
	parseTransfersData(adjacent, moo, int_to_stop_id);
	//	replace the index with the desired number to test
	// for (list<int>::iterator it=adjacent[9].begin(); it != adjacent[9].end(); ++it)
	//     cout << ' ' << *it;
}
*/

//PROBLEM 2///////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode {
    Comparable  element;
    BinaryNode *left;
    BinaryNode *right;
    int size;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt,
               BinaryNode *rt, int sz = 1 )
    : element( theElement ), left( lt ), right( rt ), size( sz ) { }
    
    friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree {
public:
    typedef BinaryNode<Comparable> Node;
    
    BinarySearchTree( ) : root( NULL ) { } // Construct the tree.
    ~BinarySearchTree( ){ makeEmpty( ); } // Destructor for the tree.
    

    // add function declarations
    
    
    bool isEmpty( ) const { return root == NULL;}
    void makeEmpty( ) { makeEmpty( root ); }
    void insert( const Comparable & x ) { insert( x, root ); }
    
private:
    Node * root;

    // add function declarations
    
    int treeSize( Node *t ) const { return t == NULL ? 0 : t->size; }
    Comparable const * elementAt( Node *t ) const;
    void insert( const Comparable & x, Node * & t );
    void makeEmpty( Node * & t ) const;
    Node * clone( Node *t ) const;
};



template <class Comparable>
Comparable const * BinarySearchTree<Comparable>::elementAt( Node *t ) const {
    if( t == NULL )
        return NULL;
    else
        return &(t->element);
}


template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, Node * & t ) {
    if( t == NULL )
        t = new Node( x, NULL, NULL, 0 );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        throw exception( );
    
    t->size++;
}


template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( Node * & t ) const {
    if( t != NULL ) {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        t = NULL;
    }
}

int main() {

}