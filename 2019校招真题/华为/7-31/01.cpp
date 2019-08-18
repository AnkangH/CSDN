#include<iostream>
#include<string>
#include <algorithm>
using namespace std;
int main()
{
	double price;
	string str;
	cin >> str;
	price = atof(str.c_str());
	int curInt = price * 1;
	double curDouble = price * 1;
	double error = min(abs(curDouble-curInt-1),abs(curDouble - curInt));
	int m;
	if (abs(curDouble - curInt - 1) < abs(curDouble - curInt))
		m = curInt + 1;
	else
		m = curInt;
	int n = 1;
	for (int i = 10000; i>=2; i--)//卖i件 从10000遍历是因为相同误差取较小的i
	{
		curInt = price * i;//向下取整
		curDouble = price * i;//当前的乘法浮点值
		double errorCur= min(abs(curDouble - curInt - 1), abs(curDouble - curInt));//乘法浮点值与向上取整和向下取整的最小差值
		if (errorCur <= error)//当前误差较小 取当前i
		{
			if (abs(curDouble - curInt - 1) < abs(curDouble - curInt))
				m = curInt + 1;//向上取整的误差比向下取整的误差小 保存向上取整
			else
				m = curInt;//否则保存向下取整
			n = i;//保存i
			error = errorCur;//更新最小误差
		}
	}
	cout << m << " " << n << endl;
	return 0;
}
