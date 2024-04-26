#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <io.h>
#include"结构体信息.h"
#include"文件处理.h"
#include"基础功能.h"
#include"管理员.h"
#include"用户.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
extern Reservation Reservations[10000];

////登记//
//int registration()			//Reservation	
//{
//	char cwd[100] = { '\0' };
//	char fileReservation[100] = { '\0' };
//	char fileRegistration[100] = { '\0' };
//	getcwd(cwd, sizeof(cwd));
//	strcpy(fileReservation, cwd);
//	strcpy(fileRegistration, cwd);
//	strcat(fileReservation, "\\reservation\\reservation.txt");
//	strcat(fileRegistration, "\\reservation\\registration.txt");
//	FILE* Reservation;//预定信息
//	Reservation = fopen(fileReservation, "r+");
//	FILE* Registration;//登记
//	Registration = fopen(fileRegistration, "a");
//	printf("请输入预定者姓名");
//	char owner[50] = {'\0'};
//	scanf("%s,owner");
//	int i = 0;
//	while (!feof(Reservation))
//	{
//		fseek(Reservation, 65*4, 1);
//		char name[51] = { '\0'};
//		fgets(name, 51, Reservation);//fget函数只会读至该行结束
//		int a = strcmp(name, owner);
//		if (a == 0)
//		{
//			fseek(Reservation, -(65+50) * 4, 1);
//			fseek(Reservation,63 * 4, 1);
//			i = fgetc(Reservation);
//			fseek(Reservation, -64 * 4, 1);
//			char share[130] = { '\0'};
//			fgets(share, 130, Reservation);
//			fputs(share, Registration);
//
//			break;
//		}
//	}
//	fclose(Reservation);
//	fclose(Registration);
//	return i;
//}
//
//
//
//
//
////显示查询结果//
//int displaying(FILE* text)
//{
//	for (int i = 0; i < 10; i++)
//	{
//		if (!feof(text))
//		{
//			char Displaying[130] = { '\0' };
//			fgets(Displaying, 129, text);
//			printf("%s", Displaying);
//		}
//		else
//			break;
//	}
//	int id = page(text);
//	return id;
//}
//
//
//
//
//
////翻页//
//int page(FILE* text)
//{
//	int ID = 0;
//	printf("在输入场地编号时输入\n");
//	printf("1 下一页   -1 上一页\n");
//	printf("请输入场地编号：");
//	scanf("%d", &ID);
//	if (ID == 1)
//	{
//		fseek(text, 0, 1);
//		ID = displaying(text);
//	}
//	else if (ID == -1)
//	{
//		fseek(text, -(10 * 128 * 4), 1);
//		ID = displaying(text);
//	}
//	return ID;//不知道这里的函数套用能否正常返回场地ID,如果不能是不是要加break？
//}
//
//
//
//
////修改场地出租状态//
//void Rewrite(int siteID, FILE* Field)
//{
//	fseek(Field, 0, 0);
//	while (!feof(Field))
//	{
//		char thisfieldID[10] = { '\0' };
//		fgets(thisfieldID, 8, Field);
//		int thisID = 0;
//		for (int x = 0; x < 8; x++)
//		{
//			thisID = 10 * thisID + thisfieldID[x];
//		}
//		fseek(Field, -8 * 4, 1);
//		if (thisID == siteID)
//		{
//			fseek(Field, 108 * 4, 1);
//			fprintf(Field, "1"); break;
//		}
//		else
//		{
//			fseek(Field, 128 * 4, 1);
//		}
//	}
//}
//
//
//
//
//
//
////查询场地//
//void site_query(char sitetype)
//{
//	char cwd[100] = { '\0' };
//	char fileField[100] = { '\0' };
//	char Text[50] = { '\0' };
//	getcwd(cwd, sizeof(cwd));
//	strcpy(fileField, cwd);
//	strcat(fileField, "\\Field\\allfield.txt");
//	strcpy(Text, cwd);
//	strcat(Text, "\\Field\\text.txt");
//	FILE* Field;
//	Field = fopen(fileField, "r+");
//	FILE* text;
//	text = fopen(Text, "w+");
//	fseek(Field, 0, 0);
//	while (!feof(Field))
//	{
//		char type =sitetype;
//		char thisfield[129] = { '\0' };
//		fgets(thisfield, 129, Field);
//		if (thisfield[108] == '0'&& thisfield[127] == type)
//		{
//			fputs(thisfield, text);
//		}
//	}
//	fseek(text, 0, 0);
//	int siteID = displaying(text);
//	Rewrite(siteID, Field);
//	fclose(Field);
//	fclose(text);
//	remove(Text);//删除txet文件
//}

