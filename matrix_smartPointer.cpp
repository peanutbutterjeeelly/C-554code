#include <iostream>
#include <vector>
#include <memory>
#include <tuple>
using namespace std;

class triple {
public:
	int value;
	int row;
	int col;
};

class node {
public:
	int value;
	int r_position;
	int c_position;
	shared_ptr<node> r_next;
	shared_ptr<node> c_next;
	node() { value = -9999; r_position = c_position = -1; }
	node(int v, int r, int c) { value = v; r_position = r; c_position = c; }

};
class matrix {
public:
	int num_rows;
	int num_cols;
	vector<shared_ptr<node>> r_vec;
	vector<shared_ptr<node>> c_vec;

	matrix() {} //default constructor
	matrix(int r, int c);
	//Constructor: to create a matrix of r rows, c cols


	//**********************//
	//You need to implement all the following member function plus overloaded operator<< for "cout << M <<endl; where M is a matrix object.
	void add_node(int v, int r, int c);
	//Create a new node with value v at row r and col c.
	//If there already exist an element at this position, then just update the node
	//value at this position to v, and do not create a new node.

	matrix(int r, int c, int n, int k);
	//Constructor: To create a matrix of r rows, c cols, n nodes, with values randomly in -(k-1) ... (k-1);

	matrix operator+(const matrix& M);//matrix addition
	matrix operator*(const matrix& M); //matrix multiplication

	matrix(const initializer_list < triple>& I);//initializer_list
	//First triple is (-1, num_rows, num_cols), where -1 will be ignored, and all other triples are nodes (value, r_position, c_position).

	matrix(const matrix& M);//copy constructor
	void operator=(const matrix& M);//copy assignment
	~matrix();//destructor
	matrix(matrix&& M);//move constructor
	void operator=(matrix&& M);//move assignment
};

void matrix::operator=(matrix&& M) {//;//move assignment
	r_vec.clear();
	c_vec.clear();
	num_rows = M.num_rows;
	num_cols = M.num_cols;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	r_vec = M.r_vec;
	c_vec = M.c_vec;
	M.r_vec.clear();
	M.c_vec.clear();
	cout << "Move Assignment" << endl;
}

matrix::matrix(matrix&& M) : matrix(M.num_rows, M.num_cols) {//move constructor
	r_vec = M.r_vec;
	c_vec = M.c_vec;
	M.r_vec.clear();
	M.c_vec.clear();
	cout << "Move Constructor" << endl;
}

matrix::~matrix() {//destructor
	r_vec.clear();
	c_vec.clear();
	cout << "Destructor" << endl;
}

matrix::matrix(const matrix& M) : matrix(M.num_rows, M.num_cols) {//;//copy constructor
	for (auto i : M.r_vec) {
		while (i) {
			add_node(i->value, i->r_position, i->c_position);
			i = i->r_next;
		}
	}
	cout << "Copy Constructor" << endl;
}

void matrix::operator=(const matrix& M) {//;//copy assignment
	r_vec.clear();
	c_vec.clear();
	num_rows = M.num_rows;
	num_cols = M.num_cols;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	for (auto i : M.r_vec) {
		while (i) {
			add_node(i->value, i->r_position, i->c_position);
			i = i->r_next;
		}
	}
	cout << "Copy Assignment" << endl;
}



matrix::matrix(const initializer_list < triple>& I) : matrix((*I.begin()).row, (*I.begin()).col) {
	auto p = I.begin() + 1;
	while (p != I.end()) {
		add_node(p->value, p->row, p->col);
		++p;
	}
	cout << "initializer_list" << endl;
}

matrix::matrix(int r, int c) {
	num_rows = r;
	num_cols = c;
	r_vec.resize(r);
	c_vec.resize(c);
}


matrix::matrix(int r, int c, int n, int k) {
	num_rows = r;
	num_cols = c;
	r_vec.resize(r);
	c_vec.resize(c);
	for (int i = 0; i < n; i++) {
		int vv = rand() % (2 * k - 1) - (k - 1);
		int rr = rand() % r;
		int cc = rand() % c;
		cout << endl;
		add_node(vv, rr, cc);
	}
}

