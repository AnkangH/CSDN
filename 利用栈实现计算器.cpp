#include<iostream> //for cout endl
#include<stack> //for stack
#include<string>// for string
using namespace std;
string mid2back(string);//中缀计算表达式转后缀计算表达式
int compute(string);//计算后缀表达式
bool priority(char a, char b);//辅助函数 判断两个运算符的优先级
int main()
{
	string str="6523+8*+3+*";//真实后缀表达式
	string str1 = "6*(5+(2+3)*8+3)";//中缀表达式 测试值
	string str2 = mid2back(str1);//改写的后缀表达式
	cout <<"infix: "<<str1 << endl;
	cout << "suffix: "<<str2 << endl;
	if (str2 == str)
		cout << "suffix re-write succeed." << endl;
	cout << str1<<"="<<compute(str2) << endl;
	return 0;
}
string mid2back(string s)
{
	string res;
	stack<char> st;
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		if (s[i] != '('&&s[i] != ')'&&s[i] != '+'&&s[i] != '*'&&s[i]!='-')
			res += s[i];//数字直接放入算术表达式
		if (s[i] == '(')
			st.push(s[i]);//'('左括号优先级最高 直接入栈
		if (s[i] == '+'||s[i]=='*'||s[i]=='-')//或'*' '+' '-'
		{
			if (st.empty())
				st.push(s[i]);//栈空 算术符号入栈
			else//否则根据算术符号优先级出栈
			while (1)
			{
				char temp = st.top();//栈顶算术符号
				if (priority(s[i], temp))//栈顶算术符号优先级高于当前算术符号
				{
					st.push(s[i]);//入栈
					break;//出循环
				}
				else
				{
					res += temp;//否则栈顶算术符号放入算术表达式
					st.pop();//直到当前算术符号优先级小于栈顶算术符号
					if (st.empty())//如果栈空 那么当前算术符号入栈
					{
						st.push(s[i]);
						break;//出循环
					}
				}
			}

		}
		if (s[i] == ')')//如果是右括号 
		{
			while (st.top() != '(')//算术符号出栈 直到栈顶为左括号
			{
				res += st.top();
				st.pop();
			}
			st.pop();//'('出栈 且不放入算术表达式
		}
	}
	while (!st.empty())//栈中剩余算术符号放入算术表达式
	{
		res += st.top();
		st.pop();
	}
	return res;//转换后的算术表达式
}
bool priority(char a, char b)
{
	//算术优先级a>b 返回true
	//加法
	if (a == '+'&&b == '+')
		return false;
	if (a == '+'&&b == '*')
		return false;
	if (a == '+'&&b == '(')
		return true;
	if (a == '+'&&b == '-')
		return false;
	//减法
	if (a == '-'&&b == '+')
		return false;
	if (a == '-'&&b == '-')
		return false;
	if (a == '-'&&b == '*')
		return true;
	if (a == '-'&&b == '(')
		return true;
	//乘法
	if (a == '*'&&b == '+')
		return true;
	if (a == '*'&&b == '-')
		return true;
	if (a == '*'&&b == '*')
		return false;
	if (a == '*'&&b == '(')
		return true;
	return false;//语法要求必有返回值
}
int compute(string str)//根据后缀算术表达式计算值
{
	stack<int> st;
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		if (str[i] != '+'&&str[i] != '*'&&str[i]!='-')
			st.push(str[i] - '0');//数字入栈 注意char转int
		if (str[i] == '+')//执行加法
		{
			int a = st.top();
			st.pop();
			int b = st.top();//取栈顶两元素
			st.pop();
			st.push(a + b);//加法的和入栈
		}
		if (str[i] == '*')//执行乘法
		{
			int a = st.top();
			st.pop();
			int b = st.top();//取栈顶两元素
			st.pop();
			st.push(a*b);//乘法的积入栈
		}
		if (str[i] == '-')//执行乘法
		{
			int a = st.top();
			st.pop();
			int b = st.top();//取栈顶两元素
			st.pop();
			st.push(b-a);//乘法的积入栈
		}
	}
	return st.top();//返回后缀表达式的计算结果
}
