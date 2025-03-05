#include <iostream>
using namespace std;
#include <vector>

void DNF(vector<int> &vec)
{
    int low = 0, mid = 0, end = vec.size() - 1;

    while (mid <= end)
    {
        if (vec[mid] == 0)
        {
            swap(vec[low], vec[mid]);
            mid++;
            low++;
        }
        else if (vec[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(vec[mid], vec[end]);
            end--;
        }
    }
}

int main()
{
    vector<int> vec = {0, 0, 1, 2, 0, 1, 0, 2, 0, 1, 2};
    DNF(vec);

    for (int i : vec)
    {
        cout << i << " ";
    }
}