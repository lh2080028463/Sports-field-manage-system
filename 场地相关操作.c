#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include<Windows.h>
#include"结构体信息.h"
#include"管理员.h"
#include"基础功能.h"
#include"用户.h"
extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern Field* FieldRoot;

/*记录场地使用情况*/
void recordUserField()
{

}

/*修改场地信息*/
void editField(Field* fieldRoot)
{
	int temp;
	char fieldname[20];
	printf("*****场地信息修改*****\n");
	printf("请输入想要更改的场地名称：");
	scanf("%s", fieldname);
	Field* tempField = findFieldname(fieldRoot, fieldname);
	if (fieldRoot != NULL && tempField != NULL)
	{
		while (true)
		{
			printf("请选择想要更改的场地信息：\n");
			printf("	1.面积\n");
			printf("	2.价格\n");
			printf("	3.开放时间\n");
			printf("请选择：");
			scanf("%d", &temp);
			system("cls");
			if (temp == 1)
			{
				printf("请输入新面积：");
				scanf("%lf", &tempField->area);
				system("cls");
			}
			else if (temp == 2)
			{
				while (true)
				{
					printf("请输入想更改的价格：\n");
					printf("	1.早间价格\n");
					printf("	2.午间价格\n");
					printf("	3.晚间价格\n");
					printf("请选择：");
					scanf("%d", &temp);
					system("cls");
					if (temp == 1)
					{
						printf("请输入新早间价格：");
						scanf("%lf", &tempField->price[0]);
					}
					if (temp == 2)
					{
						printf("请输入新午间价格：");
						scanf("%lf", &tempField->price[1]);
					}
					if (temp == 3)
					{
						printf("请输入新晚间价格：");
						scanf("%lf", &tempField->price[2]);
					}
					system("cls");
					printf("是否更改其他时间的价格？\n");
					printf("	1.是\n");
					printf("	2.否\n");
					printf("请选择：");
					scanf("%d", &temp);
					system("cls");
					if (temp == 2)
					{
						break;
					}
				}
				
			}
			else if (temp == 3)
			{
				printf("请输入新的起始时间（xx:xx)：");
				scanf("%d:%d", &tempField->openTime.start.hour, &tempField->openTime.start.minute);
				printf("请输入新的结束时间（xx:xx)：");
				scanf("%d:%d", &tempField->openTime.end.hour, &tempField->openTime.end.minute);
				system("cls");
			}
			printf("是否更改该场地的其他信息？\n");
			printf("	1.是\n");
			printf("	2.否\n");
			printf("请选择：");
			scanf("%d", &temp);
			system("cls");
			if (temp == 2)
			{
				editFielddata(tempField->idx, tempField->name, tempField->area, tempField->price, tempField->openTime, tempField->rented, tempField->time, tempField->deleted);
				printf("修改成功！");
				Sleep(2000);
				break;
			}
		}
		printf("是否更改其他场地的信息？\n");
		printf("	1.是\n");
		printf("	2.否\n");
		printf("请选择：");
		scanf("%d", &temp);
		system("cls");
		if (temp == 1)
		{
			editField(fieldRoot);
		}
	}
	else
	{
		system("cls");
		printf("该场地不存在，请重新输入！\n");
		Sleep(1000);
		system("cls");
		editField(fieldRoot);
	}
	
}

/*删除场地信息*/
void deleteField(Field* fieldRoot)
{
	int temp;
	char fieldname[20];
	printf("*****场地删除*****\n");
	printf("请输入想要删除的场地名称：");
	scanf("%s", fieldname);
	Field* tempField = findFieldname(fieldRoot, fieldname);
	if (fieldRoot != NULL && tempField != NULL)
	{
		tempField->deleted = 1;
		editFielddata(tempField->idx, tempField->name, tempField->area, tempField->price, tempField->openTime, tempField->rented, tempField->time, tempField->deleted);
		system("cls");
		printf("已成功删除！\n");
		Sleep(2000);
		system("cls");
	}
	else
	{
		system("cls");
		printf("该场地不存在，请重新输入！\n");
		Sleep(1000);
		system("cls");
		deleteField(fieldRoot);
	}
}



