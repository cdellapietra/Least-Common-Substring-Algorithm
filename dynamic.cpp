#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// print the LCS based on the table of arrow characters
void printLCS(char **b, const string &x, int i, int j) {

    if(i == 0 || j == 0) return;
    if(b[i][j] == '\\') {
        printLCS(b, x, i - 1, j - 1);
        cout << x[i - 1];
    }
    else if(b[i][j] == '|') printLCS(b, x, i - 1, j);
    else printLCS(b, x, i, j - 1);
}

// compute the LCS of two strings
void LCS(const string &x, const string &y) {

    // declare variables to hold string lengths & tables
    int m = x.length(), n = y.length();

    // dynamically allocate our variable length tables    
    int** c = new int*[m + 1];
    for(int i = 0; i <= m; i++) c[i] = new int[n + 1];    

    char** b = new char*[m];
    for(int i = 0; i <= m; i++) b[i] = new char[n];
    
    // initialize first row & column to zeroes
    for(int i = 1; i <= m; i++) c[i][0] = 0;
    for(int j = 0; j <= n; j++) c[0][j] = 0;

    // compare string characters and build arrow table
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\';
            } 
            else if(c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '_';
            }
        }
    }

    // print the LCS
    printLCS(b, x, m, n);
}

int main(int argc, const char *argv[]) {

    // declare input file & string variables, then extract strings
    ifstream input_file;
    string string1, string2;

    input_file.open(argv[1]);
    input_file >> string1;
    input_file.close();

    input_file.open(argv[2]);
    input_file >> string2;
    input_file.close();

    // pass strings to LCS function
    LCS(string1, string2);
    cout << endl;

    return 0;
}
