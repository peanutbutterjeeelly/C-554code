//HW1 by Zhixuan Fang
//SU Net ID: zfang18  SUID: 337310566
//CIS554 HW1
//Due: 11:59PM, Wednesday ( September 9)
//Do not modify main funaiton.
//Do not introduce new functions.
//In-place implementation is required.  Exteranl stuctures are not allowed.
//For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
//back to linked list.


#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node* previous;
    Node(int i) { value = i; next = previous = nullptr; }
    Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    DoublyLinkedList() { head = tail = nullptr; }
    void makeRandomList(int m, int n);
    void printForward();
    void printBackward();

    //inplement the following member functions:

    void group();
    /*
    Group all occurances of the same numbers together accourding to the order of appearance.

    For a list with values

    7 6 12 4 33 12 6 6 7 ,

    after grouping, it becomes

    7 7 6 6 6 12 12 4 33

    Note that in the original sequence, 7 appears before 6 before 12 before 4 before 33
    */


};
void DoublyLinkedList::group(){
    if (!head || !head->next || !head->next->next) return;//0 , 1, 2
    Node* p1 = head;

    while (p1->next) {
        Node* p2 = p1->next;
        int GroupEqual = p1->value;
        Node* p_equal = p1;

        while (p2){//p1->next is not null
            if (p2->value == GroupEqual && p2->previous->value!=GroupEqual){//this number is the value we are looking for
                //and also it's previous value is not the value we are looking for
                p_equal = p2;
                p2->previous->next = p2->next; //we want to remove p2 from its place so we connect its neighbour
                if(p2->next){
                p2->next->previous = p2->previous;}
                p2 ->next = p1 -> next;
                p2 ->previous = p1;
                p1->next->previous = p2;
                p1 -> next = p2;//we are inserting p2 to the position between p1 and p1.next, so connecting 4 edges
                p1 = p2;
            }
            else{
           p2 = p2->next;}
        }
        p1 = p1->next;

    }
    tail = p1;
}
void DoublyLinkedList::makeRandomList(int m, int n) {

    for (int i = 0; i < m; i++) {
        Node* p1 = new Node(rand() % n);
        p1->previous = tail;
        if (tail) tail->next = p1;
        tail = p1;
        if (!head) head = p1;
    }
}

void DoublyLinkedList::printForward() {
    cout << endl;
    Node* p1 = head;
    while (p1) {
        cout << p1->value << " ";
        p1 = p1->next;
    }
}

void DoublyLinkedList::printBackward() {
    cout << endl;
    Node* p1 = tail;
    while (p1) {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
}

int main() {
    DoublyLinkedList d1;
    d1.makeRandomList(100, 20);
    d1.printForward();
    d1.printBackward();

	d1.group();
	d1.printForward();
	d1.printBackward();

    getchar();
    getchar();
    return 0;
}

