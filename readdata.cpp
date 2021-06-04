
#include <iostream>
#include <fstream>
#include <string>

#include <string>
#include <cstring>
#include <bits/stdc++.h>

#include "person.h"

using namespace std;

fstream myfile ("person.bin", ios::in | ios::binary);

void show_person(Person p){

    cout << "---------------------------------------------" << endl;

    cout << "PIN       : " << p.pin_s << endl;
    cout << "Name      : " << p.name << endl;
    cout << "Email     : " << p.email << endl;
    cout << "Job Title : " << p.jobtitle << endl;
    cout << "Phone     : " << p.phone << endl;

    cout << "---------------------------------------------" << endl;
}

Person read_person(int pos){

    Person p;

    myfile.seekg(pos * PERSON_SIZE);    
    char buff[PERSON_SIZE];
    myfile.read((char*)buff, PERSON_SIZE);
    memcpy(&p, buff, PERSON_SIZE);

    return p;
}

int main () {
  
    string line;

    if (myfile.is_open()){

        Person p = read_person(9999);
        
        show_person(p);

        myfile.close();
    }

    return 0;
}
