#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include"结构体信息.h"
#include"管理员.h"
extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;

/*记录场地使用情况*/
void recordUserField()
{

}

/*修改场地信息*/
void editField(Field* innerField)
{
	FILE* fp;
	char name[150];
	if ((fp = fopen("name", "w+")) == NULL)
	{
		printf("Error!\n");
		exit(0);
	}
	fscanf(fp, "%s %lf %lf %lf %lf %d %d %d %d %d %u", innerField->name, innerField->area, innerField->price[0], innerField->price[1], innerField->price[2], innerField->openTime.start.hour, innerField->openTime.start.minute, innerField->openTime.end.hour, innerField->openTime.end.minute, innerField->rented, innerField->time);
}

/*删除场地信息*/
void deleteField()
{

}

/*获取场地数据地址*/
char* getFielddataPath(const Field field)
{
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	// 获取当前工作目录
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// 将当前工作目录与文件名拼接成完整的文件路径
		strcpy(filePath, cwd);
		strcat(filePath, "\\fielddata\\field");
		char fieldIdx[10] = { '\0' };
		_itoa(field.idx, fieldIdx, 10);
		strcat(filePath, fieldIdx);
		strcat(filePath, ".txt");
		return filePath;
	}
	else
	{
		perror("getcwd() 错误");
		return 1;
	}
}

/*读入已有场地数据*/
void inputFielddata(Field* FieldRoot)
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
		fscanf(filePointer, "%u\n%s\n%lf\n%lf %lf %lf\n%d:%d\n%d:%d\n%d\n%u", &newField->idx, newField->name, &newField->area, &newField->price[0], &newField->price[1], &newField->price[2], &newField->openTime.start.hour, &newField->openTime.start.minute, &newField->openTime.end.hour, &newField->openTime.end.minute, &newField->rented, &newField->time, &newField->deleted);
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
	newField->price[3] = price[3];
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
	else //重复
		return node;
	//更新节点高度
	node->Fieldheight = max(Fieldheight(node->left), Fieldheight(node->right)) + 1;

	//获取平衡因子
	int balance = getFieldBalence(node);

	//不平衡时，调整节点
	//LL
	if (balance > 1 && strcmp(name, node->left->name) < 0)
	{
		return FieldleftRotate(node);
	}
	//RR
	if (balance < -1 && strcmp(name, node->right->name) > 0)
	{
		return FieldrightRotate(node);
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