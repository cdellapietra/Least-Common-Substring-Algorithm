#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string x, y;
int** c;
char** b; 

// print the LCS based on the table of arrow characters
void printLCS(int i, int j) {

    if(i == 0 || j == 0) return;
    if(b[i][j] == '\\') {
        printLCS(i - 1, j - 1);
        cout << x[i - 1];
    }
    else if(b[i][j] == '|') printLCS(i - 1, j);
    else printLCS(i, j - 1);
}

// recursive memoized function
int memoized(int i, int j) {
    // return if already initialized
    if(c[i][j] != -1) return c[i][j];
    else {
        if(i == 0 || j == 0) {
            c[i][j] = 0;
            b[i][j] = '|';
        }
        else if(x[i - 1] == y[j - 1]) {
            c[i][j] = memoized(i - 1, j - 1) + 1;
            b[i][j] = '\\';
        }
        else if(memoized(i, j - 1) >= memoized(i - 1, j)) {
            c[i][j] = memoized(i, j - 1);
            b[i][j] = '_';
        }
        else {
            c[i][j] = memoized(i - 1, j);
            b[i][j] = '|';
        }
        return c[i][j];
    } 
}

// compute the LCS of two strings
void LCS() {

    // declare variables to hold string lengths & tables
    int m = x.length(), n = y.length();

    // dynamically allocate our variable length tables    
    c = new int*[m + 1];
    for(int i = 0; i <= m; i++) c[i] = new int[n + 1];    

    b = new char*[m];
    for(int i = 0; i <= m; i++) b[i] = new char[n];
    
    // initialize first row & column to -1
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) c[i][j] = -1;
    }

    memoized(m, n);
    printLCS(m, n);
}

int main(int argc, const char *argv[]) {

    // declare input file & string variables, then extract strings
    ifstream input_file;

    input_file.open(argv[1]);
    input_file >> x;
    input_file.close();

    input_file.open(argv[2]);
    input_file >> y;
    input_file.close();

    // pass strings to LCS function
    LCS();
    cout << endl;

    return 0;
}
