#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
void dfs(vector<int>& nums, vector<int>& temp, vector<int>& known, int idx);
bool check(vector<int>& nums);
set<vector<int>> res;
int n;
double precision = 0.00000001;
int main()
{
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	sort(nums.begin(), nums.end());
	vector<int> temp;
	vector<int> known(n, false);
	for (int i = 0; i < n; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		dfs(nums, temp, known, i);
	}
	int cnt = 0;
	for (auto p : res)
		if (check(p))
			cnt++;
	cout << cnt << endl;
	return 0;
}
void dfs(vector<int>& nums, vector<int>& temp, vector<int>& known, int idx)
{
	temp.push_back(nums[idx]);
	known[idx] = true;
	if (temp.size() == n)
		res.insert(temp);
	for (int i = 0; i < n; i++)
		if (!known[i])
			dfs(nums, temp, known, i);
	known[idx] = false;
	temp.pop_back();
}
bool check(vector<int>& nums)
{
	for (int i = 0; i < n - 1; i++)
	{
		double curDouble = sqrt(nums[i] + nums[i + 1]);
		int curInt = curDouble;
		if (abs(curDouble-curInt) > precision)
			return false;
	}
	return true;
}
