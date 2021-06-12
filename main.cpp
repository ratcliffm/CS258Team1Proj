// most work should be done in this file


#include <iostream>
#include <string>

#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <chrono>

#include "person.h"

using namespace std;

void show_person(Person p){

    cout << "---------------------------------------------" << endl;

    cout << "PIN       : " << p.pin_s << endl;
    cout << "Name      : " << p.name << endl;
    cout << "Email     : " << p.email << endl;
    cout << "Job Title : " << p.jobtitle << endl;
    cout << "Phone     : " << p.phone << endl;

    cout << "---------------------------------------------" << endl;
}

void adding_person(PersonData &pd){

    Person p("254-86-5682", "Bruce Springsteen", "bruces@gmail.com", "singer", "5-262-667-4762");
    int line = pd.add_person(p);

    cout << "---------------------------------------------" << endl;
    cout << "Person added to Line: "<< line << endl;
    cout << "---------------------------------------------" << endl;

}

void searching_person(PersonData &pd){

    Person p = pd.get_person_by_pin(254865682);

    if (p.isEmpty()){
        cout << "---------------------------------------------" << endl;
        cout << "Person ID not found!" << endl;
        cout << "---------------------------------------------" << endl;
    } else {
        show_person(p);
    }

}


int main () {
  
    string line;
    PersonData pd;

    adding_person(pd);

    auto start = std::chrono::steady_clock::now();

    searching_person(pd)    ;

    auto end = std::chrono::steady_clock::now();   
    std::chrono::duration<double> diff = end-start;

    cout << "---------------------------------------------" << endl;
    std::cout << "Elapsed time: " << diff.count() << " s\n";
    cout << "---------------------------------------------" << endl;

    return 0;

}
