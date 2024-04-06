#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"

extern unsigned int ManagerNum, UserNum, ResponNum;

/*�������û�*/
User* newUser(unsigned int idx,char username[], char password[], char name[], char phone[],unsigned int time)
{
	User* newUser = (User*)malloc(sizeof(User));
	//�û����ݶ���
	newUser->idx = idx;
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->name, name);
	strcpy(newUser->phone, phone);
	newUser->time = time;
	//�����������ڵ�
	newUser->left = NULL;
	newUser->right = NULL;
	newUser->height = 1;
	return newUser;
}

/*�������ĸ߶�*/
int height(User* node)
{
	if (node == NULL) return 0;
	return node->height;
}

/*��ȡƽ������*/
int getBalence(User* node)
{
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

/*����*/
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

/*����*/
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

/*�û�ע��*/
User* insertUser(User* node ,unsigned int idx, char username[], char password[], char name[], char phone[],unsigned int time)
{
	if (node == NULL)
	{
		UserNum++;
		if(UserNum==1) 
			editUserdata(1, username, password, name, phone, time);
		return newUser(idx,username, password, name, phone, time);
	}
		

	if (strcmp(username, node->username) < 0)
	{
		node->left = insertUser(node->left, idx, username, password, name, phone, time);
	}
	else if (strcmp(username, node->username) > 0)
	{
		node->right = insertUser(node->right, idx, username, password, name, phone, time);
	}
	else //�ظ�
		return node;
	//���½ڵ�߶�
	node->height = max(height(node->left), height(node->right)) + 1;
	
	//��ȡƽ������
	int balance = getBalence(node);

	//��ƽ��ʱ�������ڵ�
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

	editUserdata(idx,username, password, name, phone, time);
	return node;
}

/*��λ����ָ��*/
Field* findField(Field* root,char fieldName[])
{
	if (root == NULL) return root;
	Field* temp = root;
	if (strcmp(fieldName, root->name)<0)
	{
		temp = findField(root->left, fieldName);
	}
	else if (strcmp(fieldName,root->name) > 0)
	{
		temp = findField(root->right, fieldName);
	}
	else
	{
		return temp;
	}
}

/*�û�Ԥ������*/
void makeReservation(Field* root,Reservation reservation)
{
	Field* temp = findField(root, reservation.fieldName);
	if (temp == NULL) return NULL;
	
}

/*��ѯ������Ϣ*/
void queryField(Field* root,bool condition)
{
	if (root == NULL) return root;

}
