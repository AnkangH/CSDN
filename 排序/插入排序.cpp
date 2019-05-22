#include<iostream>
#include<vector>
using namespace std;
void insertionSort(vector<int>&);
int main()
{
	vector<int> arr{ 34,8,64,51,32,21 };
	insertionSort(arr);
	return 0;
}
void insertionSort(vector<int>& arr)
{
	int size = arr.size();
	for (int i = 1; i < size; i++)
	{
		int k = i;//使用i的副本 在交换后不修改i 保证循环正确
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[k] < arr[j])
			{
				int temp = arr[k];
				arr[k] = arr[j];
				arr[j] = temp;
				k = j;//交换后 值交换 在数组中的位置也要交换
					  //但是不要修改循环的初值或条件 这里如果使用i
					  //那么循环初值会改变 因此使用i的副本
			}
		}
		cout << "arr[0]-arr[" << i << "] sort: ";
		for (int j = 0; j <= i; j++)
			cout<< arr[j] << " ";
		cout << endl;
	}
}
