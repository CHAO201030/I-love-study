#include<iostream>
#include<vector>

void test_arr()
{
	int arr[2][3] = { {0,1,2},{3,4,5} };
	std::cout << &arr[0][0] << " " << &arr[0][1] << " " << &arr[0][2] << std::endl;
	std::cout << &arr[1][0] << " " << &arr[1][1] << " " << &arr[1][2] << std::endl;
}

// LeetCode 704
int search(std::vector<int>&nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);

        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    if (left < nums.size() && nums[left] == target)return left;
    return -1;
}

// LeetCode 35
int searchInsert(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    int mid;
    while (left <= right)
    {
        mid = left + ((right - left) >> 1);

        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    return left;
}

// LeetCode 34
int find_first_pos(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);

        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            // 找第一个位置 向左走
            if (mid == left || nums[mid - 1] < target)
            {
                return mid;
            }
            right = mid - 1;
        }
    }
    return -1;
}

int find_last_pos(std::vector<int>& nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);

        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            // 找最后一个位置 向右走
            if (mid == right || nums[mid + 1] > target)
            {
                return mid;
            }
            left = mid + 1;
        }
    }
    return -1;
}

std::vector<int> searchRange(std::vector<int>& nums, int target)
{
    std::vector<int>res = { -1,-1 };
    res[0] = find_first_pos(nums, target);
    res[1] = find_last_pos(nums, target);

    return res;
}

int main()
{
	// test_arr();
    std::vector<int> nums = { 5,7,7,8,8,10 };
    //printf("%d\n", searchInsert(nums, 2));
    std::vector<int> res = searchRange(nums, 8);
	return 0;
}