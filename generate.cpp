// Victor Perez
// CECS 325-02
// Prog 3 – Sorting Contest
// 03/07/23
//
// I certify that this program is my own original work. I did not copy any part of this program from
 // any other source. I further certify that I typed each and every line of code in this program
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 4) {
        cout << " Enter: generate numCount minNum maxNum" << endl;
        return 1;
    }
    int numCount = stoi(argv[1]);
    int minNum = stoi(argv[2]);
    int maxNum = stoi(argv[3]);

 
    ofstream out("numbers.dat");
    if (!out.is_open()) {
        cout << " Couldn't open file." << endl;
        return 1;
    }

    for (int i = 0; i < numCount; i++) {
        int generatedNum = rand() % (maxNum - minNum + 1) + minNum;
        out << generatedNum << endl;
    }

 
    out.close();

    return 0;
}