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
    //copies 3 characters in cpin_s and copies them to pin_s at the first index
    strncpy(&cpin_s[0], &pin_s[0], 3);
    //copies 2 characters from cpin_s, and moves the position from 3 to 4 in pin_s
    strncpy(&cpin_s[3], &pin_s[4], 2);
    //copies 4 characters from cpin_s, and moves the position from 5 to 7 in pin_s
    strncpy(&cpin_s[5], &pin_s[7], 4);
    cpin_s[9] = '\n'; //null character for the last position, so no other characters can be copied after that
    //returns converted/copied pin as an integer
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

bool Person::isEmpty(){ //if the person doesnt exist/the struct is empty, this function returns 0
    return (strlen(name) == 0);
}


PersonData::PersonData(){
    current = 0;
    // NOTE: myfile is person.bin (binary)
    myfile.open("person.bin", ios::in | ios::out | ios::binary);

    update_size();
    //seeks the beginning and end positions in the file
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
        //return (Person){};
        return p;
    }

}

// FIXME: Code edits zone below

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

/*
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
*/


// Code that Frabrizzio wrote and comments on what we need to do: 
// We need to update this function to take in the sorted array file and use binary search

/* FIXME k's note: because its so weird to read the new file, 
i'm thinkin of just copying the old style with new structs
because otherwise wont we have to read and construct a new array every time? 
even if the info is written in binary, i don't know how to make it an array structure in binary.
so trying to adapt to copy old search style but with the binary algorithm?
*/

Person PersonData::get_person_by_pin(int pin_n, fstream &ppm){
    // open the binary file, read it in blocks and perform a binary search 

    Person p;
    int elmt_size = 4;
    
    // Set BEG = lower_bound
    int beg = 0;
    
    // Getting the length of the file
    ppm.seekg(0, ppm.end);
    int length = ppm.tellg();
    ppm.seekg(0, ppm.beg);

    // Set END = upper_bound
    int end = length / elmt_size;

    // Set POS = -1
    int pos = -1;

    int mid;
    int current_elmt_pin;
    int current_elmt_id;

    while (beg <= end) {
        // mid to the middle of the data
        mid = (beg + end) / 2;
        // calls read_elmt_by_index, which retrieves the id and pin
        // assigns the second element in the returned pair (aka the pin) to be the current_elmt_pin
        current_elmt_pin = read_elmt_by_index(mid, ppm).second;
        current_elmt_id = read_elmt_by_index(mid, ppm).first;

        // if the current_elmt_pin matches the pin,
        // the search was successful and pos is set to that position
        // the corresponding id is then entered into get_person_by_id
        // and the returned Person is assigned to p
        if (current_elmt_pin == pin_n) {
            pos = mid;
            cout << "Position: " << pos << endl;
            p = get_person_by_id(current_elmt_id);
            break;
        }
        // if the current_elmt_pin is greater than the pin,
        // the end is reset to the mid - 1
        else if (current_elmt_pin > pin_n) {
            end = mid - 1;
        } 
        // otherwise, the current_elmt_pin is less than the pin,
        // the beg is set to mid + 1
        else {
            beg = mid + 1;
        }

        // if position remains unchanged, the pin wasn't found and an error is displayed
        if (pos = -1) {
            cout << "Pin not found, search unsuccessful" << endl;
            // NOTE: p is blank, using in return for convenience
            return p;
        }

    }

    return p;

    // General algorithm for binary search

    // Set BEG = lower_bound
    // Set END = upper_bound
    // Set POS = -1;
    // Set VAL = pin_n;

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

// FIXME fill this out, Emily's working on this
// This function reads through the binary file 
// and retrieves the id and pin information located at the given index.
// It returns a DualData type containing id and pin
DualData read_elmt_by_index(int index, fstream &ppm) {
    DualData dd;

    int dd_size = 4;

    // sets position to the given index
    ppm.seekg(index * dd_size);

    // reads in the id and pin at the given index and stores in dd
    ppm.read(reinterpret_cast<char *>(&dd.second), sizeof(dd.second));
    ppm.read(reinterpret_cast<char *>(&dd.first), sizeof(dd.first));

    return dd;
}


void PersonData::goto_first_person(){
    myfile.seekg(0, ios::beg);
}

bool PersonData::next_person(){
    return (current < size);
}

Person PersonData::get_current_person(){

    if (current >= size){
        cout << "There is no more person!" << endl;
        //return (Person){};
        Person p;
        return p;
    }

    Person p = get_person_by_id(current);
    current++;

    return p;

}

// End of Emily's code

// End of team written code. 

int PersonData::add_person(Person &p){

    myfile.seekp(0, ios::end);
    myfile.write((char*)&p, sizeof(Person));
    update_size();

    return size;

}
