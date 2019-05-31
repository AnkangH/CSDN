#include<iostream>
#include<string>
using namespace std;
struct TrieNode
{
	char val;
	bool end;
	int count;
	TrieNode* next[26];
	TrieNode(char c)
	{
		val = c;
		end = false;
		count = 0;
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;
	}
};
void trieInsertWord(TrieNode* root, string word);
bool trieCheckWord(TrieNode* root, string word);
bool trieCheckPrefix(TrieNode* root, string prefix);
int main()
{
	auto root = new TrieNode('*');
	string str = "string";
	cout << "After insert " << str << " in Trie: " << endl;
	trieInsertWord(root, str);
	if (trieCheckWord(root, str))
		cout << "Trie contains word " << str << endl;
	else
		cout << "Trie doesn't contain word " << str << endl;
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
	string prefix = "stringstr";
	if (trieCheckPrefix(root, prefix))
		cout << "Trie contains prefix " << prefix << endl;
	else
		cout << "Trie doesn't contain prefix " << prefix << endl;
	return 0;
}
void trieInsertWord(TrieNode* root, string word)
{
	if (word.empty())
		return;
	TrieNode* cur = root;
	int sizeWord = word.size();
	for (int i=0;i<sizeWord;i++)
	{
		if (cur->next[word[i] - 'a'] != nullptr)
		{
			cur = cur->next[word[i] - 'a'];
			if (i == sizeWord - 1)
				cur->end = true;
		}
		else
		{
			cur->next[word[i] - 'a'] = new TrieNode(word[i]);
			cur = cur->next[word[i] - 'a'];
			if (i == sizeWord - 1)
				cur->end = true;
		}
	}
}
bool trieCheckWord(TrieNode* root, string word)
{
	if (word.empty())
		return false;
	int sizeWord = word.size();
	TrieNode* cur = root;
	bool res;
	for (int i=0;i<sizeWord;i++)
	{
		if (cur->next[word[i] - 'a'] != nullptr)
		{
			if (cur->next[word[i] - 'a']->val != word[i])
				return false;
			else
			{
				cur = cur->next[word[i] - 'a'];
				if (i == sizeWord - 1)
					res = cur->end;
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
	TrieNode* cur = root;
	bool res;
	for (int i = 0; i < sizePrefix; i++)
	{
		if (cur->next[prefix[i] - 'a'] != nullptr)
		{
			if (cur->next[prefix[i] - 'a']->val != prefix[i])
				return false;
			else
			{
				cur = cur->next[prefix[i] - 'a'];
				if (i == sizePrefix-1)
					res = true;
			}
		}
		else
			return false;
	}
	return res;
}
