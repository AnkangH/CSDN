#include<iostream>
#include<vector>
#include<string>
using namespace std;
vector<int> getNext(string str);
//对输入字符串str求其最小匹配表next next[0]=-1,next[1]=0
vector<int> strKMP(string str1, string str2);
//求str1中与str2相同的字符串位置，返回相同字符串的起点坐标
//使用方法：str1.substr(start,str2.size());
//若str1中无str2的匹配，返回{-1},若str2为空，返回{0};所以{0}不一定意味着匹配，还有考虑str2的长度
int main()
{
	string s1{ "ababababcababskghibabskhbabab" };
	string s2{ "bab" };
	cout << "s1=" << s1 << endl;
	auto res = strKMP(s1, s2);
	for (auto p : res)
		cout << "s2=" << s1.substr(p, s2.size()) << ", occur at s1[" << p << "]" << endl;
	return 0;
}
vector<int> getNext(string s)
{
	//对字符串s求前缀后缀表的过程就是s和自身匹配的过程
	int size = s.size();
	vector<int> next(size + 1);
	next[0] = -1;
	int i = 0, j = -1;
	while (i < size)
	{
		if (j == -1 || s[i] == s[j])//j=-1时，直接赋值next[i]=0; 
		{
			i++;//i表征主字符串s的第i位
			j++;//j表征匹配字符串s的第j位
			next[i] = j;
		}
		else//j不为-1，且s[i]!=s[j]，此时想前回溯j
			j = next[j];//找到所有i之前的字符串中的最大前缀 若最大前缀均为0，则j最终=-1
	}
	return next;
}
vector<int> strKMP(string s1, string s2)
{
	if (s2.empty())
		return { 0 };//预判断 s2为空返回0
	if (s1.empty())
		return { -1 };//预判断 s1为空返回-1
	vector<int> res;//匹配结果
	int m = s1.size();
	int n = s2.size();
	vector<int> next = getNext(s2);
	int i = 0, j = 0;
	while (i < m)//求s1中所有s2的起始位置
	{
		if (j == -1 || s1[i] == s2[j])
		{
			i++;
			j++;
			if (j == n)
			{
				res.push_back(i - j);
				j = 0;
			}
		}
		else
			j = next[j];
	}
	return res;
}
