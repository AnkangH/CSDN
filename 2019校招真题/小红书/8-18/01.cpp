#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
void dfs(vector<int>& nums, int idx, int target);
int res = 0;
int nNum = 0;
/*
应该是输入处理有问题 输入格式 n [a1,a2,...,an]
代码没问题 64%
*/
int main()
{
	string s;
	getline(cin, s);
	int n = s.size();
	int idx = 0;
	string temp;
	for (int i = 0; i < n; i++)
	{
		if (s[i] != ' ')
			temp += s[i];
		else
		{
			idx = i + 2;//从第一个数字开始
			break;
		}
	}
	int target = atoi(temp.c_str());
	//cout << "target=" << target << endl;
	vector<int> nums;
	temp.clear();
	//cout << "idx=" << idx << endl;
	for (int i = idx; i < n; i++)
	{
		if (s[i] != ',' && s[i] != ']')
			temp += s[i];
		else
		{
			if(!temp.empty())
				nums.push_back(atoi(temp.c_str()));
			temp.clear();
		}
	}
	//for (auto p : nums)
		//cout << p << " ";
	//cout << endl;
	if (nums.empty())
	{
		cout << 0 << endl;
		return 0;
	}
	sort(nums.begin(), nums.end());
	nNum = nums.size();
	for (int i = 0; i < nNum; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		dfs(nums, i, target);
	}
	cout << res << endl;
	return 0;
}
void dfs(vector<int>& nums, int idx, int target)
{
	if (nums[idx] == target)
		res++;
	for (int i = idx; i < nNum; i++)
	{
		if (i > idx && nums[i] == nums[idx])
			continue;
		if (nums[i] <= target - nums[idx])
			dfs(nums, i, target - nums[idx]);
	}
}
