//HW7
//Due: Monday, Nov. 23 at 11:59pm 
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <string>



using namespace std;

class my_hash1 {
public:
	int operator()(const vector < vector<int>>& M) const {//the last const is necessary
		int sum = 0;
		for (auto i : M)
			for (auto j : i) {
				string  s = to_string(j);
				for (auto k : s) { sum += int(k); }
			}


		hash<int> h;
		return h(sum);
	}
};

class my_equal_to1 {
public:
	bool operator()(const vector<vector<int>>& M1, const vector<vector<int>>& M2) const { //the last const is necessary
		int sum1 = 0;
		for (auto i : M1)
			for (auto j : i) {
				string s = to_string(j);
				for (auto k : s) { sum1 += int(k); }
			}
		int sum2 = 0;
		for (auto i : M2)
			for (auto j : i) {
				string s = to_string(j);
				for (auto k : s) { sum2 += int(k); }
			}

		size_t s1{ M1.size() }, s2, s3{ M2.size() }, s4;
		s2 = M1[0].size();
		s4 = M2[0].size();
		return (sum1 == sum2 && s1 == s3 && s2 == s4);
	}

};

ostream& operator << (ostream& str, const vector<vector<int>>& M);



class myCompare1 {
public:
	bool operator()(const pair<list<int*>*, vector<int*>> P1, const pair<list<int*>*, vector<int*>> P2) const {
		int sum1{ 0 }, sum2{ 0 };
		for (auto i : *(P1.first)) {
			sum1 += *i;
		}
		for (auto i : P1.second) {
			sum1 += *i;
		}

		for (auto i : *(P2.first)) {
			sum2 += *i;
		}
		for (auto i : P1.second) {
			sum2 += *i;
		}
		return sum1 < sum2;
	}
};

class my_hash2 {
public:
	size_t operator()(const set<
		pair<list<int*>*, vector<int*>>, myCompare1>  S) const {
		int sum{ 0 };
		for (auto i : S) {
			for (auto j : *(i.first)) {
				string s = to_string(*j);
				for (auto k : s) { sum += int(k); }
			}
			for (auto j : i.second) {
				string s = to_string(*j);
				for (auto k : s) { sum += int(k); }
			}
		}
		hash<int> h;
		return h(sum);
	}
};

class my_equal_to2 {
public:
	bool operator()  (const set<
		pair<list<int*>*, vector<int*>>, myCompare1>& S1, const set<
		pair<list<int*>*, vector<int*>>, myCompare1>& S2)  const {

		int sum1{ 0 }, sum2{ 0 };
		for (auto i : S1) {
			for (auto j : *(i.first)) {
				string s = to_string(*j);
				for (auto k : s) { sum1 += int(k); }
			}
			for (auto j : i.second) {
				string s = to_string(*j);
				for (auto k : s) { sum1 += int(k); }
			}
		}
		for (auto i : S2) {
			for (auto j : *(i.first)) {
				string s = to_string(*j);
				for (auto k : s) { sum2 += int(k); }
			}
			for (auto j : i.second) {
				string s = to_string(*j);
				for (auto k : s) { sum2 += int(k); }
			}
		}

		return sum1 == sum2;

	}

};

ostream& operator<<(ostream& str, const
	unordered_set<set<
	pair<list<int*>*, vector<int*>>, myCompare1>,
	my_hash2, my_equal_to2>& HT2);

ostream& operator<<(ostream& str, const unordered_set<vector<vector<int>>, my_hash1, my_equal_to1>& HT);




ostream& operator<<(ostream& str, const set<
	pair<list<int*>*, vector<int*>>, myCompare1>& S);



int main() {
	int n;
	cin >> n;
	vector<vector<vector<int>>> M(n);
	//n matrices of r row and c columns.
	//where r and c are both random numbers in 10-25


	for (int i = 0; i < n; i++) {
		int r{ rand() % 16 + 10 }, c{ rand() % 16 + 10 };
		vector<int> v(c);
		M[i].resize(r, v);
	}
	for (int k = 0; k < n; k++) {
		for (auto& i : M[k]) {
			for (auto& j : i) {
				j = rand() % 100;
			}
		}
	}


	unordered_set<vector<vector<int>>, my_hash1, my_equal_to1> HT1;
	for (int i = 0; i < n; i++) {
		HT1.insert(M[i]);
	}
	cout << HT1 << endl;

	auto it = HT1.find(M[n - 1]);
	if (it != HT1.end()) {
		cout << *it << endl;
	}


	unordered_set<set<
		pair<list<int*>*, vector<int*>>, myCompare1>,
		my_hash2, my_equal_to2> HT2;

	set<pair<list<int*>*, vector<int*>>, myCompare1>
		s1{

			{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}}   },
			{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{100}}   }
	},
		s2{
			{ new list<int*>{new int{10}, new int{20}, new int{30} }   , {new int{20}, new int{40}} },
			{ new list<int*>{new int{40}, new int{20}, new int{30} }   , {new int{20}, new int{40}, new int{200}}   }
	};
	HT2.insert(s1);
	HT2.insert(s2);

	cout << HT2 << endl;
	cout << endl;
	auto it2 = HT2.find(s1);
	if (it2 != HT2.end())  cout << *it2 << endl;
	return 0;
}
ostream& operator << (ostream& str, const vector<vector<int>>& M) {
	str << endl;
	for (auto i : M) {
		for (auto j : i) {
			str << j << " ";
		}
		str << endl;
	}
	return str;
}

ostream& operator<<(ostream& str, const
	unordered_set<set<
	pair<list<int*>*, vector<int*>>, myCompare1>,
	my_hash2, my_equal_to2>& HT2)
{
	str << "{ ";
	for (auto i : HT2) {
		str << "[ ";
		for (auto j : i) {
			str << "< ";
			for (auto k : *(j.first)) {
				str << *k << " ";
			}
			str << "> ";
			str << "( ";
			for (auto k : j.second) {
				str << *k << " ";
			}
			str << ") ";
		}
		str << "] ";


	}
	cout << " }";
	return str;
}

ostream& operator<<(ostream& str, const unordered_set<vector<vector<int>>, my_hash1, my_equal_to1>& HT) {
	for (auto i : HT) {
		for (auto j : i) {
			for (auto k : j) {
				str << k << " ";
			}
			str << endl;
		}
		str << endl;
	}

	return str;
}

ostream& operator<<(ostream& str, const set<
	pair<list<int*>*, vector<int*>>, myCompare1>& S) {
	str << "[ ";
	for (auto i : S) {
		str << "< ";
		for (auto j : *(i.first)) {
			str << *j << " ";
		}
		str << "> ";
		str << "( ";
		for (auto j : i.second) {
			str << *j << " ";
		}
		str << ") ";
	}
	str << "] ";


	return str;
}


