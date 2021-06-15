// most work should be done in this file


#include <iostream>
#include <string>

#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <chrono>

// added blocks for segmented reading and writing
#define BLOCK_SIZE 10000
#define BLOCKS 10

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

void adding_person(PersonData &pd, fstream &bin_file){

    Person p("254-86-5682", "Bruce Springsteen", "bruces@gmail.com", "singer", "5-262-667-4762");
    int line = pd.add_person(p, bin_file);

    cout << "---------------------------------------------" << endl;
    cout << "Person added to Line: "<< line << endl;
    cout << "---------------------------------------------" << endl;

}

void searching_person(PersonData &pd, fstream &ppm){

    Person p = pd.get_person_by_pin(254865682, ppm);

    if (p.isEmpty()){
        cout << "---------------------------------------------" << endl;
        cout << "Person ID not found!" << endl;
        cout << "---------------------------------------------" << endl;
    } else {
        show_person(p);
    }

}

// ADDED: function that reads from binary, from readdata.cpp
Person read_person(int pos, fstream &myfile){

    Person p;

    myfile.seekg(pos * PERSON_SIZE);    
    char buff[PERSON_SIZE];
    myfile.read((char*)buff, PERSON_SIZE);
    memcpy(&p, buff, PERSON_SIZE);

    return p;
}

// beginning of main
int main () {

    string line;
    PersonData pd;

    // START OF MAIN CODE EDITS
    // create a dynamic array to store the ID and Pin 
    // pointer for dynamically allocating array; pointer to DualData type
    DualData * pinSortedArray;

    // array size set to be able to hold entirety of data 
    int array_size = BLOCK_SIZE * 10;
    // allocate memory for array
    pinSortedArray = new DualData[array_size]; 

    /* goal: "create an array of your index structure, read blocks of records (person),
     or one by one, and add the key and record num in each array position. "
    */
    
    // create new file stream for the array storage file
    fstream workingFile ("workingFile.bin", ios::out |ios::binary); 

    // check to see if the created array binary file fails or if it's already made and good
    if(workingFile.fail()){
    // file does not exist or other error

    // incorporating struct 
    PersonData PD_1;
    // make person.bin == myfile stream
    PD_1.myfile << ("person.bin", ios::in | ios::out |ios::binary);
  
    // check if myfile is open
    if (PD_1.myfile.is_open()) {
        // call gotoFirstPerson to set seeker at beginning of file
        PD_1.goto_first_person();
        // new iterator for keeping track of array count
        // outside of loops so it will go 0-999,999
        int array_count = 0;
        // begin for loop that reads in blocks
        for (int n=0; n < BLOCKS; n++){
            // iteration begins at 0
            int i = 0; 
            // continue while end of file not reached
            while ( !PD_1.myfile.eof()) {        
                // goes to position i in person.bin and reads a person struct
                // FIXME: the error i get on this line below is weird and might be related to my compiler.... 
                Person person_input = read_person(array_count, PD_1.myfile);
                // first part of array pair is the record ID
                // starts at 1 because the first person is record 1, not record 0
                pinSortedArray[array_count].first = array_count + 1; 
                // second part of array pair is the PIN 
                // pin is in numeric form
                pinSortedArray[array_count].second = person_input.pin_n;
                // iteration of i and of array_count
                i++;
                array_count++;
                // break upon reaching block_size
                if (i >= BLOCK_SIZE) break;
            }
        }
    }
    else {
        // error msg for failure to open
        cout << "Error: Failure to open PERSON.BIN FILE" << endl;
    }

    // array built --> needs to be sorted
    // sorting function is in person.cpp 
    SortByPIN(pinSortedArray, array_size);

    // open the file to write to
    workingFile.is_open();
        
    // write to binary file function is in person.cpp
     WriteBin(pinSortedArray, workingFile, array_size);

    }

    // this final portion will execute regardless of whether the array was already built and stored
    
    //adds new person to file person.bin and to the stored array 
    adding_person(pd, workingFile);

    // start timer
    auto start = std::chrono::steady_clock::now();

    // use binary file to search
    // updated searching will perform a binary search instead of linear
    searching_person(pd, workingFile);

    // stop timer
    auto end = std::chrono::steady_clock::now();   
    std::chrono::duration<double> diff = end-start;

    // timer output
    cout << "---------------------------------------------" << endl;
    std::cout << "Elapsed time: " << diff.count() << " s\n";
    cout << "---------------------------------------------" << endl;

    return 0;
}