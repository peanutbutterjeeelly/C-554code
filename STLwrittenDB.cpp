//HW3
//Due: 11:59PM, September 25 (Friday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <iomanip>
using namespace std;

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
float course::num_grade() const {
	map<string, float> Grade{ {"A", 4.000}, {"A-", 3.667},
	{"B+", 3.333}, {"B", 3.0000}, {"B-", 2.667}, {"C+", 2.333},
	{"C", 2.000},{"C-", 1.667}, {"D", 1.000},{"D-", 0.667}, {"F", 0}
	};
	return Grade[grade];
}
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc. 

void add_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);
void remove_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);
void add_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																//All courses in the list should be sorted according to name (increasing order)
void drop_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c);
void print_student_semester_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id);
void print_student_all_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.


ostream& operator<<(ostream& str, const course& c);

ostream& operator<<(ostream& str, const list<course*>& L);


ostream& operator<<(ostream& str, const pair<pair<int, float>*, list<course*>*>& P);


ostream& operator<<(ostream& str, const list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB);


int main() {

	list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> > DB;
	//print_student_semester_courses(DB, 20171, 11111);


	add_student(DB, 11111);
	//print_student_semester_courses(DB, 20171, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);

	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);

	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111);//ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);


	//cout << "****************" << endl;
	cout << DB << endl;

	//cout << "&&&&&&&&&&&&&&&&" << endl;
	remove_student(DB, 11111);
	cout << DB << endl;

	return 0;
}

ostream& operator<<(ostream& str, const course& c) {
	str << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ")";
	return str;
}
ostream& operator<<(ostream& str, const list<course*>& L) {
	for (auto i : L) {
		str << *i << " ";
	}
	return str;
}

ostream& operator<<(ostream& str, const pair<pair<int, float>*, list<course*>*>& P) {
	str << "GPA : " << setprecision(2) << fixed << P.first->second << endl;
	str << "Credits : " << P.first->first << endl;
	str << *(P.second) << endl;
	return str;

}

ostream& operator<<(ostream& str, const list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB) {
	if (DB.empty()) return str;
	for (auto& i : DB) {
		str << "Student ID: " << get<0>(i) << endl;
		str << "Overall GPA: " << get<2>(i) << endl;
		str << "Overall Credits: " << get<1>(i) << endl;

		//print_student_all_courses(DB, get<0>(i));
		if (get<3>(i)->size() != 0) {
			for (auto& j : *get<3>(i)) {
				str << "Semester : " << j.first << endl;
				str << *(j.second);
			}
		}

	}
	str << endl;
	return str;
}

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
void remove_student(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id) {
	bool found{ false };
	auto it1{ DB.begin() }, it2{ DB.begin() };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) {
			found = true; it2 = it1;
		}

		it1++;
	}
	if (!found) return;
	for (auto& i : *get<3>(*it2)) {
		delete i.second->first;
		for (auto j : *(i.second->second)) {
			delete j;
		}
		delete i.second->second;
		delete i.second;
	}
	delete get<3>(*it2);
	DB.erase(it2);

}


