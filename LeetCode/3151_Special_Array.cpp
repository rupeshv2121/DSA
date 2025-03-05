#include <iostream>
#include <vector>
using namespace std;

bool isArraySpecial(vector<int> nums)
{

    // nums contains one element
    if (nums.size() == 1)
    {
        return true;
    }

    bool check = false;

    // nums contains n elements
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if ((nums[i] % 2 == 0 && nums[i + 1] % 2 != 0) || (nums[i] % 2 != 0 && nums[i + 1] % 2 == 0))
        {
            check = true;
        }
        else
        {
            check = false;
            break;
        }
    }

    return check;
}

int main()
{
    vector<int> nums = {4, 3, 1, 6};
    if (isArraySpecial(nums))
    {
        cout << "True";
    }
    else
    {
        cout << "False";
    }

    return 0;
}