//HW7 zfang18 
//Due: Wednesday, Nov. 25 at 11:59pm 
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <string>



using namespace std;

class my_hash1 {
	//hash ( sum(matrix element->string->ASCII)   );
	//Will explain in class
public:
	size_t operator() (const vector<vector<int>>& v) const {
		int sum = 0;
		for (auto const& i : v) {
			for (auto const& j : i) {
				string s = to_string(j);
				
				for (auto k : s) {
					sum += k;
				}
				
			}
		}
		hash<int> h;
		return h(sum);


	}


};

class my_equal_to1 {
public:
	bool operator()(const vector<vector<int>>& v1, const vector<vector<int>>& v2) const {
		int sum1 = 0;
		int sum2 = 0;

		if (v1.size() != v2.size() || v1[0].size() != v2[0].size()) return false;
		for (unsigned int i = 0; i < v1.size(); i++) {
			for (unsigned int j = 0; j < v1[0].size(); j++) {
				string s = to_string(j);

				for (auto k : s) {
					sum1 += k;
				}
			}
		}
		for (unsigned int i = 0; i < v2.size(); i++) {
			for (unsigned int j = 0; j < v2[0].size(); j++) {
				string s = to_string(j);

				for (auto k : s) {
					sum2 += k;
				}
			}
		}
		return sum1==sum2;
	}

	//equal num_rows && equal num_cols && equal sum(matrix element->string->ASCII);
	//Will explain in class

};

class myCompare1 {
public:
	bool operator()(const pair<list<int*>*, vector<int*>>& p1,const pair<list<int*>*, vector<int*>>& p2)const{
		//compare sum(all ints)
		int sum1 = 0;
		int sum2 = 0;

		for (auto & j : *(p1.first)) {
			sum1 += *j;
		}
		for (auto & k : p1.second) {
			sum1 += *k;
		}


		for (auto & j : *(p2.first)) {
			sum2 += *j;
		}
		for (auto & k : p2.second) {
			sum2 += *k;
		}

		return sum1 < sum2;
	}

};

class my_hash2 {
public:
	size_t operator() (const set<pair<list<int*>*, vector<int*>>, myCompare1>& s) const {
		int sum = 0;
		for (auto const& i : s) {
			for (auto const& j : *(i.first)) {
				string s = to_string(*j);
				for (auto c : s) {
					sum += c;
				}
			}
			for (auto const& k : i.second) {
				string s = to_string(*k);
				for (auto c : s) {
					sum += c;
				}
			}
		}
		hash<int> h;
		return h(sum);


	}
	//hash( sum ( int->string->ASCII)  )
	//will explain in class.
};

class my_equal_to2 {
public:
	bool operator()(const set<pair<list<int*>*, vector<int*>>, myCompare1>& s1, 
		            const set<pair<list<int*>*, vector<int*>>, myCompare1>& s2) const {
		int sum1 = 0;
		int sum2 = 0;
		for (auto const& i : s1) {
			for (auto const& j : *(i.first)) {
				string s = to_string(*j);
				for (auto c : s) {
					sum1 += c;
				}
			}
			for (auto const& k : i.second) {
				string s = to_string(*k);
				for (auto c : s) {
					sum1 += c;
				}
			}
		}
		for (auto const& i : s2) {
			for (auto const& j : *(i.first)) {
				string s = to_string(*j);
				for (auto c : s) {
					sum2 += c;
				}
			}
			for (auto const& k : i.second) {
				string s = to_string(*k);
				for (auto c : s) {
					sum2 += c;
				}
			}
		}
		hash<int> h;
		return h(sum1) == h(sum2);
	}
	//equal hash(sum(int->string->ASCII))

};

//Also implement all needed overloaded operator<<
ostream& operator<<(ostream& str, const unordered_set<vector<vector<int>>, my_hash1, my_equal_to1>& HT1) {
	for (auto const &i : HT1) {
		for (auto const &j : i) {
			for (auto const &k : j) {
				str << k;
				str << " ";
			}
			str << endl;
		}
		str << endl;
	}
	str << endl;
	return str;
 }
ostream& operator<<(ostream& str, const vector<vector<int>>& v) {
	for (auto const& i : v) {
		for (auto const& j : i) {
			str << j;
			str << " ";
		}
		str << endl;
	}
	return str;
}
ostream& operator<<(ostream& str, const unordered_set<set<
	pair<list<int*>*, vector<int*>>, myCompare1>,
	my_hash2, my_equal_to2>& HT) {
	for (auto const& i : HT) {
		str << "[ ";
		for (auto const& j : i) {
			str << "< ";
			for (auto const& k : *(j.first)) {
				str << *k;
				str << " ";
			}
			str << "> ( ";
			for (auto const& q : j.second) {
				str << *q;
				str << " ";
			}
			str << ") ";
		}
		str << "]";
	}

	return str;

}
ostream& operator<<(ostream& str, const set<pair<list<int*>*, vector<int*>>, myCompare1>&s) {

	for (auto const& j : s) {
		str << "< ";
		for (auto const& k : *(j.first)) {
			str << *k;
			str << " ";
		}
		str << "> ( ";
		for (auto const& q : j.second) {
			str << *q;
			str << " ";
		}
		str << ") ";
	}

	return str;


}


int main() {
	int n;
	cin >> n;
	vector<vector<vector<int>>> M(n);
	//n matrices of r row and c columns.
	//where r and c are both random numbers in 10-25
	//all matrix elements are random numbers in 0-99.
	//Will explain in class
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
		//cout << i << endl;
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
