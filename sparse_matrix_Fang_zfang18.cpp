//HW6. Due: Monday, Nov. 9, at 11:59PM
//You are required to use smart pointers in HW6. Raw pointers are not allowed.
//Sparse Matrix -- only non-zero elements are created as nodes.  See the diagram.
#include <iostream>
#include <vector>
#include <memory>
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
	void   add_node(int v, int r, int c);
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
	//You should do as few operations as possible to best benefit from smart pointers.
	matrix ThreeTimes();
	matrix(matrix&& M);//move constructor
	void operator=(matrix&& M);//move assignment
};
//matrix matrix::operator+(const matrix& M) {
//	matrix temp{ *this };
//	return temp;
//
//}
matrix matrix::ThreeTimes() {
	matrix temp{ *this };
	for (int r = 0; r < temp.num_rows; ++r) {
		shared_ptr<node> row_cursor = temp.r_vec[r];
		while (row_cursor){
			row_cursor->value *= 3;
			row_cursor = row_cursor->r_next;
		}
	}
	cout << "Threetimes" << endl;
	return temp;

}
matrix matrix::operator+(const matrix& M) {
	matrix temp{ *this };
	matrix res;
	vector<shared_ptr<node>> thisrow_vec;
	vector<shared_ptr<node>> Mrow_vec;
	if (num_rows == M.num_rows && num_cols == M.num_cols) {
		res.r_vec.resize(num_rows);
		res.c_vec.resize(num_cols);
		for (int r = 0; r < num_rows; ++r) {
			shared_ptr<node> thisrow = r_vec[r];
			shared_ptr<node> Mrow = M.r_vec[r];
			while (thisrow) {
				thisrow_vec.push_back(thisrow);
				thisrow = thisrow->r_next;
			}
			while (Mrow) {
				Mrow_vec.push_back(Mrow);
				Mrow = Mrow->r_next;
			}
			for (auto  Mrow_element : Mrow_vec) {
				int knob = 0;
				for (auto thisrow_element : thisrow_vec) {
					if (thisrow_element->c_position == Mrow_element->c_position) {
						knob = 1;
						//cout << thisrow_element->c_position;
						cout << thisrow_element->value + Mrow_element->value;
						res.add_node(thisrow_element->value+Mrow_element->value,thisrow_element->r_position,thisrow_element->c_position);
					}
				}
				if (knob==0) {
					cout << Mrow_element->value;
					res.add_node(Mrow_element->value, Mrow_element->r_position, Mrow_element->c_position);
				}
			}
			for (auto  thisrow_element : thisrow_vec) {
				int knob = 0;
				for (auto Mrow_element : Mrow_vec) {
					if (thisrow_element->c_position == Mrow_element->c_position) {
						knob = 1;
					}
				}
				if (knob == 0) {
					res.add_node(thisrow_element->value, thisrow_element->r_position, thisrow_element->c_position);
				}
			}
			thisrow_vec.clear();
			Mrow_vec.clear();
		}
	}
	return res;

}

