//Brian Chuk
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
using namespace std;


template<class Object>
class LList;

template<class Object>
class LListItr;

template<class Object>
class LListNode {

    LListNode(const Object& element = Object(), LListNode* n = nullptr):element(element),next(n){}

    Object element;
    LListNode * next;
    
    friend class LList<Object>;
    friend class LListItr<Object>;

};

template<class Object>
class LListItr {
public:
    LListItr():current(nullptr){}
    
    LListItr& operator++();
    LListItr operator++(int);
    
    bool operator==(const LListItr& rhs);
    bool operator!=(const LListItr& rhs);
    
    Object& operator*();

private:
    LListItr(LListNode<Object>* p) : current(p) {}

    LListNode<Object>* current;
    
    friend class LList<Object>;
};

template<class Object>
class LList {
public:
    typedef LListItr<Object> iterator; // I added this typedef
    
    LList() : header(new LListNode<Object>()), s(0) {}

// Using the STL method names for the methods above
    LListItr<Object> before_begin() {return LListItr<Object>(header);}
    LListItr<Object> begin() {return LListItr<Object>(header->next);}
    LListItr<Object> end() {return LListItr<Object>(LListItr<Object>(nullptr));}
    
    void push_front(const Object& x) {
    	LListNode<Object>* fresh = new LListNode<Object>();
    	fresh->element = x;
    	fresh->next = header;
    	header = fresh;
    	s++;
    }
    
    bool empty() {return header->next == nullptr;}
    
    int size() {return s;}
    
    void pop_front() {
    	header = header->next;
    	s--;
    }

    template<class Predicate>// This is how you create a template method within a class
    void remove_if(Predicate pred);

    LListItr<Object> erase_after(LListItr<Object> itr) {
    	
    }

    void print() {
    	cout << size() << " elements: ";
    	LListNode<Object>* p = header;
    	while (p->next != nullptr) {
    		cout << p->element << " ";
    		p = p->next;
    	}
    	cout << endl;
    }
 

    
private:
    LListNode<Object>* header;
    int s;
};

template<class Object> template< class Predicate> /* The signature for when you define the template method outside the class*/
void LList<Object>::remove_if( Predicate pred) {

}

int main() {
	LList<int> list = LList<int>();
	list.push_front(5);
	list.push_front(4);
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	list.print();
	list.pop_front();
	list.print();
}