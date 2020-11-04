Some general information for HW3:

You are not allow to create any additional help functions.
You don't need to use templates in HW3, but You can if you think they would help.


class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

	bool operator==(const course& c) const { return name == c.name; }
	bool operator<(const course& c) const { return name < c.name; }

	float num_grade() const;


	//You might need to implement some overloaded operators here.

};

void add_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id) {
	auto it1{ DB.begin() };
	bool found{ false };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) found = true;
		it1++;
	}
	if (found) return;
	
	tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> 
		t1{ id,0,0.00, new map<int, pair<pair<int, float>*, list<course*>*>*> };
	DB.push_back(t1);
}

#include <iostream>
#include <iomanip>
using namespace std;


int main() {

	float f1{ 34.7903 };

	cout  << setprecision(2) <<fixed<< f1;

}


list.insert(6, it1);

references  &
