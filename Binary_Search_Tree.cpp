#include <iostream>
using namespace std;
#include <stack>
#include <string>

class Node
{
	int key;//键
	char value;//值
	Node *lchild;//左结点
	Node *rchild;//右结点
	int count;//结点计数器，以该结点为根的子树中结点的总数
public:
	Node();
	Node(int data, char s, int n)
	{
		key = data;
		this->value = s;
		count = n;
	}
	friend class Binary_Search_Tree;
};

class Binary_Search_Tree
{
private:
	Node *root;
	int size(Node *cur) { 
		if (cur == NULL)
			return 0;
		return cur->count;
	}

	char get(Node *cur, int k);//查找
	Node *put(Node *cur, int k, char v);//插入

	Node *min(Node *cur);
	Node *max(Node *cur);

	Node* floor(Node *cur, int k);
	Node* celling(Node *cur, int k);

	Node* select(Node *cur, int k);
	int rank(Node *cur, int k);

	Node* delMin(Node *cur); 
	Node* delMax(Node *cur); 

	Node* Delete(Node *cur, int k);

public:
	int size() { return size(root);}
	char get(int k);//获得指定键的值
	void put(int k, char v);//将一对键值加入二叉查找树

	Node *min();
	Node *max();

	Node* floor(int k);
	Node* celling(int k);

	Node* select(int k);
	int rank(int k);

	void delMin();
	void delMax();
	void Delete(int k);

};

char Binary_Search_Tree::get(Node *cur, int k)
{
	if (cur == NULL)
		return NULL;
	if (k < cur->key)
		return get(cur->lchild, k);
	else if (cur->key < k)
		return get(cur->rchild, k);
	else
		return cur->value;
}
char Binary_Search_Tree::get(int k)
{
	return get(root, k);
}


Node *Binary_Search_Tree::put(Node *cur, int k, char v)
{
	if (cur == NULL)
		return new Node(k, v, 1);
	if (k < cur->key)
		cur = put(cur->lchild, k, v);
	else if (k > cur->key)
		cur = put(cur->rchild, k, v);
	else
		cur->value = v;
	cur->count = size(cur->lchild) + size(cur->rchild) + 1;
	return cur;
}
void Binary_Search_Tree::put(int k, char v)
{
	root = put(root, k, v);
}

Node* Binary_Search_Tree::min(Node *cur)
{
	if (cur->lchild == NULL)
		return cur;
	else 
		return min(cur->lchild);
}
Node* Binary_Search_Tree::min()
{
	return min(root);
}
Node* Binary_Search_Tree::max(Node *cur)
{
	if (cur->rchild == NULL)
		return cur;
	else 
		return cur = max(cur->rchild);
}
Node* Binary_Search_Tree::max()
{
	return max(root);
}
Node* Binary_Search_Tree::floor(Node *cur, int k)
{
	if (cur == NULL)
		return NULL;
	if (k = cur->key)
		return cur;
	if (k < cur->key)
	{
		return floor(cur->lchild, k);
	}
	Node *t = floor(cur->rchild, k);
	if (t == NULL)
		return cur;
	else
		return t;
}
Node* Binary_Search_Tree::floor(int k)
{
	return floor(root, k);
}

Node* Binary_Search_Tree::celling(Node *cur, int k)
{
	if (cur == NULL)
		return NULL;
	if (k = cur->key)
		return cur;
	if (k > cur->key)
	{
		return floor(cur->rchild, k);
	}
	Node *t = floor(cur->lchild, k);
	if (t == NULL)
		return cur;
	else
		return t;
}
Node* Binary_Search_Tree::celling(int k)
{
	return celling(root, k);
}

Node* Binary_Search_Tree::select(Node *cur, int k)//寻找排名为k的结点
{
	if (cur == NULL)
		return cur;
	int t = size(cur->lchild);
	if (t > k)
		return select(cur->lchild, k);
	else if (t < k)
		return select(cur->rchild, t - k - 1);
	else
		return cur;
}
Node* Binary_Search_Tree::select(int k)
{
	return select(root, k);
}

int Binary_Search_Tree::rank(Node *cur, int k)//寻找键值小于k的结点数
{
	if (cur == NULL)
		return NULL;
	if (k < cur->key)
		return rank(cur->lchild, k);
	else if (k > cur->key)
		return 1 + size(cur->lchild) + rank(cur->lchild, k);
	else
		return size(cur->lchild);
}
int Binary_Search_Tree::rank(int k)
{
	return rank(k);
}	

Node* Binary_Search_Tree::delMin(Node *cur)
{
	if (cur->lchild == NULL)
		return cur->rchild;
	cur->lchild = delMin(cur->lchild);
	cur->count = size(cur->lchild) + size(cur->rchild) + 1;
	return cur;
}
void Binary_Search_Tree::delMin()
{
	root = delMin(root);
}
Node* Binary_Search_Tree::delMax(Node *cur)
{
	if (cur->rchild == NULL)
		return cur->lchild;
	cur->rchild = delMax(cur->rchild);
	cur->count = size(cur->lchild) + size(cur->rchild) + 1;
	return cur;
}
void Binary_Search_Tree::delMax()
{
	root = delMax(root);
}

Node* Binary_Search_Tree::Delete(Node *cur, int k)
{
	if (cur == NULL)
		return NULL;
	if (k < cur->key)
		cur->lchild = Delete(cur->lchild, k);
	else if (k > cur->key)
		cur->rchild = Delete(cur->rchild, k);
	else
	{
		if (cur->lchild == NULL)
			return cur->rchild;
		if (cur->rchild == NULL)
			return cur->lchild;
		Node *t = cur;
		cur = min(t->rchild);
		cur->rchild = delMin(t->rchild);
		cur->lchild = t->lchild;
	}
	cur->count = size(cur->lchild) + size(cur->rchild) + 1;
	return cur;
}
