#include<iostream> //for cout endl
#include<stack> //for stack
#include<string>// for string
#include<vector>// for vector
#include<algorithm> //for pow()
using namespace std;
string mid2back(string);//中缀计算表达式转后缀计算表达式
int compute(string);//计算后缀表达式 个位数 + - * /
int computeSuffix(vector<string>);//计算后缀表达式 int整数可多于1位 + - * /
bool priority(char a, char b);//辅助函数 判断两个运算符的优先级
bool priority(string a, string b);//辅助函数 判断两个运算符的优先级
int str2dec(string);//字符串转int
vector<string> str2str(const string&);//无空格运算表达式分割 
vector<string> infix2suffix(const vector<string>&);//分割后的字符串中缀转后缀
int main()
{
	/*
	//test for mid2back() and compute()
	string str1 = "6*((1-2)*5+(2-3)*8)";//中缀表达式 测试值
	string str2 = mid2back(str1);//改写的后缀表达式
	cout <<"infix: "<<str1 << endl;
	cout << "suffix: "<<str2 << endl;
	cout << str1<<"="<<compute(str2) << endl;*/
	//测试后缀表达式计算函数的正确性
	//vector<string> str3 = { "10","11","21","12","-","5","*","+","44","+","*" };
	//str=10*(11+(21-12)*5+44)=1000
	//cout << "10*(11+(21-12)*5+44)=" << computeSuffix(str3) << endl;
	//测试整个问题的解决正确性 输入为无分割的字符串
	string str4 = "10*(11+(21-12)*5+44)";//测试用例
	cout << "输入字符串=" << endl;
	cout << str4 << endl;
	vector<string> str5 = str2str(str4);//字符串分割
	cout << "分割后字符串=" << endl;
	for (int i = 0; i < str5.size(); i++)
		cout << str5[i]<<" ";
	cout << endl;
	cout << "由中缀表达式改写的后缀表达式=:" << endl;
	vector<string> str6 = infix2suffix(str5);//中缀改写后缀
	for (int i = 0; i < str6.size(); i++)
		cout << str6[i]<<" ";
	cout << endl;
	cout<<str4<<"="<<computeSuffix(str6) << endl;//计算结果
	return 0;
}
string mid2back(string s)
{
	string res;
	stack<char> st;
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		if (s[i] != '('&&s[i] != ')'&&s[i] != '+'&&s[i] != '*'&&s[i]!='-'&&s[i]!='/')
			res += s[i];//数字直接放入算术表达式
		if (s[i] == '(')
			st.push(s[i]);//'('左括号优先级最高 直接入栈
		if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '/')//或'*' '+' '-' '/'
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
	if (a == '+')
	{
		if (b == '(')
			return true;
		else
			return false;
	}
	if (a == '-')
	{
		if (b == '(')
			return true;
		else
			return false;
	}
	if (a == '*')
	{
		if (b == '('||b=='+'||b=='-')
			return true;
		else
			return false;
	}
	if (a == '/')
	{
		if (b == '('||b=='+'||b=='-')
			return true;
		else
			return false;
	}
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
		if (str[i] == '/')//执行乘法
		{
			int a = st.top();
			st.pop();
			int b = st.top();//取栈顶两元素
			st.pop();
			st.push(b / a);//乘法的积入栈
		}
	}
	return st.top();//返回后缀表达式的计算结果
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
vector<string> str2str(const string& str)
{
	int size = str.size();
	vector<string> res;
	string temp;
	for (int i = 0; i < size; i++)
	{
		if (str[i] != '+'&&str[i] != '-'&&str[i] != '*'&&str[i] != '/'&&str[i]!='('&&str[i]!=')')
			temp += str[i];
		if (str[i] == '+')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back("+");
		}
		if (str[i] == '-')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back("-");
		}
		if (str[i] == '*')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back("*");
		}
		if (str[i] == '/')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back("/");
		}
		if (str[i] == '(')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back("(");
		}
		if (str[i] == ')')
		{
			if (!temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			res.push_back(")");
		}
		if (i == size - 1&&!temp.empty())
			res.push_back(temp);
	}
	return res;
}
vector<string> infix2suffix(const vector<string>& s)
{
	vector<string> res;
	stack<string> st;
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		if (s[i] != "("&&s[i] != ")"&&s[i] != "+"&&s[i] != "*"&&s[i] != "-"&&s[i]!="/")
			res.push_back(s[i]);//数字直接放入算术表达式
		if (s[i] == "(")
			st.push(s[i]);//'('左括号直接入栈
		if (s[i] == "+" || s[i] == "*"|| s[i] == "-"||s[i]=="/")//+ -*/
		{
			if (st.empty())
				st.push(s[i]);//栈空 算术符号入栈
			else//否则根据算术符号优先级出栈
				while (1)
				{
					string temp = st.top();//栈顶算术符号
					if (priority(s[i], temp))//栈顶算术符号优先级高于当前算术符号
					{
						st.push(s[i]);//入栈
						break;//出循环
					}
					else
					{
						res.push_back(temp);//否则栈顶算术符号放入算术表达式
						st.pop();//直到当前算术符号优先级小于栈顶算术符号
						if (st.empty())//如果栈空 那么当前算术符号入栈
						{
							st.push(s[i]);
							break;//出循环
						}
					}
				}
		}
		if (s[i] == ")")//如果是右括号 
		{
			while (st.top() != "(")//算术符号出栈 直到栈顶为左括号
			{
				res.push_back(st.top());
				st.pop();
			}
			st.pop();//'('出栈 且不放入算术表达式
		}
	}
	while (!st.empty())//栈中剩余算术符号放入算术表达式
	{
		res.push_back(st.top());
		st.pop();
	}
	return res;//转换后的算术表达式
}
bool priority(string a, string b)
{
	//算术优先级a>b 返回true 这里注意(优先级低于所有的运算符 
	if (a == "+")
	{
		if (b == "(")
			return true;
		else
			return false;
	}
	if (a == "-")
	{
		if (b == "(" )
			return true;
		else
			return false;
	}
	if (a == "*")
	{
		if (b == "+" || b == "-" || b=="(")
			return true;
		else
			return false;
	}
	if (a == "/")
	{
		if (b == "+" || b == "-" || b == "(")
			return true;
		else
			return false;
	}
	return false;//语法要求必有返回值
}
