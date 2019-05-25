#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
enum method{setFunc,uniqueFunc,mapFunc};
void deleteDupVector(vector<int>&, method);
int main()
{
	vector<int>arr{ 23,45,21,21,66,12,3,3,3,1,6,32,23 };
	cout << "Original Vector:" << endl;
	for (auto p : arr)
		cout << p << " ";
	cout << endl;
	cout << "Delete dup via Set:" << endl;
	deleteDupVector(arr, setFunc);
	for (auto p : arr)
		cout << p << " ";
	cout << endl;
	arr={ 23,45,21,21,66,12,3,3,3,1,6,32,23 };
	cout << "Delete dup via Unique:" << endl;
	deleteDupVector(arr, uniqueFunc);
	for (auto p : arr)
		cout << p << " ";
	cout << endl;
	arr = { 23,45,21,21,66,12,3,3,3,1,6,32,23 };
	cout << "Delete dup via Map:" << endl;
	deleteDupVector(arr, mapFunc);
	for (auto p : arr)
		cout << p << " ";
	cout << endl;
	return 0;
}
void deleteDupVector(vector<int>& arr, method m)
{
	if (m == setFunc)
	{
		set<int> auxSet;
		for (auto p : arr)
			auxSet.insert(p);
		arr.clear();
		for (auto p : auxSet)
			arr.push_back(p);
	}
	else if (m == uniqueFunc)
	{
		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());
	}
	else if (m == mapFunc)
	{
		map<int, int> exist;
		auto itr = arr.begin();
		while (itr != arr.end())
		{
			if (exist.count(*itr) == 0)
			{
				exist[*itr]++;
				itr++;
			}
			else
			{
				itr = arr.erase(itr);
			}
		}
	}
}
