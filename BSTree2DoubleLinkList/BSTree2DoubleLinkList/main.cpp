/*********************************************************
* Description:�������ݣ�C++ ��������ʵ��&���������&������ת˫����
* Author:Jay Wang
* DateTime:2016-5-3 22:53
* Compile Environment��win8.1+vs2013
***********************************************************/

#include <iostream>
using namespace std;
int ret;

//*************************************************************************************
//�����������Ķ���
template<class T>                  //ģ��ṹ��
struct TreeNode
{
	T data;                       //�ڵ������
	TreeNode <T> *Lchild, *Rchild,*pParent; //�ڵ����������������

	//��ѡ�������Ĭ�Ϲ��캯��
	TreeNode(T nodeValue = T(), TreeNode<T> *leftNode = NULL, TreeNode<T> *rightNode = NULL, TreeNode<T> *parentNode = NULL)
	:data(nodeValue),Lchild(leftNode),Rchild(rightNode),pParent(parentNode){}
};
TreeNode<int> * pHead =NULL;
TreeNode<int> * previous = NULL;

template<typename T>
void insert(TreeNode<T>* &tree, TreeNode<T>* z)
{
	TreeNode<T>* parent = NULL;
	TreeNode<T>* temp = tree;
	//Ѱ�Ҳ����
	while(temp != NULL)
	{
		parent = temp;
		if (z->data>temp->data)
			temp = temp->Rchild;
		else
			temp = temp->Lchild;
	}
	z->pParent = parent;
	if (parent == NULL) //������������ǿ�������ֱ�Ӱ�z�ڵ������ڵ�
		tree = z;
	else if (z->data>parent->data) //���z��ֵ������˫�ף���zΪ��˫�׵��Һ�
		parent->Rchild = z;
	else
		parent->Lchild = z;
}

//**************************************************************************************
//�������Ľ���
template <class T> //ģ�淽��
void createBinaryTree(TreeNode<T> *&root)  //����ָ�������
{
	TreeNode<T>* p = root;
	T nodeValue;
	if (ret!=0)cin >> nodeValue;
	else{
		nodeValue = -1;
	}
	if (nodeValue == -1)
	{
		ret = 0;
		root = NULL;
	}
	else
	{
		root = new TreeNode<T>();            //����һ���ڵ�
		root->data = nodeValue;
		if (!(root->Lchild))createBinaryTree(root->Lchild);    //�ݹ鹹��������
		if (!(root->Rchild))createBinaryTree(root->Rchild);    //�ݹ鹹��������
	}
}

//************************************************************************************
//���������������
template <class T>
void preOrder(TreeNode<T> * & p) //����ָ�������
{
	if (p)
	{
		cout << p->data << " ";
		preOrder(p->Lchild);
		preOrder(p->Rchild);
	}
}

//**************************************************************************************
//���������������
template <class T>
void inOrder(TreeNode<T> * & p) //����ָ�������
{
	if (p)
	{
		inOrder(p->Lchild);
		cout << p->data << " ";
		inOrder(p->Rchild);
	}
}

//**************************************************************************************
//�������ĺ������
template <class T>
void postOrder(TreeNode<T> *& p) //����ָ�������
{
	if (p)
	{
		postOrder(p->Lchild);
		postOrder(p->Rchild);
		cout << p->data << " ";
	}
}
//**************************************************************************************
//˫����ı���
template <class T>
void nextOrder(TreeNode<T> *& p) //����ָ�������
{
	if (!p) return;
	if (p->Rchild)
	{
		cout << p->data << " ";
		nextOrder(p->Rchild);
	}
}
//*************************************************************************************
//ͳ�ƶ������н��ĸ���
template<class T>
int countNode(TreeNode<T> * & p) //����ָ�������
{
	if (p == NULL) return 0;
	return 1 + countNode(p->Lchild) + countNode(p->Rchild);
}

//***********************************************************************************
//������������
template<class T>
int depth(TreeNode<T> *& p) //����ָ�������
{
	if (p == NULL)
		return -1;
	int h1 = depth(p->Lchild);
	int h2 = depth(p->Rchild);
	if (h1>h2)return (h1 + 1);
	return h2 + 1;
}

template<class T>
void Tranverse(TreeNode<T> * root)//��ǰ��
{
	if (root){
		Tranverse(root->Lchild);

		if (previous){
			if (!pHead){
				pHead = previous;
			}
			previous->Rchild = root;
			root->Lchild = previous;
		}
		previous = root;
		Tranverse(root->Rchild);
	}
}

