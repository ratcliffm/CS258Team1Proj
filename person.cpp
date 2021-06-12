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

// steps to take in order to perform the search: 

// FIXME: moved creation of array to main


// Read in binary file using blocks and assign to new array 
// FIXME: is this a function def?
//ios::binary_file_type  transorm_bin_into_array(og_bin_file) {

//my vers of func:

/* goal: "You can create an array of your index structure, 
read blocks of records (person), or one by one, and add the key and record num in each array position. "
*/
void transform_bin_into_array() {
// make person.bin == myfile stream
    fstream myfile ("person.bin", ios::in | ios::out |ios::binary);
    if (myfile.is_open()) {
        // call gotoFirstPerson to set seeker at beginning of file

// this is how i think we can actually assign as we move through this
dynamic_array[0].first = FIRST RECORD;
dynamic_array[0].second = FIRST PIN;

            for (int n=0; n < BLOCKS; n++){

            int i = 0;

            while ( getline (myfile,line) ) {            
                persons[i] = tokenize_line(line);
                i++;
                if (i >= BLOCK_SIZE) break;
            }

            myfile2.write((char*)&persons, sizeof(Person) * BLOCK_SIZE);

        }

        pinSortedArray read_new_array(int pos);
        pinSortedArray = new DualData[]; 

        return pinSortedArray;
        // FIXME: i dont think this needs to return anything... if it sorts within this function --> straight to storage with ye
    }
    else {
        // error msg for failure to open
        cout << "Error: Could Not Open File" << endl;
    }
    }



// sort the array by pin 
// FIXME: should this be void return type? i dont think it needs to return a pair
DualData SortByPIN(thearray) {
   DualData newarr;
   // sort through vector to return smallest coord
   for (unsigned int i = 0; i < thearray.size(); ++i) {
       for (unsigned int j = i + 1; j < thearray.size(); ++j) {
       if (thearray[i] < thearray[j]) {
           swap(thearray[i], thearray[j]);
       }
   } 
   }
for (unsigned int i = 0; i < thearray.size(); ++i) {
       for (unsigned int j = i + 1; j < thearray.size(); ++j) {
      newarr[i] = thearray[i]; 
newarr[j] = thearray[j]; 
       }return newarr; 

// write out the new array into a new binary file
void WriteBin(sortedArrayByPin, ofstream &oppm) {
 // for each pixel assign to color and then turn back to binary
// Do I need to be using blocks right here? I think I Do 
   for (int i = 0; i < sizeOf(sortedArrayByPin)/sizeof(int); ++i) {
     unsigned int p = DualData.pin;
     unsigned int r = DualData.ID;
     oppm.write(reinterpret_cast<char *>(&p), 1);
     oppm.write(reinterpret_cast<char *>(&r), 1);
   }
 // close file
 oppm.close();
}

// use new binary file as input for get_person_by_pin 
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
// End of team written code. 




// Code that Frabrizzio wrote and comments on what we need to do: 
// We need to update this function to take in the sorted array file and use quick sort
Person PersonData::get_person_by_pin(int pin){
// open the binary file
// read it in blocks and perform a quick search 
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