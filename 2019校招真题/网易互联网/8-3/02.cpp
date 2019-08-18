#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
int maxLine(vector<int> line);
int main()
{
	int numRound;
	cin >> numRound;
	for (int round = 0; round < numRound; round++)
	{
		int m, n,k;
		cin >> m >> n >> k;
		if (m == 0 || n == 0)
			cout << "NO" << endl;
		vector<vector<int>> grid(m, vector<int>(n, 0));//0代表空地
		for (int i = 0; i < k; i++)
		{
			int x, y;
			cin >> x >> y;
			grid[x - 1][y - 1] = 1;//放置障碍物
		}
		int c, d;
		cin >> c >> d;//箱子大小;
		int maxArea = 0;
		vector<int> height(n);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == 1) height[j] = 0;
				else height[j]++;
			}
			maxArea = max(maxArea, maxLine(height));
		}
		if (c * d <= maxArea)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
int maxLine(vector<int> line)
{
	stack<int> s;
	int res = 0;
	int n = line.size();
	for (int i = 0; i <= n; i++) {
		int h = (i ==n) ? 0 : line[i];
		while (!s.empty() && line[s.top()] >= h) {
			int maxheight = line[s.top()];
			s.pop();
			int area = s.empty() ? i * maxheight : maxheight * (i - s.top() - 1);
			res = max(res, area);
		}
		s.push(i);
	}
	return res;
}