//***********************************************************************************
//�����������ٲ���
//���׻����Ĵ���������void destroy(TreeNode<T>* p) ���������ᴴ��һ���ֲ�����ʱ���������洫�ݵ�ָ��
//��Ȼ2��ָ�붼ִ��ͬһ��ѿռ䣬delete�ֲ�ָ�� Ҳ��ɾ���������ṹ��ռ�õĶ��ڴ�
//����ȫ�ִ��ݵ��Ǹ�ָ�뽫��������ָ�룬���������Ԥ�ϵĴ���
//void destroy(TreeNode<T> *& p) �˺����Ĳ���Ϊȫ��ָ���һ������������ȫ��ָ��rootNode����
//  ����p = NULL;�ܴﵽ�ÿ�ָ�������
//��ѡ�ķ������ڵ�����destroy����֮������������ִ��rootNode = NULL����
template<class T>
void destroy(TreeNode<T> *& p)  //����ָ�������,���ٺ������������ٶ������еĸ������
{
	if (p)
	{
		//���� return֮�� û��ִ��delete p
		//return destroy(p->Lchild);
		//return destroy(p->Rchild);

		destroy(p->Lchild);
		destroy(p->Rchild);

		//deleteֻ���ͷ����û�ͨ��new��ʽ�ڶ���������ڴ棬
		//��ͨ�����������ķ�ʽ��ϵͳ��������ջ�ڴ治��ʹ��deleteɾ��

		//delete��free����һ�������޸���������Ӧָ��ָ������ݣ�Ҳ���޸�ָ�뱾��
		//ֻ���ڶ��ڴ����ṹ�н�ָ��ָ������ݱ��Ϊ�ɱ����·���
		delete p;

		//�����ڴ��ͷ� ջ��ָ�벢������
		//��ʱpָ��ĵ�ַδ֪,��ʱִ��*p = ? �����ᵼ�²���Ԥ�ϵĴ���
		//���ǿ������¸�ֵp = &x;
		//���delete֮���P�ÿ�
		p = NULL;

	}
}

//********************************************************************************
//����������� 
int main()
{
	TreeNode<int> * rootNode = NULL;
	TreeNode<int> * preNode = NULL;
	int choiced = 0;
	while (true)
	{
		system("cls"); //����
		cout << "\n\n\n                              ---������---\n\n\n";
		cout << "                     1������������                2���������������\n";
		cout << "                     3���������������            4���������������\n";
		cout << "                     5��ͳ�ƽ������              6���鿴�����    \n";
		cout << "                     7�����ٶ�����                8��������ת˫����\n";
		cout << "                     9���������������                0���˳�\n\n";
		cout << "             ��ѡ�������";
		cin >> choiced;
		if (choiced == 0)
			return 0;
		else if (choiced == 1)
		{
			ret = 1;
			system("cls");
			cout << "������ÿ����㣬�س�ȷ�ϣ�����-1������\n";
			createBinaryTree(rootNode);
		}
		else if (choiced == 2)
		{
			system("cls");
			cout << "������������������\n";
			preOrder(rootNode);
			cout << endl;
			system("pause"); //��ͣ��Ļ
		}
		else if (choiced == 3)
		{
			system("cls");
			cout << "������������������\n";
			inOrder(rootNode);
			cout << endl;
			system("pause");
		}
		else if (choiced == 4)
		{
			system("cls");
			cout << "������������������\n";
			postOrder(rootNode);
			cout << endl;
			system("pause");
		}
		else if (choiced == 5)
		{
			system("cls");
			int count = countNode(rootNode);
			cout << "�������н������Ϊ" << count << endl;
			system("pause");
		}
		else if (choiced == 6)
		{
			system("cls");
			int dep = depth(rootNode);
			cout << "�˶����������Ϊ" << dep << endl;
			system("pause");
		}
		else if (choiced == 7)
		{
			system("cls");
			cout << "�������ѱ����٣�\n";
			destroy(rootNode);
			cout << endl;
			system("pause");
		}
		else if (choiced == 8){
			system("cls");
			if (rootNode == NULL)
				system("pause");
			Tranverse(rootNode);

			while (pHead != NULL){
				cout << pHead->data << endl;
				pHead = pHead->Rchild;
			}
			system("pause");

		}
		else if (choiced == 9){
			system("cls");
			int nodeValue;
			while (1){
				cin >> nodeValue;
				if (nodeValue == -1)
				{
					break;
				}
				else
				{
					TreeNode<int>* z = new TreeNode<int>(nodeValue, NULL, NULL, NULL);
					insert(rootNode, z);
				}
			}	
			system("pause");
		}
		else
		{
			system("cls");
			cout << "\n\n\n\n\n\t����ѡ��\n";
		}

	}
}