#include<iostream>
#include<vector>
using namespace std;
void sortInsert(vector<int>&);//插入升序 
void sortShell(vector<int>&);//希尔升序 
void heapInsert(vector<int>& nums, int val);//小顶堆 向堆中插入一个新节点
void heapDelete(vector<int>& nums,int& n);//小顶堆 删除堆顶 返回剩余节点个数
void sortHeap(vector<int>& nums);//堆排序 默认使用小顶堆 使数组升序
int main()
{
	vector<int> nums;
	heapInsert(nums, 13);
	heapInsert(nums, 21);
	heapInsert(nums, 16);
	heapInsert(nums, 24);
	heapInsert(nums, 31);
	heapInsert(nums, 19);
	heapInsert(nums, 68);
	heapInsert(nums, 65);
	heapInsert(nums, 26);
	heapInsert(nums, 32);
	heapInsert(nums, 14);
	cout << "original arr:" << endl;
	for (auto p : nums)
		cout << p << " ";
	cout << endl;
	cout << "sortHeap arr:" << endl;
	sortHeap(nums);
	for (auto p : nums)
		cout << p << " ";
	cout << endl;
	return 0;
}
void sortInsert(vector<int>& num)//升序
{
	int n = num.size();
	for (int i = 0; i < n; i++)//第i趟排序 前i+1个数有序
	{
		int idx = i;//当前数字
		for (int j = i-1; j >= 0; j--)//在前面的所有有序数组中找到插入位置
		{
			if (num[idx] < num[j])//当前数字小 前移
			{
				int temp = num[idx];
				num[idx] = num[j];
				num[j] = temp;
				idx = j;
			}
			else
				break;//找到插入位置 结束当前趟
		}
	}
}
void sortShell(vector<int>& nums)
{
	/*
	希尔排序是以希尔数列hk为间隔，每次将数组每隔hk组成的子数组进行一次插入排序。
	希尔数列需保证最后的hn=1，否则不能保证数组有序。
	外层以hk循环，将插入排序程序的步长1改为hk即可。
	*/
	int n = nums.size();
	for (int gap = n / 2; gap > 0; gap /= 2)//子数组的间隔
	{
		for (int i = 0; i < n; i+=gap)//每个子数组
		{
			int idx = i;//当前趟插入排序
			for (int j = idx - gap; j >= 0; j--)
			{
				if (nums[idx] < nums[j])
				{
					int temp = nums[idx];
					nums[idx] = nums[j];
					nums[j] = temp;
				}
				else
					break;
			}
		}
	}
}
void heapInsert(vector<int>& nums, int val)
{
	/*
	小顶堆插入节点。放到数组尾，执行上滤，
	一直到当前节点与其父节点满足堆序或到达根节点。
	*/
	nums.push_back(val);//数组末尾放入新节点
	int n = nums.size();
	int idx = n - 1;//空穴初始位置
	for (int i = (idx-1)/2; i >= 0; i=(i-1)/2)//从其父节点开始 直到根节点
	{
		if (nums[idx] < nums[i])//不满足堆序 上滤
		{
			nums[idx] = nums[i];
			nums[i] = val;
			idx = i;
		}
		else
			break;//满足堆序 退出
	}
}
void heapDelete(vector<int>& nums, int& n)
{
	/*
	删除堆顶，将堆顶放到数组尾，并标记数组大小，防止访问已出堆的元素。
	将数组尾元素放到堆顶，执行下滤，每次在两个子节点中选择较小的交换下滤，直到满足堆序或
	到达叶节点。
	*/
	int end = nums[n - 1];//数组末尾元素
	nums[n - 1] = nums[0];//删除堆顶
	nums[0] = end;
	n--;//数目更新
	int idx = 0;//从堆顶开始下滤
	while (1)
	{
		int left = 2 * idx + 1;//左子节点索引
		int right = 2 * idx + 2;//右子节点索引
		if (left < n && right < n)//左右子节点均合法
		{
			if (nums[idx] <= nums[left] && nums[idx] <= nums[right])
				break;//当前位置符合堆序 退出
			else
			{
				if (nums[left] < nums[right])//left<cur<right
				{
					nums[idx] = nums[left];//当前位置选较小的
					nums[left] = end;//下移
					idx = left;
				}
				else//right<cur<left 当前位置选较小的
				{
					nums[idx] = nums[right];//下移
					nums[right] = end;
					idx = right;
				}
			}
		}
		else if (left < n)//只有左子节点
		{
			if (nums[idx] <= nums[left])
				break;//符合堆序 退出
			else
			{
				nums[idx] = nums[left];//下滤
				nums[left] = end;
				idx = left;
			}
		}
		else if (right < n)//只有右子节点
		{
			if (nums[idx] <= nums[right])
				break;//符合堆序 退出
			else
			{
				nums[idx] = nums[right];//下滤
				nums[right] = end;
				idx = right;
			}
		}
		else
			break;//到达叶节点 退出
	}
}
void sortHeap(vector<int>& nums)
{
	int n = nums.size();
	vector<int> temp;
	for (auto p : nums)
		heapInsert(temp, p);
	while (n > 0)
		heapDelete(temp, n);
	nums = temp;
}
