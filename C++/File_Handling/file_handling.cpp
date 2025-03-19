#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream fout;                 // open the file
    fout.open("test.txt");         // if file present it will open otherwise create and open the file.
    fout << "Hi, Rupesh Varshney"; // write in file

    fout.close();

    ifstream fin;
    fin.open("test.txt");

    char c;
    // fin >> c; // it will ignore the spaces
    c = fin.get();

    while (!fin.eof())
    {
        cout << c;
        // fin >> c;
        c = fin.get();
    }

    fin.close();

    return 0;
}