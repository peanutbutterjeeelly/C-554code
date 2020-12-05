#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>


using namespace std;

template <class T> ostream& operator<<(ostream& str, const vector<T>& V);
template <class T> ostream& operator<<(ostream& str, const list<T>& L);
template <class T> ostream& operator<<(ostream& str, const vector<T *>& V);
template <class T> ostream& operator<<(ostream& str, const list<T *>& L);

void DB1_to_DB2(vector<list<list< int>*>*>& DB1, list<vector<list<int*>*>>& DB2);

int main() {

	vector<list<list< int>*>*> DB1 {
		new list<list<int>*>  { new list<int>{1,2,3}, new list<int>{4,5}, new list<int>{7,8,9,10}},
		new list<list<int>*>  {  new list<int> {10, 20}, new list<int>{30, 40, 50}, new list<int>{60, 70}, new list<int> {80, 90}}
	};
	cout << DB1 << endl;
	list<vector<list<int*>*>> DB2;
	DB1_to_DB2(DB1, DB2);
	cout << DB2 << endl;


}
template <class T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto i : V) { str << i << " "; }
	str << "]";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto i : L) { str << i << " "; }
	str << ">";
	return str;

}
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V){
	str << "[ ";
	for (auto i : V) { str << *i << " "; }
	str << "]";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "< ";
	for (auto i : L) { str << *i << " "; }
	str << ">";
	return str;
}

void DB1_to_DB2(vector<list<list< int>*>*>& DB1, list<vector<list<int*>*>>& DB2) {
	for (auto i : DB2) {
		for (auto j : i) {
			for (auto k : *j) {
				delete k;
			}
			delete j;
		}
	}
	DB2.clear();

	for (auto i : DB1) {
		vector<list<int*>*> V1;
		for (auto j : *i) {
			auto p1 = new list<int*>;
			for (auto k : *j) {
				auto p2 = new int{ k };
				p1->push_back(p2);
			}
			V1.push_back(p1);
		}
		DB2.push_back(V1);
	}
}
