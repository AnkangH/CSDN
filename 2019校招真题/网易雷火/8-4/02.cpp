#include<iostream>
#include<vector>
using namespace std;
int main()
{
	while (1)
	{
		int p, q;
		cin >> p >> q;
		vector<vector<pair<int, int>>> nums(12);//12行的二叉树 构造方式杨辉三角 只看左子树即可
		nums[0] = { {0,1},{1,1} };//首尾元素 0 1 和 1 1
		if (p == q)
			cout << "1 1" << endl;//
		for (int i = 1; i < 12; i++)//构造其下每一层
		{
			int n = nums[i - 1].size();//上一层的节点个数
			nums[i].push_back({ 0,1 });//首节点
			for (int j = 0; j < n - 1; j++)//其后每两个节点之和作为当前层的当前节点
			{
				int a = nums[i - 1][j].first + nums[i - 1][j + 1].first;// c+a 
				int b = nums[i - 1][j].second + nums[i - 1][j + 1].second;//d+b
				if (p * b == q * a)//p/q = a/b  在当前左子树中
				{
					cout << i + 1 << " " << j + 1 << endl;//上一层每两个数字的和为当前层 所以序号对应
					break;
				}
				if (p * a == q * b)//p/q =b/a 在对称的右子树中
				{
					cout << i + 1 << pow(2,i)-j << endl;//行标不变 列标从后开始向前数
                    break;
				}
				nums[i].push_back({ a, b });//当前节点
				nums[i].push_back(nums[i - 1][j + 1]);//下个节点
			}
		}
	}
	return 0;
}
