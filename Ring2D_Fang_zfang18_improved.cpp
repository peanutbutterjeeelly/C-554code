//HW4 due: Thursday (10/8/2020).
//zfang18 337310566
#include <iostream>
#include <list>
#include <string>

using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() :ht(0), wid(0), dep(0) {}
	ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
	T getVol() const { return ht * wid * dep; }
	bool operator==(const ThreeD<T>& t) const { return getVol() == t.getVol(); }
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

template <class T> class linked_list {
public:
	node<T>* head;
	node<T>* tail;
	linked_list() { head = tail = nullptr; }
	linked_list(const initializer_list<T>& V);
	void push_front(T t);//The implementation is given below.
	void push_back(T t);//The implementation is given below.
	bool operator==(const linked_list<T>& L) const;

	linked_list(const linked_list<T>& L); //copy constructor
	linked_list(linked_list<T>&& L); //move constructor
	~linked_list();//destructor
	void operator=(const linked_list<T>& L);//Lvalue operator= ; i.e., copy assignment
	void operator=(linked_list<T>&& L);//Rvalue operator= ; i.e., move assignment

};
template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
	//Your code
	auto p1{ V.end() - 1 };
	while (p1 != V.begin() - 1) {
		node<T>* p2 = new node<T>(*p1);
		p2->next = head;
		head = p2;
		if (head->next != nullptr) head->next->previous = head;
		--p1;
	}
	node<T>* p3 = head;
	while (p3) {
		if (p3->next == nullptr)tail = p3;
		p3 = p3->next;
	}


	cout << "initializer_list LL" << endl;
}

