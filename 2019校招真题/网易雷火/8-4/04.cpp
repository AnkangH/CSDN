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
	vector<int> resA, resB;
	int cnt = 0;
	bool round= true, a2 = true, b2 = true;
	int l = 0, r = n - 1;
	while (cnt < n)
	{
		if (round)//A先挑选
		{
			if (a2)//先挑大的
			{
				if (nums[r] > nums[l])
				{
					resA.push_back(nums[r]);
					r--;
				}
				else
				{
					resA.push_back(nums[l]);
					l++;
				}
			}
			else
			{
				if (nums[r] < nums[l])
				{
					resA.push_back(nums[r]);
					r--;
				}
				else
				{
					resA.push_back(nums[l]);
					l++;
				}
			}
			a2 = !a2;
		}
		else
		{
			if (b2)//先挑大的
			{
				if (nums[r] > nums[l])
				{
					resB.push_back(nums[r]);
					r--;
				}
				else
				{
					resB.push_back(nums[l]);
					l++;
				}
			}
			else
			{
				if (nums[r] < nums[l])
				{
					resB.push_back(nums[r]);
					r--;
				}
				else
				{
					resB.push_back(nums[l]);
					l++;
				}
			}
			b2 = !b2;
		}
		round = !round;
		cnt++;
	}
	//for (auto p : resA)
		//cout << p << " ";
	////cout << endl;
	//for (auto p : resB)
		//cout << p << " ";
	//cout << endl;
	int sizeA = resA.size();
	int res = 0;
	res += resA[0];
	for (int i = 1; i < sizeA; i++)
		res += abs(resA[i] - resA[i - 1]);
	cout << res << " ";
	res = 0;
	res += resB[0];
	int sizeB = resB.size();
	for (int i = 1; i < sizeB; i++)
		res += abs(resB[i] - resB[i - 1]);
	cout << res << endl;
	return 0;
}
