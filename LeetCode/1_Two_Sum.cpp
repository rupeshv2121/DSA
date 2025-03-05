#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// vector<int> twoSum(vector<int> &vec, int target)
// {
//     vector<int> vec2;
//     for (int i = 0; i < vec.size(); i++)
//     {
//         for (int j = i + 1; j < vec.size(); j++)
//         {
//             if (vec[i] + vec[j] == target)
//             {
//                 vec2.push_back(i);
//                 vec2.push_back(j);
//                 break;
//             }
//         }
//     }

//     return vec2;
// }

class test
{
public:
    vector<int> countingSort(vector<int> &vec)
    {
        // Calculate Max
        int max = INT_MIN;
        for (int i : vec)
        {
            if (max < i)
            {
                max = i;
            }
        }

        vector<int> countVec(max + 1, 0);
        vector<int> calCount(vec.size());

        // calculate frequency
        for (int i : vec)
        {
            countVec[i]++;
        }

        // calculate cumulative frequency
        for (int i = 1; i < countVec.size(); i++)
        {
            countVec[i] += countVec[i - 1];
        }

        // sorting
        for (int i = vec.size() - 1; i >= 0; i--)
        {
            int num = vec[i];
            int idx = --countVec[vec[i]];
            calCount[idx] = num;
        }

        return calCount;
    }

    vector<int> twoSum(vector<int> &vec, int target)
    {
        vec = countingSort(vec);
        vector<int> vec2;

        int si = 0;
        int ei = vec.size() - 1;
        while (si < ei)
        {
            if (vec[si] + vec[ei] == target)
            {
                vec2.push_back(si);
                vec2.push_back(ei);
                return vec2;
            }
            else if (vec[si] + vec[ei] > target)
            {
                ei--;
            }
            else
            {
                si++;
            }
        }
    }

    void printVec(vector<int> &countVec)
    {
        for (int i = 0; i < countVec.size(); i++)
        {
            cout << countVec[i] << " ";
        }
    }
};
int main()
{
    // vector<int> vec = {2, 7, 11, 19};

    // vector<int> vec2 = twoSum(vec, 9);
    // for (int i = 0; i < vec2.size(); i++)
    // {
    //     cout << vec2[i] << " ";
    // }

    vector<int> vec = {2, 7, 11, 19};
    test t;
    vector<int> vec2 = t.twoSum(vec, 9);
    t.printVec(vec2);

    return 0;
}