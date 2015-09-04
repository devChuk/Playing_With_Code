#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
using namespace std;


struct Node {
  Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
  int data;
  Node* link;
};

class Sequence {
  public:
  Sequence(): head(NULL), curr(NULL) {}
  ~Sequence() {
    Node* p = head;
    while (p) {
      Node* temp = p;
      p = p-> link;
      delete temp;
      temp = NULL;
  }
    head = curr = NULL;
    delete head;
    delete curr;
  }
  Node* getHead() const{
    return head;
  }
  int getCurr() const{ return curr->data;}
  Sequence(const Sequence& rhs) {
    if (rhs.getHead()) {
      head = new Node;
      *head = *rhs.getHead();
    }
  }
  Sequence& operator=(Sequence& rhs) {
    rhs.reset();
    int i = 0;
    while(rhs.next())
      i++;
    head = curr = new Node;
      curr->link = new Node;
    for (int g = 0; g < i; g++) {
      curr->link = new Node;
      curr = curr->link;
    }
    reset();
    rhs.reset();
    while (curr != NULL) {
      curr->data = rhs.getCurr();
      next();
      rhs.next();
    }
    return *this;
  }
  void add(int i) {
    if (!curr && !head) {
      Node* nod = new Node;
      nod->data = i;
      curr = head = nod;
    }
    else if (!curr) {}
    else {
      Node* nod = new Node;
      nod->data = i;
      nod->link = curr->link;
      curr->link = nod;
      curr = curr->link;
    }
  }
  void display() {
    const Node* p = head;
    while(p) {
      cout << p->data << ' ';
      p = p->link;
    }
    cout << endl;
  }
  void reset() {
    curr = head;
  }
  Node* next() {
    curr = curr->link;
    return curr;
  }
  void remove() {
    Node* p = head;
    while(p->link != curr) {
      p = p->link;
    }
    delete p->link;
    p->link = p->link->link;
  }
  void clear() {
    Node* p = head;
    while (p) {
      Node* temp = p;
      p = p-> link;
      delete temp;
      temp = NULL;
    }
    head = curr = NULL;
  }
private:
  Node* head;
  Node* curr;
};

int main() {
  Sequence s;
  for (int i = 0; i < 6; ++i) s.add(i);
  s.display();
  Sequence jay;
  jay = s;
  cout << "==========\n";
  s.reset();
  for (int i = 0; i < 3; ++i) s.next();
  s.add(42);
  s.display();
  cout << "==========\n";
  s.reset();
  for (int i = 0; i < 2; ++i) s.next();
  s.remove();
  s.display();
  cout << "==========\n";
  s.clear();
  s.display();
  cout << "==========\n";
  // jay.display();
}

// 0 1 2 3 4 5 
// ==========
// 0 1 2 3 42 4 5 
// ==========
// 0 1 3 42 4 5
// ==========

// ========== 