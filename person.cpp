#include <iostream>
#include <cstring>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <fstream>
#include <bits/stdc++.h>

// added blocks for segmented reading and writing
#define BLOCK_SIZE 10000
#define BLOCKS 10

#include "person.h"

using namespace std;

int convert_pin_n(std::string pin_s){

    char cpin_s[10];
    strncpy(&cpin_s[0], &pin_s[0], 3);
    strncpy(&cpin_s[3], &pin_s[4], 2);
    strncpy(&cpin_s[5], &pin_s[7], 4);
    cpin_s[9] = '\n';

    return atoi(cpin_s);

}

Person::Person(string _pin, string _name, string _email, string _jobtitle, string _phone){
// this is where the conversion is happening
    strcpy(pin_s, _pin.c_str());
    pin_n = convert_pin_n(pin_s);
    strcpy(name, _name.c_str());
    strcpy(email, _email.c_str());
    strcpy(jobtitle, _jobtitle.c_str());
    strcpy(phone, _phone.c_str());
    
}

bool Person::isEmpty(){
    return (strlen(name) == 0);
}


PersonData::PersonData(){
    current = 0;
    // NOTE: myfile is person.bin (binary)
    myfile = fstream("person.bin", ios::in | ios::out | ios::binary);

    update_size();

    myfile.seekg(0, ios::beg);
    myfile.seekp(0, ios::end);
}

void PersonData::update_size(){

    long begin, end;
    myfile.seekg (0, ios::beg);
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    file_size = end - begin;
    size = file_size / PERSON_SIZE;
    myfile.seekg (current);
}

PersonData::~PersonData(){
    myfile.close();
}

// this will be staying this way (functon already completed by Fabrizzio)
Person PersonData::get_person_by_id(int id){

    Person p;
    char buff[PERSON_SIZE];

    myfile.seekg(id * PERSON_SIZE, ios::beg);

    if (!myfile.eof()){

        myfile.read((char*)buff, PERSON_SIZE);            
        memcpy(&p, buff, PERSON_SIZE);

        // Small Delay!!!
        std::this_thread::sleep_for (std::chrono::microseconds(100));

        return p;

    } else {
        cout << "No person with id " << id << endl;
        return (Person){};
    }

}

/* This section of the file is sort of just my thoughts/steps we need to take, 
please feel free to change any code as you see fit. 
I used person.cpp because most of it will probalby end up going in here since the 
following function is what we need to change. This is just a starting place 
so we can sort of see what needs ot be done. */ 

// FIXME: moved creation of array to main

/* goal: "You can create an array of your index structure, 
read blocks of records (person), or one by one, and add the key and record num in each array position. "
*/

// sort the array by pin 
// passing array by address so it will be modified outside of function
void SortByPIN(DualData the_array[], int array_size) {
   DualData new_arr;
   // sort through vector to return smallest coord, stop before last element
   for (unsigned int starter_i = 0; starter_i < array_size - 1; ++starter_i) {
       // initally set the smallest as the first 
        int smallestIndex = starter_i;
        // nested loop for comparisons 
       for (unsigned int current_i = starter_i + 1; current_i < array_size; ++current_i){
       // swap if new one is smaller, second is the pin
       if (the_array[current_i].second < the_array[smallestIndex].second) 
           // replace the smallest
           smallestIndex = current_i;
       }
       // swap first with the newfound smallest element
        swap(the_array[starter_i], the_array[smallestIndex]);
   } 
   }
   
// write out the new array into a new binary file
void WriteBin(DualData sortedArrayByPin[], fstream &oppm, int size_of_array) {
// loops through array size (avoids issue with sizeof(array))
   for (int i = 0; i < size_of_array; ++i) {
    // identify p (pin) and r (record id)
     unsigned int p = sortedArrayByPin[i].second;
     unsigned int r = sortedArrayByPin[i].first;
     // reinterpret cast should change from int to char
     // write function will write to the binary file entered for ofstream
     oppm.write(reinterpret_cast<char *>(&p), sizeof(p));
     oppm.write(reinterpret_cast<char *>(&r), sizeof(r));
    // loop until every pair is written to file in pin, record order
    }
 // close file
 oppm.close();
}

// FIXME: Emily is working on this part!

// Original version of the get_person_by_pin function written by Fabrizzio
Person PersonData::linear_search(int pin) {
    Person p;
    char buff[PERSON_SIZE];

    goto_first_person();

    while (next_person()){
        p = get_current_person();
        if (p.pin_n == pin)
            return p;
    } 

    return (Person){};
}


// Code that Frabrizzio wrote and comments on what we need to do: 
// We need to update this function to take in the sorted array file and use binary search
Person PersonData::get_person_by_pin(int pin_n, fstream &ppm){
    // open the binary file
    // read it in blocks and perform a binary search 

    // The chunk below is just pasted for reference. Will be removed before submission.
    /*
    // FIXME instead of blocks rn this is writing each one but i guess that works
    for (int i = 0; i < sizeof(sortedArrayByPin)/sizeof(int); ++i) {
        unsigned int p = sortedArrayByPin[i].second;
        unsigned int r = sortedArrayByPin[i].first;
        // FIXME reinterpret cast should change from int to char
        oppm.write(reinterpret_cast<char *>(&p), sizeof(p));
        oppm.write(reinterpret_cast<char *>(&r), sizeof(r));
        // FIXME: the key line: myfile2.write((char*)&persons, sizeof(Person) * BLOCK_SIZE);
    }
    // close file
    oppm.close();
    }
    */
    
    ppm.seekg(0, ppm.beg);

    while (!ppm.eof()) {

    }


    Person p;
    
    // Set BEG = lower_bound
    // K's FIXME: can lower bound (beg) initially just be 0?
    int beg = goto_first_person();
    // Set END = upper_bound
    // K's FIXME: and can this upper bound be the total array size (which is already an established variable)?
    int end;
    // Set POS = -1
    int pos = -1;

    int mid;

    while (beg <= end) {
        mid = (beg + end) / 2;
        //  IF (ARR[MID] == pin_n)
        if () {
            pos = mid;
            cout << "Position: " << pos << endl;
            break;
        // ELSE IF (ARR[MID] > pin_n)
        } else if () {
            end = mid - 1;
        } else {
            beg = mid + 1;
        }

        if (pos = -1) {
            cout << "Pin not found, search unsuccessful" << endl;
            return p;
        }

    }

    return p;

    // While (BEG <= END) {
    //  Set MID = ((BEG + END) / 2)
    //  IF (ARR[MID] == VAL) {
    //      POS = MID
    //      Print POS
    //      BREAK LOOP
    //  } ELSE IF (ARR[MID] > VAL) {
    //      Set END = MID - 1
    //  } ELSE {
    //      Set BEG = MID + 1
    //  }
    // }
    // IF (POS = -1){
    //  Print "VALUE NOT FOUND, SEARCH UNSUCCESSFUL"
    // }

}
// End of Emily's code

// End of team written code. 

void PersonData::goto_first_person(){
    myfile.seekg(0, ios::beg);
}

bool PersonData::next_person(){
    return (current < size);
}

Person PersonData::get_current_person(){

    if (current >= size){
        cout << "There is no more person!" << endl;
        return (Person){};
    }

    Person p = get_person_by_id(current);
    current++;

    return p;

}

int PersonData::add_person(Person &p){

    myfile.seekp(0, ios::end);
    myfile.write((char*)&p, sizeof(Person));
    update_size();

    return size;

}
