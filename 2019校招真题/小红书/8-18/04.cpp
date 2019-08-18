#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
/*
二分+贪心 67%
贪心用于确定m次必杀技 杀死怪物的最小回合
二分在1-max(nums[i])之间搜索
m一定，
当x=1时，每个怪物都需要nums[i]个回合 此时回合数最大
当x>=max(nums[i])时，每个怪物都需要1个回合 此时回合数最少
效率不够。超时。
*/
int main()
{
	int n, t, m;
	cin >> n >> t >> m;
	vector<int> hp(n);
	for (int i = 0; i < n; i++)
		cin >> hp[i];
	priority_queue<int> q;
	for (auto p : hp)
		q.push(p);
	int l = 1, r = q.top();//二分法的起点和终点
	while (l < r)
	{
		int mid = (r - l) / 2 + l;//当前的必杀技攻击力
		int mCur = m;//当前可使用m次必杀技
		auto qCur = q;//大顶堆初始状态
		int res = 0;//当前攻击次数
		while (!qCur.empty())
		{
			int cur = qCur.top();//当前最大血量怪物 优先使用必杀技
			qCur.pop();
			if (mCur > 0)//可使用必杀技
			{
				cur -= mid;//使用必杀技扣除mid血量
				mCur--;//必杀技使用次数-1
				if (cur > 0)
					qCur.push(cur);//未杀死 放入堆
			}
			else//不可使用必杀技
			{
				res += cur;//一次一点血量
				while (!qCur.empty())
				{
					res += qCur.top();//取出剩余所有怪物
					qCur.pop();
				}
				break;
			}
			res++;
		}
		//cout << "mid=" << mid<<",res="<<res;
		if (res <=t)//mid选大了
		{
			r = mid;
			//cout << ",r左移" << endl;
		}
		else
		{
			l = mid+1;
			//cout << ",l右移" << endl;
		}
	}
	//cout << "l=" << l << "r=" << r << endl;
	if(l<q.top())
		cout << r << endl;
	else
	{
		int res = 0;//当前攻击次数
		while (!q.empty())
		{
			int cur = q.top();//当前最大血量怪物 优先使用必杀技
			q.pop();
			if (m > 0)//可使用必杀技
			{
				cur -= l;//使用必杀技扣除mid血量
				m--;//必杀技使用次数-1
				if (cur > 0)
					q.push(cur);//未杀死 放入堆
			}
			else//不可使用必杀技
			{
				res += cur;//一次一点血量
				while (!q.empty())
				{
					res += q.top();//取出剩余所有怪物
					q.pop();
				}
				break;
			}
			res++;
		}
		if (res > t)
			cout << "-1" << endl;
		else
			cout << l << endl;
	}
	return 0;
}
