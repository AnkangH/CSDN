#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;
int main()
{
	string str;
	getline(cin, str);
	vector<string> nums;
	string temp;
	for (auto p : str)
	{
		if (p != ' ')
			temp += p;
		else
		{
			if(!temp.empty())
				nums.push_back(temp);
			temp.clear();
		}
	}
	if (!temp.empty())
		nums.push_back(temp);
	stack<int> s;
	for (auto p : nums)
	{
		if (p != "+" && p != "-" && p != "*" && p != "/")
			s.push(atoi(p.c_str()));
		else if (p == "+")
		{
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(a + b);
		}
		else if (p == "-")
		{
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(b-a);
		}
		else if (p == "*")
		{
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(a*b);
		}
		else
		{
			int a = s.top();
			s.pop();
			int b = s.top();
			s.pop();
			s.push(b/a);
		}
	}
	cout << s.top() << endl;
	return 0;
}
