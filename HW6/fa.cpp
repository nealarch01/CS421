#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------
// CS421 File fa.cpp for HW2B DFA->Scanner Function
// Your name: Neal Archival
//------------------------------------------------

// ** Change this to fit the HW2B specification - look for **
// ** Must have the same types of tracing couts as mytoken.
// ** Must complete the ** comments with RE

// ---------- DFAs follow -------------------------

// MYTOKEN DFA done by professor as a sample
// This FA is for c d^+
bool mytoken(string s) {
    int state = 0; 
    int charpos = 0;

    cout << "Trying the mytoken machine..." << endl;

    while (s[charpos] != '\0') {
        cout << "current state: " << state << endl;
        cout << "character: " << s[charpos] << endl;

        if (state == 0 && s[charpos] == 'c')
            state = 1;
        else if (state == 1 && s[charpos] == 'd')
            state = 2;
        else if (state == 2 && s[charpos] == 'd')
            state = 2;
        else {
            cout << "I am stuck in state " << state << endl;
            return (false);
        }
        charpos++;
    }  // end of while

    // where did I end up????
    if (state == 2)
        return (true);  // end in a final state
    else
        return (false);
}  // end of mytoken

// IDENT DFA
// This FA is for RE: (c | d)(c | d | 8 | 9 | _)*
bool ident_token(string s) {
    // ** complete this based on mytoken
    cout << "Trying ident token" << endl; // print to console we are trying if string read is an identifier token (variable)
    int state = 0; // initialize the state to 0
	// for loop to iterate through string input
    for (string::size_type i = 0; i < s.length(); i++) {
        cout << "current state: " << state << endl; // print the current state
        cout << "character: " << s[i] << endl; // print the current character 
        if (state == 0) {
            switch (s[i]) {
                case ('c'):
                case ('d'): // cases to go to state 1
                    state = 1;
                    break;
                default:
                    cout << "I am stuck in state " << state << endl; // an unknown input is read
                    return false; // token is not an identifier, return false
            }
        } else if (state == 1) { // if at state one
            switch (s[i]) {
                case ('c'):
                case ('d'):
                case ('8'):
                case ('9'):
                case ('_'): // c,d,8,9,_ can have zero more
                    state = 1; // set state to one (stay in state)
                    break;
                default: 
                    cout << "I am stuck in state " << state << endl; // an unknown input is read
                    return false; // token is not an identifier, return false
            }
        }
    }
    if (state == 1) return true; // if we have reached end state, return true
    return false; // we have not reached end state
}  // end of ident

// REAL DFA
// This FA is for RE: (8|9)*.(8|9)+
bool real_token(string s) {
    cout << "Trying real token" << endl; // print to console checking if token is of real type
    int state = 0; // initialize state 
	// for loop to iterate through the string
    for (string::size_type i = 0; i < s.length(); i++) {
        cout << "current state: " << state << endl; // print to console the curent state
        cout << "character: " << s[i] << endl; // print the character being read
        if (state == 0) { // state = 0
            switch (s[i]) {
                case ('8'):
                case ('9'): // 8,9 can be repeated 0 or more
                    state = 0; // state = 0
                    break;
                case ('.'): // . period character to push input into the next state
                    state = 1; // move to state 1
                    break;
                default:
                    cout << "I am stuck in state " << state << endl; // unknown input was entered that isn't 8,9, or .
                    return false;
            }
        } else if (state == 1) { // when we are at a state 1, there needs to be one or more 8 or 9
            switch (s[i]) {
                case ('8'):
                case ('9'): // 8,9 is required after a '.'
                    state = 2; // move to the next state after receiving an 8 or 9 in state one
                    break;
                default:
                    cout << "I am stuck in state " << state << endl; // if character cannot transition
                    return false; 
            }
        } else if (state == 2) { // if state is 2
            switch (s[i]) { 
                case ('8'):
                case ('9'): // 8 or 9 can be repeated 0 or more times
                    state = 2;
                    break;
                default:
                    cout << "I am stuck in state " << state << endl;
                    return false;
            }
        }
    }
    if (state == 2) return true; // if we have reached final state, return true
    return false; // we have not reached final state, return false
    // ** complete this based on mytoken
}  // end of real

// INT DFA
//  This FA is for RE: (8|9)+
bool integer_token(string s) {
    // ** complete this based on mytoken
    cout << "Trying integer token" << endl;
    int state = 0;
    for (string::size_type i = 0; i < s.length(); i++) {
        cout << "current state: " << state << endl;
        cout << "character: " << s[i] << endl;
        if (state == 0) { // in case 0, we need one 8 or 9 to transition into next state
            switch (s[i]) {
                case ('8'):
                case ('9'):
                    state = 1; // 8 and 9 are valid decimals, transition to next state
                    break;
                default:
                    cout << "I am stuck in state " << state << endl; // invalid character was read
                    return false; // return false
            }
        } else if (state == 1) { // state is 1
            switch (s[i]) {
                case ('8'): 
                case ('9'): // repeated decimals
                    state = 1; // stay in final state
                    break;
                default:
                    cout << "I am stuck in state " << state << endl; // invalid character was read
                    return false; // return false
            }
        }
    }
    if (state == 1) return true; // if we have reached final state, return true
    return false; // we have not reached final state
}  // end of int

// -----------------------------------------------------

enum tokentype { ERROR, MYTOKEN, IDENT, REAL, INT };
int scanner(tokentype&, string&);  // to be called by main
fstream fin;                       // file stream to use

// The test-driver -- NO NEED TO CHANGE THIS
int main() {
    string fname;
    cout << "Enter the input file name:";
    cin >> fname;

    fin.open(fname.c_str(), fstream::in);

    string tokens[5] = {"ERROR", "MYTOKEN", "IDENT", "REAL", "INT"};
    tokentype thetype;
    string theword;

    while (true)  // keep on going
    {
        scanner(thetype, theword);  // the paramers will be set by Scanner
        if (theword == "EOF") break;

        cout << ">>>>>Type is:" << tokens[thetype] << endl;
    }

    cout << ">>>>>End of File encountered" << endl;
    fin.close();
}  // end of main

// Scanner sets the_type and w - TO BE COMPLETED **
int scanner(tokentype& the_type, string& w) {
    // This goes through all machines one by one on the input string w

    cout << endl;
    cout << ".....Scanner was called..." << endl;

    fin >> w;  // grab next word from fain.txt
    cout << ">>>>>Word is:" << w << endl;

    if (mytoken(w)) {
        the_type = MYTOKEN;
    }

    else if (ident_token(w)) {
        the_type = IDENT;
    }

    else if (real_token(w)) {
        the_type = REAL;
    }

    else if (integer_token(w)) {
        the_type = INT;
    }

    // ** add other if-then's here in the right order to go through
    // ** all FAs one by one and set the_type to be IDENT, REAL or INT.

    else  // none of the FAs returned TRUE
    {
        cout << ">>>>>Lexical Error: The string is not in my language" << endl;
        the_type = ERROR;
    }
    return 0;
}  // the very end of scanner
