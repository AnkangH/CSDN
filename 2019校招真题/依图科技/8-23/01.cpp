#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;
void dfs(string& s, string& temp, vector<bool>known, int idx);
int n;
set<string> res;
int str2int(string s);
unordered_map<string, int> dict1;//个位
unordered_map<string, int> dict2;//十位
int main()
{
	string str;
	cin >> str;
	n = str.size();
	vector<string> num1{ "I","II","III","IV","V","VI","VII","VIII","IX" };
	vector<string> num2{ "X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
	for (int i = 0; i < 9; i++)
		dict1[num1[i]] = i + 1;
	for (int i = 0; i < 9; i++)
		dict2[num2[i]] = (i + 1) * 10;
	vector<bool>known(n, false);
	string temp;
	for (int i = 0; i < n; i++)
		dfs(str, temp, known, i);
	int minVal = INT_MAX;
	for (auto p : res)
		minVal = min(minVal, str2int(p));
	int a = minVal % 10;
	int b = minVal / 10;
	if (b == 0)
		cout << num1[a - 1] << endl;
	else
	{
		string temp;
		temp += num2[b - 1];
		temp += num1[a - 1];
		cout << temp << endl;
	}
	return 0;
}
void dfs(string& s, string& temp, vector<bool>known, int idx)
{
	temp += s[idx];
	known[idx] = true;
	if (temp.size() == n)
		res.insert(temp);
	for (int i = 0; i < n; i++)
		if (!known[i])
			dfs(s, temp, known, i);
	known[idx] = false;
	temp.pop_back();
}
int str2int(string s)
{
	int n = s.size();
	int res = INT_MAX;
	for (int i = 1; i <= n; i++)
	{
		string a = s.substr(0, i);//左侧为十位
		string b = s.substr(i);//右侧为各位
		//cout << "a=" << a << ",b=" << b << endl;
		if (!b.empty())
		{
			if (dict2.count(a) != 0 && dict1.count(b) != 0)
				res = min(res, dict2[a] + dict1[b]);
		}
		else
		{
			if (dict1.count(a))
				res = min(res, dict1[a]);
			if (dict2.count(a))
				res = min(res, dict2[a]);
		}
	}
	return res;
}
