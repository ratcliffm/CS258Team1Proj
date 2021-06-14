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
   // sort through vector to return smallest coord
   for (unsigned int i = 0; i < array_size; ++i) {
       for (unsigned int j = i + 1; j < array_size; ++j) {
       if (the_array[i] < the_array[j]) {
           swap(the_array[i], the_array[j]);
       }
   } 
   }
   // FIXME ZONE -- new arr is a PAIR... need to assign a first and second
for (unsigned int i = 0; i < array_size; ++i) {
       for (unsigned int j = i + 1; j < array_size; ++j) {
           // FIXME -- WHAT ARE NEW ARR I AND J REPRESENTING?
        new_arr[i] = the_array[i]; 
        new_arr[j] = the_array[j]; 
       }
}
// return nothing because array will simply be sorted
}

// write out the new array into a new binary file
// FIXME: katherine work on this!
void WriteBin(DualData sortedArrayByPin[], ofstream &oppm) {
// for each pixel assign to color and then turn back to binary
// FIXME Do I need to be using blocks right here? I think I Do ?
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

// use new binary file as input for get_person_by_pin 
// FIXME: what is this portion??
int n = sizeof(newArray) / sizeof(newArray[0]);
   quickSort(newArray, 0, n - 1);
   
 
int partition (int newArray[], int low, int high)
{
   int pivot = newArray[high]; // pivot
   int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
   for (int j = low; j <= high - 1; j++)
   {
       // If current element is smaller than the pivot
       if (newArray[j] < pivot)
       {
           i++; // increment index of smaller element
           swap(&newArray[i], &newArray[j]);
       }
   }
   swap(&newArray[i + 1], &newArray[high]);
   return (i + 1);
}
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int newArray[], int low, int high)
{
   if (low < high){
       /* pi is partitioning index, arr[p] is now
       at right place */
       int pi = partition(newArray, low, high);
       // Separately sort elements before
       // partition and after partition
       quickSort(newArray, low, pi - 1);
       quickSort(newArray, pi + 1, high);
   }
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
    int beg = goto_first_person();
    // Set END = upper_bound
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
