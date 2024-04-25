#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include<Windows.h>
#include"结构体信息.h"
#include"管理员.h"
#include"用户.h"
#include"文件处理.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation Reservations[10000];

/*场地负责人功能：登记用户*/
void registerUser()
{
	printf("请输入用户名(输入0取消):");
	char tempUsername[50];
	while (true)
	{
		scanf("%s", tempUsername);
		if (strcmp(tempUsername, "0") == 0) break;
		if (findUsername(UserRoot, tempUsername) == NULL)
		{
			printf("该用户名未注册！\n请重新输入用户名：");
		}
		else
		{
			makeReservation(Reservations[ReservationNum], FieldRoot, tempUsername);
			break;
		}
	}
}

/*场地负责人功能：信息查询*/
void responQueryMessage()
{
	int querycmd;
	printf(" ******************信息查询****************\n");
	printf("                 0.退出\n");
	printf("                 1.场地信息查询\n");
	printf("                 2.个人预定信息查询\n");
	printf(" ******************************************\n");
	printf("\n");
	printf("请选择信息查询功能：");

	while (true)
	{
		scanf("%d", &querycmd);
		if (querycmd == 0)
		{
			break;
		}
		else if (querycmd == 1)
		{
			Field* tempField[100] = { NULL };
			char query[100];
			printf("请输入查询场地名：");
			scanf("%s", query);
			int num = 0;
			queryField(FieldRoot, query, tempField,&num);
			sortFields(tempField, num, 0);
			putFieldMessage(tempField);


			int conditon;
			while (true)
			{
				printf(" ******************场地信息排序****************\n");
				printf("                 0.取消排序\n");
				printf("                 1.名称\n");
				printf("                 2.面积\n");
				printf("                 3.早上价格\n");
				printf("                 4.下午价格\n");
				printf("                 5.晚上价格\n");
				printf("                 6.开放时间\n");
				printf("                 7.关闭时间\n");
				printf(" ******************************************\n");
				printf("请选择场地信息排序功能：");
				scanf("%d", &conditon);
				if (conditon == 0)
				{
					break;
				}
				else if (conditon > 0 && conditon < 8)
				{
					sortFields(tempField, num, conditon);
					putFieldMessage(tempField);
				}
				else
				{
					system("cls");
					printf("请输入正确的序号!");
					Sleep(500);
					system("cls");
				}
			}


		}
		else if (querycmd == 2)
		{
			printf("请输入待查询的用户名(输入0取消):");
			char tempUsername[50];

			while (true)
			{
				scanf("%s", tempUsername);
				if (strcmp(tempUsername, "0") == 0) break;
				User* currentUser = findUsername(UserRoot, tempUsername);
				if (currentUser == NULL)
				{
					printf("该用户名未注册！\n请重新输入用户名：");
				}
				else
				{
					int flag = 1;
					for (int i = 0; Reservations[i].idx != 0; i++)
					{
						if (Reservations[i].deleted)
						{
							continue;
						}
						if (strcmp(currentUser->username, Reservations[i].owner) == 0)
						{
							flag = 0;
							putReservation(Reservations[i]);
						}
					}
					if (flag)
					{
						printf("当前暂无预定场地！\n");
						Sleep(1000);
						break;
					}
				}
			}
		}
		else
		{
			system("cls");
			printf("请输入正确的序号!");
			Sleep(500);
			system("cls");
		}

	}
}

/*场地负责人功能：重置密码*/
void resetResponPass(Respondent* curRespondent)
{
	char password0[20];
	char newPass[20];
	printf("请输入旧密码：");
	scanf("%s", password0);
	printf("请输入新密码：");
	scanf("%s", newPass);
	if (strcmp(curRespondent->password, password0) == 0)
	{
		strcpy(curRespondent->password, newPass);
		char path[100] = { '\0' };
		strcpy(path, getRespondataPath(curRespondent));
		FILE* filePointer = fopen(path, "r+");
		// 检查文件是否成功打开
		if (filePointer == NULL)
		{
			printf("无法打开文件。\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n", curRespondent->idx, curRespondent->name, curRespondent->phone, curRespondent->username, curRespondent->password, curRespondent->deleted);
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

