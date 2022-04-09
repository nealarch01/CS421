
#include <stdlib.h>

#include <fstream>
#include <iostream>
// #include"stack.h"  // ** can be removed
#include <stack>  // standard lib stack
#include <string>
#include <vector>
using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Neal Archival
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.
stack<char> parseStack;
vector<char> M[3][2];  // the table of rules
                       // 3 rows for S, A, B
                       // 2 rows for 2, 3
                       // Each slot contains a rule's right side
                       // which is a vector of characters

//  ------- conversion functions ------------------------

// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C) {
    //**  bunch of if then else
    // special case for S
    if (C == 'S') {
        return 0;
    } else if (C == 'A') {
        return 1;
    } else if (C == 'B') {
        return 2;
    }
    // if character read is not S, A, or B, return -1 invalid row
    return -1;
}

// to convert '2' and '3' to table columns 0 and 1
int toCol(char c) {
    // ** bunch of if then else
    // when c is 2 return a 0
    // when c is 3 return a 1
    if (c == '2') {
        return 0;
    } else if (c == '3') {
        return 1;
    }
    // character read is not 2 or 3
    return -1;
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r) {
    // ** bunch of if then else
    if (r == 0) {
        return 'S';
    } else if (r == 1) {
        return 'A';
    } else if (r == 2) {
        return 'B';
    }
    return '-'; // number does not have an associated non-terminal, return a hyphen
}

// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V) {
    // ** display V horizontally e.g. 2 A 2
    for (int i = 0; i < V.size(); i++) {
        cout << V[i] << " ";
    }
}

// to read in the rules into M, make sure ; is not stored
void readrules() {
    ifstream fin("rules", ios::in);
    char rule;
    while (fin >> rule) {
        int row = toRow(rule);
        fin >> rule; // get input to access S
        int col = toCol(rule); // convert character into index position

        // if the conversion algorithm returns a character that is not recognized
        if (row == -1 || col == -1) {
            cout << "Unknown character encountered" << endl;
            continue;
        }
        M[row][col].push_back(rule);
        while (fin >> rule) {
            if (rule == ';') {
                break; // break out the loop to process next line
            }
            M[row][col].push_back(rule); // push the character into the vector
        }
    }

    // display the table
    for (int i = 0; i < 3; i++) {
        cout << toNonterm(i) << "| ";
        for (int j = 0; j < 2; j++) {
            displayVector(M[i][j]);
        }
        cout << endl;
    }
    // For each line of "rules" (e.g. S  2 A 2 ;)
    // The first char of a line determines the row of M
    // The second char of a line determine the column of M
    // Note that each entry of M (the second char up to ;)
    // will be a vector representing
    // the right hand side of a rule (rhs)

    // ** Display the table nicely
    //    use toNonterm to show row labels (S, A, B)
    //    use displayVector for each content
}

//  pushes V contents to the stack
void addtostack(vector<char> V) {
    cout << "Pushing rhs of a rule to the stack." << endl;
    // iterate backwards to put the first character as the top element of the stack
    for (int i = V.size() - 1; i >= 0; i--) {
        parseStack.push(V[i]);
    }
    // **  be careful of the order
    // because 3 2 2 means 3 will be at the top of the stack
}

// function to display the stack
void displayStack() {
    cout << "Stack" << endl;
    if (parseStack.empty()) {
        cout << "[ Empty ]" << endl;
    } else {
        stack<char> stackCopy = parseStack; // create a copy of the stack so we can display its content
        while (!stackCopy.empty()) {
            cout << stackCopy.top() << endl; // display the top element
            stackCopy.pop(); // remove the top element from the stack
        }
    }
    cout << "----------------------" << endl;
}

int main() {
    readrules();  // M is filled and displayed
    
    string ss;
    cout << "Enter a string made of 2's and/or 3's: ";
    cin >> ss;

    // ** push 'S' onto the stack to start
    parseStack.push('S');  // S initializes
    // ** display the stack vertically from top to bottom

    int i = 0;               // index for ss
    while (ss[i] != '\0') {  // for each char of ss
        string remainingInput = "";
        for (int j = i; j < ss.length(); j++) {
            remainingInput += ss[j];
        }
        cout << "remaining input string: " << remainingInput << endl;

        displayStack();
        if (parseStack.empty()) {
            cout << "mismatch: stack is empty" << endl;
            return 0; // return early, no more to process since stack is empty
        }
        cout << "current character is: " << ss[i] << endl;
        char charFromStack = parseStack.top(); // get the non-terminal from the stack
        parseStack.pop();

        int rowIndex = toRow(charFromStack);
        int colIndex = toCol(ss[i]); // obtain the next character of the string inputted

        // if column index is equal to negative one, the character read is either a non-terminal or is not part of the grammar rules
        if (colIndex == -1) {
            cout << "Error: character in string is not part of grammar rules" << endl;
            return 0; // terminate the program
        }
        
        // if statement to check if character in stack is a non terminal
        if (rowIndex != -1) { // not -1 means toRow read a terminal
            // since row index is a non-terminal then we add a rule into the stack
            addtostack(M[rowIndex][colIndex]);
            continue; // continue to the next iteration to not do any matching
        }

        if (ss[i] == charFromStack) {
            // match was successful
            cout << "match!" << endl;
        } else {
            // we have encountered a mismatch
            cout << "mismatch" << endl;
            return 0; // return early
        }

        // display the updated stack
        i++;
        // Based on ss[i] and
        //    the top of stack, update the stack:
        // ** note that empty stack will cause immediate failure
        // ** note that top of stack terminal and ss[i] mismatching
        //    will cause immediate failure
        // ** note that no entry in M for the top of stack (non-terminal)
        //    and ss[i] will cause immediate
        //    failure  (use toRow and toCol to look up M)
        // ** otherwise, addtoStack the M entry based on ss[i] and the top of
        // stack
    }  // end of string

    // ** Here, check for success for failure based on stack empty or not
    displayStack(); // printing the empty stack once more
    if (parseStack.empty()) {
        cout << "Accepted. String follows grammar rules" << endl;
    } else {
        cout << "Rejected. String is incomplete" << endl;
    }
    return 0;
}  // end of main
