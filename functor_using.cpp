//CIS554 HW4 Due: 11:59pm, 10/28 Wednesday
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

class myCompare1 {
public:
	bool operator()(const list<int*>* pl1, const list<int*>* pl2) const {
		int count_l1{ 0 }, count_l2{ 0 };
		for (auto i : *pl1) { count_l1 += *i; }
		for (auto i : *pl2) { count_l2 += *i; }
		return count_l1 < count_l2;
	}
};
class myCompare2 {
public:
	bool operator()(const map<list<int*>*, vector<int>*, myCompare1>& m1, const map<list<int*>*, vector<int>*, myCompare1>& m2)   const {
		int count_m1{ 0 }, count_m2{ 0 };
		for (auto i : m1) {
			for (auto j : *(i.first)) { count_m1 += *j; }
			for (auto j : *(i.second)) { count_m1 += j; }
		}
		for (auto i : m2) {
			for (auto j : *(i.first)) { count_m2 += *j; }
			for (auto j : *(i.second)) { count_m2 += j; }
		}
		return count_m1 < count_m2;
	}

};
class myCompare3 {
public:
	bool operator()(const map<list<int*>*, vector<int*>*, myCompare1>& m1, const map<list<int*>*, vector<int*>*, myCompare1>& m2)   const {
		int count_m1{ 0 }, count_m2{ 0 };
		for (auto i : m1) {
			for (auto j : *(i.first)) { count_m1 += *j; }
			for (auto j : *(i.second)) { count_m1 += *j; }
		}
		for (auto i : m2) {
			for (auto j : *(i.first)) { count_m2 += *j; }
			for (auto j : *(i.second)) { count_m2 += *j; }
		}
		return count_m1 < count_m2;
	}

} f2;

ostream& operator<<(ostream& str, const map < list<int*>*, vector<int*>, myCompare1>& M);

ostream& operator<<(ostream& str, const list<map < list<int*>*, vector<int*>*, myCompare1 >>& L);


ostream& operator<<(ostream& str, const set<map<list<int*>*, vector<int>*, myCompare1>, myCompare2>& M);

bool f1(const map < list<int*>*, vector<int*>*, myCompare1 >& M1,
	const map < list<int*>*, vector<int*>*, myCompare1 >& M2);


int main() {

	set<map<list<int*>*, vector<int>*, myCompare1>, myCompare2> M1
	{
		{   {
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , new vector<int> {20, 40}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , new vector<int> {20, 40,100}   }
			}
		},


		{	{
				{ new list<int*>{new int{10}, new int{20}, new int{30} }   , new vector<int> {20, 40}   },
				{ new list<int*>{new int{40}, new int{20}, new int{30} }   , new vector<int> {20, 40, 200}   }
			}
		}
	};
	//Implement the needed overloading operator<< to support the following printing.
	cout << M1 << endl;



	/*
	For the following, implement the functions used
	in sorting the list elements using regular function, functor, and lambda in the three cases.
	In addition, you need to implement the needed overloaded operator<< to supporting the printing.
	*/

	cout << endl;
	list<map < list<int*>*, vector<int*>*, myCompare1 >> L1{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{100}}
				}
	} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{200}}
				}
	} };
	cout << L1 << endl;
	L1.sort(f1);//???: use a regular function
	cout << L1 << endl;
	cout << endl;
	list<map < list<int*>*, vector<int*>*, myCompare1 >> L2{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{100}}
				}
	} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{200}}
				}
	} };

	cout << L2 << endl;
	L2.sort(f2);//use a functor 
	cout << L2 << endl;
	cout << endl;

	list<map < list<int*>*, vector<int*>*, myCompare1 >> L3{ {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{400}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{100}}
				}
	} , {
				{
					new list<int*>{new int{10}, new int{20}, new int{30} } ,
					new vector<int*> {new int{20}, new int{40}}
				},

				{
					new list<int*>{new int{40}, new int{20}, new int{30} }   ,
					new vector<int*> {new int{20}, new int{40}, new int{200}}
				}
	} };

	cout << L3 << endl;
	L3.sort([](const map < list<int*>*, vector<int*>*, myCompare1 >& M1,
		const map < list<int*>*, vector<int*>*, myCompare1 >& M2) {
			int num1{ 0 }, num2{ 0 };
			for (auto i : M1) {
				for (auto j : *(i.first)) {
					num1 += *j;
				}
				for (auto j : *i.second) {
					num1 += *j;
				}
			}
			for (auto i : M2) {
				for (auto j : *(i.first)) {
					num2 += *j;
				}
				for (auto j : *i.second) {
					num2 += *j;
				}
			}

			return num1 < num2;
		});//???: use a lambda 
	cout << L3 << endl;

	return 0;
}
ostream& operator<<(ostream& str, const map < list<int*>*, vector<int*>, myCompare1>& M) {
	str << "{ ";
	for (auto i : M) {
		str << "( ";
		for (auto j : *i.first) {
			str << *j << " ";
		}
		str << ") ";
		str << "[ ";
		for (auto j : i.second) {
			str << *j << " ";
		}
		str << "] ";
	}
	str << "}";
	return str;
}

ostream& operator<<(ostream& str, const list<map < list<int*>*, vector<int*>*, myCompare1 >>& L) {
	str << "( ";
	for (auto i : L) {
		str << "< ";
		for (auto j : i) {
			str << "( ";
			for (auto k : *j.first) {
				cout << *k << " ";
			}
			str << ") ";
			str << "[ ";
			for (auto k : *j.second) {
				cout << *k << " ";
			}
			str << "] ";

		}
		str << "> ";
	}
	str << ")";


	return str;

}

ostream& operator<<(ostream& str, const set<map<list<int*>*, vector<int>*, myCompare1>, myCompare2>& M) {

	str << "{ ";
	for (auto i : M) {
		str << "< ";
		for (auto j : i) {
			str << "( ";
			for (auto k : *(j.first)) {
				str << *k << " ";
			}
			str << ") ";
			str << "[ ";
			for (auto k : *(j.second)) {
				str << k << " ";
			}
			str << "] ";
		}
		str << "> ";
		str << " ";
	}
	str << "}";
	return str;

}

bool f1(const map < list<int*>*, vector<int*>*, myCompare1 >& M1,
	const map < list<int*>*, vector<int*>*, myCompare1 >& M2) {
	int num1{ 0 }, num2{ 0 };
	for (auto i : M1) {
		for (auto j : *(i.first)) {
			num1 += *j;
		}
		for (auto j : *i.second) {
			num1 += *j;
		}
	}
	for (auto i : M2) {
		for (auto j : *(i.first)) {
			num2 += *j;
		}
		for (auto j : *i.second) {
			num2 += *j;
		}
	}

	return num1 < num2;
}


//The following is a sample display
/*

{ < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 100 ] >  < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] >  }

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

( < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > )
( < ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] > < ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] > )

*/
