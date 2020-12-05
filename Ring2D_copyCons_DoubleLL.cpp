
#include <iostream>
//#include <list>
//#include <string>

using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() :ht(0), wid(0), dep(0) {}
	ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
	T getVol() const { return ht * wid * dep; }
	bool operator==(const ThreeD<T>& t) { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
	T value;
	node<T>* next;
	node<T>* previous;
	node<T>() { next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
	bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <class T> class linked_list {
public:
	node<T>* head;
	node<T>* tail;
	linked_list() { head = tail = nullptr; }
	linked_list(const initializer_list<T>& V);
	void push_front(T t);
	void push_back(T t);
	bool operator==(const linked_list<T>& L) const;

	linked_list(const linked_list<T>& L); //copy constructor
	linked_list(linked_list<T>&& L); //move constructor
	~linked_list();//destructor
	void operator=(const linked_list<T>& L);//L-value operator=
	void operator=(linked_list<T>&& L);//R-value operator=
	template <class T> friend ostream& operator<<(ostream& str, const linked_list<T>& L);
};

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L);

template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
	auto it1 = V.begin();
	while (it1 != V.end()) {
		push_back(*it1);
		it1++;
	}
	cout << "initializer_list LL" << endl;
}

template <class T> linked_list<T>::~linked_list() {  //destructor										
	node<T>* p;
	while (head != nullptr) {
		p = head->next;
		delete head;
		head = p;
	}
	cout << "Destructor LL" << endl;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
	node<T>* p1 = L.head;
	while (p1 != nullptr) {
		push_back(p1->value);
		p1 = p1->next;
	}
	cout << "Copy Constructor LL" << endl;
}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
	head = L.head;
	tail = L.tail;
	L.head = nullptr;
	L.tail = nullptr;
	cout << "Move Constructor LL" << endl;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //Lvalue operator=
	node<T>* p;
	while (head != nullptr) {
		p = head->next;
		delete head;
		head = p;
	}
	p = L.head;
	while (p != nullptr) {
		push_back(p->value);
		p = p->next;
	}
	cout << "Copy Assignment LL" << endl;

}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
	node<T>* p;
	while (head != nullptr) {
		p = head->next;
		delete head;
		head = p;
	}
	head = L.head;
	tail = L.head;
	L.head = nullptr;
	L.tail = nullptr;

	cout << "Move Assignment LL" << endl;
}


template <class T> void linked_list<T>::push_front(T t) {
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }
	else {
		p->next = head;
		head->previous = p;
		head = p;
	}
}

template <class T> void linked_list<T>::push_back(T t)
{
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }

	else {
		p->previous = tail;
		tail->next = p;
		tail = p;
	}
}

