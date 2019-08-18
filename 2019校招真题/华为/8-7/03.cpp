#include<iostream>
#include<string>
#include<stack>
using namespace std;
string mid2back(string str);
char compute(string s);
int main()
{
	string str;
	cin >> str;
	string res;
	int n = str.size();
	for (int i = 0; i < n; i++)
	{
		if (str[i] != '!')
			res += str[i];
		else
		{
			if (str[i + 1] == '0')
				res += '1';
			else
				res += '0';
			i++;
		}
	}
	stack<char> s;
	for (auto p : res)
	{
		if (p != ')')
			s.push(p);
		else
		{
			string temp;
			while (s.top() != '(')
			{
				temp += s.top();
				s.pop();
			}
			s.pop();
			reverse(temp.begin(), temp.end());
			temp = mid2back(temp);
			s.push(compute(temp));
		}
	}
	string temp;
	while (!s.empty())
	{
		temp += s.top();
		s.pop();
	}
	reverse(temp.begin(), temp.end());
	temp = mid2back(temp);
	cout << compute(temp) << endl;
	return 0;
}
string mid2back(string str)
{
	stack<char> s;
	string res;
	for (auto p : str)
	{
		if (p == '1' || p == '0')
			res += p;
		else
		{
			if (s.empty())
				s.push(p);
			else
			{
				if (p == '|')
				{
					while (!s.empty())
					{
						if (s.top() == '&')
						{
							res += '&';
							s.pop();
						}
					}
				}
				else
					s.push(p);
			}
		}
	}
	while (!s.empty())
	{
		res += s.top();
		s.pop();
	}
	return res;
}
char compute(string str)
{
	stack<char> s;
	for (auto p : str)
	{
		if (p == '1' || p == '0')
			s.push(p);
		else if (p == '&')
		{
			char a = s.top();
			s.pop();
			char b = s.top();
			s.pop();
			if (a == '0' || b == '0')
				s.push('0');
			else
				s.push('1');
		}
		else
		{
			char a = s.top();
			s.pop();
			char b = s.top();
			s.pop();
			if (a == '1' || b == '1')
				s.push('1');
			else
				s.push('0');
		}
	}
	return s.top();
}
