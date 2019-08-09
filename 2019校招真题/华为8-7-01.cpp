#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
int main()
{
	string s;
	cin >> s;
	string a, b;
	int n = s.size();
	for (int i = 0; i < n; i++)
	{
		if (s[i] != '@')
			a += s[i];
		else
		{
			for (int j = i + 1; j < n; j++)
				b += s[j];
			break;
		}
	}
	unordered_map<char, int> dict;
	vector<char> order;
	string temp;
	int size;
	char c;
	int cnt;
	for (auto p : a)
	{
		if (p != ',')
			temp += p;
		else
		{
			size = temp.size();
			c = temp[0];
			order.push_back(c);
			cnt = atoi(temp.substr(2, size).c_str());
			dict[c] = cnt;
			temp.clear();
		}
	}
	size = temp.size();
	c = temp[0];
	order.push_back(c);
	cnt = atoi(temp.substr(2, size).c_str());
	dict[c] = cnt;
	temp.clear();
	for (auto p : b)
	{
		if (p != ',')
			temp += p;
		else
		{
			size = temp.size();
			c = temp[0];
			cnt = atoi(temp.substr(2, size).c_str());
			dict[c] -= cnt;
			temp.clear();
		}
	}
	size = temp.size();
	c = temp[0];
	cnt = atoi(temp.substr(2, size).c_str());
	dict[c] -= cnt;
	string res;
	for(auto p:order)
		if (dict[p] > 0)
		{
			res += p;
			res += ":";
			res += to_string(dict[p]);
			res += ",";
		}
	if (!res.empty())
	{
		res.pop_back();
		cout << res << endl;
	}
	return 0;
}
