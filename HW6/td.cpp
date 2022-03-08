#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Neal Archival
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.

// info on each DFA
struct info {
    string name;  // token name
    int startstate;
    int finalstate;
};

const int DFA_SIZE = 4;
info DFAs[DFA_SIZE];  // store up to 4 dfas' start and final

// defining the size of columns and rows as constant integers to be referred to later
const int COL_SIZE = 10; // column size of transition table
const int ROW_SIZE = 4;  // row size of transition table

int TRS[COL_SIZE][ROW_SIZE];  // store all trs's - states 0-9 and chars a b c d -- all dfas
                 // transitions are in here

// ----- utility functions -----------------------

int readTables() {
    ifstream fin("trs.txt", ios::in); // data to read transition table
    ifstream fin2("dfas.txt", ios::in); // data to read dfa's

	for (int i = 0; i < COL_SIZE; i++) {
		for (int j = 0; j < ROW_SIZE; j++) {
			int data = -100;
			fin >> data;
			TRS[i][j] = data;
			// fin >> TRS[i][j]; // load the read data into the table
		}
	}
	// declare variables to hold read data
	string dfa_name; // string to hold read dfa_name
	int dfaCount = 0; // integer to be returned
	int startState, endState; // states
	// read data into dfa
	while (fin2 >> dfa_name) {
		fin2 >> startState;
		fin2 >> endState;
		DFAs[dfaCount].name = dfa_name;
		DFAs[dfaCount].startstate = startState;
		DFAs[dfaCount].finalstate = endState;
		dfaCount++; // increment the dfaCount
	}
	
    // ** Read in the files into TRS and DFAs
    // ** Return how many DFAs were read
	cout << "Finished reading tables" << endl;
	return dfaCount; // return the number of DFA's that were read
}

void displayTables(int numDFAs) {
    // ** display DFAs nicely labeled
    // ** display TRS nicely labeled
	cout << "         a b c d" << endl;
	for (int i = 0; i < COL_SIZE; i++) {
		cout << "State " << i << ": ";
		for (int j = 0; j < ROW_SIZE; j++) {
			if (TRS[i][j] > -1) {
				cout << TRS[i][j] << " ";
			} else {
				cout << " " << " ";
			}
		}
		cout << endl;
	}
	// for loop to display the DFAs
	for (int i = 0; i < numDFAs; i++) {
		cout << DFAs[i].name  << ": " << DFAs[i].startstate << " " <<  DFAs[i].finalstate << endl; // printing DFA information
	}
}

bool accept(info dfa, string word) {
    // ** Does the dfa accept the word?
    // Start with the start state of the DFA and
    // look up the next state in TRS for each char in word.
    // At the end of the word, make sure you are in the
    // final state of the DFA.
    // Use a formula to convert chars to TRS col numbers.
	int currentState = dfa.startstate; // initialize state to the start state of the dfa tested
	for (string::size_type i = 0; i < word.length(); i++) {
		cout << "State: " << currentState << " Char: " << word[i] << endl;
		int colNum = word[i] - 'a'; // convert the read character into an integer to access a column
		if (colNum > 3 || colNum < 0) { // if not in the range of 1 to 4, then the column doesn't exist 
			return false; // reject the string, character is not in this dfa
		}
		cout << "New state: " << TRS[currentState][colNum] << endl; // access the transition table with the current state and column number to get the data
		currentState = TRS[currentState][colNum]; // update the current state to the new state in the transition table
		if (currentState == -1) return false;
	}
	if (currentState == dfa.finalstate) { // compare if we have reached final state
		return true; // if we have reached final state return true
	}
	return false; // this means we haven't reached final state so return false
}

int main() {
    cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
    cout << "States are 0 to 9 and chars are a to d" << endl;

    int numDFA = readTables();  // how many DFAs were read
    displayTables(numDFA);      // DISPLAY TABLES
    cout << ".....done reading tables...." << endl;

    string word;
    while (true) {
        cout << "@@Enter a string: ";
        cin >> word;
        // ** try the DFAs one by one and see
        //      if the word is accepted
		bool isStrValid = false; // bool variable that will let us know if a valid dfa was found
		for (int i = 0; i < numDFA; i++) {
			cout << "Trying DFA: " << i << "----------------------" << endl;
			if (accept(DFAs[i], word)) {
				cout << "Found token: " << DFAs[i].name << endl;
				isStrValid = true;
				break;
			}
		}
		if (isStrValid == false) {
			cout << "Lexical error" << endl;
		}
        //      if so, display the word and the token name
        // ** if no DFA does, generate a lexical error message.
        cout << "do control-C to quit" << endl;
    }

}  // the end
