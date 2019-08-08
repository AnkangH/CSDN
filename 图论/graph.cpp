#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<int> sortTopo(vector<vector<int>> ad, vector<int> inDec);//拓扑排序 ad为邻接表 inDec为节点的入度
void sortTopoResult(void);//显示拓扑排序的例子
vector<int> minPathGraphWithoutWeight(vector<vector<int>>ad, int n,int start, int end=-1);//无权无向图的最小路径算法
void minPathGraphWithoutWeightResult(void);//显示无权无向图的最小路径例程
vector<int> minPathGraphWithWeight(vector<vector<pair<int, int>>> ad, int n, int start, int end = -1);//显示有权有向图最小路径
void minPathGraphWithWeightResult(void);//有权有向图最小路径的显示例程
vector<int> minSpanningTree(vector<vector<pair<int, int>>>  ad, int n);//无向图最小生成树
void minSpanningTreeResult(void);//最小生成树显示例程
vector<int> minPathWithMinusWeight(vector<vector<pair<int, int>>> ad, int n, int start, int end = -1);//有负值权重有向图的最小路径
void minPathWithMinusWeight(void);//有负值权重的有向图最小路径例程
int main()
{
	cout << "Please call function. " << endl;
	return 0;
}
vector<int> sortTopo(vector<vector<int>> ad, vector<int> cnt)
{
	int n = cnt.size();//节点个数
	queue<int> q;//辅助队列 顺序访问
	for (int i = 0; i < n; i++)
		if (cnt[i] == 0)
			q.push(i);//入度为0的节点入队列
	vector<int> res;//拓扑排序
	while (!q.empty())
	{
		int cur = q.front();//当前节点
		res.push_back(cur);//放入拓扑排序
		q.pop();//出队列
		auto adCur = ad[cur];//当前节点的邻接节点
		for (auto p : adCur)//遍历每一个节点p
		{
			cnt[p]--;//邻接节点p的入度减1
			if (cnt[p] == 0)//入度为0
				q.push(p);//放入队列
		}
	}
	if (res.size() == n)//所有节点均拓扑有序
		return res;
	else
		return {};//无拓扑排序
}
void sortTopoResult(void)
{
	int n = 5;//节点个数
	vector<vector<int>> ad(5);
	ad[0] = { 2,3,4 };//1邻接3 4 5
	ad[1] = { 0,2,3 };//2邻接 1 3 4
	ad[2] = { 4 };//3邻接 5
	ad[3] = { 4 };//4邻接 5
	ad[4] = {};//5无邻接
	vector<int> cnt(n, 0);
	for (auto p : ad)
		for (auto pp : p)
			cnt[pp]++;
	vector<int> sortTopoNum = sortTopo(ad, cnt);
	if (sortTopoNum.empty())
		cout << "Graph has not topo sort arr." << endl;
	else
	{
		for (auto p : sortTopoNum)
			cout << p + 1 << " ";//图中节点序号与数组索引对齐
		cout << endl;
	}
}
vector<int> minPathGraphWithoutWeight(vector<vector<int>>ad, int n,int start, int end)//无权无向图的最小路径算法
{
	start--;//节点序号与索引对齐
	end--;//节点序号与索引对齐
	queue<int> q;
	vector<bool> known(n, false);
	vector<int> res(n,-1);//起始距离为-1
	q.push(start);
	known[start] = true;
	int layer = 0;
	while (!q.empty())
	{
		int size = q.size();//当前层的节点个数
		for (int i = 0; i < size; i++)//遍历当前层
		{
			auto cur = q.front();//当前节点
			q.pop();//出队列
			res[cur] = layer;//记录最小路径
			if (cur == end)
				return res;//指定终点 提前退出
			for(auto p:ad[cur])
				if (!known[p])//未访问
				{
					q.push(p);//放入队列
					known[p] = true;//记录已在队列中
				}
		}
		layer++;//层序增加
	}
	return res;
}
void minPathGraphWithoutWeightResult(void)
{
	int n = 7;
	vector<vector<int>> ad(n);
	ad[0] = { 1,2 };
	ad[1] = { 0,3 };
	ad[2] = { 0,3,5 };
	ad[3] = { 1,2,5,6 };
	ad[4] = { 6 };
	ad[5] = { 2,3 };
	ad[6] = { 3,4 };
	int start = 3;
	vector<int> path = minPathGraphWithoutWeight(ad, n, start);//path[i]=path start->(i+1)
	cout << "minPath of Vertex" << start << " to every Vertex:" << endl;
	for (auto p : path)
		cout << p << " ";
	cout << endl;
	int end = 2;
	path = minPathGraphWithoutWeight(ad, n, start, end);
	cout << "minPath of Vertex" << start << " to Vertex" << end << endl;
	for (auto p : path)
		cout << p << " ";
	cout << endl;
}
vector<int> minPathGraphWithWeight(vector<vector<pair<int, int>>> ad, int n, int start, int end)
{
	start--;//序号对齐
	end--;//序号对齐
	vector<int> res(n,INT_MAX);
	vector<bool> known(n, false);
	res[start] = 0;
	//queue<int> q;
	int cur = start;//当前节点
	while (cur != -1)//当没有下个需要更新或者能更新的节点 置cur为-1 使循环退出
	{
		known[cur] = true;
		if (cur == end)
			return res;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> s;//使用小顶堆求当前下个待处理节点
		for(auto p:ad[cur])
			if (!known[p.first])//未读节点
			{
				res[p.first] = min(res[p.first], res[cur] + p.second);//更新最小距离
				s.push({ res[p.first],p.first});//放入小顶堆 求下一个节点
			}
		if (s.empty())//没有需要更新的节点或没有能更新的节点了
			cur = -1;//结束
		else
			cur = s.top().second;
	}
	return res;
}
void minPathGraphWithWeightResult(void)
{
	int n = 7;
	vector<vector<pair<int, int>>> ad(n);
	ad[0] = { {3,1} };
	ad[1] = { {3,3},{4,10} };
	ad[2] = { {0,4},{5,5} };
	ad[3] = { {2,2},{5,8},{6,4},{4,2} };
	ad[4] = { {6,6} };
	ad[5] = {};
	ad[6] = { {5,1} };
	vector<int> path = minPathGraphWithWeight(ad, n, 3);
	for (auto p : path)
		cout << p << " ";
	cout << endl;
}
vector<int> minSpanningTree(vector<vector<pair<int, int>>>  ad, int n)
{
	vector<bool> known(n, false);//记录每个顶点是否已读
	vector<int> res(n,-1);//记录每个顶点连接的顶点
	vector<int> cost(n, INT_MAX);//cost[i]=min(w(j,i)) 所有邻接到i的边的最小权重 初值为INT_MAX便于取min
	queue<int> q;
	q.push(0);//从顶点1开始构建最小生成树 起点任意
	known[0] = true;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		auto adj = ad[cur];//cur的所有边
		for (auto p : adj)
			if (!known[p.first] && cost[p.first] > p.second)
			{
				res[p.first] = cur;//记录边 要在更新当前边的cost时 更新连接的顶点
				cost[p.first] = p.second;
			}
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> s;//小顶堆 求当前顶点的最小边
		for (int i = 0; i < n; i++)
			if (!known[i])
				s.push({ cost[i],i });
		if (!s.empty())
		{
			int nxt = s.top().second;//当前顶点在最小生成树中的边 做为下个顶点
			q.push(nxt);
			known[nxt] = true;//记为已读
		}
		cout << "cur=" << cur+1 << ":";//当前顶点和 当前轮每个顶点的连接情况
		for (auto p : res)
			cout << p + 1 << " ";
		cout << endl;
	}
	return res;
}
void minSpanningTreeResult(void)
{
	int n = 7;
	vector<vector<pair<int, int>>> ad(n);
	ad[0] = { {1,2},{3,1},{2,4} };
	ad[1] = { {0,2},{3,3},{4,10} };
	ad[2] = { {0,4},{3,2},{5,5} };
	ad[3] = { {0,1},{1,3},{2,2},{4,7},{5,8},{6,4} };
	ad[4] = { {1,10},{3,7},{6,6} };
	ad[5] = { {2,5},{3,8},{6,1} };
	ad[6] = { {3,4},{5,1},{4,6} };
	vector<int> res = minSpanningTree(ad, n);
	for (int i = 0; i < n; i++)
		cout << "Vertex" << i + 1 << " link Vertex" << res[i] + 1 << endl;
}
vector<int> minPathWithMinusWeight(vector<vector<pair<int, int>>> ad, int n,int start,int end)
{
	start--;//顶点序号与索引对齐
	end--;//顶点序号与索引对齐
	vector<int> path(n, INT_MAX);//从start出发到其他顶点的最小距离
	path[start] = 0;//起点到起点的最小距离 初始值为0
	for (int i = 0; i <= n; i++)//若能进入第n次循环说明存在负值圈
	{
		if (i == n)
			return {};//有负值圈时返回空 当i==n时能更新（更小路径）的顶点都是在负值圈上的点
		bool update = true;//记录本轮是否有更新 若无更新 说明已达到所有顶点的最小路径 若指定end顶点 则update只检测end顶点是否更新
		//遍历每条边 若d[u]不为INT_MAX 则以min(path[u]+w(u,v),path[u])更新v j记录边的起点 p.first为边的终点 p.second为边的权重
		for (int j = 0; j < n; j++)
		{
			if (path[j] == INT_MAX)
				continue;//起点为j的路径 s->j还未更新
			for (auto p : ad[j])//遍历起点为顶点j的每条边
			{
					if (path[p.first] > path[j] + p.second)//path[v]>path[u]+w(u,v)
					{
						path[p.first] = path[j] + p.second;//更新start->v的最小路径
						update = false;//记录本轮有最小路径更新
					}
			}
		}
		if (update)
			break;//该轮没有更小的路径更新 说明已经迭代已经停止
	}
	return path;
}
void minPathWithMinusWeight(void)
{
	int n = 4;
	int start = 1;
	vector<vector<pair<int, int>>> ad(n);
	ad[0] = { {1,8},{3,4} };
	ad[1] = { {3,-5} };
	ad[2] = {};
	ad[3] = { {2,3} };
	vector<int> res = minPathWithMinusWeight(ad, n, start);//从顶点1出发的所有最小路径
	for (int i = 0; i < n; i++)
		cout << "Path of " << start << " to " << i + 1 << " = " << res[i] << endl;
}
