#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
using namespace std;

struct Node {
	Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
	int data;
	Node* link;
};

void listInsertHead(int entry, Node*& headPtr) {
	headPtr = new Node(entry, headPtr);
}

void listDisplay(const Node* headPtr) {
	const Node* p = headPtr;
	// Loop through the list.
	while (p != NULL) {
		cout << p->data << ' ';
		p = p->link;
	}
	cout << endl;
}

void listDisplayAdd(const Node* headPtr) {
	const Node* p = headPtr;
	// Loop through the list.
	while (p != NULL) {
		cout << p->data << ' ';
		p = p->link;
	}
}

void spliceInto(Node* target, Node* insertion) {
	Node* p = insertion;
	while (p->link != NULL)
		p = p->link;
	p->link = target->link;
	target->link = insertion;
}

Node* search(Node* head, Node* subListHead)
{
	Node* originalSubHead = subListHead;
	while (head != nullptr)
	{
		if (head->data != subListHead->data)
		{
			head = head->link;
		}
		else
		{
			head = head->link;
			Node* startingNode = head;
			subListHead = subListHead->link;
			bool match = true;
			while (subListHead != nullptr)
			{
				if (head->data != subListHead->data)
				{
					match = false;
					break;
				}
				head = head->link;
				subListHead = subListHead->link;
			}
			if (match) {
				listDisplay(head);
				return originalSubHead;
			}
			subListHead = originalSubHead;
			head = startingNode;
		}
	}
	cout << "Failed to match";
	return NULL;
}


int main() {
	cout << "Part One\n\n";
	cout << "L1: ";
	Node one; one.data = 1;
	Node nine; nine.data = 9; nine.link = &one;
	Node seven; seven.data = 7; seven.link = &nine;
	Node five; five.data = 5; five.link = &seven;
	listDisplay(&five);

	cout << "L2: ";
	Node two; two.data = 2;
	Node three; three.data = 3; three.link = &two;
	Node six; six.data = 6; six.link = &three;
	listDisplay(&six);

	cout << "Target: ";
	listDisplay(&seven);
	cout << "Splicing L2 at target in L1" << endl;
	
	cout << "L1: ";
	spliceInto(&seven, &six);
	listDisplay(&five);
	cout << "L2: ";
	listDisplay(&six);
	cout << "===========================\n\n" << endl;
	cout << "Part Two\n\n";

	Node nueve; nueve.data = 6;
	Node ocho; ocho.data = 5; ocho.link = &nueve;
	Node siete; siete.data = 4; siete.link = &ocho;
	Node seis; seis.data = 2; seis.link = &siete;
	Node cinco; cinco.data = 3; cinco.link = &seis;
	Node cuatro; cuatro.data = 2; cuatro.link = &cinco;
	Node tres; tres.data = 3; tres.link = &cuatro;
	Node dos; dos.data = 2; dos.link = &tres;
	Node uno; uno.data = 1; uno.link = &dos;
	cout << "Target: ";
	listDisplay(&uno);

	Node on; on.data = 1;
	Node secondary; secondary.data = 9;
	Node primary; primary.data = 3; primary.link = &secondary;
	Node second; second.data = 3;
	Node first; first.data = 2; first.link = &second;
	Node shi; shi.data = 6;
	Node san; san.data = 5; san.link = &shi;
	Node er; er.data = 4; er.link = &san;
	Node yi; yi.data = 2; yi.link = &er;
	Node say; say.data = 4;
	Node sam; sam.data = 2; sam.link = &say;
	Node ee; ee.data = 3; ee.link = &sam;
	Node yut; yut.data = 2; yut.link = &ee;
	Node hurrr; hurrr.data = 7;
	Node hurr; hurr.data = 6; hurr.link = &hurrr;
	Node hur; hur.data = 5; hur.link = &hurr;

	cout << "\nAttempted match: ";
	listDisplay(&on);
	listDisplayAdd(&on);
	search(&uno,&on);

	cout << "\nAttempted match: ";
	listDisplay(&primary);
	search(&uno,&primary);

	cout << "\n\nAttempted match: ";
	listDisplay(&first);
	listDisplayAdd(&first);
	search(&uno, &first);

	cout << "\nAttempted match: ";
	listDisplay(&yi);
	listDisplayAdd(&yi);
	search(&uno, &yi);

	cout << "\nAttempted match: ";
	listDisplay(&yut);
	listDisplayAdd(&yut);
	search(&uno, &yut);

	// cout << "\nAttempted match: ";
	// listDisplay(&hur);
	// search(&uno, &hur);


	/*
Part two:

Target: 1 2 3 2 3 2 4 5 6

Attempt match: 1
1 2 3 2 3 2 4 5 6

Attempt match: 3 9
Failed to match

Attempt match: 2 3
2 3 2 3 2 4 5 6

Attempt match: 2 4 5 6
2 4 5 6

Attempt match: 2 3 2 4
2 3 2 4 5 6

Attempt match: 5 6 7
Failed to match

Press any key to continue*/
}