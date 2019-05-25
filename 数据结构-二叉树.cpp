#include<iostream>		//for cout endl
#include<vector>		//for vector
#include<queue>			//for queue
#include<stack>
using namespace std;
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};
void treeLayOrder(TreeNode*);//层序遍历 无返回值
void treeLayOrder(TreeNode*, vector<int>&);//层序遍历 有返回值
void treePreOrder(TreeNode*, vector<int>&);//前序遍历，第二个输入为输出遍历
void treeMidOrder(TreeNode*, vector<int>&);//序遍历，第二个输入为输出遍历
void treeBacOrder(TreeNode*, vector<int>&);//前序遍历，第二个输入为输出遍历
vector<int> preorderTraversal(TreeNode* root);//前序遍历非递归
vector<int> inorderTraversal(TreeNode* root);//中序遍历非递归
vector<int> postorderTraversal(TreeNode* root);//后序遍历非递归
int main()
{
	//构建二叉树
	TreeNode* t = new TreeNode(1);
	TreeNode* head = t;
	t->left = new TreeNode(2);
	t->right = new TreeNode(3);
	t = head->left;
	t->left = new TreeNode(4);
	t->right = new TreeNode(5);
	t = head->right;
	t->left = new TreeNode(6);
	t->right = new TreeNode(7);
	vector<int>res;
	//前序遍历
	cout << "Tree Pre order: " << endl;
	treePreOrder(head,res);
	for (auto p : res)
		cout << p << " ";
	cout << endl;
	//中序变量
	res.clear();
	cout << "Tree Mid order: " << endl;
	treeMidOrder(head,res);
	for (auto p : res)
		cout << p << " ";
	cout << endl;
	//后序遍历
	res.clear();
	cout << "Tree Back order: " << endl;
	treeBacOrder(head,res);
	for (auto p : res)
		cout << p << " ";
	cout << endl;
	cout << "Tree Layer order: " << endl;
	treeLayOrder(head);
	cout << "Tree Layer order with return array:" << endl;
	res.clear();
	treeLayOrder(head, res);
	for (auto p : res)
		cout << p << " ";
	cout << endl;
	return 0;
}
void treePreOrder(TreeNode* t, vector<int>& res)
{
	if (t == NULL)
		return;
	res.push_back(t->val);
	treePreOrder(t->left, res);
	treePreOrder(t->right, res);
}
void treeMidOrder(TreeNode* t, vector<int>& res)
{
	if (t == NULL)
		return;
	treePreOrder(t->left, res);
	res.push_back(t->val);
	treePreOrder(t->right, res);
}
void treeBacOrder(TreeNode* t, vector<int>& res)
{
	if (t == NULL)
		return;
	treePreOrder(t->left, res);
	treePreOrder(t->right, res);
	res.push_back(t->val);
}
void treeLayOrder(TreeNode* t)
{
	queue<TreeNode*> que;
	que.push(t);
	int layerCount = 1;
	while (!que.empty())
	{
		int size = que.size();
		cout << "layer" << layerCount << ":" << endl;
		for (int i = 0; i < size; i++)
		{
			TreeNode* temp = que.front();
			cout << temp->val;
			que.pop();
			if (temp->left != NULL)
				que.push(temp->left);
			if (temp->right != NULL)
				que.push(temp->right);
		}
		layerCount++;
		cout << endl;
	}
}
vector<int> preorderTraversal(TreeNode* root)
{
	vector<int>res;
	if (root == NULL)
		return res;//预判断树空
	stack<TreeNode*> st;//辅助栈
	st.push(root);
	while (!st.empty())
	{
		TreeNode* temp = st.top();//当前节点为栈顶元素
		st.pop();//访问后出栈
		if (temp != NULL)
			res.push_back(temp->val);//当前元素非空，其值放入遍历序列
		if (temp->right != NULL)
			st.push(temp->right);//先右  这样栈顶后右
		if (temp->left != NULL)
			st.push(temp->left);//后左  这样栈顶先左 满足先序遍历
	}
	return res;
}
vector<int> inorderTraversal(TreeNode* root)
{
	vector<int> res;
	if (root == NULL)
		return res;
	stack<TreeNode*> st;
	TreeNode* cur = root;
	while (cur != NULL || !st.empty())
	{
		while (cur != NULL)
		{
			st.push(cur);
			cur = cur->left;//左斜树节点全部入栈
		}
		TreeNode* t = st.top();
		st.pop();//栈顶出栈
		res.push_back(t->val);//栈顶节点值保存
		cur = t->right;//遍历右节点。
	}
	return res;
}
vector<int> postorderTraversal(TreeNode* root)
{
	vector<int> res;
	if (root == NULL)
		return res;
	stack<TreeNode*> st;//辅助栈
	st.push(root);
	while (!st.empty())
	{
		TreeNode* t = st.top();
		st.pop();
		if (t != NULL)
			res.push_back(t->val);
		if (t->left != NULL)
			st.push(t->left);//先左 这样栈顶后左
		if (t->right != NULL)
			st.push(t->right);//后右 这样栈顶先右  
	}
	reverse(res.begin(), res.end());//res中保存了根右左的遍历顺序，反转即可。
	return res;
}
void treeLayOrder(TreeNode* root, vector<int>& arr)//层序遍历 有返回值
{
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; i++)
		{
			TreeNode* t = q.front();
			arr.push_back(t->val);
			q.pop();
			if (t->left != nullptr)
				q.push(t->left);
			if (t->right != nullptr)
				q.push(t->right);
		}
	}
}
