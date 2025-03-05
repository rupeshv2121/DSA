#include <iostream>
#include <vector>
using namespace std;

int maxAscendingSum(vector<int> &nums)
{
    int sum = nums[0];
    int maxSum = sum;

    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] > nums[i - 1])
        {
            sum += nums[i];
        }
        else
        {
            maxSum = max(maxSum, sum);
            sum = nums[i];
        }
    }

    return max(maxSum, sum);
}

int main()
{
    vector<int> nums = {5, 6, 6, 6, 9, 1, 2};
    cout << maxAscendingSum(nums);
    return 0;
}