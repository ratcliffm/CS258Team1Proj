
#include <iostream>
#include <fstream>
#include <string>

#include <string>
#include <cstring>
#include <bits/stdc++.h>

#include "person.h"

using namespace std;

#define BLOCK_SIZE 10000
#define BLOCKS 10

Person tokenize_line(string value){

    stringstream ss(value);
    vector <string> tokens;
    string temp_str;
    Person p;
    
    while(getline(ss, temp_str, ',')){ //use - as delim for cutting string
        tokens.push_back(temp_str);
    }

    p.pin_n = convert_pin_n(tokens[4].c_str());

    strcpy(p.pin_s, tokens[4].c_str());
    strcpy(p.name, tokens[3].c_str());
    strcpy(p.email, tokens[2].c_str());
    strcpy(p.jobtitle, tokens[1].c_str());
    strcpy(p.phone, tokens[5].c_str());

    return p;    
}

int main () {
  
    string line;
    ifstream myfile ("data.csv");
    ofstream myfile2 ("person.bin", ios::out | ios::binary);
    Person p;

    Person persons[BLOCK_SIZE];

    getline (myfile,line);

    for (int n=0; n < BLOCKS; n++){

        int i = 0;

        while ( getline (myfile,line) ) {            
            persons[i] = tokenize_line(line);
            i++;
            if (i >= BLOCK_SIZE) break;
        }

        myfile2.write((char*)&persons, sizeof(Person) * BLOCK_SIZE);

    }

    myfile.close();
    myfile2.close();

    return 0;
}
