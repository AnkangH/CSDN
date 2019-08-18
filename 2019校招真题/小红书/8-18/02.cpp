#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*
字符串反转 AC
*/
int main()
{
	string s;
	getline(cin, s);
	string temp;
	vector<string> res;
	int n = s.size();
	for (int i = n-1; i >=0; i--)
	{
		if (s[i] != ' ')
			temp += s[i];
		else
		{
			if (!temp.empty())
			{
				reverse(temp.begin(), temp.end());
				res.push_back(temp);
			}
			temp.clear();
		}
	}
	if (!temp.empty())
	{
		reverse(temp.begin(), temp.end());
		res.push_back(temp);
	}
	n = res.size();
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
