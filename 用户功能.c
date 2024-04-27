#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"结构体信息.h"
#include"文件处理.h"
#include"基础功能.h"
#include<Windows.h>

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation Reservations[10000];

/*创建新用户*/
User* newUser(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	User* newUser = (User*)malloc(sizeof(User));
	//用户数据读入
	newUser->idx = idx;
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->name, name);
	strcpy(newUser->phone, phone);
	newUser->time = time;
	newUser->deleted = deleted;
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
int getBalance(User* node)
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
	return y;
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
	return y;
}

/*用户注册*/
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
	//更新节点高度
	node->height = max(height(node->left), height(node->right)) + 1;

	//获取平衡因子
	int balance = getBalance(node);

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

	editUserdata(idx, username, password, name, phone, time, deleted);
	return node;
}

/*取树中最小值*/
User* minValueNode(User* node) {
	User* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*删除用户树中的节点*/
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

			root->idx = temp->idx;
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
void makeReservation(Reservation* reserv, Field* root, char username[])
{
	Reservation reservation;
	reservation.idx = ReservationNum+1;
	printf("请输入需要预定的场地名称（输入0取消预定）：");
	scanf("%s", reservation.fieldName);
	if (strcmp(reservation.fieldName, "0") == 0)
	{
		return;
	}
	//检查场地是否存在
	Field* temp = findField(FieldRoot, reservation.fieldName);
	if (temp == NULL)
	{
		printf("无该场地名称！请重新预定！\n");
		makeReservation(reserv, root, username);
	}
	else
	{

		printf("请输入起始时间：");
		scanf("%d:%d", &reservation.time.start.hour, &reservation.time.start.minute);
		printf("请输入截止时间：");
		scanf("%d:%d", &reservation.time.end.hour, &reservation.time.end.minute);
		if (checkTime(reservation.time,temp->openTime))
		{
			if (!rented(reservation))
			{
				reservation.cost = calculatePrice(reservation);
				strcpy(reservation.owner, username);
				reserv[ReservationNum].idx = reservation.idx;
				reserv[ReservationNum].time = reservation.time;
				strcpy(reserv[ReservationNum].owner, reservation.owner);
				reserv[ReservationNum].cost = reservation.cost;
				strcpy(reserv[ReservationNum].fieldName, reservation.fieldName);
				ReservationNum++;
				
				editReservations(ReservationNum, reservation.fieldName, reservation.time, reservation.owner, 0,reservation.cost);
				printf("场地预定成功！\n");
				Sleep(500);
			}
			else
			{
				printf("该场地目前已被预定！\n请重新选择！\n");
				makeReservation(reserv, root, username);
			}
		}
		else
		{
			printf("该时间段场地未开放！请重新预定！\n");
			makeReservation(reserv, root, username);
		}
		
	}

}

void queryField(Field* root, const char* query, Field fields[], int* count) 
{
	if (root == NULL) return;

	// 如果场地名称包含查询条件字符串，则将该场地加入结果数组中
	if (strstr(root->name, query) != NULL) {
		fields[*count] = *root;
		(*count)++;
	}
	// 递归查询左子树和右子树
	queryField(root->left, query, fields, count);
	queryField(root->right, query, fields, count);
}

/*遍历场地*/
void traverseField(Field* root, Field fields[], int* count)
{
	if (root == NULL) return;
		fields[*count] = *root;
	(*count)++;
	traverseField(root->left, fields, count);
	traverseField(root->right, fields, count);
}


/*输出场地信息*/
void putFieldMessage(Field tempField[])
{
	printf("   场地名称             场地面积             早上价格             下午价格             晚上价格              开放时间段\n");
	for (int i = 0; tempField[i].idx != NULL; i++)
	{
		printf("%12s %13.2lf平方米 %18.2lf元 %18.2lf元 %18.2lf元            %02d:%02d~%02d:%02d\n", tempField[i].name, tempField[i].area, tempField[i].price[0], tempField[i].price[1], tempField[i].price[2], tempField[i].openTime.start.hour, tempField[i].openTime.start.minute, tempField[i].openTime.end.hour, tempField[i].openTime.end.minute);

	}
	printf("\n");
}
/*输出预定信息*/
void putReservation(Reservation tempReservation)
{
	printf("%s ", tempReservation.fieldName);
	printf("%02d:%02d~%02d:%02d\n", tempReservation.time.start.hour, tempReservation.time.start.minute, tempReservation.time.end.hour, tempReservation.time.end.minute);
	printf("\n");
}

/*删除预定场地信息*/
void deleteReservation(char username[])
{
	bool flag = 1;
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0)
		{
			flag = 0;
			putReservation(Reservations[i]);
		}
	}
	if (flag)
	{
		printf("当前暂无预定信息!\n");
		Sleep(500);
		return;
	}

	Reservation tempReserve;

	printf("请按照以上格式输入你要删除的预定信息：");
	scanf("%s %02d:%02d~%02d:%02d", tempReserve.fieldName, &tempReserve.time.start.hour, &tempReserve.time.start.minute, &tempReserve.time.end.hour, &tempReserve.time.end.minute);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0 &&
			strcmp(tempReserve.fieldName, Reservations[i].fieldName) == 0 &&
			tempReserve.time.start.hour == Reservations[i].time.start.hour &&
			tempReserve.time.start.minute == Reservations[i].time.start.minute &&
			tempReserve.time.end.hour == Reservations[i].time.end.hour &&
			tempReserve.time.end.minute == Reservations[i].time.end.minute)
		{
			Reservations[i].deleted = 1;
			printf("已成功取消该预定！\n");
			editReservations(Reservations[i].idx, Reservations[i].fieldName, Reservations[i].time, Reservations[i].owner, Reservations[i].deleted,Reservations[i].cost);
			Sleep(500);
			
		}
	}
	
}

