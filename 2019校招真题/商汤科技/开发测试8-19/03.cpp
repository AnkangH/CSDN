#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int n, a, b, c, f0;
	cin >> n >> a >> b >> c >> f0;
	int pre3, pre2, pre1;
	pre3 = f0;
	if (n == 0)
	{
		cout << pre3 << endl;
		return 0;
	}
	pre2 = a * pre3 + 2 * 1 * 1 - 1+32767;
	if (n == 1)
	{
		cout << pre2 << endl;
		return 0;
	}
	pre1 = a * pre2 + b * pre3 + 2 * 2 * 2 - 2+32767;
	if (n == 2)
	{
		cout << pre1 << endl;
		return 0;
	}
	for (int i = 3; i <= n; i++)
	{
		int cur = (a * pre1 + b * pre2 + c * pre3 + 2 * i * i - i + 32767) % 1000000007;
		pre3 = pre2;
		pre2 = pre1;
		pre1 = cur;
	}
	cout << pre1 << endl;
}
