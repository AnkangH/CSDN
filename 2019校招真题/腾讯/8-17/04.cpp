#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	vector<int> res(n, 1);
	for (int i = 0; i < n; i++)
	{
		if (i - 1 >= 0)
		{
			int cur = nums[i - 1];
			res[i]++;
			for (int j = i - 2; j >= 0; j--)
				if (nums[j] > cur)
				{
					res[i]++;
					cur = nums[j];
				}
		}
		if (i + 1 < n)
		{
			int cur = nums[i + 1];
			res[i]++;
			for (int j = i + 2; j < n; j++)
				if (nums[j] > cur)
				{
					res[i]++;
					cur = nums[j];
				}
		}

	}
	for (int i = 0; i < n; i++)
	{
		cout << res[i];
		if (i != n - 1)
			cout << " ";
		else
			cout << endl;
	}
	return 0;
}