void matrix::add_node(int v, int r, int c) {
	shared_ptr<node> pp = make_shared<node>(v, r, c);

	{
		shared_ptr<node> p1 = r_vec[r];

		if (!p1) {
			if (v == 0) { pp.reset(); return; }
			r_vec[r] = pp;
		}
		else if (c <= p1->c_position) {
			if (c == p1->c_position) { 
				if (v != 0) {
					p1->value = v;  pp.reset();
					return;
				}
				else {//deleted the existing node
					r_vec[r]= r_vec[r]->r_next;
					shared_ptr<node> p2{ c_vec[c] };
					if (p2->r_position == r) {
						c_vec[c] = c_vec[c]->c_next;
						pp.reset();
						return;
					}
					while (p2->c_next->r_position != r) { p2 = p2->c_next; }
					p2->c_next = p2->c_next->c_next;
					pp.reset();
					return;

				}
			}
			else {
				pp->r_next = r_vec[r];
				r_vec[r] = pp;
			}
		}
		else {
			shared_ptr<node> p2 = p1->r_next;
			while (p2 != nullptr && c > p2->c_position) { p1 = p2; p2 = p2->r_next; }
			if (p2 == nullptr) { p1->r_next = pp; }
			else if (c == p2->c_position) { 
				if (v != 0) {
					p2->value = v;   pp.reset(); return;
				}
				else {
					p1->r_next = p2->r_next;
					shared_ptr<node> p3;
					p3 = c_vec[c];
					if (p3->r_position == r) { c_vec[c] = c_vec[c]->c_next; pp.reset(); return; }
					while (p3->c_next->r_position != r) { p3 = p3->c_next; }
					p3->c_next = p3->c_next->c_next;
					pp.reset();
					return;
				}
			}
			else if (c < p2->c_position) { p1->r_next = pp; pp->r_next = p2; }
		}
	}
	{
		shared_ptr<node> p1 = c_vec[c];
		if (!p1) {
			c_vec[c] = pp;
		}
		else if (r < p1->r_position) {

			pp->c_next = c_vec[c];
			c_vec[c] = pp;
		}
		else {
			shared_ptr<node> p2 = p1->c_next;
			while (p2 != nullptr && r > p2->r_position) { p1 = p2; p2 = p2->c_next; }
			if (p2 == nullptr) { p1->c_next = pp; }
			else if (r < p2->r_position) { p1->c_next = pp; pp->c_next = p2; }
		}
	}

}



matrix matrix::operator+(const matrix& M) {

	matrix temp(num_rows, num_cols);
	//if (size != V.size) { cout << "  Error!" << endl; return temp; }
	for (int i = 0; i < num_rows; i++) {
		shared_ptr<node> p1 = r_vec[i], p2 = M.r_vec[i];
		while (p1 != nullptr || p2 != nullptr) {
			if (p1 == nullptr) { temp.add_node(p2->value, i, p2->c_position); p2 = p2->r_next; }
			else if (p2 == nullptr) { temp.add_node(p1->value, i, p1->c_position); p1 = p1->r_next; }
			else if (p1->c_position < p2->c_position) { temp.add_node(p1->value, i, p1->c_position); p1 = p1->r_next; }
			else if (p2->c_position < p1->c_position) { temp.add_node(p2->value, i, p2->c_position); p2 = p2->r_next; }
			else if (p1->c_position == p2->c_position) {

				if ((p1->value + p2->value) != 0) {
					temp.add_node(p1->value + p2->value, i, p1->c_position);
				}
				p1 = p1->r_next; p2 = p2->r_next;
			}
		}

	}
	cout << endl;
	cout << "operator+" << endl;
	return temp;

}

matrix matrix::operator*(const matrix& M) {
	matrix temp(num_rows, M.num_cols);
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < M.num_cols; j++) {
			int inner_product = 0;
			shared_ptr<node> p1 = r_vec[i], p2 = M.c_vec[j];
			while (p1 != nullptr && p2 != nullptr) {
				if (p1->c_position < p2->r_position) { p1 = p1->r_next; }
				else if (p2->r_position < p1->c_position) { p2 = p2->c_next; }
				else if (p1->c_position == p2->r_position) {
					inner_product += (p1->value * p2->value);
					p1 = p1->r_next; p2 = p2->c_next;
				}
			}
			temp.add_node(inner_product, i, j);
		}
	}
	cout << "operator*" << endl;
	return temp;

}


ostream& operator<<(ostream& str, const matrix& M) { //Printing matrix row by row
	for (int i = 0; i < M.num_rows; i++) {
		shared_ptr<node> p = M.r_vec[i];
		if (!p) continue;
		str << endl;
		while (p) {
			cout << p->value << " " << p->r_position << " " << p->c_position << "  ";
			p = p->r_next;
		}
	}
	return str;
}

int main() {
	matrix M1(7, 5, 11, 8), M2(7, 5, 10, 8), M3(7, 5), M4(5, 6, 13, 9), M5(7, 6);
	cout << M1 << endl << endl;
	cout << M2 << endl << endl;
	M3 = M1 + M2;
	cout << M3 << endl << endl;
	cout << M4 << endl << endl;

	M5 = M1 * M4;
	cout << M5 << endl << endl;


	matrix  M6{ {-1,6, 5},{ 300, 4 ,3} , { 200, 4, 2 }, {100, 3, 2}, };
	//M6's num_rows = 6, num_cols = 5, and there are four non-zero nodes in M6.
	cout << M6 << endl << endl;
	matrix M7{ M6 };
	cout << M7 << endl << endl;

	matrix M8;
	M8 = M7;
	cout << M8 << endl;

	return 0;
}
