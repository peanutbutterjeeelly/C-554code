//CIS554 HW2.  Due: 11:59pm, Wednesday, September 16.
//Tree

#include <iostream>
using namespace std;
int m = 50;
class Node {
public:
	int value;
	Node* l_child;
	Node* r_child;
	Node() : l_child(nullptr), r_child(nullptr) {}
	Node(int i) :value(i), l_child(nullptr), r_child(nullptr) {}
};

class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
	Node* root;
	Tree() : root(nullptr) {}
	Node* makeTree(int n);
	void printTree1(Node* p); //in-order printing
	void printTree2(Node* p); //pre-order printing
	void printTree3(Node* p); //post-order printing
	//*************
	//Design and implement the following two member functions, Func1 and Func2, using recursion.
	//loop structures (such for, while, etc) are not allowed.
	//You are also required to do in-place implementation.

	//function 1, Func1, which will re-structure the subtree rooted at a node pointed by a pointer such that
	//at every node,  value(l_child) >= value(r_child) >= value(parent).
	//Will draw example diagrams in class.

	//function 2, Func2, which will re-structure the subtree rooted at a node pointed by a pointer such that
	//at every node, value(parent) <= value(l_child) and value(parent) <= value(r_child).
	//In addition, for every subtree, the largest value  at the bottom right node of the subtree.
	//Will draw example diagrams in class.
	void Func1(Node* p);
	Node* Func2(Node* p);
};

Node* Tree::Func2(Node* p) {
	if (!p) return nullptr;
	if (!p->l_child) return p;
	//if (!p || !p->l_child || !p->r_child) return;
	Node* p1, * p2;
	p1 = Func2(p->l_child);
	p2 = Func2(p->r_child);
	if (p1->value > p2->value) {
		swap(p->l_child, p->r_child);
		//p2 = p1;
		swap(p1, p2);
	}
	if (p->value > p2->value) swap(p->value, p2->value);
	if ((p->l_child->value < p->value) || (p->r_child->value < p->value)) {
		if (p->l_child->value <= p->r_child->value) {
			int i = p->value;
			p->value = p->l_child->value;
			p->l_child->value = i;
			Func2(p->l_child);
		}
		else {
			int i = p->value;
			p->value = p->r_child->value;
			p->r_child->value = i;
			Func2(p->r_child);
		}
	}
	return p2;


}
void Tree::Func1(Node* p) {
	if (!p || !p->l_child || !p->r_child) return;
	Func1(p->l_child);
	Func1(p->r_child);
	if ((p->l_child->value < p->value) || (p->r_child->value < p->value)) {
		if (p->l_child->value <= p->r_child->value) {
			int i = p->value;
			p->value = p->l_child->value;
			p->l_child->value = i;
			Func1(p->l_child);
		}
		else {
			int i = p->value;
			p->value = p->r_child->value;
			p->r_child->value = i;
			Func1(p->r_child);
		}
	}
	if (p->l_child->value < p->r_child->value) swap(p->l_child, p->r_child);

}

Node* Tree::makeTree(int n) { //Create an n-level full binary tree with 
							  //with random values between 0 ... m-1
							  //and returns a pointer to the root.

	Node* p = new Node(rand() % m);
	if (n == 1) return p;
	p->l_child = makeTree(n - 1);
	p->r_child = makeTree(n - 1);
	return p;
}

void Tree::printTree1(Node* p) { //in-order printing
	if (p == nullptr) return;
	printTree1(p->l_child);
	cout << p->value << " ";
	printTree1(p->r_child);
}

void Tree::printTree2(Node* p) { //pre-order printing

	if (p == nullptr) return;
	cout << p->value << " ";
	printTree2(p->l_child);
	printTree2(p->r_child);
}
void Tree::printTree3(Node* p) { //post-order printing
	if (p == nullptr) return;
	printTree3(p->l_child);
	printTree3(p->r_child);
	cout << p->value << " ";
}

int main() {

	Tree T1;
	T1.root = T1.makeTree(5);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	T1.Func1(T1.root);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	cout << "****************" << endl;
	Tree T2;
	T2.root = T2.makeTree(5);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;
	T2.Func2(T2.root);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;

	return 0;
}