/*用户功能：重置密码*/
void resetUserPass(User* curUser,bool forget)
{
	char password0[20];
	char newPass[20];
	if (!forget)
	{
		printf("请输入旧密码：");
		scanf("%s", password0);
	}
	
	printf("请输入新密码：");
	scanf("%s", newPass);
	if (forget||strcmp(curUser->password, password0) == 0)
	{
		strcpy(curUser->password, newPass);
		char path[100] = { '\0' };
		strcpy(path, getUserdataPath(*curUser));
		FILE* filePointer = fopen(path, "r+");
		// 检查文件是否成功打开
		if (filePointer == NULL)
		{
			printf("无法打开文件。\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n", curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, curUser->deleted);
			system("cls");
			printf("密码修改成功!\n");
			Sleep(500);
		}
		fflush(filePointer);
		// 关闭文件
		fclose(filePointer);
	}
	else
	{
		printf("密码输入错误！\n");
	}
}

/*注销用户*/
void deleteUser(User* curUser)
{
	editUserdata(curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, 1);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, curUser->username) == 0)
		{
			Reservations[i].deleted = 1;
			editReservations(Reservations[i].idx, Reservations[i].fieldName, Reservations[i].time, Reservations[i].owner, Reservations[i].deleted,Reservations[i].cost);
		}
	}

	system("cls");
	printf("账户注销成功!\n");
	Sleep(500);
}

/*用户忘记密码*/
void userForget()
{
	char username[20];
	while (true)
	{
		printf("请输入账号（输入0退出）:");
		scanf("%s", username);
		if (strcmp(username, "0") == 0)
		{
			break;
		}
		User* currentUser = findUsername(UserRoot, username);
		if (currentUser != NULL)
		{
			char currentPhone[20];
			while (true)
			{
				printf("请输入你的联系方式（输入0退出）：");
				scanf("%s", &currentPhone);
				if (strcmp(currentPhone, "0") == 0)
				{
					break;
				}
				else
				{
					if (strcmp(currentPhone, currentUser->phone) == 0)
					{
						resetUserPass(currentUser, 1);
						break;
					}
					else
					{
						printf("联系方式输入错误！\n");
						Sleep(1000);
						system("cls");
					}
				}
			}

		}
		else
		{
			printf("未查询到该账号信息！请重新输入！\n");
		}
	}
}

/*统计：用户总支出金额*/
unsigned int countAllCost(char username[])
{
	unsigned int allCost = 0;
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0&&!Reservations[i].deleted)
		{
			allCost += Reservations[i].cost;
		}
	}
	return allCost;
}

/*统计：用户某时间段支出金额*/
void periodCost(char username[])
{
	unsigned int cost = 0;
	Duration tempd;
	printf("请输入需要查询的起始时间:");
	scanf("%02d:%02d", &tempd.start.hour, &tempd.start.minute);
	printf("请输入需要查询的结束时间:");
	scanf("%02d:%02d", &tempd.end.hour, &tempd.end.minute);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0 && !Reservations[i].deleted)
		{
			if (checkTime(Reservations[i].time, tempd))
			{
				cost += Reservations[i].cost;
			}
		}
	}
	
	
	printf("该时间段内消费：%u元\n", cost);
	
	
}