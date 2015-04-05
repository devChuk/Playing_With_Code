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
    
    LListItr& operator++() {
    	current = current->next;
    }

    LListItr operator++(int) {
    	LListItr ans = *this;
    	++*this;
    	return ans;
    }
    
    bool operator==(const LListItr& rhs) {
    	if (current == nullptr && rhs.current == nullptr) return true;
    	if (current == nullptr || rhs.current == nullptr) return false;
    	return current->element == rhs.current->element && current->next == rhs.current->next;
    }


    bool operator!=(const LListItr& rhs) {
    	return !(operator==(rhs));
    }
    
    Object& operator*() {
    	return current->element;
    }

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
    	if (header->next == nullptr) {
    		header->next = fresh;
    	}
    	else {
    		fresh->next = header->next;
    		header->next = fresh;	
    	}
    	s++;
    }
    
    bool empty() {return header->next == nullptr;}
    
    int size() {return s;}
    
    void pop_front() {
    	header = header->next;
    	s--;
    }

    template<class Predicate>// This is how you create a template method within a class
    void remove_if(Predicate pred) {
    	LListItr<Object> p = before_begin();
    	while (p != end()) {
    		if (p.current->next != nullptr && pred(*p))
    			erase_after(p);
    		p++;
    	}
    }

    void remove_last(const Object& x) {
    	LListItr<Object> target;
    	LListItr<Object> p = before_begin();
    	while (p != end()) {
    		if (p.current->next != nullptr && pred(*p))
    			erase_after(p);
    		p++;
    	}
    }

    LListItr<Object> erase_after(LListItr<Object> itr) {
    	itr.current->next = itr.current->next->next;
    	s--;
    }

    void print() {
    	cout << size() << " elements: ";
    	LListNode<Object>* p = header->next;
    	while (p != nullptr) {
    		cout << p->element << " ";
    		p = p->next;
    	}
    	cout << endl;
    }
 

    
private:
    LListNode<Object>* header;
    int s;
};

// template<class Object> template< class Predicate> /* The signature for when you define the template method outside the class*/
// void LList<Object>::remove_if( Predicate pred) {

// }

class LessThanThree { // <3
public:
	bool operator()(int x) const {
		return x < 3;
	}
};

int main() {
	LList<int> list = LList<int>();
	list.push_front(5);
	list.push_front(4);
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);						// {1, 2, 3, 4, 5}
	list.print();
	list.pop_front();						// {2, 3, 4, 5}
	list.print();
	list.erase_after(list.begin());			// {2, 4, 5}
	list.print();
	list.remove_if(LessThanThree());		// {4, 5}
	list.print();


}