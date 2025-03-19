#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> vec(5);
    for (int i = 0; i < vec.size(); i++)
    {
        cin >> vec[i];
    }

    ofstream fout;
    fout.open("test.txt");
    fout << "Original Data : ";

    for (int i = 0; i < vec.size(); i++)
    {
        fout << vec[i] << " ";
    }

    sort(vec.begin(), vec.end());
    fout << "\nSorted Data : ";
    for (int i = 0; i < vec.size(); i++)
    {
        fout << vec[i] << " ";
    }

    fout.close();

    ifstream fin;
    fin.open("test.txt");

    string line;
    while (getline(fin, line))
    {
        cout << line << endl;
    }

    fin.close();
}