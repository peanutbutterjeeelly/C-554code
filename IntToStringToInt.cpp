#include <iostream>
#include <string>
using namespace std;


int main() {

	int a{ 65 };
	int sum{ 0 };
	string s = to_string(a); //s = "65";
	for (auto i : s) { sum += int(i); }
	cout << sum << endl;

	hash<int> h1;


	return 0;
}
