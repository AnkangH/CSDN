#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int res = 0;
void dfs(vector<vector<int>>& nums, int i, int j, int target);
int n;
int main()
{
	int target;
	cin >> n >> target;
	vector<vector<int>> nums(n, vector<int>(6));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 6; j++)
			cin >> nums[i][j];
		sort(nums[i].begin(), nums[i].end());
	}
	for (int i = 0; i < 6; i++)
		if (nums[0][i] <= target)
			dfs(nums, 0, i, target);
	cout << res << endl;
	return 0;
}
void dfs(vector<vector<int>>& nums, int r, int c, int target)
{
	if (nums[r][c] == target&&r==n-1)
		res++;
	for (int i = r + 1; i < n; i++)
		for (int j = 0; j < 6; j++)
		{
			if (nums[i][j] <= target - nums[r][c])
				dfs(nums, i, j, target - nums[r][c]);
			else
				break;
		}
}
