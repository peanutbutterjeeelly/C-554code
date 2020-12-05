#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node() { next = nullptr; }
	Node(int i) { value = i; next = nullptr; }
};

class Ring {
public:
	int numNodes;
	Node* head;
	Ring() { numNodes = 0; head = nullptr; }
	Ring(const initializer_list<int>& I);//initializer_list
	~Ring();//Destructor
	Ring(const Ring& R);//Copy constructor
	Ring(Ring&& R); //Move constructor
	void operator=(const Ring& R);//Copy Assignment (i.e., Lvalue assignment)
	void operator=(Ring&& R);//Move assignment (i.e., Rvalue assignment)
	Ring ThreeTimes();//Retrun a ring with the values of all nodes being three times of the value of current Ring
};
ostream& operator<<(ostream& str, const Ring& R);


void Ring::operator=(Ring&& R) {//Move Assignment (i.e., Rvalue assignment)
	for (int i = 0; i < numNodes; ++i) {
		Node* p1 = head->next;
		delete head;
		head = p1;
	}
	numNodes = R.numNodes;
	head = R.head;
	R.head = nullptr;
	R.numNodes = 0;
	cout << "Move Assignment" << endl;
}
Ring::Ring(Ring&& R) { //Move constructor
	numNodes = R.numNodes;
	head = R.head;
	R.numNodes = 0;
	R.head = nullptr;
	cout << "Move Constructor" << endl;
}


void Ring::operator=(const Ring& R) {//Copy Assignment (i.e., Lvalue assignment)
	for (int i = 0; i < numNodes; ++i) {
		Node* p1 = head->next;
		delete head;
		head = p1;
	}
	head = nullptr;
	numNodes = R.numNodes;
	Node* p1, * p2 = nullptr;
	for (int i = 0; i < numNodes; ++i) {
		p1 = new Node();
		if (i == 0) p2 = p1;
		p1->next = head;
		head = p1;
	}
	p2->next = head;
	p1 = head;
	p2 = R.head;
	for (int i = 0; i < numNodes; ++i) {
		p1->value = p2->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Assignment" << endl;
}

Ring::Ring(const Ring& R) {//Copy constructor
	//head = nullptr;
	numNodes = R.numNodes;
	Node* p1, * p2 = nullptr;
	for (int i = 0; i < numNodes; ++i) {
		p1 = new Node();
		if (i == 0) p2 = p1;
		p1->next = head;
		head = p1;
	}
	p2->next = head;
	p1 = head;
	p2 = R.head;
	for (int i = 0; i < numNodes; ++i) {
		p1->value = p2->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Constructor" << endl;
}
Ring::~Ring() {
	for (int i = 0; i < numNodes; ++i) {
		Node* p1 = head->next;
		delete head;
		head = p1;
	}
	cout << "Destructor" << endl;
}
Ring::Ring(const initializer_list<int>& I) {//initializer_list
	numNodes = I.size();
	head = nullptr;
	auto p = I.end() - 1;
	Node* p1, * p2 = head;
	for (int i = 0; i < numNodes; i++) {
		Node* p1 = new Node(*p);
		if (head == nullptr) p2 = p1;
		p1->next = head;
		head = p1;
		--p;
	}
	p2->next = head;
	cout << "initializer_list" << endl;
}

Ring Ring::ThreeTimes() {

	Ring temp{ *this };
	Node* p = temp.head;
	for (int i = 0; i < temp.numNodes; ++i) {
		p->value *= 3;
		p = p->next;
	}
	cout << "ThreeTimes" << endl;
	return temp;
}
//ostream& operator<<(ostream& str, const Ring& R);

int main() {
	Ring R1{ 1,2,3,4,5 };
	cout << R1 << endl;
	Ring R2{ R1 };
	cout << R2 << endl;

	Ring R3;
	R3 = R1;
	cout << R3 << endl;
	Ring R4;
	R4 = R1.ThreeTimes();
	cout << R4 << endl;
	return 0;
}
ostream& operator<<(ostream& str, const Ring& R) {
	str << "{ ";
	Node* p1 = R.head;
	for (int i = 0; i < R.numNodes; ++i) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << "}";
	return str;
}
