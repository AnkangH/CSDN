#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int main()
{
	int n, l;
	cin >> n >> l;
	vector<pair<int, int>> light(n);
	for (int i = 0; i < n; i++)
		cin >> light[i].first >> light[i].second;
	sort(light.begin(), light.end());
  if(light[0].first>0)//无法从起点出发
    {
        cout<<"-1"<<endl;
        return 0;
    }
	int pos = 0;
	int res = 0;
	int idx = 0;
	while (pos < l)
	{
		int cur = 0;
		for (int i = idx; i < n; i++)//当前可达距离中最远的那个
		{
			if (light[i].first <= pos && light[i].second > cur)
				cur = light[i].second;
			else
			{
				idx = i;//把当前不可达的作为下次的起点
				break;
			}
		}
		if (cur == 0)//当前没有能走的了
		{
			cout << "-1" << endl;
			return 0;
		}
		pos = cur;
		res++;
	}
	cout << res << endl;
	return 0;
}
