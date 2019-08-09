#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> res;
void dfs(vector<int>& arr, vector<int>& temp, int target, int idx);
int m;
//重复元素不可重复选取组成目标值得互异组合数目
int main()
{
	vector<int> value{ 1,5,10,20,50,100 };//面值
	vector<int> nums = { 6,5,4,3,2,1 };//每种面值的数目
	vector<int> arr;
	int n = value.size();
	int target = 100;//要凑成的面值
	for (int i = 0; i < n; i++)
	{
		if (target < value[i])
			break;
		for (int j = 0; j < nums[i]; j++)
			arr.push_back(value[i]);//将多重背包转换为01背包
	}
	m = arr.size();//01背包的大小
	vector<int> temp;
	for (int i = 0; i < m; i++)
	{
		if (i > 0 && arr[i] == arr[i - 1])//相同的数字 不再作为首个选取的面值进行dfs
			continue;
		dfs(arr, temp, target, i);
	}
	cout << "总价值为" << target << "的组合方式为：" << endl;
	for (auto p : res)
	{
		for (auto pp : p)
			cout << pp << " ";
		cout << endl;
	}
	return 0;
}
void dfs(vector<int>& arr, vector<int>& temp, int target, int idx)
{
	temp.push_back(arr[idx]);
	if (arr[idx] == target)
		res.push_back(temp);
	for (int i = idx + 1; i < m; i++)
	{
		if (i >= idx + 2 && arr[i] == arr[i - 1])
			continue;//跳过重复组合 重复的1 1 1 1 只有索引连续才作为组合
		if (arr[i] <= target - arr[idx])
			dfs(arr, temp, target - arr[idx], i);//对剩余价值进行dfs
	}
	temp.pop_back();
}
