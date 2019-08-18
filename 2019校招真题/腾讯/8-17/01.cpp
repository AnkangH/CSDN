#include<iostream>
#include<string>
#include<stack>
using namespace std;
string help(string s);
int main()
{
	string s;
	cin >> s;
	string res;
	stack<char> st;
	for (auto p : s)
	{
		if (p != ']')
			st.push(p);
		else
		{
			string temp;
			while (st.top() != '[')//一个基本表达式
			{
				temp += st.top();
				st.pop();
			}
			st.pop();//左括号出栈
			reverse(temp.begin(), temp.end());//恢复顺序
			string cur = help(temp);//计算一个基本表达式
			for (auto p : cur)
				st.push(p);//结果入栈
		}
	}
	while (!st.empty())//取出栈中所有字符
	{
		res += st.top();
		st.pop();
	}
	reverse(res.begin(), res.end());//恢复顺序
	cout << res << endl;
	return 0;
}
string help(string s)//计算一个基本表达式
{
	string res;
	string temp;
	int n = s.size();
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] != '|')
			temp += s[i];
		else
		{
			index = i + 1;
			break;
		}
	}
	int a = atoi(temp.c_str());
	temp = s.substr(index);
	for (int i = 0; i < a; i++)
		res += temp;
	return res;
}
