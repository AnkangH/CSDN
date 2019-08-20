#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	int res = 0;
	for (int i = 1; i < n-1 ; i++)
	{
		int cnt = 1;
		for (int j = i; j >= 0; j--)
		{
			if (j - 1 >= 0 && nums[j] > nums[j - 1])
				cnt++;
		}
		for (int j = i; j < n; j++)
		{
			if (j + 1 < n && nums[j] > nums[j + 1])
				cnt++;
		}
		res = max(res, cnt);
	}
	if (res < 3)
		cout << 0 << endl;
	else
		cout << res << endl;
	return 0;
}
