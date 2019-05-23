#include<iostream>
#include<vector>
#include<queue>      //for priority_queue
#include<functional> //for greater<>
using namespace std;
void insertionSort(vector<int>&,bool method=false);//插入排序 默认升序 true降序
void heapSort(vector<int>&,bool method=false);//堆排序 默认升序 true降序
void shellSort(vector<int>&, bool method=false);//希尔排序 默认升序 true降序
int main()
{
	vector<int>arr{ 81,94,11,96,12,35,17,95,28,58,41,75,15 };
	cout << "Original array:" << endl;
	for (auto itr = arr.begin(); itr != arr.end(); itr++)
		cout << *itr << " ";
	cout << endl;
	cout << "shellSort increase:" << endl;
	shellSort(arr);//升序排序
	cout << "shellSort increase result:" << endl;
	for (auto itr = arr.begin(); itr != arr.end(); itr++)
		cout << *itr << " ";
	cout << endl;
	cout << "shellSort decrease:" << endl;
	shellSort(arr, true);//降序排序
	cout << "shellSort decrease result:" << endl;
	for (auto itr = arr.begin(); itr != arr.end(); itr++)
		cout << *itr << " ";
	cout << endl;
	return 0;
}
void insertionSort(vector<int>& arr,bool method)
{
	int size = arr.size();
	if(!method)//升序
	for (int i = 1; i < size; i++)
	{
		int k = i;//使用i的值而不要修改i k的赋值要在下面的循环之外 因为下面会修改k的值
		for (int j = i - 1; j >= 0; j--)//对于所有的j<i,判断大小并执行交换
		{
			if (arr[k] < arr[j])
			{
				int temp = arr[k];
				arr[k] = arr[j];
				arr[j] = temp;
				k = j;//交换arr[k]和arr[j]之后，arr[k]位于j处，因此k也要变
			}
		}
		cout << "arr[0]-arr[" << i << "] sort: ";
		for (int j = 0; j <= i; j++)
			cout<< arr[j] << " ";
		cout << endl;
	}
	else//降序
		for (int i = 1; i < size; i++)
		{
			int k = i;//使用i的值而不要修改i
			for (int j = i - 1; j >= 0; j--)//对于所有的j<i,判断大小并执行交换
			{
				if (arr[k] > arr[j])
				{
					int temp = arr[k];
					arr[k] = arr[j];
					arr[j] = temp;
					k = j;//交换arr[k]和arr[j]之后，arr[k]位于j处，因此k也要变
				}
			}
			cout << "arr[0]-arr[" << i << "] sort: ";
			for (int j = 0; j <= i; j++)
				cout << arr[j] << " ";
			cout << endl;
		}
}
void heapSort(vector<int>& arr,bool method)
{
	if (!method)//升序
	{
		priority_queue<int, vector<int>, greater<> >queMin;//小顶堆
		int size = arr.size();
		for (int i = 0; i < size; i++)
			queMin.push(arr[i]);
		int i = 0;
		while (!queMin.empty())
		{
			arr[i] = queMin.top();
			queMin.pop();
			i++;
		}
	}
	else//降序
	{
		priority_queue<int>queMax;//大顶堆
		int size = arr.size();
		for (int i = 0; i < size; i++)
			queMax.push(arr[i]);
		int i = 0;
		while (!queMax.empty())
		{
			arr[i] = queMax.top();
			queMax.pop();
			i++;
		}
	}
}
void shellSort(vector<int>& arr, bool method)
{
	int size = arr.size();
	if (!method)//升序排序
		for (int gap = size / 2; gap >= 1; gap = gap / 2)//取常用ht=size/2，hk=hk+1/2
		{
			for (int i = gap; i < size; i++)//每一轮希尔排序是插入排序的变体 当hk=1时为插入排序
			{
				int k = i;
				for (int j = i - gap; j >= 0; j -= gap)
				{

					if (arr[k] < arr[j])
					{
						int temp = arr[k];
						arr[k] = arr[j];
						arr[j] = temp;
						k = j;
					}
				}
			}
			cout << "gap=" << gap << ": ";
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			cout << endl;
		}
	else
		for (int gap = size / 2; gap >= 1; gap = gap / 2)
		{
			for (int i = gap; i < size; i++)
			{
				int k = i;
				for (int j = i - gap; j >= 0; j -= gap)
				{

					if (arr[k] > arr[j])
					{
						int temp = arr[k];
						arr[k] = arr[j];
						arr[j] = temp;
						k = j;
					}
				}
			}
			cout << "gap=" << gap << ": ";
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			cout << endl;
		}
}
