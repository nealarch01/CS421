#include <iostream>
#include <string>
using namespace std;
// ** // include queue.h or equivalent such as <queue>
#include <queue>  // std::queue

//----------------------------------------------
// CS421 HW1
// Write a generator in C++ for L = {x | x is any combination of a's and b's}.
// Your name: Neal Archival
// Compile command used: g++ -std=c++11 generator.cpp -o g.out
//----------------------------------------------

// Copy the recognizer function here from the other file.
// **

bool recognizer(const string &s) {
    if (s.length() == 0) {
        return false; // empty string (lambda), which isn't isn't part of our language
    }
    for(string::size_type i = 0; i < s.length(); i++) { // for loop string iteration
        switch(s[i]) { // using switch statement to make it easier if we want to add additional valid characters to the language
            case('a'):
            case('b'):
                continue; // continue iterating through string
            default: 
                return false; // if a character, not a or b is found, return false
        }
    }
    return true; // finished iterating through the string with no invalid characters found so return true
}// end of recognizer

// main: It should create each string over E = {a,b,c} systematically
//   (short to long) and pass each string to the recognizer function
//   created in Part a).  Hint: use a queue to generate strings
//   Only those strings for which the recognizer returned TRUE
//   should be displayed.
//   Keeps on going until the queue overflows but the user can
//   terminate the program with control-C
//   after about 20 strings have been displayed.
int main() {
    queue<string> strQueue; // instantiate a queue that will be used to generate strings
    char E[] = {'a', 'b', 'c'}; // letters needed to create a string to be sent into the recognizer
    const int e_size = sizeof(E) / sizeof(E[0]); // const int of the size of the array
    for(int i = 0; i < e_size; i++) { // for loop to initialize the queue
      string emptyStr = "";
      strQueue.push(emptyStr + E[i]); // initialize the queue with the first three strings
    }
    int count = 0; // the count of how many strings should be displayed
    while (true) {
        // generate a string
        // if the recognizer says true, display it
        if(count == 20) {
          char contResponse; // character input variable to take user input whether to continue generating strings
          while(1) { // infinite loop that will prompt the user whether or not to continue
            cout << "Continue (y/n): "; // the cout prompt
            cin >> contResponse; // read user input
            contResponse = tolower(contResponse); // convert character to lowercase if upper case input is entered
            if(contResponse == 'n') { // if response read was 'N' or 'n'
              return 0; // end program is user doesn't want to continue generating strings
            } else if(contResponse == 'y') { // if user wants to generate more strings (y or Y) is entered
              count = 0; // reset count back to 0
              break; // break out the continue prompt loop, move control back to the generator loop
            }
          } // end of continue loop
        } // end of if 
        string recentStr = strQueue.front(); // .front() method returns the top most element of the queue (however, it doesn't remove the element from the queue)
        strQueue.pop(); // remove the string from the queue
        if(recognizer(recentStr)) { // if the recognizer detects 
          cout << recentStr << endl; // print out the string if it is part of the language
          count++; // increment count
        }
        // if not part of the language, continue
        for(int i = 0; i < e_size; i++) { // loop to append the generator strings into the last popped string
          strQueue.push(recentStr + E[i]); // push the string with the new element into the string
        }
    }  // end of while
    return 0;
}  // end of main


/*
a
b
c
aa
ab
ac

*/