/*读入已有场地数据*/
void inputFielddata(Field* fieldRoot)
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	for (int i = 1; i <= FieldNum; i++)
	{
		//更新文件路径
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\fielddata\\field");
			char fieldIdx[10] = { '\0' };
			_itoa(i, fieldIdx, 10);
			strcat(filePath, fieldIdx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() 错误");
			return 1;
		}
		//读入txt中场地数据
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		Field* newField = (Field*)malloc(sizeof(Field));
		fscanf(filePointer, "%u\n%s\n%lf\n%lf %lf %lf\n%d:%d\n%d:%d\n%d\n%u\n%u\n", &newField->idx, newField->name, &newField->area, &newField->price[0], &newField->price[1], &newField->price[2], &newField->openTime.start.hour, &newField->openTime.start.minute, &newField->openTime.end.hour, &newField->openTime.end.minute, &newField->rented, &newField->time, &newField->deleted);
		if (newField->deleted == 0)
		{
			FieldRoot = addField(FieldRoot, newField->idx, newField->name, newField->area, newField->price, newField->openTime, newField->rented, newField->time, newField->deleted);
			FieldNum--;
		}
		fflush(filePointer);
		fclose(filePointer);
	}
	
}

/*新建场地*/
Field* newField(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time,unsigned int deleted)
{
	Field* newField = (Field*)malloc(sizeof(Field));
	//场地数据读入
	newField->idx = idx;
	strcpy(newField->name, name);
	newField->area = area;
	newField->price[0] = price[0];
	newField->price[1] = price[1];
	newField->price[2] = price[2];
	newField->openTime = openTime;
	newField->rented = rented;
	newField->time = time;
	newField->deleted = deleted;
	//构建二叉树节点
	newField->left = NULL;
	newField->right = NULL;
	newField->Fieldheight = 1;
	return newField;
}

/*计算树的高度*/
int Fieldheight(Field* node)
{
	if (node == NULL) return 0;
	return node->Fieldheight;
}

/*获取平衡因子*/
int getFieldBalence(Field* node)
{
	if (node == NULL) return 0;
	return Fieldheight(node->left) - Fieldheight(node->right);
}

/*右旋*/
Field* FieldrightRotate(Field* x)
{
	Field* y = x->left;
	Field* t = y->right;
	y->right = x;
	x->left = t;
	x->Fieldheight = max(Fieldheight(x->left), Fieldheight(x->right)) + 1;
	y->Fieldheight = max(Fieldheight(y->left), Fieldheight(y->right)) + 1;
	return y;
}

/*左旋*/
Field* FieldleftRotate(Field* x)
{
	Field* y = x->right;
	Field* t = y->left;
	y->left = x;
	x->right = t;
	x->Fieldheight = max(Fieldheight(x->left), Fieldheight(x->right)) + 1;
	y->Fieldheight = max(Fieldheight(y->left), Fieldheight(y->right)) + 1;
	return y;
}

/*场地添加*/
Field* addField(Field* node, unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted)
{
	if (node == NULL)
	{
		FieldNum++;
		if (FieldNum == 1)
			editFielddata(1, name, area, price, openTime, rented, time, deleted);
		return newField(idx, name, area, price, openTime, rented, time, deleted);
	}
	if (strcmp(name, node->name) < 0)
	{
		node->left = addField(node->left, idx, name, area, price, openTime, rented, time, deleted);
	}
	else if (strcmp(name, node->name) > 0)
	{
		node->right = addField(node->right, idx, name, area, price, openTime, rented, time, deleted);
	}
	else
		return node;
	//更新节点高度
	node->Fieldheight = max(Fieldheight(node->left), Fieldheight(node->right)) + 1;

	//获取平衡因子
	int balance = getFieldBalence(node);

	//不平衡时，调整节点
	//LL
	if (balance > 1 && strcmp(name, node->left->name) < 0)
	{
		return FieldrightRotate(node);
	}
	//RR
	if (balance < -1 && strcmp(name, node->right->name) > 0)
	{
		return FieldleftRotate(node);
	}
	// LR
	if (balance > 1 && strcmp(name, node->left->name) > 0)
	{
		node->left = FieldleftRotate(node->left);
		return FieldrightRotate(node);
	}
	//RL
	if (balance < -1 && strcmp(name, node->left->name) < 0)
	{
		node->right = FieldrightRotate(node->left);
		return FieldleftRotate(node);
	}
	editFielddata(idx, name, area, price, openTime, rented, time, deleted);
	return node;
}

/*管理员查询场地信息*/
void mangerqueryfield()
{
	Field* tempField[100] = { NULL };
	char query[100];
	printf("请输入查询场地名称：");
	scanf("%s", query);
	int num = queryField(FieldRoot, query, tempField);
	sortFields(tempField, num, 0);
	putFieldMessage(tempField);
	while (true)
	{
		int temp2 = 0;
		printf("\n\n	1.查询其他场地信息\n");
		printf("	2.返回场地信息管理界面\n");
		printf("请选择：");
		scanf("%d", &temp2);
		if (temp2 == 1)
		{
			system("cls");
			mangerqueryfield();
			break;
		}
		else if (temp2 == 2)
		{
			system("cls");
			break;
		}
		else
		{
			system("cls");
			printf("请输入正确的序号!");
			Sleep(1000);
			system("cls");
		}
	}
			
}