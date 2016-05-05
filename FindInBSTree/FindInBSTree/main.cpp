/*************************************************************************
����һ�������������ʵ�������²����������㡢�����������ɾ����㡢���ҡ�
�������ֵ��������Сֵ������ָ������ǰ���ͺ�̡��������в���ʱ�临�Ӷ�
��Ϊo(h),����h�����ĸ߶�

������c���Ե�typedefģʽ
*************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<set>
#include <vector>
//����������������
typedef int KeyType;
typedef struct TreeNode
{
	KeyType key;          //�ؼ���
	struct TreeNode * left;   //����ָ��
	struct TreeNode * right;  //�Һ���ָ��
	struct TreeNode * parent; //ָ�򸸽ڵ�ָ��
}TreeNode, *PNode;

//������������в�����
//����Ļ�������Ҫ�ı�����ĵ�ַ�����Դ����Ƕ���ָ��
void inseart(PNode * root, KeyType key)
{
	//��ʼ��������
	PNode p = (PNode)malloc(sizeof(TreeNode));
	p->key = key;
	p->left = p->right = p->parent = NULL;
	//����ʱ��ֱ����Ϊ�����
	if ((*root) == NULL){
		*root = p;
		return;
	}
	//���뵽��ǰ��㣨*root��������
	if ((*root)->left == NULL && (*root)->key > key){
		p->parent = (*root);
		(*root)->left = p;
		return;
	}
	//���뵽��ǰ��㣨*root�����Һ���
	if ((*root)->right == NULL && (*root)->key < key){
		p->parent = (*root);
		(*root)->right = p;
		return;
	}
	if ((*root)->key > key)
		inseart(&(*root)->left, key);
	else if ((*root)->key < key)
		inseart(&(*root)->right, key);
	else
		return;
}

//����Ԫ��,�ҵ����عؼ��ֵĽ��ָ�룬û�ҵ�����NULL
PNode search(PNode root, KeyType key)
{
	if (root == NULL)
		return NULL;
	if (key > root->key) //����������
		return search(root->right, key);
	else if (key < root->key) //����������
		return search(root->left, key);
	else
		return root;
}

//������С�ؼ���,����ʱ����NULL
PNode searchMin(PNode root)
{
	if (root == NULL)
		return NULL;
	if (root->left == NULL)
		return root;
	else  //һֱ�������ң�ֱ��û�����ӵĽ��
		return searchMin(root->left);
}

//�������ؼ���,����ʱ����NULL
PNode searchMax(PNode root)
{
	if (root == NULL)
		return NULL;
	if (root->right == NULL)
		return root;
	else  //һֱ���Һ����ң�ֱ��û���Һ��ӵĽ��
		return searchMax(root->right);
}

//����ĳ������ǰ��
PNode searchPredecessor(PNode p)
{
	//����
	if (p == NULL)
		return p;
	//�����������������������Ǹ�
	if (p->left)
		return searchMax(p->left);
	//��������,����ĳ��������������������
	else{
		if (p->parent == NULL)
			return NULL;
		//����Ѱ��ǰ��
		while (p){
			if (p->parent->right == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

//����ĳ�����ĺ��
PNode searchSuccessor(PNode p)
{
	//����
	if (p == NULL)
		return p;
	//��������������������С���Ǹ�
	if (p->right)
		return searchMin(p->right);
	//��������,����ĳ��������������������
	else{
		if (p->parent == NULL)
			return NULL;
		//����Ѱ�Һ��
		while (p){
			if (p->parent->left == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

//���ݹؼ���ɾ��ĳ�����,ɾ���ɹ�����1,���򷵻�0
//����Ѹ����ɾ������ôҪ�ı�����ĵ�ַ�����Դ�����ָ��
int deleteNode(PNode* root, KeyType key)
{
	PNode q;
	//���ҵ�Ҫɾ���Ľ��
	PNode p = search(*root, key);
	KeyType temp;    //�ݴ��̽���ֵ
	//û�鵽�˹ؼ���
	if (!p)
		return 0;
	//1.��ɾ�����Ҷ�ӽ�㣬ֱ��ɾ��
	if (p->left == NULL && p->right == NULL){
		//ֻ��һ��Ԫ�أ�ɾ��֮����һ�ſ���
		if (p->parent == NULL){
			free(p);
			(*root) = NULL;
		}
		else{
			//ɾ���Ľ���Ǹ��ڵ������
			if (p->parent->left == p)
				p->parent->left = NULL;
			else  //ɾ���Ľ���Ǹ��ڵ���Һ���
				p->parent->right = NULL;
			free(p);
		}
	}

	//2.��ɾ���ֻ��������
	else if (p->left && !(p->right)){
		p->left->parent = p->parent;
		//���ɾ���Ǹ���㣬Ҫ�ı丸�ڵ�ָ��
		if (p->parent == NULL)
			*root = p->left;
		//ɾ���Ľ���Ǹ��ڵ������
		else if (p->parent->left == p)
			p->parent->left = p->left;
		else //ɾ���Ľ���Ǹ��ڵ���Һ���
			p->parent->right = p->left;
		free(p);
	}
	//3.��ɾ���ֻ���Һ���
	else if (p->right && !(p->left)){
		p->right->parent = p->parent;
		//���ɾ���Ǹ���㣬Ҫ�ı丸�ڵ�ָ��
		if (p->parent == NULL)
			*root = p->right;
		//ɾ���Ľ���Ǹ��ڵ������
		else if (p->parent->left == p)
			p->parent->left = p->right;
		else //ɾ���Ľ���Ǹ��ڵ���Һ���
			p->parent->right = p->right;
		free(p);
	}
	//4.��ɾ���Ľ��������ӣ������Һ���
	//�ý��ĺ�̽��϶���������(�ο�������Һ�̽�㺯��)
	//ɾ����̽��,��̽���ֵ����ý��
	else{
		//�ҵ�Ҫɾ�����ĺ��
		q = searchSuccessor(p);
		temp = q->key;
		//ɾ����̽��
		deleteNode(root, q->key);
		p->key = temp;
	}
	return 1;
}

//����һ�ö��������
void create(PNode* root, KeyType *keyArray, int length)
{
	int i;
	//����������������
	for (i = 0; i<length; i++)
		inseart(root, keyArray[i]);
}

//���ҷ�Χ������ ͬһ������һ��(��Ȼ��������vector��flag�ж�)
set<KeyType> searchRange(KeyType min, KeyType max, set<KeyType> &vt, TreeNode *root){
	if (!root) return vt ;
	if (min < (root)->key)
		searchRange(min, max, vt,(root)->left);
	if (min < (root)->key && max >= (root)->key){
		vt.insert(root->key);
	}
	if (min<(root)->key || max>(root)->key)
		searchRange(min, max, vt,(root)->right);
	return vt;
}


int main(void)
{
	PNode root = NULL;
	int nodeValue;
	while (1){
		cin >> nodeValue;
		if (nodeValue == -1)
		{
			break;
		}
		else
		{
			inseart(&root, nodeValue);
		}
	}
	int i;

	//KeyType nodeArray[11] = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
	//create(&root, nodeArray, 11);
	//for (i = 0; i<2; i++)
	//	deleteNode(&root, nodeArray[i]);
//	printf("%d\n", searchPredecessor(root)->key);
//	printf("%d\n", searchSuccessor(root)->key);
	printf("%d\n", searchMin(root)->key);
	printf("%d\n", searchMax(root)->key);
	//printf("%d\n", search(root, 2)->key);
	set<int> ss = set<int>();
	ss = searchRange(1, 3, ss, root);
	cout << "vv.size() "<<ss.size()<<endl;
	for each (int item in ss)
	{
		cout << item<<endl;
	}
	system("pause");
	return 0;
}