//r_next往右
//c_next往下
//c_position左右
//r_position上下
matrix matrix::operator*(const matrix& M) {
	matrix res;
	vector<shared_ptr<node>> thisrow_vec;
	vector<shared_ptr<node>> Mcol_vec;
	
	if (num_cols == M.num_rows) {
		res.r_vec.resize(num_rows);
		res.c_vec.resize(M.num_cols);
		
		for (int r = 0; r < num_rows; ++r) {
			
			shared_ptr<node> thisrow = r_vec[r];
			
			while (thisrow) {
				//cout << 1;
				thisrow_vec.push_back(thisrow);
				thisrow = thisrow->r_next;
			}
			for (int c = 0; c < M.num_cols; ++c) {
				shared_ptr<node> Mcol = M.c_vec[c];
				while (Mcol) {
					Mcol_vec.push_back(Mcol);
					Mcol = Mcol->c_next;
				}
				int value = 0;
				for (auto thisrow_element : thisrow_vec) {
					for (auto Mcol_element : Mcol_vec) {
						if (thisrow_element->c_position == Mcol_element->r_position) {
							value += (thisrow_element->value * Mcol_element->value);
						}
					}
				}
				res.add_node(value, r, c);
				Mcol_vec.clear();
			}
			thisrow_vec.clear();
		}
	}
	return res;
}
void matrix::operator=(matrix&& M) {//move assignment
	for (auto i : r_vec) {
		i.reset();
	}
	for (auto i : c_vec) {
		i.reset();
	}
	//cout << r_vec.size();
	
	for (int r = 0; r < num_rows; ++r) {
		//head = L.head;
		r_vec[r] = M.r_vec[r];
		M.r_vec[r].reset();
	}
	for (int c = 0; c < num_cols; ++c) {
		c_vec[c] = M.c_vec[c];
		M.c_vec[c].reset();
	}

	cout << "move assignment" << endl;
}
matrix::matrix(matrix&& M) {//move constructor
	//r_vec[0] = 
	num_rows = M.r_vec.size();
	num_cols = M.c_vec.size();
	r_vec.resize(M.r_vec.size());
	c_vec.resize(M.c_vec.size());
	/*cout << num_cols;
	cout << M.r_vec[0]->value << ">";*/

	for (int r = 0; r < num_rows; ++r) {
		//head = L.head;
		r_vec[r] = M.r_vec[r];
		M.r_vec[r].reset();
	}
	for (int c = 0; c < num_cols; ++c) {
		c_vec[c] = M.c_vec[c];
		M.c_vec[c].reset();
	}

	cout << "move constructor" << endl;
}


void matrix::add_node(int v, int r, int c) {
	//shared_ptr<node>
	//cout << 1;
	shared_ptr<node> row_p = r_vec[r];
	shared_ptr<node> col_p = c_vec[c];
	shared_ptr<node> saverow = row_p;
	shared_ptr<node> savecol = col_p;
	shared_ptr<node> p = make_shared<node>(v, r, c);
	//r_next往右
	//c_next往下
	//c_position左右
	//r_position上下
	//cout << v;
	if (v != 0) {//if the value is adding is not zero, proceed to add
		if (!r_vec[r]) {
			r_vec[r] = p;
			//cout << v;
		}
		else {
			if (c < r_vec[r]->c_position) {//before first node in this row
				p->r_next = r_vec[r];
				r_vec[r] = p;

				//cout << v;
			}
			else if (c == r_vec[r]->c_position) {//hit first node
				r_vec[r]->value = v;
				p.reset();
				//update value, no need to create a node
			}
			else if (c > r_vec[r]->c_position) {//after first node in this row
				while (row_p->c_position < c) {
					saverow = row_p;
					row_p = row_p->r_next;
					if (!row_p) break;
				}
				if (!row_p) {//till the end, put at the end
					saverow->r_next = p;
					//cout << v;

				}
				else if (row_p->c_position == c) {//this node existed
					//cout << v;
					//cout << saverow->value;
					//cout << row_p->value;
					row_p->value = v;
					p.reset();
					//update value
				}
				else if (row_p->c_position > c) {
					saverow->r_next = p;
					p->r_next = row_p;
				}
			}
		}

		if (!col_p) {
			c_vec[c] = p;
			//cout << v;
		}
		else {
			if (r < col_p->r_position) {
				p->c_next = c_vec[c];
				c_vec[c] = p;

			}
			else if (r == col_p->r_position) {
				savecol->value = v;
				p.reset();
			}
			else if (r > col_p->r_position) {
				while (col_p->r_position < r) {
					savecol = col_p;
					col_p = col_p->c_next;
					if (!col_p) break;
				}
				if (!col_p) {
					savecol->c_next = p;
				}
				else if (col_p->r_position == r) {
					col_p->value = v;
					p.reset();
				}
				else if (col_p->r_position > r) {
					savecol->c_next = p;
					p->c_next = col_p;
				}
			}
		}
	}
	else {
		return;
	}

}

