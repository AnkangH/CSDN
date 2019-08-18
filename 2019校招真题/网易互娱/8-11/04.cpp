#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<int> heights(n);
	for (int i = 0; i < n; i++)
		cin >> heights[i];
	int m;
	cin >> m;
	int y;
	for (int i = 0; i < m; i++)
	{
		cin >> y;
		int res = 0;
		vector<int> affter;
		for (int i = 0; i < n; i++)
			if (heights[i] > y)
				affter.push_back(i);
		int size = affter.size();
		for (int i = 1; i < size; i++)
			if (affter[i] - affter[i - 1] > 1)
				res++;
		if(size>=1)
			res++;
		cout << res << endl;
	}
	return 0;
}
