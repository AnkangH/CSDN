#include<iostream>			//for cout endl
#include<vector>			//for vector
#include<queue>				//for queue
#include<unordered_map>		//for unordered_map
#include<algorithm>			//for min()
using namespace std;
struct Vertex
{
	vector<pair<int, int>> ad;//当前节点的邻接表
	bool known;//标记访问
	int dis;//起点到当前节点的最小距离
};
void bfsViaStruct(void);
//bfs搜索 结构体实现 求无向图赋权最小路径
vector<int> bfsOfWeightGraph(const unordered_map<int, vector<pair<int, int>>>& graph, int start, int end = -1);
//Dijkstra算法求赋权最小路径 graph为邻接表 索引从0开始 start与end的索引从0开始，+1代表节点索引
vector<pair<int, int>> primOfWeightGraph(const unordered_map<int, vector<pair<int, int>>>& graph);
//Prim算法求赋权无向图的最小生成树
int main()
{
	unordered_map<int, vector<pair<int, int>>> graph;
	graph[1] = { {2,2},{4,1},{3,4} };
	graph[2] = { { 1,2 },{ 4,3 },{ 5,10 } };
	graph[3] = { { 1,4 },{ 4,2 },{ 6,5 } };
	graph[4] = { { 1,1 },{ 2,3 },{ 5,7 },{7,4},{6,8},{3,2} };
	graph[5] = { { 2,10 },{ 4,7 },{ 7,6 } };
	graph[6] = { { 3,5 },{ 4,8 },{ 7,1 } };
	graph[7] = { { 4,4 },{ 6,1 },{ 5,6 } };
	auto prim = primOfWeightGraph(graph);
	int size = prim.size();
	cout << "Afted Find minimum Tree :" << endl;
	int minPath = 0;
	for (int i = 1; i < size; i++)
	{
		cout << "Vertex" << i << ",Link Vertex" << prim[i].first << " ,path=" << prim[i].second << endl;
		minPath += prim[i].second;
	}
	cout << "MinPath=" << minPath << endl;
	/*
	// Dijkstra算法求赋权有向图的最小路径测试用例
	//赋权图 注意图中顶点序号-1为储存结构中的索引
	unordered_map<int, vector<pair<int, int> > >graph;
	graph[0] = { { 1,2 },{ 3,1 } };
	graph[1] = { { 3,3 },{ 4,10 } };
	graph[2] = { { 0,4 },{ 5,5 } };
	graph[3] = { { 2,2 },{ 5,8 },{ 6,4 },{ 4,2 } };
	graph[4] = { { 6,6 } };
	graph[5] = {};
	graph[6] = { { 5,1 } };
	//求顶点1到所有顶点的最小赋权距离
	vector<int>dist = bfsOfWeightGraph(graph, 0);
	cout << "Dist of Vertex1 to all other Vertexs:" << endl;
	int sizeDist = dist.size();
	for (int i = 0; i<sizeDist; i++)
		cout << "dist[1]-dist[" << i + 1 << "]=" << dist[i] << endl;
	//求顶点2到顶点7的最小赋权距离
	//vertexIndex-1=arrIndex
	int start = 1;//顶点2
	int end = 6;//顶点7
	cout << "Dist of Vertex" << start + 1 << " to Vertex" << end + 1 << ":" << endl;
	dist = bfsOfWeightGraph(graph, start, end);
	cout << "dist[" << start + 1 << "]-dist[" << end + 1 << "]=" << dist[end] << endl;
	*/
	return 0;
}
void bfsViaStruct(void)
{
	//构建有向赋权图
	int vertexSize = 8;
	auto graph = new Vertex[vertexSize];
	graph[1].ad = { { 2,2 },{ 4,1 } };
	graph[2].ad = { { 4,3 },{ 5,10 } };
	graph[3].ad = { { 1,4 },{ 6,5 } };
	graph[4].ad = { { 3,2 },{ 6,8 },{ 7,4 },{ 5,2 } };
	graph[5].ad = { { 7,6 } };
	graph[6].ad = {};
	graph[7].ad = { { 6,1 } };
	for (int i = 2; i < vertexSize; i++)
	{
		graph[i].known = false;
		graph[i].dis = INT_MAX;
	}
	graph[1].dis = 0;
	//BFS
	queue<int>q;
	q.push(1);
	graph[1].known = true;
	while (!q.empty())
	{
		int cur = q.front();//当前节点
		q.pop();
		auto p = graph[cur].ad;//当前节点的邻接节点
		int size = p.size();
		//当前节点的所有未访问邻接节点更新
		for (int i = 0; i < size; i++)
			if (!graph[p[i].first].known)//遍历邻接节点
				graph[p[i].first].dis = min(graph[p[i].first].dis, graph[cur].dis + p[i].second);
		//取最小值	 		     上个邻接节点修改后的距离    当前节点修改后的距离
		//打印结果
		cout << "Vertex " << cur << "is known, dis[1]-dis[7]=" << endl;
		for (int i = 1; i < vertexSize; i++)
			cout << graph[i].dis << " ";
		cout << endl;
		//以未访问的节点中，最小距离最小的节点为下一个节点
		int minIndex = INT_MAX;
		int minVal = INT_MAX;
		for (int i = 1; i < vertexSize; i++)//遍历图节点
			if (graph[i].known == false)//若节点未访问
			{
				if (minIndex == INT_MAX)//首次赋值
				{
					minIndex = i;
					minVal = graph[i].dis;
				}
				else//取最小值，保存其对应索引
				{
					if (graph[i].dis < minVal)
					{
						minVal = graph[i].dis;
						minIndex = i;
					}
				}
			}
		//若存在未访问最小节点 则入队列，标记已读
		if (minIndex != INT_MAX)
		{
			q.push(minIndex);
			graph[minIndex].known = true;
		}
	}
}
vector<int> bfsOfWeightGraph(const unordered_map<int, vector<pair<int, int>>>&graph, int start, int end)
{
	if(end==-1)//求所有终点
	{ 
		int sizeGraph = graph.size();
		vector<int> dist(sizeGraph);
		unordered_map<int, bool> known;
		queue<int> q;
		for (int i = 0; i < sizeGraph; i++)
		{
			if (i == start)
				dist[i] = 0;
			else
				dist[i] = INT_MAX;
		}
		q.push(start);
		known[start] = true;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			auto adj = graph.find(cur)->second;
			int sizeAdj = adj.size();
			for (int i = 0; i < sizeAdj; i++)
			{
				if (known.count(adj[i].first) == 0)
					dist[adj[i].first] = min(dist[adj[i].first], dist[cur] + adj[i].second);
			}
			int minVal = INT_MAX;
			int minIndex = INT_MAX;
			for (int i = 0; i < sizeGraph; i++)
			{
				if (known.count(i) == 0)
				{
					if (minVal == INT_MAX)
					{
						minVal = dist[i];
						minIndex = i;
					}
					else if (dist[i] < minVal)
					{
						minVal = dist[i];
						minIndex = i;
					}
				}
			}
			if (minIndex != INT_MAX)
			{
				q.push(minIndex);
				known[minIndex] = true;
			}
		}
		return dist;
	}
	else//求指定终点
	{
		int sizeGraph = graph.size();
		vector<int> dist(sizeGraph);
		unordered_map<int, bool> known;
		queue<int> q;
		for (int i = 0; i < sizeGraph; i++)
		{
			if (i == start)
				dist[i] = 0;
			else
				dist[i] = INT_MAX;
		}
		q.push(start);
		known[start] = true;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			auto adj = graph.find(cur)->second;
			int sizeAdj = adj.size();
			for (int i = 0; i < sizeAdj; i++)
			{
				if (known.count(adj[i].first) == 0)
					dist[adj[i].first] = min(dist[adj[i].first], dist[cur] + adj[i].second);
			}
			int minVal = INT_MAX;
			int minIndex = INT_MAX;
			for (int i = 0; i < sizeGraph; i++)
			{
				if (known.count(i) == 0)
				{
					if (minVal == INT_MAX)
					{
						minVal = dist[i];
						minIndex = i;
					}
					else if (dist[i] < minVal)
					{
						minVal = dist[i];
						minIndex = i;
					}
				}
			}
			if (minIndex == end)
			{
				for (int i = 0; i < sizeGraph; i++)
					if (i != end)
						dist[i] = INT_MAX;
				break;
			}
			if (minIndex != INT_MAX)
			{
				q.push(minIndex);
				known[minIndex] = true;
			}
		}
		return dist;
	}
}
vector<pair<int, int>> primOfWeightGraph(const unordered_map<int, vector<pair<int, int>>>& graph)
{
	int sizeGraph = graph.size() + 1;
	vector<pair<int, int>>prim(sizeGraph);//下标从1开始 first邻接索引，second距离
	unordered_map<int, bool>known;
	//初始化 除起点外均初始化为INT_MAX
	prim[1].first = 1;
	prim[1].second = 0;
	for (int i = 2; i < sizeGraph; i++)
	{
		prim[i].first = INT_MAX;
		prim[i].second = INT_MAX;
	}
	//执行Prim算法
	queue<int>q;
	q.push(1);
	known[1] = true;
	while (!q.empty())
	{
		int cur = q.front();
		cout << "Vertex"<<cur << " is known:" << endl;
		q.pop();
		auto adj = graph.find(cur)->second;//adj邻接表 adj[i]=<index,path>
		int sizeAdj = adj.size();
		for(int i=0;i<sizeAdj;i++)
			if (known.count(adj[i].first) == 0)
			{
				int preDist = prim[adj[i].first].second;
				int curDist = adj[i].second;
				if (preDist > curDist)//cur的邻接节点 若边小于邻接节点的当前值
				{
					prim[adj[i].first].second = curDist;//值修改为小的边
					prim[adj[i].first].first = cur;//邻接节点为当前节点
				}
			}
		//路径最小的未访问的顶点入队列进行下次判断
		int minVal = INT_MAX;
		int minIndex = INT_MAX;
		for (int i = 1; i < sizeGraph; i++)
		{
			if (known.count(i) == 0)
			{
				if (minVal == INT_MAX)
				{
					minVal = prim[i].second;
					minIndex = i;
				}
				else if (minVal > prim[i].second)
				{
					minVal = prim[i].second;
					minIndex = i;
				}
			}
		}
		//仍有未访问的节点
		if(minIndex!=INT_MAX)
		{
			q.push(minIndex);
			known[minIndex] = true;
		}
		//打印每个顶点访问后的结果
		for (int i = 1; i < sizeGraph; i++)
			cout << "Vertex" << i << " link " << prim[i].first << " path = " << prim[i].second << endl;
	}
	return prim;
}
