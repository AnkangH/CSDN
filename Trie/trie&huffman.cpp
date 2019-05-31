#include<iostream>		//for cout endl
#include<string>		//for string 
#include<vector>		//for vector
#include<queue>			//for priority_queue
#include<functional>	//for greater<>
using namespace std;
struct TrieNode	
{
	char val;
	bool end;
	int count;
	TrieNode* next[26];//子节点 小写字母这里数目26
	TrieNode(char c)
	{
		val = c;
		end = false;
		count = 0;
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;//初始化为nullptr 防止不使用new创建时 对野指针的访问
	}
};//Trie树的节点
struct TreeNode
{
	char val;
	int weight;
	TreeNode* left;
	TreeNode* right;
	TreeNode(char c, int n) :val(c), weight(n), left(nullptr), right(nullptr) {};
	TreeNode():val('*'),weight(0),left(nullptr),right(nullptr) {};
};//带权的哈夫曼编码树节点
void trieInsertWord(TrieNode* root, string word);
//Trie树插入单词 root为Trie树的根节点 word为待插入单词
bool trieCheckWord(TrieNode* root, string word);
//Trie树查询单词 root为Trie树的根节点 word为待查询单词 找到返回true 否则false
bool trieCheckPrefix(TrieNode* root, string prefix);
//Trie树查询前缀 root为Trie树的根节点 wprefix为待查询前缀 找到返回true 否则false
TreeNode* huffmanCode(const vector<pair<int, char>>& file);
//file 输入文件 .first为频率 .second为字符 返回值为构建的哈夫曼编码的根节点
//这里不能将树作为参数传递，否则为传值传递不会保存构造的哈夫曼编码树
int main()
{
	//哈夫曼编码树的测试用例
	vector<pair<int, char>> file = { {10,'a'},{15,'e'},{12,'i'},{3,'s'},{4,'t'},{13,'b'},{1,'f'} };
	cout << "HuffmanTree building progress: " << endl;
	TreeNode* root = huffmanCode(file);
	TreeNode* cur = root;
	//层序打印各节点
	queue<TreeNode*> que;
	que.push(cur);
	int layer = 1;
	cout << "After Huffman Coding,Tree is:" << endl;
	while (!que.empty())
	{
		int size = que.size();
		cout << "Layer" << layer << ": " << endl;
		layer++;
		for (int i = 0; i < size; i++)
		{
			auto temp = que.front();
			que.pop();
			cout << temp->val << "," << temp->weight << " ";
			if (temp->left != nullptr)
				que.push(temp->left);
			if (temp->right != nullptr)
				que.push(temp->right);
		}
		cout << endl;
	}
	/*
	queue<TreeNode*>que;
	que.push(cur);
	while (!que.empty())
	{
		int size = que.size();
		for (int i = 0; i < size; i++)
		{
			TreeNode* temp = que.front();
			cout << "char = " << temp->val << " ,weight = " << temp->weight<<" ";
			que.pop();
			if (temp->left != nullptr)
				que.push(temp->left);
			if (temp->right != nullptr)
				que.push(temp->right);
		}
		cout << endl;
	}
	*/
	/*
	//Trie树测试用例
	auto root = new TrieNode('*');//前缀树根节点 字符任意
	//插入"string"查询单词"string"和"stringstring"
	string str = "string";
	cout << "After insert " << str << " in Trie: " << endl;
	trieInsertWord(root, str);
	if (trieCheckWord(root, str))
		cout << "Trie contains word " << str << endl;
	else
		cout << "Trie doesn't contain word " << str << endl;
	//继续插入"stringstring" 查询单词"stringstring"
	str = "stringstring";
	if (trieCheckWord(root, str))
		cout << "Trie contains word " << str << endl;
	else
		cout << "Trie doesn't contain word " << str << endl;
	trieInsertWord(root,str);
	cout << "After insert " << str << " in Trie: " << endl;
	if (trieCheckWord(root, str))
		cout << "Trie contains word " << str << endl;
	else
		cout << "Trie doesn't contain word " << str << endl;
	//查询前缀"stringstr"
	string prefix = "stringstr";
	if (trieCheckPrefix(root, prefix))
		cout << "Trie contains prefix " << prefix << endl;
	else
		cout << "Trie doesn't contain prefix " << prefix << endl;*/
	return 0;
}
void trieInsertWord(TrieNode* root, string word)
{
	if (word.empty())
		return;
	TrieNode* cur = root;//防止修改Trie树的根节点
	int sizeWord = word.size();
	for (int i=0;i<sizeWord;i++)
	{
		//先判断是否是nullptr 防止访问不存在的地址
		if (cur->next[word[i] - 'a'] != nullptr)//当前字母对应节点存在
		{
			cur = cur->next[word[i] - 'a'];//移动当前节点
			if (i == sizeWord - 1)
				cur->end = true;//标记单词尾
		}
		else//当前字母对应节点不存在
		{
			cur->next[word[i] - 'a'] = new TrieNode(word[i]);//创建该节点
			cur = cur->next[word[i] - 'a'];//移动当前节点
			if (i == sizeWord - 1)
				cur->end = true;//标记单词尾
		}
	}
}
bool trieCheckWord(TrieNode* root, string word)
{
	if (word.empty())
		return false;
	int sizeWord = word.size();
	TrieNode* cur = root;//防止修改Trie树的根节点
	bool res;
	for (int i=0;i<sizeWord;i++)
	{
		if (cur->next[word[i] - 'a'] != nullptr)//先判断是否是空指针
		{
			if (cur->next[word[i] - 'a']->val != word[i])//当前字母不相同
				return false;//查询失败
			else//当前字母相同
			{
				cur = cur->next[word[i] - 'a'];//移动当前节点
				if (i == sizeWord - 1)
					res = cur->end;//检查当前节点是否有单词尾标记
			}
		}
		else
			return false;
	}
	return res;
}
bool trieCheckPrefix(TrieNode* root, string prefix)
{
	if (prefix.empty())
		return false;
	int sizePrefix = prefix.size();
	TrieNode* cur = root;//防止修改Trie树的根节点
	bool res;
	for (int i = 0; i < sizePrefix; i++)
	{
		if (cur->next[prefix[i] - 'a'] != nullptr)//先检查是否是空指针
		{
			if (cur->next[prefix[i] - 'a']->val != prefix[i])//当前节点与字母不相同
				return false;//查询失败
			else//当前节点与字母相同
			{
				cur = cur->next[prefix[i] - 'a'];//移动当前节点
				if (i == sizePrefix-1)
					res = true;//前缀不需检查单词尾标记 只要所有字母均相同即输出true
			}
		}
		else
			return false;
	}
	return res;
}
TreeNode* huffmanCode(const vector<pair<int, char>>& file)
{
	int sizeFile = file.size();
	priority_queue<pair<int,TreeNode*>,vector<pair<int,TreeNode*>>,greater<> > que;//小顶堆
	for (int i = 0; i < sizeFile; i++)
	{
		TreeNode* temp = new TreeNode(file[i].second, file[i].first);//根据输入字符构建节点
		que.emplace(temp->weight, temp);//节点入堆
	}
	cout << "HuffmanCode:" << endl;
	int count = 1;
	while (que.size() > 1)
	{
		auto p = que.top();
		TreeNode* t1 = p.second;
		que.pop();//最小的出堆
		p = que.top();
		TreeNode* t2 = p.second;
		que.pop();//第二小的出堆
		cout << "Round" << count << " t1&t2 ->t:" << endl;
		count++;
		TreeNode* t = new TreeNode('*', t1->weight + t2->weight);//权加和
		cout << "t1: " << t1->val << " " << t1->weight << ", t2: " << t2->val << " ";
		cout << t2->weight << ", t: " << t->val << " " << t->weight << endl;
		t->left = t1;//合并t1与t2
		t->right = t2;
		que.emplace(t->weight, t);//新树入堆
	}
	return que.top().second;//合并完后堆中只剩一个根节点
}
