#include<iostream>
using namespace std;
int main()
{
	int round;
	cin >> round;
	int m, t, m1, t1, m2, t2;
	for (int i = 0; i < round; i++)
	{
		cin >> m >> t >> m1 >> t1 >> m2 >> t2;
		bool flagIn = true, flagOut = true;
		int res = 0;//初始水
		for (int j = 0; j < t; j++)//共t分钟
		{
			if (flagIn && flagOut)
			{
				res += m1 - m2;
				if (res >= m)
					res = m;
				if (res <= 0)
					res = 0;
			}
			else if (flagIn && !flagOut)
			{
				res += m1;
				if (res >= m)
					res = m;
			}
			else if(!flagIn&&flagOut)
			{
				res -= m2;
				if (res <= 0)
					res = 0;
			}
			if ((j + 1) % t1 == 0)
				flagIn = !flagIn;
			if ((j + 1) % t2 == 0)
				flagOut = !flagOut;
		}
		cout << res << endl;
	}
	return 0;
}