matrix::matrix(int r, int c) {
	num_rows = r;
	num_cols = c;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
}
matrix::matrix(int r, int c, int n, int k) {
	//Constructor: To create a matrix of r rows, c cols, n nodes, 
	//with values randomly in -(k-1) ... (k-1);
	num_rows = r;
	num_cols = c;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	for (int i = 0; i < n; i++) {
		add_node((rand()% (2*k-1))-k, (rand() % r), (rand() % c));
	}
}
matrix::~matrix() {
	for (auto i : r_vec) {
		i.reset();
	}
	for (auto i : c_vec) {
		i.reset();
	}
	cout << "destructor"<<endl;
}
ostream& operator<< (ostream & str, const matrix& m) {
	for (int r = 0; r < m.num_rows; ++r) {
		shared_ptr<node> row_cursor = m.r_vec[r];
		while (row_cursor) {
			str <<"<" <<row_cursor->value << " " << row_cursor->r_position << " " << row_cursor->c_position<<">";
			row_cursor = row_cursor->r_next;
		}
		//str << row_cursor->value;
		str << endl;
	}
	//for (int r = 0; r < m.num_cols; ++r) {
	//	shared_ptr<node> row_cursor = m.c_vec[r];
	//	while (row_cursor) {
	//		str << "<" << row_cursor->value << " " << row_cursor->r_position << " " << row_cursor->c_position << ">";
	//		row_cursor = row_cursor->c_next;
	//	}
	//	//str << row_cursor->value;
	//	str << endl;
	//}
	return str;
}
matrix::matrix(const matrix& M) {//copy constructor
	num_rows = M.num_rows;
	num_cols = M.num_cols;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	for (int r = 0; r < M.num_rows; ++r) {
		shared_ptr<node>cursor = M.r_vec[r];
		while (cursor) {
			//cout << cursor->value;
			add_node(cursor->value,cursor->r_position,cursor->c_position);
			cursor = cursor->r_next;
		}
	}
	
	cout << "copy constructor" << endl;
}

void matrix::operator=(const matrix& M) {//copy assignment
	for (auto i : r_vec) {
		i.reset();
	}
	for (auto i : c_vec) {
		i.reset();
	}
	num_rows = M.num_rows;
	num_cols = M.num_cols;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	for (int r = 0; r < M.num_rows; ++r) {
		shared_ptr<node>cursor = M.r_vec[r];
		while (cursor) {
			//cout << cursor->value;
			add_node(cursor->value, cursor->r_position, cursor->c_position);
			cursor = cursor->r_next;
		}
	}
	cout << "copy assignment" << endl;
}
matrix::matrix(const initializer_list < triple>& I) {//initializer list
	num_rows = I.begin()->row;
	num_cols = I.begin()->col;
	r_vec.resize(num_rows);
	c_vec.resize(num_cols);
	auto p = I.begin()+1;
	while (p != I.end()) {
		add_node(p->value,p->row,p->col);
		++p;
	}
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
	//M6's num_rows = 6, num_cols = 5, and there are three non-zero nodes in M6.
	cout << M6 << endl << endl;
	matrix M7{ M6 };
	cout << M7 << endl << endl;
	matrix M8;
	M8 = M7;
	cout << M8 << endl;
	return 0;
}



/*
//The following is a sample screenshot

7 0 0 - 4 0 2
4 1 4
2 3 3  3 3 4
5 4 1
- 5 5 1
4 6 0 - 6 6 1  4 6 2


- 5 0 0  7 0 1  7 0 2  5 0 3
1 1 2
- 5 2 3
2 3 1
- 6 4 0
- 1 5 3


operator+
Move Constructor
Destructor
Move Assignment
Destructor

2 0 0  7 0 1  3 0 2  5 0 3
1 1 2  4 1 4
- 5 2 3
2 3 1  2 3 3  3 3 4
- 6 4 0  5 4 1
- 5 5 1 - 1 5 3
4 6 0 - 6 6 1  4 6 2


- 3 0 4
8 1 3  7 1 4
- 6 2 3 - 7 2 4
7 3 3 - 2 3 4 - 8 3 5
4 4 2  1 4 4

operator*
Move Constructor
Destructor
Move Assignment
Destructor

24 0 3  7 0 4
16 1 2  4 1 4
12 3 2  14 3 3 - 1 3 4 - 16 3 5
40 4 3  35 4 4
- 40 5 3 - 35 5 4
- 72 6 3 - 82 6 4

initializer_list

100 3 2
200 4 2  300 4 3

Copy Constructor

100 3 2
200 4 2  300 4 3

Copy Assignment

100 3 2
200 4 2  300 4 3
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor

*/
