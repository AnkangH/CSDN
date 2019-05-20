#include<iostream> //for cout endl
#include<stack> //for stack
#include<string>// for string
#include<vector>
#include<algorithm> //for pow()
using namespace std;
int computeSuffix(vector<string>);//计算后缀表达式 int整数多于1位 + - * /
int str2dec(string);
int main()
{
	vector<string> str = { "10","11","21","12","-","5","*","+","44","+","*" };
	//str=10*(11+(21-12)*5+44)=1000
	cout << computeSuffix(str) << endl;
	return 0;
}
int computeSuffix(vector<string> str)
{
	int size = str.size();
	stack<int> st;
	for (int i = 0; i < size; i++)
	{
		if (str[i] != "+"&&str[i] != "-"&&str[i] != "*"&&str[i] != "/")
			st.push(str2dec(str[i]));
		if (str[i] == "+")
		{
			int a = st.top();
			st.pop();
			int b = st.top();
			st.pop();
			st.push(a + b);
		}
		if (str[i] == "-")
		{
			int a = st.top();
			st.pop();
			int b = st.top();
			st.pop();
			st.push(b - a);
		}
		if (str[i] == "*")
		{
			int a = st.top();
			st.pop();
			int b = st.top();
			st.pop();
			st.push(a * b);
		}
		if (str[i] == "/")
		{
			int a = st.top();
			st.pop();
			int b = st.top();
			st.pop();
			st.push(b / a);
		}
	}
	return st.top();
}
int str2dec(string str)
{
	int size = str.size();
	int res = 0;
	for (int i = 0; i < size; i++)
		res += (str[i] - '0')*pow(10, size-i-1);
	return res;
}
