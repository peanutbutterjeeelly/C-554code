//typeid
#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

class ThreeD {
public:
    int ht;
    int wid;
    int dep;
    ThreeD() {}
    ThreeD(int i, int j, int k) : ht(i), wid(j), dep(k) {}
    int vol() const { //the keyword const declare "this" is of type ThreeD const * 
        cout << typeid(this).name() << endl;
        //Four types of casting defined in C++
        //static_cast, dynamic_cast, const_cast, reinterpret_cast
        //const_cast -- temporarily cast away constness
        //"this" is of type    ThreeD const *
        //Let's temporarily change it to ThreeD *

        const_cast<ThreeD*>(this)->ht = 250;
        cout << "ht = " << ht << endl;
        return ht * wid * dep;
    }

    friend ostream& operator<<(ostream& str, const ThreeD& t);
    //The keyword friend allow this function to access all private and protected members.
    //If ht, wid, or dep are private or protected, then this statement is necessary.
};


ostream& operator<<(ostream& str, const ThreeD& t) {
    str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
    return str;
}



int main() {
    

    ThreeD t2{ 4,5,6 };
    cout << t2 << " "<< t2.vol()<<endl;




    return 0;
}
