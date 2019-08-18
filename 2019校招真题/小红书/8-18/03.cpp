#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
DP AC. dp[i][0]前i个挑选的最大值 dp[i][1]前i个最大值使用的个数
*/
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	if (n == 0)
	{
		cout << 0 << " " << 0 << endl;
		return 0;
	}
	if (n == 1)
	{
		cout << nums[0] << " "<<1 << endl;
		return 0;
	}
	if (n == 2)
	{
		cout << max(nums[0], nums[1]) << " " << 1 << endl;
		return 0;
	}
	vector<vector<int>> dp(n, {0,0});//[0] 最大点赞数 [1]点赞数使用的书本个数
	dp[0][0] = nums[0];
	dp[0][1] = 1;
	dp[1][0] = max(nums[0], nums[1]);
	dp[1][1] = 1;
	for (int i = 2; i < n; i++)
	{
		if (dp[i - 2][0] + nums[i] > dp[i - 1][0])//选第i个
		{
			dp[i][0] = dp[i - 2][0] + nums[i];
			dp[i][1] = dp[i - 2][1] + 1;
		}
		else//不选第i个
		{
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = dp[i - 1][1];
		}
	}
	cout << dp[n - 1][0] << " " << dp[n - 1][1] << endl;
	return 0;
}
