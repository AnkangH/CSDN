#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
bool check(const unordered_map<char, int>& dict);
//最多改动两处  题目求的是包含字母N的最长连续子串  该代码求得是任意字母的最长子串
int main()
{
	int round;
	cin >> round;
	for (int i = 0; i < round; i++)
	{
		string str;
		cin >> str;
		int n = str.size();
		int l = 0, r = 0;
		unordered_map<char, int> dict;
		int size = 0;
		while (r < n)
		{
			dict[str[r]]++;//记录当前
			if (!check(dict))
			{
				dict.clear();
				int k = r;
				while (k>0)
				{
					dict[str[k]]++;
					if (!check(dict))
					{
						dict[str[k]]--;
						if (dict[str[k]] <= 0)
							dict.erase(str[k]);
						break;
					}
					k--;
				}
				l = k+1;
			}
			if (r - l > size)
			{
				cout << "l=" << l << ",r=" << r << endl;
				size = r - l;
			}
			r++;
		}
		cout << size+1 << endl;
	}
	return 0;
}
bool check(const unordered_map<char, int>& dict)
{
	int size = dict.size();
	if (size > 3)
		return false;
	if (size == 3)
	{
		int n = 0;
		for (auto p : dict)
			if (p.second > 1)
				n++;
		if (n >= 2)
			return false;//3个数字 至少有两个数字次数>=2 不符
	}
	if (size == 2)//两个字母
	{
		int n = 0;
		for (auto p : dict)
			if (p.second > 2)
				n++;
		if (n > 1)
			return false;//出现次数都大于2 不符
	}
	return true;
}