template <class T> bool linked_list<T>::operator==(const linked_list<T>& L) const {
	int n1 = 0, n2 = 0;
	node<T>* p;
	p = head;
	while (p != nullptr) {
		p = p->next;
		n1++;
	}
	p = L.head;
	while (p != nullptr) {
		p = p->next;
		n2++;
	}
	if (n1 != n2) return false;
	node<T>* p1 = head, * p2 = L.head;

	while (p1 != nullptr) {
		if (!(p1->value == p2->value)) { cout << "operator== LL" << endl; return false; }
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "operator== LL" << endl;
	return true;
}


template <typename T> class Node { //Your T has to support either int or float
public:
	T* pValue; //pValue is a pointer to an object of type T
	Node<T>* row_next;//Points to the next node in the same row
	Node<T>* col_next;//Points to the nexe node in the same col
	Node() {}
	Node(T v) { pValue = new T(v); }
};

template <typename T> class Ring2D {
public:
	Node<T>* head;//Points to the node at first row and first column
	T* pValue;

	Ring2D() {};

	//Implement the following functions:
	Ring2D(const initializer_list< initializer_list<T>>& I); //nested initializer_list; will explain in class 
	/*
	For example, {{1, 2, 3, 4} , {5, 6, 7, 8},  {9, 10, 11, 12}}: 3 rows and 4 columns; first row: pointers to 1 2 3 4;
	second row: pointers to 5 6 7 8; third row: pointers to 9 10 11 12
	*/

	~Ring2D();//destructor; 
	Ring2D(const Ring2D<T>& R);//copy constructor

	void operator=(const Ring2D<T>& R);//Lvalue operator=; i.e., copy assignment

	Ring2D(Ring2D<T>&& R);//move constructor
	void operator=(Ring2D<T>&& R);//Rvalue operator=; i.e.,move assignment
	Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D

	bool operator==(const Ring2D<T>& R) const;
};

template <class T> bool Ring2D<T>::operator==(const Ring2D<T>& R) const {
	//template <class T> bool Ring2D<T>::operator==(const Ring2D<T> & R) const {
	if (!head && !R.head) { cout << "Operator== Ring2D" << endl; return true; }
	if (!head && R.head) { cout << "Operator== Ring2D" << endl; return false; }
	if (head && !R.head) { cout << "Operator== Ring2D" << endl; return false; }
	int r{ 1 }, c{ 1 };
	Node<T>* sp1, * sp2, * sp3, * sp4;
	sp1 = R.head;
	while (sp1->row_next != R.head) { c++; sp1 = sp1->row_next; }
	sp1 = R.head;
	while (sp1->col_next != R.head) { r++; sp1 = sp1->col_next; }

	int r1{ 1 }, c1{ 1 };
	//shared_ptr<Node<T>> sp1, sp2;
	sp1 = head;
	while (sp1->row_next != head) { c1++; sp1 = sp1->row_next; }
	sp1 = head;
	while (sp1->col_next != head) { r1++; sp1 = sp1->col_next; }

	if (r != r1 || c != c1) return false;

	sp1 = R.head;
	sp3 = head;
	for (int i = 0; i < r; i++) {
		sp2 = sp1->col_next;
		sp4 = sp3->col_next;
		for (int j = 0; j < c; j++) {
			if (!(*sp1->pValue == *sp3->pValue)) return false;
			sp1 = sp1->row_next;
			sp3 = sp3->row_next;
		}
		sp1 = sp2;
		sp3 = sp4;
	}

	cout << "Operator== Ring2D" << endl;
	return true;
}



template <class T> void Ring2D<T>::operator=(Ring2D<T>&& R) {//;//Rvalue operator=; move assignment
	if (head) {
		Node<T>* p1 = head, * p2 = head->col_next;
		Node<T>* p3 = p1->row_next;
		while (p3 != p1) {
			Node<T>* p4 = p3->row_next;
			delete p3->pValue;
			delete p3;
			p3 = p4;
		}
		delete p1->pValue;
		delete p1;
		p1 = p2;
		while (p1 != head) {
			p2 = p1->col_next;
			p3 = p1->row_next;
			while (p3 != p1) {
				Node<T>* p4 = p3->row_next;
				delete p3->pValue;
				delete p3;
				p3 = p4;
			}
			delete p1->pValue;
			delete p1;
			p1 = p2;
		}
	}
	head = R.head;
	R.head = nullptr;
	cout << "Move Assignment Ring2D" << endl;
}

template<class T> Ring2D<T>::Ring2D(Ring2D<T>&& R) {//move constructor
	head = R.head;
	R.head = nullptr;

	cout << "Move Constructor Ring2D" << endl;
}

template <class T> Ring2D<T> Ring2D<T>::ThreeTimes() {//ThreeTimes;
	
	auto temp{ *this };
	int r{ 1 }, c{ 1 };
	Node<T>* sp1, * sp2;
	sp1 = head;
	while (sp1->row_next != head) { c++; sp1 = sp1->row_next; }
	sp1 = head;
	while (sp1->col_next != head) { r++; sp1 = sp1->col_next; }

	sp1 = temp.head;
	for (int i = 0; i < r; i++) {
		sp2 = sp1->col_next;
		for (int j = 0; j < c; j++) {
			*sp1->pValue *= 3;
			sp1 = sp1->row_next;
		}
		sp1 = sp2;
	}

	cout << "ThreeTimes Ring2D" << endl;
	return temp;
}



template <class T> Ring2D<T>::~Ring2D() {//;//destructor

	if (!head) {
		cout << "Destructor Ring2D" << endl;
		return;
	}
	Node<T>* p1 = head, * p2 = head->col_next;
	Node<T>* p3 = p1->row_next;
	while (p3 != p1) {
		Node<T>* p4 = p3->row_next;
		delete p3->pValue;
		delete p3;
		p3 = p4;
	}
	delete p1->pValue;
	delete p1;
	p1 = p2;
	while (p1 != head) {
		p2 = p1->col_next;
		p3 = p1->row_next;
		while (p3 != p1) {
			Node<T>* p4 = p3->row_next;
			delete p3->pValue;
			delete p3;
			p3 = p4;
		}
		delete p1->pValue;
		delete p1;
		p1 = p2;
	}

	cout << "Destructor Ring2D" << endl;
}


template <class T> void Ring2D<T>::operator=(const Ring2D<T>& R) {//;//Lvalue operator=; copy assignment
	if (head) {
		Node<T>* p1 = head, * p2 = head->col_next;
		Node<T>* p3 = p1->row_next;
		while (p3 != p1) {
			Node<T>* p4 = p3->row_next;
			delete p3->pValue;
			delete p3;
			p3 = p4;
		}
		delete p1->pValue;
		delete p1;
		p1 = p2;
		while (p1 != head) {
			p2 = p1->col_next;
			p3 = p1->row_next;
			while (p3 != p1) {
				Node<T>* p4 = p3->row_next;
				delete p3->pValue;
				delete p3;
				p3 = p4;
			}
			delete p1->pValue;
			delete p1;
			p1 = p2;
		}
	}
	if (!R.head) {
		cout << "Copy Assignment Ring2D" << endl;
		return;
	}
	head = nullptr;
	int r{ 1 }, c{ 1 };
	Node<T>* sp0;
	sp0 = R.head;
	while (sp0->row_next != R.head) { c++; sp0 = sp0->row_next; }
	sp0 = R.head;
	while (sp0->col_next != R.head) { r++; sp0 = sp0->col_next; }
	sp0 = nullptr;
	Node<T>* sp1{ nullptr }, * sp2{ nullptr }, * sp3{ nullptr }, * pLast{ nullptr };
	for (int j = 0; j < c; j++) {
		sp2 = new Node<T>();
		sp2->row_next = sp1;
		if (j == 0) pLast = sp2;
		sp1 = sp2;
	}
	pLast->row_next = sp1;
	head = sp1;

	sp0 = sp1;
	for (int i = 0; i < r - 1; i++) {
		sp1 = nullptr;
		for (int j = 0; j < c; j++) {
			sp2 = new Node<T>();
			sp2->row_next = sp1;
			if (j == 0) pLast = sp2;
			sp1 = sp2;
		}
		pLast->row_next = sp1;

		sp2 = sp0;
		sp3 = sp1;
		for (int j = 0; j < c; j++) {
			sp2->col_next = sp3;
			sp2 = sp2->row_next;
			sp3 = sp3->row_next;
		}
		sp0 = sp1;
	}
	sp2 = head;
	sp3 = sp0;
	for (int j = 0; j < c; j++) {
		sp3->col_next = sp2;
		sp2 = sp2->row_next;
		sp3 = sp3->row_next;
	}

	sp0 = head;
	sp1 = R.head;
	for (int i = 0; i < r; i++) {
		sp2 = sp0->col_next;
		sp3 = sp1->col_next;
		for (int j = 0; j < c; j++) {
			sp0->pValue = new T(*sp1->pValue);
			sp0 = sp0->row_next;
			sp1 = sp1->row_next;
		}
		sp0 = sp2;
		sp1 = sp3;
	}

	cout << "Copy Assignment Ring2D" << endl;
}


template<class T> Ring2D<T>::Ring2D(const Ring2D<T>& R) {//copy constructor
	head = nullptr;
	if (!R.head) {
		cout << "Copy Constructor Ring2D" << endl;
		return;
	}
	int r{ 1 }, c{ 1 };
	Node<T>* sp0;
	sp0 = R.head;
	while (sp0->row_next != R.head) { c++; sp0 = sp0->row_next; }
	sp0 = R.head;
	while (sp0->col_next != R.head) { r++; sp0 = sp0->col_next; }
	sp0 = nullptr;
	Node<T>* sp1{ nullptr }, * sp2{ nullptr }, * sp3{ nullptr }, * pLast{ nullptr };
	for (int j = 0; j < c; j++) {
		sp2 = new Node<T>();
		sp2->row_next = sp1;
		if (j == 0) pLast = sp2;
		sp1 = sp2;
	}
	pLast->row_next = sp1;
	head = sp1;

	sp0 = sp1;
	for (int i = 0; i < r - 1; i++) {
		sp1 = nullptr;
		for (int j = 0; j < c; j++) {
			sp2 = new Node<T>();
			sp2->row_next = sp1;
			if (j == 0) pLast = sp2;
			sp1 = sp2;
		}
		pLast->row_next = sp1;

		sp2 = sp0;
		sp3 = sp1;
		for (int j = 0; j < c; j++) {
			sp2->col_next = sp3;
			sp2 = sp2->row_next;
			sp3 = sp3->row_next;
		}
		sp0 = sp1;
	}
	sp2 = head;
	sp3 = sp0;
	for (int j = 0; j < c; j++) {
		sp3->col_next = sp2;
		sp2 = sp2->row_next;
		sp3 = sp3->row_next;
	}

	sp0 = head;
	sp1 = R.head;
	for (int i = 0; i < r; i++) {
		sp2 = sp0->col_next;
		sp3 = sp1->col_next;
		for (int j = 0; j < c; j++) {
			sp0->pValue = new T(*sp1->pValue);
			sp0 = sp0->row_next;
			sp1 = sp1->row_next;
		}
		sp0 = sp2;
		sp1 = sp3;
	}
	cout << "Copy Constructor Ring2D" << endl;
}

template <class T> Ring2D<T>::Ring2D(const initializer_list< initializer_list<T>>& I) {

	int r{ int(I.size()) }, c{ int((*I.begin()).size()) };
	Node<T>* sp0{ nullptr }, * sp1{ nullptr }, * sp2{ nullptr }, * sp3{ nullptr }, * pLast{ nullptr };
	for (int j = 0; j < c; j++) {
		sp2 = new Node<T>();
		sp2->row_next = sp1;
		if (j == 0) pLast = sp2;
		sp1 = sp2;
	}
	pLast->row_next = sp1;
	head = sp1;

	sp0 = sp1;
	for (int i = 0; i < r - 1; i++) {
		sp1 = nullptr;
		for (int j = 0; j < c; j++) {
			sp2 = new Node<T>();
			sp2->row_next = sp1;
			if (j == 0) pLast = sp2;
			sp1 = sp2;
		}
		pLast->row_next = sp1;

		sp2 = sp0;
		sp3 = sp1;
		for (int j = 0; j < c; j++) {
			sp2->col_next = sp3;
			sp2 = sp2->row_next;
			sp3 = sp3->row_next;
		}
		sp0 = sp1;
	}
	sp2 = head;
	sp3 = sp0;
	for (int j = 0; j < c; j++) {
		sp3->col_next = sp2;
		sp2 = sp2->row_next;
		sp3 = sp3->row_next;
	}
	sp1 = head;


	auto p1{ I.begin() };
	for (int i = 0; i < r; i++) {
		sp2 = sp1->col_next;
		auto p2{ p1->begin() };
		for (int j = 0; j < c; j++) {
			sp1->pValue = new T(*p2);
			//p++;
			sp1 = sp1->row_next;
			p2++;
		}
		sp1 = sp2;
		p1++;
	}

	cout << "initializer_list Ring2D" << endl;
}


template<class T> ostream& operator<<(ostream& str, const Ring2D<T>& R);



int main() {


	Ring2D<int> R1{ {1, 2, 3, 4},  {5, 6, 7, 8},  {9, 10, 11, 12} };//initializer_list
	cout << R1 << endl << endl;
	Ring2D<int> R2{ R1 };
	cout << R2 << endl;

	Ring2D<int> R3;
	R3 = R1;
	cout << R3 << endl;

	Ring2D<int> R4;
	R4 = R1.ThreeTimes();
	cout << R4 << endl;

	Ring2D<linked_list<ThreeD<int>>> R5{ {{{3,4,5},{7,1,4},{6,7,3}},{{8,4,2},{8,8,2}}},
		{{{9,5,4},{10,3,2},{7,9,1},{2,2,3}}, { {5,4,8 },{4,2,16  }, {7, 8, 4} } } };
	cout << R5 << endl;

	Ring2D<linked_list<ThreeD<int>>> R6{ {{{5,3,4,},{14,2,1},{6,7,3}},{{8,2,4},{8,4,4}}},
		{{{9,4,5},{10,3,2},{7,3,3},{2,3,2}}, { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
	cout << R6 << endl;

	if (R5 == R6) cout << "EQUAL" << endl;
	else cout << "NOT EQUQL" << endl;
	Ring2D<linked_list<ThreeD<int>>>* p1 = new Ring2D<linked_list<ThreeD<int>>>
	{ {{{5,3,4,},{14,2,1},{6,7,3}},{{8,2,4},{8,4,4}}},
		{{{9,4,5},{10,3,2},{7,3,3},{2,3,2}}, { {4, 5,8 },{8,2,8  }, {2, 16, 7} } } };
	cout << *p1 << endl;
	delete p1;
	return 0;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
	str << "[ ";
	node<T>* p1 = L.head;
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << " ]";
	return str;
}

template<class T> ostream& operator<<(ostream& str, const Ring2D<T>& R) {
	if (!R.head) return str;
	int r{ 1 }, c{ 1 };
	Node<T>* sp1, * sp2;
	sp1 = R.head;
	while (sp1->row_next != R.head) { c++; sp1 = sp1->row_next; }
	sp1 = R.head;
	while (sp1->col_next != R.head) { r++; sp1 = sp1->col_next; }
	sp1 = R.head;
	for (int i = 0; i < r; i++) {
		str << "{ ";
		sp2 = sp1->col_next;
		for (int j = 0; j < c; j++) {
			str << *sp1->pValue << " ";
			sp1 = sp1->row_next;
		}
		str << "}";
		sp1 = sp2;
		str << endl;
	}
	return str;
}


//Sample screenshot
/*
initializer_list Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }


Copy Constructor Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }

Copy Assignment Ring2D
{ 1 2 3 4 }
{ 5 6 7 8 }
{ 9 10 11 12 }

Copy Constructor Ring2D
ThreeTimes Ring2D
Move Constructor Ring2D
Destructor Ring2D
Move Assignment Ring2D
Destructor Ring2D
{ 3 6 9 12 }
{ 15 18 21 24 }
{ 27 30 33 36 }

initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [ (3, 4, 5) (7, 1, 4) (6, 7, 3)  ] [ (8, 4, 2) (8, 8, 2)  ] }
{ [ (9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3)  ] [ (5, 4, 8) (4, 2, 16) (7, 8, 4)  ] }

initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [ (5, 3, 4) (14, 2, 1) (6, 7, 3)  ] [ (8, 2, 4) (8, 4, 4)  ] }
{ [ (9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2)  ] [ (4, 5, 8) (8, 2, 8) (2, 16, 7)  ] }

operator== LL
operator== LL
operator== LL
operator== LL
Operator== Ring2D
EQUAL
initializer_list LL
initializer_list LL
initializer_list LL
initializer_list LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
Copy Constructor LL
initializer_list Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
{ [ (5, 3, 4) (14, 2, 1) (6, 7, 3)  ] [ (8, 2, 4) (8, 4, 4)  ] }
{ [ (9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2)  ] [ (4, 5, 8) (8, 2, 8) (2, 16, 7)  ] }

Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
*/