void add_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c) {
	bool found{ false };
	auto it1{ DB.begin() }, it2{ DB.begin() };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) {
			found = true; it2 = it1;
		}

		it1++;
	}
	if (!found) return;
	if (get<3>(*it2)->size() == 0) {
		get<3>(*it2)->insert({ semester,new pair<pair<int, float>*, list<course*>*> });
		(*get<3>(*it2))[semester]->first = new pair<int, float>{ c.credits, c.num_grade() };
		(*get<3>(*it2))[semester]->second = new list<course*>;
		(*get<3>(*it2))[semester]->second->push_back(new course{ c });
		get<1>(*it2) = c.credits;
		get<2>(*it2) = c.num_grade();
		return;
	}

	for (auto i : *get<3>(*it2)) {
		for (auto it = i.second->second->begin(); it != i.second->second->end(); it++) {
			if (**it == c) return;
		}
	}


	if (get<3>(*it2)->find(semester) == get<3>(*it2)->end()) {
		get<3>(*it2)->insert({ semester,new pair<pair<int, float>*, list<course*>*> });
		(*get<3>(*it2))[semester]->first = new pair<int, float>{ c.credits, c.num_grade() };
		(*get<3>(*it2))[semester]->second = new list<course*>;
		(*get<3>(*it2))[semester]->second->push_back(new course{ c });

		get<2>(*it2) = (get<2>(*it2) * get<1>(*it2) + c.num_grade() * c.credits) / (get<1>(*it2) + c.credits);
		get<1>(*it2) += c.credits;
		return;
	}

	auto  p1{ (*get<3>(*it2))[semester] };
	auto& R1{ *((*get<3>(*it2))[semester]) };

	//auto it3{ R1.second->find(R1.second->begin(), R1.second->end(), c) };
	bool course_found{ false };
	auto it3{ R1.second->begin() };
	while (it3 != R1.second->end()) {
		if (**it3 == c) course_found = true;
		it3++;
	}
	if (course_found) return;
	it3 = R1.second->begin();
	while (it3 != R1.second->end() && **it3 < c) {
		it3++;
	}
	R1.second->insert(it3, new course{ c });

	R1.first->second = (R1.first->second * R1.first->first + c.num_grade() * c.credits) / (R1.first->first + c.credits);
	R1.first->first += c.credits;

	get<2>(*it2) = (get<2>(*it2) * get<1>(*it2) + c.num_grade() * c.credits) / (get<1>(*it2) + c.credits);
	get<1>(*it2) += c.credits;
}

void drop_course(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id, course c) {

	bool found{ false };
	auto it1{ DB.begin() }, it2{ DB.begin() };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) {
			found = true; it2 = it1;
		}

		it1++;
	}
	if (!found) return;

	if (get<3>(*it2)->find(semester) == get<3>(*it2)->end()) return;

	auto& R1{ *((*get<3>(*it2))[semester]) };


	bool course_found{ false };
	auto it3{ R1.second->begin() }, it4{ R1.second->begin() };
	while (it3 != R1.second->end()) {
		if (**it3 == c) {
			course_found = true;
			//delete* it3;
			it4 = it3;
		}
		it3++;
	}
	if (!course_found) return;
	delete* it4;
	R1.second->erase(it4);


	if (R1.first->first == c.credits) {
		R1.first->first = 0;
		R1.first->second = 0.00;
		return;
	}
	R1.first->second = (R1.first->second * R1.first->first - c.num_grade() * c.credits) / (R1.first->first - c.credits);
	R1.first->first -= c.credits;
}

void print_student_semester_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int semester, int id) {

	bool found{ false };
	auto it1{ DB.begin() }, it2{ DB.begin() };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) {
			found = true; it2 = it1;
		}

		it1++;
	}
	if (!found) return;

	if (get<3>(*it2)->find(semester) == get<3>(*it2)->end()) return;

	cout << "Student ID: " << id << endl;
	cout << "Semester: " << semester << endl;

	cout << *(*get<3>(*it2))[semester];
	cout << endl;


}
void print_student_all_courses(list<tuple<int, int, float, map<int, pair<pair<int, float>*, list<course*>*>*>*> >& DB, int id) {

	bool found{ false };
	auto it1{ DB.begin() }, it2{ DB.begin() };
	while (it1 != DB.end()) {
		if (get<0>(*it1) == id) {
			found = true; it2 = it1;
		}

		it1++;
	}
	if (!found) return;

	cout << "Student ID: " << id << endl;
	cout << "Overall GPA : " << setprecision(2) << fixed << get<2>(*it2) << endl;
	cout << "Overall Credits : " << get<1>(*it2) << endl;
	/*
	ID: 11111
	Overall GPA : x.xx
	Overall Credits : 22
	*/
	if (get<3>(*it2)->empty()) return;


	for (auto i : (*get<3>(*it2))) {
		cout << "semester: " << i.first << endl;
		cout << *(i.second);

	}

	cout << endl;

}


