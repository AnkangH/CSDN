#include <iostream>
#include <string>

using namespace std;

string add(string& a1, string& a2)
{
	string pre1, pre2, back1, back2;//切分两个浮点数的整数部分和小数部分
	int size1 = a1.size();
	for (int i = 0; i < size1; i++)
	{
		if (a1[i] != '.')
			pre1 += a1[i];//加数1的整数部分
		else
		{
			for (int j = i + 1; j < size1; j++)
				back1 += a1[j];//加数1的小数部分
			break;
		}
	}
	int size2 = a2.size();
	for (int i = 0; i < size2; i++)
	{
		if (a2[i] != '.')
			pre2 += a2[i];//加数2的整数部分
		else
		{
			for (int j = i + 1; j < size2; j++)
				back2 += a2[j];//加数2的小数部分
			break;
		}
	}
	string res1, res2;//两数之和的整数部分和小数部分
	if (pre1.empty())
		res1 = pre2;//加数1的整数部分为空
	else if (pre2.empty())
		res1 = pre1;//加数2的整数部分为空
	else
	{
		int flag = 0;
		int cur;
		size1 = pre1.size();
		size2 = pre2.size();
		int i = size1 - 1, j = size2 - 1;
		while (i >= 0 || j >= 0)//低位对齐求和
		{
			if (i < 0)
			{
				cur = pre2[j] - '0' + flag;
				res1.insert(res1.begin(), cur % 10 + '0');
				flag = cur / 10;
				j--;
			}
			else if (j < 0)
			{
				cur = pre1[i] - '0' + flag;
				res1.insert(res1.begin(), cur % 10 + '0');
				flag = cur / 10;
				i--;
			}
			else
			{
				cur = (pre1[i] - '0') + (pre2[j] - '0') + flag;
				res1.insert(res1.begin(), cur % 10 + '0');
				flag = cur / 10;
				i--;
				j--;
			}
		}
		if (flag != 0)
			res1.insert(res1.begin(), '1');//有进位 高位+1
	}
	if (back1.empty())
		res2 = back2;//加数1的小数部分为空
	else if (back2.empty())
		res2 = back1;//加数2的小数部分为空
	else
	{
		int flag = 0;
		int cur;
		size1 = back1.size();
		size2 = back2.size();
		int i = size1 - 1, j = size2 - 1;
		while (i >= 0 || j >= 0)//低位对齐
		{
			if (i < 0)
			{
				cur = back2[j] - '0' + flag;
				res2.insert(res2.begin(), cur % 10 + '0');
				flag = cur / 10;
				j--;
			}
			else if (j < 0)
			{
				cur = back1[i] - '0' + flag;
				res2.insert(res2.begin(), cur % 10 + '0');
				flag = cur / 10;
				i--;
			}
			else
			{
				cur = (back1[i] - '0') + (back2[j] - '0') + flag;
				res2.insert(res2.begin(), cur % 10 + '0');
				flag = cur / 10;
				i--;
				j--;
			}
		}
		if (flag != 0)//小数部分有进位
		{
			int size = res1.size();
			for (int i = size - 1; i >= 0; i--)//将进位加到整数部分
			{
				cur = res1[i]-'0' + flag;
				res1[i] = cur % 10 + '0';
				flag = cur / 10;
			}
			if (flag != 0)
				res1.insert(res1.begin(), '1');//进位持续到整数的高位 整数高位进1
		}
	}
	if (res2.empty())
		return res1;
	else
	{
		bool hasNum = false;
		for (auto p : res2)
			if (p != '0')
			{
				hasNum = true;
				break;
			}
		if (!hasNum)
			return res1;
		else
			return res1 + '.' + res2;//结果
	}
}


// please don't modify any code below.
int main(void) {
	string a1, a2, a3;
	cin >> a1 >> a2;
	a3 = add(a1, a2);
	cout << a3 << endl;
	return 0;
}