template <class T> linked_list<T>::~linked_list() {  //destructor										
	node<T>* p1 = head;
	node<T>* p2;
	while (p1) {
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
	cout << "Destructor LL" << endl;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
	//Your code
	node<T>* p1 = L.tail;
	node<T>* p2;
	while (p1) {
		node<T>* p2 = new node<T>(*p1);
		p1 = p1->previous;
		p2->next = head;
		head = p2;
		if (head->next != nullptr) head->next->previous = head;
	}
	node<T>* p3 = head;
	while (p3) {
		if (p3->next == nullptr)tail = p3;
		p3 = p3->next;
	}

	cout << "Copy Constructor LL" << endl;
}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
	//Your code

	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor LL" << endl;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //Lvalue operator=
	//Your code
	node<T>* p1 = head;
	node<T>* p2;
	while (p1) {
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
	head = tail = nullptr;//
	node<T>* p3 = L.head;
	node<T>* p4;
	while (p3) {
		p4 = new node<T>;
		p4->next = head;
		head = p4;
		if (head->next != nullptr) head->next->previous = head;
		p3 = p3->next;
	}
	p3 = L.head;
	p4 = head;
	while (p3) {
		p4->value = p3->value;
		p3 = p3->next;
		p4 = p4->next;
	}
	p3 = head;
	while (p3) {
		if (!p3->next) {
			tail = p3;
			delete p3->next;
			break;
		}
		p3 = p3->next;
	}

	cout << "Copy Assignment LL" << endl;
}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
	//Your code
	while (head) {
		node<T>* p3{ head->next };
		delete head;
		head = p3;
	}
	head = L.head;
	L.head = nullptr;
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
	//Your code
	//Two linked lists are equal if they have same number of nodes, and each pair of corresponding nodes have equal values.
	int countthis = 0;
	int countlist = 0;
	node<T>* p1 = head;
	node<T>* p2 = L.head;
	while (p1 != nullptr) {
		++countthis;
		p1 = p1->next;
	}
	while (p2 != nullptr) {
		++countlist;
		p2 = p2->next;
	}
	if (countthis != countlist) return false;
	else {
		p1 = head;
		p2 = L.head;
		while (p1 != nullptr) {
			if (!(p1->value == p2->value)) return false;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return true;
}







template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
	str << "[";
	node<T>* p = L.head;
	while (p) {
		str << p->value << " ";
		p = p->next;
	}
	str << "]";
	return str;
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
	//Your code
	//If you return in the middle of code, you also need to print the following message
	auto i = R.head;
	auto colcursor = R.head;
	auto rowcursor = R.head;
	auto THIS = head;
	auto this_rowcursor = head;
	auto this_colcursor = head;
	int this_rowsize = 0;
	int this_colsize = 0;
	int rowsize = 0;
	int colsize = 0;

	while (colcursor->col_next) {
		while (rowcursor->row_next) {
			++rowsize;
			rowcursor = rowcursor->row_next;
			if (rowcursor == colcursor) break;
		}
		++colsize;
		//cout << colsize;
		colcursor = colcursor->col_next;
		rowcursor = colcursor;
		if (rowcursor == i) break;
	}
	while (this_colcursor->col_next) {
		while (this_rowcursor->row_next) {
			++this_rowsize;
			this_rowcursor = this_rowcursor->row_next;
			if (this_rowcursor == this_colcursor) break;
		}
		++this_colsize;
		this_colcursor = this_colcursor->col_next;
		this_rowcursor = this_colcursor;
		if (this_rowcursor == THIS) break;
	}
	if (rowsize != this_rowsize || colsize != this_colsize) {
		return false;
		cout << "Operator== Ring2D" << endl;
	}
	else if (rowsize == this_rowsize && colsize == this_colsize) {
		auto i = R.head;
		auto colcursor = R.head;
		auto rowcursor = R.head;
		auto THIS = head;
		auto this_rowcursor = head;
		auto this_colcursor = head;
		while (this_colcursor->col_next) {
			while (this_rowcursor->row_next) {
				if (*(*this_rowcursor).pValue == *(*rowcursor).pValue) {//**
					this_rowcursor = this_rowcursor->row_next;
					rowcursor = rowcursor->row_next;
				}
				else {
					//cout << *(*this_rowcursor).pValue << *(*rowcursor).pValue;
					return false;
					cout << "Operator== Ring2D" << endl;
				}
				if (this_rowcursor == this_colcursor) break;
			}
			this_colcursor = this_colcursor->col_next;
			colcursor = colcursor->col_next;
			this_rowcursor = this_colcursor;
			rowcursor = colcursor;
			if (this_rowcursor == THIS) break;
		}
	}
	return true;
	cout << "Operator== Ring2D" << endl;

}



template <class T> void Ring2D<T>::operator=(Ring2D<T>&& R) {//;//Rvalue operator=; move assignment
	//Your code
	if (head) {
		Node<T>* colcursor = head->row_next;

		while (colcursor != head) {
			Node<T>* p1 = colcursor->row_next;
			delete colcursor->pValue;
			delete colcursor;
			colcursor = p1;

		}
		Node<T>* rowcursor = head->col_next;
		Node<T>* stoprow = head;
		Node<T>* stopcol = rowcursor;
		colcursor = rowcursor->row_next;
		while (rowcursor != stoprow) {

			while (colcursor != stopcol) {
				Node<T>* p2 = colcursor->row_next;
				delete colcursor->pValue;
				delete colcursor;
				colcursor = p2;
			}
			Node<T>* p3 = rowcursor->col_next;
			delete rowcursor->pValue;
			delete rowcursor;
			rowcursor = p3;
			stopcol = rowcursor;
			colcursor = rowcursor->row_next;
		}
		delete head->pValue;
		delete head;
	}
	head = R.head;
	R.head = nullptr;

	cout << "Move Assignment Ring2D" << endl;
}

template<class T> Ring2D<T>::Ring2D(Ring2D<T>&& R) {//;//move constructor
	//Your code
	head = R.head;
	R.head = nullptr;
	cout << "Move Constructor Ring2D" << endl;
}

template <class T> Ring2D<T> Ring2D<T>::ThreeTimes() {//ThreeTimes;
	//Your code
	Ring2D<T> temp = *this;
	Node<T>* i = temp.head;
	Node<T>* colcursor = temp.head;
	Node<T>* rowcursor = temp.head;
	while (colcursor) {
		while (rowcursor) {
			*(*rowcursor).pValue = 3 * (*(*rowcursor).pValue);
			//cout << *(*rowcursor).pValue << " ";
			rowcursor = rowcursor->row_next;
			if (rowcursor == colcursor) break;
		}
		colcursor = colcursor->col_next;
		rowcursor = colcursor;
		if (colcursor == i) break;
	}

	cout << "ThreeTimes Ring2D" << endl;
	return temp;
}



template <class T> Ring2D<T>::~Ring2D() {//;//destructor
	//Your code
	//If you return in the middle of your code, you also need to print the following message.
	if (head) {
		Node<T>* colcursor = head->row_next;

		while (colcursor != head) {
			Node<T>* p1 = colcursor->row_next;
			delete colcursor->pValue;
			delete colcursor;
			colcursor = p1;

		}
		Node<T>* rowcursor = head->col_next;
		Node<T>* stoprow = head;
		Node<T>* stopcol = rowcursor;
		colcursor = rowcursor->row_next;
		while (rowcursor != stoprow) {

			while (colcursor != stopcol) {
				Node<T>* p2 = colcursor->row_next;
				delete colcursor->pValue;
				delete colcursor;
				colcursor = p2;
			}
			Node<T>* p3 = rowcursor->col_next;
			delete rowcursor->pValue;
			delete rowcursor;
			rowcursor = p3;
			stopcol = rowcursor;
			colcursor = rowcursor->row_next;
		}
		delete head->pValue;
		delete head;
	}


	cout << "Destructor Ring2D" << endl;
}

template <class T> void Ring2D<T>::operator=(const Ring2D<T>& R) {//;//Lvalue operator=; copy assignment
	//Your code
	//If you return in the middle of your code, you also need to print the following message.
	Node<T>* i = head;
	Node<T>* colcursor = head;
	Node<T>* rowcursor = head;
	Node<T>* saverowcursor = head;
	Node<T>* savecolcursor = head;
	Node<T>* HEAD = new Node<T>;//to find head and tail in current row
	Node<T>* TAIL = new Node<T>;
	Node<T>* prow = new Node<T>;
	Node<T>* pcol = new Node<T>;
	Node<T>* colhead = new Node<T>;
	Node<T>* coltail = new Node<T>;
	Node<T>* newhead = R.head;
	Node<T>* newcolcursor = R.head;
	Node<T>* newrowcursor = R.head;
	int colsize = 0;
	int rowsize = 0;
	if (head != nullptr) {
		while (head->col_next) {
			++colsize;
			colcursor = colcursor->col_next;
			if (colcursor == head) break;
		}
		while (head->col_next) {
			++rowsize;
			rowcursor = rowcursor->row_next;
			if (rowcursor == head) break;
		}

		for (int i = 0; i < colsize; ++i) {
			//if (i != colsize - 1) {
			//	savecolcursor = colcursor->col_next;
			//	cout << "loop " << i << endl;
			//	cout << "saved first colcurse" << *(*savecolcursor).pValue << endl;
			//}
			for (int j = 0; j < rowsize; ++j) {

				if (i != 0 && j == 0) {
					rowcursor = savecolcursor;

				}
				if (i != colsize - 1 && j == 0) {
					savecolcursor = savecolcursor->col_next;
				}
				if (j != rowsize - 1) {

					saverowcursor = rowcursor->row_next;
				}
				//cout << *(*rowcursor).pValue;
				delete rowcursor;
				if (j == rowsize - 1) {
					break;
				}
				if (j != rowsize - 1) {
					rowcursor = saverowcursor;
				}
			}

		}
		head = nullptr;
	}
	//cout new row/ col number
	int num_newrow = 0;
	int num_newcol = 0;

	while (newcolcursor) {
		++num_newcol;
		newcolcursor = newcolcursor->col_next;
		if (newcolcursor == newhead) break;
	}
	while (newrowcursor) {
		++num_newrow;
		newrowcursor = newrowcursor->row_next;
		if (newrowcursor == newhead) break;
	}
	//start to build new nodes structure
	for (int i = 0; i < num_newcol; i++) {
		for (int j = 0; j < num_newrow; j++) {
			Node<T>* newnode = new Node<T>(0);//lazy initialize to 0, later assign value
			if (i == 0 && j == 0) {//the top left position
				head = newnode;
				pcol = newnode;
				prow = newnode;
				colhead = newnode;
			}
			if (i == 0) {//if this is the first line, we dont have next line yet, so all col_next should be initialized to point null
				newnode->col_next = nullptr;
			}
			if (i != 0) {//when this is not the first line
				pcol->col_next = newnode;//previous row point to the new node created
				pcol = pcol->row_next;//move this cursor to the next in row
			}
			if (j == 0) {//first element of each row
				HEAD = newnode;
				prow = newnode;
			}
			if (j == (num_newrow - 1)) {
				TAIL = newnode;
			}
			if (j != 0) {
				prow->row_next = newnode;
				prow = newnode;
			}
			if (i == (num_newcol - 1)) {
				newnode->col_next = colhead;
				colhead = colhead->row_next;
			}
		}
		if (i != 0) {
			pcol = head->col_next;
		}
		TAIL->row_next = HEAD; //connect head and tail within a row
	}
	Node<T>* ii = head;
	Node<T>* ccolcursor = head;
	Node<T>* rrowcursor = head;
	//cout << *(*head).pValue<<ed;
	while (newcolcursor->col_next) {//assign value to the nodes created
		while (newrowcursor->row_next) {
			//if (rrowcursor == nullptr) break;
			*rrowcursor->pValue = *newrowcursor->pValue;
			//cout << *(*rrowcursor).pValue;
			rrowcursor = rrowcursor->row_next;
			newrowcursor = newrowcursor->row_next;
			if (rrowcursor == ccolcursor) break;
		}
		//if (colcursor == nullptr) break;
		ccolcursor = ccolcursor->col_next;
		newcolcursor = newcolcursor->col_next;
		rrowcursor = ccolcursor;
		newrowcursor = newcolcursor;
		if (rrowcursor == ii) break;
	}
	cout << "Copy Assignment Ring2D" << endl;
}


template<class T> Ring2D<T>::Ring2D(const Ring2D<T>& R) {//copy constructor
	//Your code
	//If you return in the middle of your code, you also need to print the following message.
	auto i = R.head;
	auto colcursor = R.head;
	auto rowcursor = R.head;
	Node<T>* HEAD = new Node<T>;//to find head and tail in current row
	Node<T>* TAIL = new Node<T>;
	Node<T>* prow = new Node<T>;
	Node<T>* pcol = new Node<T>;
	Node<T>* colhead = new Node<T>;
	Node<T>* coltail = new Node<T>;
	int count_nodes = 0;
	int colsize = 0;
	while (colcursor->col_next) {//count rowsize and colsize, to make sure the size we gonna build
		while (rowcursor->row_next) {
			++count_nodes;
			rowcursor = rowcursor->row_next;
			if (rowcursor == colcursor) break;
		}
		//cout << colsize;
		++colsize;
		colcursor = colcursor->col_next;
		rowcursor = colcursor;
		if (rowcursor == i) break;
	}
	int rowsize = count_nodes / colsize;
	for (int i = 0; i < colsize; i++) {
		for (int j = 0; j < rowsize; j++) {
			Node<T>* newnode = new Node<T>(0);//lazy initialize to 0, later assign value
			if (i == 0 && j == 0) {//the top left position
				head = newnode;
				pcol = newnode;
				prow = newnode;
				colhead = newnode;
			}
			if (i == 0) {//if this is the first line, we dont have next line yet, so all col_next should be initialized to point null
				newnode->col_next = nullptr;
			}
			if (i != 0) {//when this is not the first line
				pcol->col_next = newnode;//previous row point to the new node created
				pcol = pcol->row_next;//move this cursor to the next in row
			}
			if (j == 0) {//first element of each row
				HEAD = newnode;
				prow = newnode;
			}
			if (j == (rowsize - 1)) {
				TAIL = newnode;
			}
			if (j != 0) {
				prow->row_next = newnode;
				prow = newnode;
			}
			if (i == (colsize - 1)) {
				newnode->col_next = colhead;
				colhead = colhead->row_next;
			}
		}
		if (i != 0) {
			pcol = head->col_next;
		}
		TAIL->row_next = HEAD; //connect head and tail within a row
	}
	//auto i = R.head;//reset pos of cursor
	auto Colcursor = R.head;
	auto Rowcursor = R.head;
	auto THIS = head;
	auto this_rowcursor = head;
	auto this_colcursor = head;
	while (this_colcursor->col_next) {//assign value to the nodes created
		while (this_rowcursor->row_next) {

			*(*this_rowcursor).pValue = *(*Rowcursor).pValue;
			//cout << *(*this_rowcursor).pValue;
			this_rowcursor = this_rowcursor->row_next;
			Rowcursor = Rowcursor->row_next;
			if (this_rowcursor == this_colcursor) break;
		}
		this_colcursor = this_colcursor->col_next;
		Colcursor = Colcursor->col_next;
		this_rowcursor = this_colcursor;
		Rowcursor = Colcursor;
		if (this_rowcursor == THIS) break;
	}
	cout << "Copy Constructor Ring2D" << endl;
}

template<class T> ostream& operator<<(ostream& str, const Ring2D<T>& R) {

	auto i = R.head;
	//i = i->col_next->col_next->col_next;
	//str << *(*i).pValue;
	auto rowcursor = R.head;
	auto colcursor = R.head;
	while (colcursor->col_next) {
		str << "{";
		while (rowcursor->row_next) {
			str << " ";
			str << *(rowcursor)->pValue;
			rowcursor = rowcursor->row_next;
			if (rowcursor == colcursor) break;
		}
		str << " ";
		str << "}" << endl;
		colcursor = colcursor->col_next;
		rowcursor = colcursor;
		if (rowcursor == i) break;
	}
	return str;
}


template <class T> Ring2D<T>::Ring2D(const initializer_list< initializer_list<T>>& I) {

	int row_num = I.size();

	if (row_num != 0) {
		Node<T>* HEAD = new Node<T>;//to find head and tail in current row
		Node<T>* TAIL = new Node<T>;
		Node<T>* prow = new Node<T>;
		Node<T>* pcol = new Node<T>;
		Node<T>* savefirstofrow = new Node<T>;
		Node<T>* colhead = new Node<T>;
		Node<T>* coltail = new Node<T>;
		for (auto i = I.begin(); i != I.end(); i++) {
			for (auto j = (*i).begin(); j != (*i).end(); j++) {
				Node<T>* newnode = new Node<T>(*j);
				if (j == (*i).begin() && i == I.begin()) { //when it's top left
					head = newnode;  //head point to this top left
					pcol = newnode; //rolling pcol pointer point to the first node created
					prow = newnode; //also prow
					colhead = newnode;
				}//head of all
				if (i == I.begin()) {
					newnode->col_next = nullptr;//while it is first line, all the new node should point col_next to nullptr
				}
				if (i != I.begin()) {
					pcol->col_next = newnode;//while it is not the first line, pcol saved top left, then below is 
					pcol = pcol->row_next;
				}
				if (j == (*i).begin()) { //when it's 
					HEAD = newnode;
					prow = newnode;

				}//head of this row
				if (j == (*i).end() - 1) {
					TAIL = newnode;
				} //tail of this row
				if (j != (*i).begin()) {
					prow->row_next = newnode;
					prow = newnode;
				}
				if (i == I.end() - 1) {//when come to the last row, all of the elements col->next should point to  first row correspondingly
					newnode->col_next = colhead;
					colhead = colhead->row_next;//only output one line would cause error
				}

			}
			if (i != I.begin()) {
				pcol = head->col_next;
			}
			TAIL->row_next = HEAD; //connect head and tail within a row


		}

		//Your code
	}
	cout << "initializer_list Ring2D" << endl;


}




int main() {


	Ring2D<int> R1{ {1, 2, 3, 4},  {5, 6, 7, 8},  {9, 10, 11, 2} };//initializer_list
	cout << R1 << endl << endl;
	Ring2D<int> R2{ R1 };
	cout << R2 << endl;
	Ring2D<int> R3;
	R3 = R1;
	cout << R3 << endl;
	Ring2D<int> R4{ {1, 2, 3, 4},  {5, 6, 7, 8},  {9, 10, 11, 120} };
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
{ [(3, 4, 5) (7, 1, 4) (6, 7, 3) ] [(8, 4, 2) (8, 8, 2) ] }
{ [(9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3) ] [(5, 4, 8) (4, 2, 16) (7, 8, 4) ] }

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
{ [(5, 3, 4) (14, 2, 1) (6, 7, 3) ] [(8, 2, 4) (8, 4, 4) ] }
{ [(9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2) ] [(4, 5, 8) (8, 2, 8) (2, 16, 7) ] }

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
{ [(5, 3, 4) (14, 2, 1) (6, 7, 3) ] [(8, 2, 4) (8, 4, 4) ] }
{ [(9, 4, 5) (10, 3, 2) (7, 3, 3) (2, 3, 2) ] [(4, 5, 8) (8, 2, 8) (2, 16, 7) ] }

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
Destructor LL
Destructor LL
Destructor LL
Destructor LL
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
Destructor Ring2D
	*/
}
