#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

void countingSort(vector<int> &vec)
{
    if (vec.empty())
    {
        return;
    }

    int max = INT_MIN;
    // max element in vec
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] > max)
        {
            max = vec[i];
        }
    }
    vector<int> countVec(max + 1, 0);
    vector<int> output(vec.size());

    // calculate frequency
    for (int num : vec)
    {
        countVec[num]++;
    }

    // count vector
    for (int i = 1; i < countVec.size(); i++)
    {
        countVec[i] += countVec[i - 1];
    }

    // sorting
    for (int i = vec.size() - 1; i >= 0; i--)
    {
        int num = vec[i];
        int idx = --countVec[vec[i]];
        output[idx] = num;
    }
    vec = output;
}

void printVec(vector<int> &countVec)
{
    for (int i = 0; i < countVec.size(); i++)
    {
        cout << countVec[i] << " ";
    }
}

int main()
{
    vector<int> vec = {6, 4, 2, 9, 1, 3, 0, 4, 2};

    countingSort(vec);
    printVec(vec);
    return 0;
}