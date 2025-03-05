#include <iostream>
#include <vector>
using namespace std;

int longestMonotonicSubArray(vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int maxCount = 1, maxCount2 = 1;
    int count = 1, count2 = 1;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] < nums[i - 1])
        {
            count++;
            count2 = 1;
        }
        else if (nums[i] > nums[i - 1])
        {
            count2++;
            count = 1;
        }
        else
        {
            count2 = 1;
            count = 1;
        }

        maxCount = max(count, maxCount);
        maxCount2 = max(count2, maxCount2);
    }

    return max(maxCount, maxCount2);
}

int main()
{
    vector<int> nums = {1, 4, 3, 3, 2};
    cout << longestMonotonicSubArray(nums);
    return 0;
}