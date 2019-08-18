#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	cin >> n;
	vector<int> score(n);
	for (int i = 0; i < n; i++)
		cin >> score[i];
	vector<int> scoreOriginal = score;//排序前保存原顺序
	sort(score.begin(), score.end());//升序排序
	unordered_map<int, double> m;//记录每个分数对应的百分数
	for (int i = 0; i < n; i++)
		m[score[i]] = double(i) / n*100;//计算百分数
	int q,cur;
	cin >> q;
	cout.setf(ios_base::fixed);
	cout.precision(6);
	for (int i = 0; i < q; i++)
	{
		cin >> cur;
		if (m[scoreOriginal[cur - 1]] == 0)
			cout << "0.000000" << endl;
		else
			cout << m[scoreOriginal[cur - 1]] << endl;
	}
	return 0;
}
