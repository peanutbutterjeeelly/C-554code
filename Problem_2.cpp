//Problem 2: Write code for the member functions mirror and mirrorCopy, described below.. 
#include <iostream>
using namespace std;


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

//**********************************************************
	void mirror(Node* p); //Re-arrange the current tree such that, after rearrangement the tree becomes mirror of the original one. (See the diagram)
	//Note that you are re-arrange the current tree, rather than creating a new tree.

	Node* mirrorCopy(Node* p); // Create a new tree which is a mirror of the current tree, and return the address of the root of the mirror tree.
	//You are not allowed to call the function makeTree.
//***********************************************************
};


void Tree::mirror(Node* p) {
	if (!p) return;
	swap(p->l_child, p->r_child);
	mirror(p->l_child);
	mirror(p->r_child);
}

Node* Tree::mirrorCopy(Node* p) {
	
	if (!p) return nullptr;
	Node* p1 = new Node(p->value);
	p1->l_child = mirrorCopy(p->r_child);
	p1->r_child = mirrorCopy(p->l_child);
	return p1;
}

Node* Tree::makeTree(int n) { //Create an n-level full binary tree with 
							  //with random values between 0 ... m-1
							  //and returns a pointer to the root.

	Node* p = new Node(rand() % 50);
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
	T1.mirror(T1.root);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;

	Tree T2;
	T2.root = T2.makeTree(5);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;

	Tree T3;

	T3.root = T2.mirrorCopy(T2.root);
	T3.printTree2(T3.root);
	cout << endl;
	T3.printTree2(T3.root);
	cout << endl;
	T3.printTree3(T3.root);
	cout << endl;
	return 0;
}