/*创建场地负责人节点*/
Respondent* createRespondentNode(unsigned int idx, const char* username, const char* password, const char* name, const char* phone, bool deleted)
{
	Respondent* newNode = (Respondent*)malloc(sizeof(Respondent));
	if (newNode == NULL)
	{
		fprintf(stderr, "内存分配失败\n");
		exit(1);
	}
	newNode->idx = idx;
	strcpy(newNode->username, username);
	strcpy(newNode->password, password);
	strcpy(newNode->name, name);
	strcpy(newNode->phone, phone);
	newNode->deleted = deleted;
	newNode->next = NULL;
	editRespondents(idx, username, password, name, phone, deleted);
	return newNode;

}

/*插入场地负责人节点到链表中*/
void insertRespondentNode(Respondent** head, Respondent* newNode)
{
	if (*head == NULL) {
		*head = newNode;
	}
	else {
		newNode->next = *head;
		*head = newNode;
	}
}

/*删除场地负责人节点*/
void deleteRespondentNode(Respondent** head, const char* username)
{
	if (*head == NULL)
	{
		return;
	}
	Respondent* current = *head;
	Respondent* prev = NULL;

	while (current != NULL) {
		if (strcmp(current->username, username) == 0)
		{
			if (prev == NULL) {
				*head = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

/*查找场地负责人节点*/
Respondent* findRespondentNode(Respondent* head, const char* username)
{
	Respondent* current = head;
	while (current != NULL)
	{
		if (strcmp(current->username, username) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/*打印场地负责人链表*/
void printRespondentList(Respondent* head)
{
	printf("场地负责人信息：\n");
	Respondent* current = head;
	while (current != NULL) {
		printf("账号：%s，密码：%s，姓名：%s，联系方式：%s，删除情况：%s\n",
			current->username, current->password, current->name,
			current->phone, current
			->deleted ? "已删除" : "未删除");
		current = current->next;
	}
}

/*管理员：场地查询*/
int managerputFieldMessage(Field* tempField[], int temp)
{
	for (int i = 0; tempField[i] != NULL; i++)
	{
		printf("场地名称：%s\n", tempField[i]->name);
		printf("场地面积：%.2lf平方米\n", tempField[i]->area);
		printf("早上价格：%.2lf元 下午价格：%.2lf元 晚上价格：%.2lf元\n", tempField[i]->price[0], tempField[i]->price[1], tempField[i]->price[2]);
		printf("开放时间段：%02d:%02d~%02d:%02d\n", tempField[i]->openTime.start.hour, tempField[i]->openTime.start.minute, tempField[i]->openTime.end.hour, tempField[i]->openTime.end.minute);
		printf("\n");
		temp++;
	}
	return temp;
}

/*删除场地负责人*/
void deleteRespondent()
{
	int temp = 0;
	char responname[20];
	Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	printf("*****场地负责人删除*****\n");
	printf("请输入想要删除的场地负责人账号：");
	scanf("%s", responname);
	for (int i = 1; i <= ResponNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respondent");
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
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, &queryRespondent->deleted);
		if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
		{
			temp = 1;
			break;
		}
		else
			temp = 0;
	}
	if (temp == 0)
	{
		system("cls");
		printf("该负责人不存在，请重新输入！\n");
		Sleep(1000);
		system("cls");
		deleteRespondent();
	}
	else
	{
		filePointer = fopen(filePath, "w");
		queryRespondent->deleted = 1;
		deleteRespondentNode(RespondentsHead, queryRespondent->username);
		fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, queryRespondent->deleted);
		fclose(filePointer);
		system("cls");
		printf("已成功删除！\n");
		Sleep(2000);
		system("cls");
	}
}

/*修改场地负责人信息*/
void editRespondent()
{
	int temp = 0;
	char responname[20];
	Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	printf("*****场地负责人信息修改*****\n");
	printf("请输入想要修改的场地负责人账号：");
	scanf("%s", responname);
	for (int i = 1; i <= ResponNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respondent");
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
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, &queryRespondent->deleted);
		if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
		{
			temp = 1;
			break;
		}
		else
			temp = 0;
	}
	if (temp == 0)
	{
		system("cls");
		printf("该负责人不存在，请重新输入！\n");
		Sleep(1000);
		system("cls");
		deleteRespondent();
	}
	else
	{
		while (true)
		{
			system("cls");
			filePointer = fopen(filePath, "w");
			Respondent* fileRespondent = findRespondentNode(RespondentsHead, responname);
			printf("请选择修改的负责人信息：\n");
			printf("	1.账号\n");
			printf("	2.密码\n");
			printf("	3.姓名\n");
			printf("	4.联系方式\n");
			printf("请选择：");
			scanf("%d", &temp);
			system("cls");
			if (temp == 1)
			{
				printf("请输入更改后的信息；");
				scanf("%s", fileRespondent->username);
			}
			if (temp == 2)
			{
				printf("请输入更改后的信息；");
				scanf("%s", fileRespondent->password);
			}
			if (temp == 3)
			{
				printf("请输入更改后的信息；");
				scanf("%s", fileRespondent->name);
			}
			if (temp == 4)
			{
				printf("请输入更改后的信息；");
				scanf("%s", fileRespondent->phone);
			}
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", queryRespondent->idx, fileRespondent->name, fileRespondent->phone, fileRespondent->username, fileRespondent->password, queryRespondent->deleted);
			fclose(filePointer);
			system("cls");
			printf("修改成功！\n");
			Sleep(2000);
			system("cls");
			printf("1.修改其他信息\n");
			printf("2.退出\n");
			printf("请选择：");
			scanf("%d", &temp);
			if (temp == 2)
			{
				system("cls");
				break;
			}
		}
	}
}

/*查询用户预订信息*/
void queryUserReservation()
{
	system("cls");
	printf("请输入待查询的用户名(输入0取消):");
			char tempUsername[50];
			while (true)
			{
				scanf("%s", tempUsername);
				if (strcmp(tempUsername, "0") == 0) 
					break;
				User* currentUser = findUsername(UserRoot, tempUsername);
				if (currentUser == NULL)
				{
					system("cls");
					printf("该用户名未注册！\n请重新输入用户名：");
				}
				else
				{
					int temp = 1;
					for (int i = 0; Reservations[i].idx != 0; i++)
					{
						if (Reservations[i].deleted)
						{
							continue;
						}
						if (strcmp(currentUser->username, Reservations[i].owner) == 0)
						{
							temp = 0;
							putReservation(Reservations[i]);
						}
					}
					if (temp == 0)
					{
						printf("输入任意数字退出：");
						scanf("%d", &temp);
						system("cls");
						break;
					}
					if (temp == 1)
					{
						system("cls");
						printf("当前暂无预定场地！\n");
						Sleep(1000);
						break;
					}
				}
			}
}

void FieldtoRespondent(Field* fieldRoot)
{
	int temp;
	char fieldname[20];
	printf("*****分配场地给场地负责人*****\n");
	printf("请输入被分配的场地名称：");
	scanf("%s", fieldname);
	Field* tempField = findFieldname(fieldRoot, fieldname);
	if (fieldRoot != NULL && tempField != NULL)
	{
		char responname[20];
		Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
		FILE* filePointer;
		char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
		char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
		printf("请输入分配到的场地负责人账号：");
		scanf("%s", responname);
		for (int i = 1; i <= ResponNum; i++)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				strcpy(filePath, cwd);
				strcat(filePath, "\\respondata\\respondent");
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
			filePointer = fopen(filePath, "r");
			if (filePointer == NULL)
			{
				printf("初始化读入数据%d时无法打开文件！\n", i);
				return 1;
			}
			fscanf(filePointer, "%u\n%s\n%s\n%s\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username);
			if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
			{
				temp = 1;
				break;
			}
			else
				temp = 0;
		}
		if (temp == 0)
		{
			system("cls");
			printf("该负责人不存在，请重新输入！\n");
			Sleep(1000);
			system("cls");
			FieldtoRespondent(fieldRoot);
		}
		else
		{
			tempField->respondentIdx = queryRespondent->idx;
			editFielddata(tempField->idx, tempField->name, tempField->area, tempField->price, tempField->openTime, tempField->rented, tempField->time, tempField->deleted, tempField->respondentIdx);
			system("cls");
			printf("分配成功！\n");
			Sleep(1000);
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("该场地不存在，请重新输入！\n");
		Sleep(1000);
		system("cls");
		FieldtoRespondent(fieldRoot);
	}
}