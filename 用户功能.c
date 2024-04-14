#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"结构体信息.h"
#include"文件处理.h"
#include"基础功能.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum;

/*创建新用户*/
User* newUser(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time)
{
	User* newUser = (User*)malloc(sizeof(User));
	//用户数据读入
	newUser->idx = idx;
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->name, name);
	strcpy(newUser->phone, phone);
	newUser->time = time;
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
User* insertUser(User* node, unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time)
{
	if (node == NULL)
	{
		UserNum++;
		if (UserNum == 1)
			editUserdata(1, username, password, name, phone, time);
		return newUser(idx, username, password, name, phone, time);
	}


	if (strcmp(username, node->username) < 0)
	{
		node->left = insertUser(node->left, idx, username, password, name, phone, time);
	}
	else if (strcmp(username, node->username) > 0)
	{
		node->right = insertUser(node->right, idx, username, password, name, phone, time);
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

	editUserdata(idx, username, password, name, phone, time);
	return node;
}

/*定位场地指针*/
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

/*用户预订场地*/
void makeReservation(Reservation reservation, Field* root, char username[])
{
	printf("请输入需要预定的场地名称：");
	scanf("%s", reservation.fieldName);
	//检查场地是否存在
	Field* temp = findField(root, reservation.fieldName);
	if (temp == NULL)
	{
		printf("无该场地名称！请重新预定！\n");
		makeReservation(reservation, root, username);
	}
	else
	{
		printf("请输入预定时间：");
		scanf("%d:%d", &reservation.time.start.hour, &reservation.time.start.minute);
		printf("请输入截止时间：");
		scanf("%d:%d", &reservation.time.end.hour, &reservation.time.end.minute);
		strcpy(reservation.owner, username);
		editReservations(ReservationNum, reservation.fieldName, reservation.time, reservation.owner);
	}

}

/*按照名称查询场地信息（模糊查询）并保存在fields中*/
void queryField(Field* root, const char* query, Field* fields[])
{
	static int i = 0;
	if (root == NULL) return;

	// 如果场地名称包含查询条件字符串，则将该场地加入结果数组中
	if (strstr(root->name, query) != NULL)
	{
		fields[i++] = root;
	}

	// 递归查询左子树和右子树
	queryField(root->left, query, fields);
	queryField(root->right, query, fields);
}

/*输出场地信息*/
void putFieldMessage(Field* tempField[])
{
	for (int i = 0; tempField[i] != NULL; i++)
	{
		printf("场地名称：%s\n", tempField[i]->name);
		printf("早晨价格：%lf 中午价格：%lf 晚上价格：%lf\n", tempField[i]->price[0], tempField[i]->price[1], tempField[i]->price[2]);
		printf("开放时间：%d:%d~%d:%d\n", tempField[i]->openTime.start.hour, tempField[i]->openTime.start.minute, tempField[i]->openTime.end.hour, tempField[i]->openTime.end.minute);
		printf("\n");
	}
}

/*输出预定信息*/
void putReservation(Reservation tempReservation)
{
	printf("%d:%d~%d:%d  ", tempReservation.time.start.hour, tempReservation.time.start.minute, tempReservation.time.end.hour, tempReservation.time.end.minute);
	printf("%s\n", tempReservation.fieldName);
	printf("\n");
}

/*删除预定场地信息*/
void deleteReservation(Reservation reservation, Field* root, char username[])
{

}

/*用户功能：重置密码*/
void resetUserPass(User* curUser)
{
	char password0[20];
	char newPass[20];
	printf("请输入旧密码：");
	scanf("%s", password0);
	printf("请输入新密码：");
	scanf("%s", newPass);
	if (strcmp(curUser->password, password0) == 0)
	{
		strcpy(curUser->password, newPass);
		char* path = getUserdataPath(*curUser);
		FILE* filePointer = fopen(path, "r+");
		// 检查文件是否成功打开
		if (filePointer == NULL)
		{
			printf("无法打开文件。\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n", curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time);
		}
		
		// 关闭文件
		fclose(filePointer);
	}
	else
	{
		printf("密码输入错误！\n");
	}
}