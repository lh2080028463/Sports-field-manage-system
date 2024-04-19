#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"
#include"��������.h"
#include<Windows.h>

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum;
extern User* UserRoot;

/*�������û�*/
User* newUser(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	User* newUser = (User*)malloc(sizeof(User));
	//�û����ݶ���
	newUser->idx = idx;
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->name, name);
	strcpy(newUser->phone, phone);
	newUser->time = time;
	newUser->deleted = deleted;
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
int getBalance(User* node)
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
	return y;
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
	return y;
}

/*�û�ע��*/
User* insertUser(User* node, unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	if (node == NULL)
	{
		UserNum++;
		if (UserNum == 1)
			editUserdata(1, username, password, name, phone, time, deleted);
		return newUser(idx, username, password, name, phone, time, deleted);
	}


	if (strcmp(username, node->username) < 0)
	{
		node->left = insertUser(node->left, idx, username, password, name, phone, time, deleted);
	}
	else if (strcmp(username, node->username) > 0)
	{
		node->right = insertUser(node->right, idx, username, password, name, phone, time, deleted);
	}
	else
		return node;
	//���½ڵ�߶�
	node->height = max(height(node->left), height(node->right)) + 1;

	//��ȡƽ������
	int balance = getBalance(node);

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

	editUserdata(idx, username, password, name, phone, time, deleted);
	return node;
}

/*��λ����ָ��*/
Field* findField(Field* root, char fieldName[])
{
	if (root == NULL) return root;
	Field* temp = root;
	if (strcmp(fieldName, root->name) < 0)
	{
		temp = findField(root->left, fieldName);
	}
	else if (strcmp(fieldName, root->name) > 0)
	{
		temp = findField(root->right, fieldName);
	}
	else
	{
		return temp;
	}
}

/*�û�Ԥ������*/
void makeReservation(Reservation reservation, Field* root, char username[])
{
	printf("��������ҪԤ���ĳ������ƣ�");
	scanf("%s", reservation.fieldName);
	//��鳡���Ƿ����
	Field* temp = findField(root, reservation.fieldName);
	if (temp == NULL)
	{
		printf("�޸ó������ƣ�������Ԥ����\n");
		makeReservation(reservation, root, username);
	}
	else
	{
		printf("������Ԥ��ʱ�䣺");
		scanf("%d:%d", &reservation.time.start.hour, &reservation.time.start.minute);
		printf("�������ֹʱ�䣺");
		scanf("%d:%d", &reservation.time.end.hour, &reservation.time.end.minute);
		strcpy(reservation.owner, username);
		editReservations(ReservationNum, reservation.fieldName, reservation.time, reservation.owner);
		printf("����Ԥ���ɹ���\n");
	}

}

/*�������Ʋ�ѯ������Ϣ��ģ����ѯ����������fields��*/
void queryField(Field* root, const char* query, Field* fields[])
{
	static int i = 0;
	if (root == NULL) return;

	// ����������ư�����ѯ�����ַ������򽫸ó��ؼ�����������
	if (strstr(root->name, query) != NULL)
	{
		fields[i++] = root;
	}

	// �ݹ��ѯ��������������
	queryField(root->left, query, fields);
	queryField(root->right, query, fields);
}

/*���������Ϣ*/
void putFieldMessage(Field* tempField[])
{
	for (int i = 0; tempField[i] != NULL; i++)
	{
		printf("�������ƣ�%s\n", tempField[i]->name);
		printf("�糿�۸�%lf ����۸�%lf ���ϼ۸�%lf\n", tempField[i]->price[0], tempField[i]->price[1], tempField[i]->price[2]);
		printf("����ʱ�䣺%d:%d~%d:%d\n", tempField[i]->openTime.start.hour, tempField[i]->openTime.start.minute, tempField[i]->openTime.end.hour, tempField[i]->openTime.end.minute);
		printf("\n");
	}
}

/*���Ԥ����Ϣ*/
void putReservation(Reservation tempReservation)
{
	printf("%d:%d~%d:%d  ", tempReservation.time.start.hour, tempReservation.time.start.minute, tempReservation.time.end.hour, tempReservation.time.end.minute);
	printf("%s\n", tempReservation.fieldName);
	printf("\n");
}

/*ɾ��Ԥ��������Ϣ��δ��ɣ�*/
void deleteReservation(Reservation reservation, Field* root, char username[])
{

}

/*�û����ܣ���������*/
void resetUserPass(User* curUser)
{
	char password0[20];
	char newPass[20];
	printf("����������룺");
	scanf("%s", password0);
	printf("�����������룺");
	scanf("%s", newPass);
	if (strcmp(curUser->password, password0) == 0)
	{
		strcpy(curUser->password, newPass);
		char path[100] = { '\0' };
		strcpy(path, getUserdataPath(*curUser));
		FILE* filePointer = fopen(path, "r+");
		// ����ļ��Ƿ�ɹ���
		if (filePointer == NULL)
		{
			printf("�޷����ļ���\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n", curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, curUser->deleted);
			printf("�����޸ĳɹ�!\n");
		}

		// �ر��ļ�
		fclose(filePointer);
	}
	else
	{
		printf("�����������\n");
	}
}

/*ע���û�*/
void deleteUser(User* curUser)
{
	editUserdata(curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, 1);
		
		system("cls");
		printf("�˻�ע���ɹ�!\n");
		Sleep(500);
	

	
}

/*ȡ������Сֵ*/
User* minValueNode(User* node) {
	User* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*ɾ���û����еĽڵ�*/
User* deleteUserNode(User* root, char username[]) 
{
	if (root == NULL)
		return root;

	if (strcmp(username, root->username) < 0)
	{
		root->left = deleteUserNode(root->left, username);
	}
		
	else if (strcmp(username, root->username) > 0)
	{
		root->right = deleteUserNode(root->right, username);
	}
	else 
	{
		if ((root->left == NULL) || (root->right == NULL)) 
		{
			User* temp = root->left ? root->left : root->right;
			if (temp == NULL) 
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else 
		{
			User* temp = minValueNode(root->right);
			
			root->idx=temp->idx;
			strcpy(root->username, temp->username);
			strcpy(root->password, temp->password);
			strcpy(root->name, temp->name);
			strcpy(root->phone, temp->phone);
			root->time = temp->time;

			root->right = deleteUserNode(root->right, temp->username);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0) 
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0) 
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}