#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//--------------------------------------
// CS421 File mat.cpp for HW2A Matrix Practice
// Your name: Neal Archival
//--------------------------------------

// the following can be changed and the rest of the code should work
int const R = 3;   // number of rows
int const C = 4;   // number of columns
int const VM = 3;  // table entry (vector) length

vector<char> T[R][C];  // 3 rows and 4 columns table for now // array of vectors

// ------------------ Functions --------------------------------

int convert(char x) {
    // ** do a formula to convert m to 0, n to 1, o to 2 etc.
    return x - 'm'; // subtract the current char with 'm' which is implicitly converted into the ascii number
}

// this function reads the data from lines.txt
int readTable() {
    int row, col;  // row and col numbers
    char col_c;    // column indicator
    ifstream fin("lines.txt", ios::in);
    // Read in the file into T
    while (fin >> row) { // next line of file
        fin >> col_c;
        col = convert(col_c);  // convert to a slot number
        vector<char> v;        // a vector to fill
        char c;                // one char from the file
        for(int i = 0; i < VM; i++) { // for loop to read VM characters
            fin >> c; // store read character into c variable
            v.push_back(c); // push character into the vector
        }
        T[row][col] = v;
        // ** Fill v with chars from the file (there are VM chars)
        // ** Put  v in T[row][col]
    }  // end of while
    return 0;
}

// Displays a vector or "---" if the vector is empty
void showVector(vector<char> v) {
    if (v.size() == 0)  // empty entry
        for (int i = 1; i <= VM; i++) cout << "- "; // display dash if empty
    else
        for(int i = 0; i < VM; i++) {
            cout << v[i] << " ";
        }
    // show the content of v separated by blanks (e.g. "m n o")
}

// Displays T as a table, separating entries with "|"
void displayTable() {
    // ** display T nicely labeled with row numbers (col numbers not needed)
    for(int i = 0; i < R; i++) { // iterate through the rows first 
        cout << i << " | "; // print the current row index and bar for formatting
        for(int j = 0; j < C; j++) { // iterate through the columns index
            showVector(T[i][j]); // pass the vector in row and col into showVector function
            cout << " | "; // bar for separation formatting
        }
        cout << endl; // print a new line for the next row
    }
}

// Driver
int main() {
    cout << "Reading table from lines.txt..." << endl;
    readTable();
    displayTable();
    return 0;
}  // the end

