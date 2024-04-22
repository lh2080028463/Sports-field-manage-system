#define _CRT_SECURE_NO_WARNINGS 1  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <io.h>
#include"结构体信息.h"
#include"文件处理.h"

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

// 创建场地负责人节点
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

// 插入场地负责人节点到链表中
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

// 删除场地负责人节点
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

// 查找场地负责人节点
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

// 打印场地负责人链表
void printRespondentList(Respondent* head)
{
	printf("场地负责人信息：\n");
	Respondent* current = head;
	while (current != NULL) {
		printf("账号：%s，密码：%s，姓名：%s，联系方式：%s，删除情况：%s\n",
			current->username, current->password, current->name,
			current->phone, current->deleted ? "已删除" : "未删除");
		current = current->next;
	}
}



