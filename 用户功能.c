#include<stdio.h>
#include<stdlib.h>
#include"结构体信息.h"

/*创建新用户*/
User* newUser(char username[], char password[], char name[], char phone[])
{
	User* newUser = (User*)malloc(sizeof(User));
	//用户数据读入
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->phone, phone);
	newUser->time = 0;
	//构建二叉树节点
	newUser->left = NULL;
	newUser->right = NULL;
	newUser->height = 1;
	return newUser;
}

/*计算树的高度*/
int height(User* node)
{
	if (node == NULL) return 0;
	return node->height;
}

/*获取平衡因子*/
int getBalence(User* node)
{
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

/*右旋*/
User* rightRotate(User* x)
{
	User* y = x->left;
	User* t = y->right;
	y->right = x;
	x->left = t;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return x;
}

/*左旋*/
User* leftRotate(User* x)
{
	User* y = x->right;
	User* t = y->left;
	y->left = x;
	x->right = t;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return x;
}

/*用户注册*/
User* insertUser(User* node , char username[], char password[], char name[], char phone[])
{
	if (node == NULL) 
		return newUser(username, password, name, phone);

	if (strcmp(username, node->username) < 0)
	{
		node->left = insertUser(node->left, username, password, name, phone);
	}
	else if (strcmp(username, node->username) > 0)
	{
		node->right = insertUser(node->right,username, password, name, phone);
	}
	else //重复
		return node;
	//更新节点高度
	node->height = max(height(node->left), height(node->right)) + 1;
	
	//获取平衡因子
	int balance = getBalence(node);

	//不平衡时，调整节点
	//LL
	if (balance > 1 && strcmp(username, node->left->username) < 0)
	{
		return rightRotate(node);
	}
	//RR
	if (balance < -1 && strcmp(username, node->right->username) > 0)
	{
		return leftRotate(node);
	}
	// LR
	if (balance > 1 && strcmp(username, node->left->username) > 0) 
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	//RL
	if (balance < -1 && strcmp(username, node->left->username) < 0)
	{
		node->right = rightRotate(node->left);
		return leftRotate(node);
	}
	return node;
}

/*定位场地指针*/
Field* findField(Field* root,char fieldName[])
{
	if (root == NULL) return root;
	Field* temp = (Field*)malloc(sizeof(Field));
	if (strcmp(root->name,fieldName)<0)
	{
		temp = findField(root->left, fieldName);
	}
	else if (strcmp(root->name, fieldName) > 0)
	{
		temp = findField(root->right, fieldName);
	}
	else
	{
		return temp;
	}
}
/*用户预订场地*/
void makeReservation(Field* root,Reservation reservation)
{
	Field* temp = findField(root, reservation.fieldName);
	if (temp == NULL) return NULL;
	
}

/*查询场地信息*/
void queryField(Field* root,bool condition)
{
	if (root == NULL) return root;

}
