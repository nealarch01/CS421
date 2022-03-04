#include<iostream>
#include<string>
using namespace std;

//-------------------------------------------------------
// CS421 HW1 
// Write a recognizer in C++ for L = {x | x is any coombination of a's and b's}.
// Your name: Neal Archival
// Compile command used: g++ -std=c++11 recognizer.cpp -o r.out
//-------------------------------------------------------

//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is a or b.
// Parameters: input string
// Pass by reference to save memory, adding const to make sure no unintended changes to the user input string (this function only recognizes, no mutations should happen to the input string)
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

//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout "YES IN L" or "NO NOT IN L" depending on what was returned.
int main() {
    string userInput; // string that is going to take the userinput
    // feel free to put it in a loop 
    while(1) {
        cout << "Enter your string: "; // prompt the user to enter a string
        std::getline(cin, userInput); // added std:: to specify we're using std::getline not std::cin::istream::getline // purpose: to read if input contains empty spaces
        recognizer(userInput) ? cout << "Yes, in language" : cout << "No, not in language"; // ternary conditional to print if input is in language
        cout << endl; // end line so we can redisplay the output
        userInput = ""; // make the string empty again so we can take new input
    } // end of loop
    return 0;
}// end of main
