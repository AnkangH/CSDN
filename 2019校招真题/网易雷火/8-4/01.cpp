#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> window(n,vector<int>(m));//x1，y1 x2，y2
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
			cin >> window[i][j];//记录每个窗口的起始位置和大小
	}
	queue<int> q;//辅助队列
	for (int i = n - 1; i >= 0; i--)
		q.push(i);//后打开的窗口在上 所以从后向前放入队列
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;//当前鼠标点击点坐标
		vector<int> temp;//保存当前层的窗口顺序
		bool find = false;
		while (!q.empty())
		{
			int cur = q.front();
			//cout << "cur=" << cur << endl;
			q.pop();
			if (x >= window[cur][0] && x <= window[cur][0] + window[cur][2] && y >= window[cur][1] && y <= window[cur][1] + window[cur][3])//点击位置在当前窗口中
			{
				find = true;//找到窗口
				cout << cur+1 << endl;//当前窗口号
				temp.insert(temp.begin(), cur);//当前窗口放到队列首
				while (!q.empty())
				{
					temp.push_back(q.front());//队列剩余窗口id顺序出队列
					q.pop();
				}
			}
			else
				temp.push_back(cur);//点击点不在当前窗口中 出队列放入暂存数组
		}
		if (!find)
			cout << "-1" << endl;//当前点击点无窗口对应
		for (auto p : temp)
			q.push(p);//将本轮的窗口顺序入队列
	}
	return 0;
}
