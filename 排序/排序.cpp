#include<iostream>
#include<vector>
#include<queue>      //for priority_queue
#include<functional> //for greater<>
#include<algorithm>
using namespace std;
void insertionSort(vector<int>&,bool method=false);
void heapSort(vector<int>&,bool method=false);
void shellSort(vector<int>&, bool method=false);
vector<int> mergeVector(vector<int>,vector<int>, bool method=false);
void merge(vector<int>&, int, bool method=false);
void mergeSort(vector<int>&, bool method = false);
void bucketSort(vector<int>&, int, bool method = false);
void radixSort(vector<int>&, int, bool method = false);
int main()
{
	vector<int>arr{ 64,8,216,512,027,729,0,1,343,125 };
	int size = arr.size();
	cout << "Original array:" << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << "radixSort increase:" << endl;
	radixSort(arr, 10);
	cout << "radixSort increase result:" << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
	arr = { 64,8,216,512,027,729,0,1,343,125 };
	cout << "radixSort decrease:" << endl;
	radixSort(arr, 10,true);
	cout << "radixSort decrease result:" << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
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
vector<int> mergeVector(vector<int>arr1, vector<int>arr2, bool method)
{
	int size1 = arr1.size();
	int size2 = arr2.size();
	int size = size1 + size2;
	vector<int> res(size, 0);
	if (!method)
	{
		int pt1 = 0, pt2 = 0, pt = 0;
		while (pt < size)
		{
			if (pt1 == size1&&pt2 < size2)
			{
				res[pt] = arr2[pt2];
				pt2++;
				pt++;
			}
			else if (pt1 < size1&&pt2 == size2)
			{
				res[pt] = arr1[pt1];
				pt1++;
				pt++;
			}
			else
			{
				if (arr1[pt1] < arr2[pt2])
				{
					res[pt] = arr1[pt1];
					pt1++;
				}
				else
				{
					res[pt] = arr2[pt2];
					pt2++;
				}
			}
			pt++;
		}
	}
	else
		{
			int pt1 = 0, pt2 = 0, pt = 0;
			while (pt < size)
			{
				if (pt1 == size1&&pt2 < size2)
				{
					res[pt] = arr2[pt2];
					pt2++;
				}
				else if (pt1 < size1&&pt2 == size2)
				{
					res[pt] = arr1[pt1];
					pt1++;
				}
				else
				{
					if (arr1[pt1] > arr2[pt2])
					{
						res[pt] = arr1[pt1];
						pt1++;
					}
					else
					{
						res[pt] = arr2[pt2];
						pt2++;
					}
				}
				pt++;
			}
		}
	return res;
}
void merge(vector<int>&arr, int n, bool method)
{
	//n指代第几次合并 n=2 每个数组中有两个元素
	//n=1代表每个数组中有一个元素。
	int size = arr.size();
	vector<vector<int>> temp;//需要进行合并的数组
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		temp[k].push_back(arr[i]);
		int sizeTemp = temp[k].size();
		if (sizeTemp == n)//数组中有一个
			k++;
	}
	int tempSize = temp.size();
	vector<int> res;
	for (int i = 0; i < tempSize; i += 2)
	{
		vector<int> mergeTemp = mergeVector(temp[i], temp[i + 1]);
		int size = mergeTemp.size();
		for (int i = 0; i < size; i++)
			res.push_back(mergeTemp[i]);
	}
	for (int i = 0; i < size; i++)
		arr[i] = res[i];
}
void bucketSort(vector<int>&arr,int m, bool method)//m_min=max(arr)
{
	int size = arr.size();
	vector<int>bucket(m, 0);
	for (int i = 0; i < size; i++)
		bucket[arr[i]]++;//记录每个数字出现次数
	arr.clear();
	if (!method)//升序
	{
		for (int i = 0; i < m; i++)//i为arr中的数字，bucket[i]为出现的次数
		{						   //顺序打印即为升序 倒序打印即为降序
			if (bucket[i] != 0)
				for (int j = 0; j < bucket[i]; j++)
					arr.push_back(i);
		}
	}
	else//降序
	{
		for (int i = m - 1; i >= 0; i--)
		{
			if (bucket[i] != 0)
				for (int j = 0; j < bucket[i]; j++)
					arr.push_back(i);
		}
	}
}
void radixSort(vector<int>&arr, int b, bool method)
{
	int size = arr.size();
	vector<vector<int>> bucket(b);//因为某一位相同而其他位可能不同
	if(!method)
	for (int i = 1; i < 32; i++)//所以每个桶中不是存储出现次数 而是该位相同的所有数字
	{
		for (int j = 0; j < size; j++)
		{
			bucket[arr[j]/int(pow(b,i-1))%10].push_back(arr[j]);//将当前位的值相同的放入同一个桶中
		}
		arr.clear();//arr清空 储存当前位排序后的顺序
		for (int j = 0; j < b; j++)//顺序将桶中元素取出 当前位排序后的升序序列
		{
			for (int k = 0; k < bucket[j].size(); k++)
				arr.push_back(bucket[j][k]);
		}
		cout << i << "th: " << endl;
		for (int j = 0; j < arr.size(); j++)
			cout << arr[j] << " ";
		cout << endl;
		if (bucket[0].size() == size)//说明所有元素都已经到达最高位
			break;
		for (int j = 0; j < b; j++)//注意当更新arr中的值后，将bucket中每个元素清空
			bucket[j].clear();
	}
	else
		for (int i = 1; i < 32; i++)//所以每个桶中不是存储出现次数 而是该位相同的所有数字
		{
			for (int j = 0; j < size; j++)
			{
				bucket[arr[j] / int(pow(b, i - 1)) % 10].push_back(arr[j]);
			}
			arr.clear();
			for (int j = b-1; j >= 0; j--)
			{
				int size = bucket[j].size();
				for (int k = 0; k < size; k++)
					arr.push_back(bucket[j][k]);
			}
			cout << i << "th: " << endl;
			for (int j = 0; j < arr.size(); j++)
				cout << arr[j] << " ";
			cout << endl;
			if (bucket[0].size() == size)
				break;
			for (int j = 0; j < b; j++)//注意当更新arr中的值后，将bucket中每个元素清空
				bucket[j].clear();
		}
}
