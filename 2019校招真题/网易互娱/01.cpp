#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
int one(int x);
int main()
{
	int t;
	cin >> t;
	int n;
	for (int i = 0; i < t; i++)
	{
		cin >> n;
		vector<int> nums(n);
		for (int i = 0; i < n; i++)
			cin >> nums[i];
		unordered_map<int, bool> dict;
		for (auto p : nums)
		{
			int cur = one(p);
			if (dict.count(cur) == 0)
				dict[cur] = true;
		}
		cout << dict.size() << endl;
	}
	return 0;
}
int one(int x)
{
	int res = 0;
	for (int i = 0; i < 32; i++)
	{
		if ((x & 1) == 1)
			res++;
		x = x >> 1;
	}
	return res;
}
