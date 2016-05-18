#include "GetDepth.h"
#include<iostream>  
#include<stack>  
#include<queue>  
using namespace std;
GetDepth::GetDepth()
{
}

GetDepth::~GetDepth()
{
}

typedef struct TreeNode{
	char data;
	struct TreeNode *lchild, *rchild, *parent;
}TreeNode, *BiTree;

void CreateTree(BiTree &T)
{
	char ch;
	cin >> ch;
	if (ch == '#') T = NULL;
	else
	{
		T = (BiTree)malloc(sizeof(TreeNode));//c��ʽ��ʼ��һ�����ڵ�
		if (!T)  cout << "���ɽ�����" << endl;
		T->data = ch;
		CreateTree(T->lchild);
		CreateTree(T->rchild);
	}
}

//��1�����������������ջ����Ϊ���ĸ߶�  
int BT_high(BiTree T)
{
	BiTree p = T, r = NULL;
	int max = 0;     //����  
	stack<BiTree> s;
	while (p || !s.empty())
	{
		if (p != NULL){
			cout << "��ջ�ڵ㣺" << (int)p->data << endl;
			s.push(p);
			p = p->lchild;
		}
		else{
			p = s.top();
			if (p->rchild != NULL && p->rchild != r)
				p = p->rchild;
			else{
				if (s.size()>max) max = s.size();//����μ�Ϊ�߶�  
				r = p;
				cout << "��ջ�ڵ㣺"<<(int)s.top()->data << endl; 
				s.pop();
				p = NULL;
			}
		}
	}
	return max;
}

//��2����α���1����μ�Ϊ�߶� ���������±�ָʾ��ǰ��������
int BT_level_depth(BiTree T){
	if (!T)  return 0;
	BiTree p = T, QQ[100];//���Ԫ�ظ�����һ������
	int front = -1, rear = -1, last = 0, level = 0;
	QQ[++rear] = p;
	cout <<"Rear:"<< (int)QQ[rear]->data<<endl;
	while (front<rear){
		p = QQ[++front];
		cout<<"Front:" << (int)QQ[front]->data << " ";
		if (p->lchild){
			QQ[++rear] = p->lchild;
			cout << "Rear:" << (int)QQ[rear]->data << " ";
		}
		if (p->rchild){
			QQ[++rear] = p->rchild;
			cout << "Rear:" << (int)QQ[rear]->data << " ";
		}
		if (front == last){
			last = rear;
			level++;               //���+1  
		}
		cout << endl;
	}
	return level;
}
//��2-2����α���2��˫�˶��� ��������
int BT_level_depth222(BiTree T)
{
	int  max = 0;
	deque<TreeNode*> q_first, q_second;
	q_first.push_back(T);
	while (!q_first.empty()) {
		while (!q_first.empty()) {
			TreeNode *temp = q_first.front();
			q_first.pop_front();
			cout << (int)temp->data << " ";
			if (temp->lchild)
				q_second.push_back(temp->lchild);
			if (temp->rchild)
				q_second.push_back(temp->rchild);
		}
		cout << endl;
		max++;
		q_first.swap(q_second);
	}
	return max;
}
//��3���ݹ�������1  
int max1 = 0;//����  
int BT_depth1(BiTree T, int depth)
{
	if (T)
	{
		if (T->lchild)
			BT_depth1(T->lchild, depth + 1);
		if (T->rchild)
			BT_depth1(T->rchild, depth + 1);
	}
	if (depth>max1)
		max1 = depth;
	return depth;
}

//��3���ݹ�������2  
int Height(BiTree T)
{
	if (T == NULL) return 0;
	else
	{
		int m = Height(T->lchild);
		int n = Height(T->rchild);
		return (m > n) ? (m + 1) : (n + 1);
	}
}
void inseart(BiTree * root, int key)
{
	//��ʼ��������  T = (BiTree)malloc(sizeof(TreeNode));//c��ʽ��ʼ��һ�����ڵ�
	BiTree p = (BiTree)malloc(sizeof(TreeNode));
	p->data = key;
	p->lchild = p->rchild = p->parent = NULL;
	//����ʱ��ֱ����Ϊ�����
	if ((*root) == NULL){	
		*root = p;
		return;
	}
	//���뵽��ǰ��㣨*root��������
	if ((*root)->lchild == NULL && (*root)->data > key){
		p->parent = (*root);
		(*root)->lchild = p;
		return;
	}
	//���뵽��ǰ��㣨*root�����Һ���
	if ((*root)->rchild == NULL && (*root)->data < key){
		p->parent = (*root);
		(*root)->rchild = p;
		return;
	}
	if ((*root)->data > key)
		inseart(&(*root)->lchild, key);
	else if ((*root)->data < key)
		inseart(&(*root)->rchild, key);
	else
		return;
}
int main()
{
	//BiTree T = NULL;
	//CreateTree(T);
	BiTree root = NULL;
	//int nodeValue;
	//while (1){
	//	cin >> nodeValue;
	//	if (nodeValue == -1)
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		inseart(&root, nodeValue);
	//	}
	//}
	inseart(&root, 5);
	inseart(&root, 4);
	inseart(&root, 8);
	inseart(&root, 0);
	inseart(&root, 6);
	inseart(&root, 11);
	inseart(&root, 1);
	inseart(&root, 3);
	inseart(&root, 7);
	inseart(&root, 12);
	inseart(&root, 2);
	cout << "������������ߣ�" <<  BT_high(root) << endl;
	cout << "��α��������ߣ�" << BT_level_depth(root) << endl;
	cout << "��α���2�����ߣ�" << BT_level_depth222(root) << endl;
	cout << "�ݹ�������1��";BT_depth1(root, 1);	cout << max1 << endl;
	cout << "�ݹ�������2��" << Height(root) << endl;
	system("pause");
	return 0;
}