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
#include"基础功能.h"
#include"管理员.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
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
		User* user = findUsername(UserRoot, tempUsername);
		if (user == NULL)
		{
			printf("该用户名未注册！\n请重新输入用户名：");
		}
		else
		{
			
			if (user->timed >= 10)
			{
				system("cls");
				printf("预约次数已达到上限！");
				Sleep(1000);
				system("cls");
				break;
			}
			else
			{
				makeReservation(&Reservations[ReservationNum], FieldRoot, tempUsername);
				user->timed++;
				editUserdata(user->idx, user->username, user->password, user->name, user->phone, user->time, user->deleted, user->timed)
				break;
			}
		}
	}
}

/*场地负责人功能：信息查询*/
void responQueryMessage()
{
	int querycmd;
	while (true)
	{
		printf(" ******************信息查询****************\n");
		printf("                 0.退出\n");
		printf("                 1.场地信息查询\n");
		printf("                 2.个人预定信息查询\n");
		printf(" ******************************************\n");
		printf("\n");
		printf("请选择信息查询功能：");
		scanf("%d", &querycmd);
		if (querycmd == 0)
		{
			break;
		}
		else if (querycmd == 1)
		{
			Field tempField[100] = { NULL };
			char query[100];
			int num = 0;
			while (true)
			{
				printf("请输入查询场地名：");
				scanf("%s", query);

				queryField(FieldRoot, query, tempField, &num);
				qsort(tempField, num, sizeof(Field), compareFields1);
				if (num > 0)
				{
					putFieldMessage(tempField);
					break;
				}
				else
				{
					getchar();
					system("cls");
					printf("未查询到含该关键词的场地!请重新输入！\n");
					Sleep(500);
					system("cls");
				}
			}
			sortFields(tempField, num);
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
void resetResponPass(Respondent* curRespondent,bool forget)
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
	if (forget||strcmp(curRespondent->password, password0) == 0)
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

/*场地负责人忘记密码*/
void responForget()
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
		Respondent* currentRespon = findRespondentNode(RespondentsHead, username);
		if (currentRespon != NULL)
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
					if (strcmp(currentPhone, currentRespon->phone) == 0)
					{
						resetResponPass(currentRespon,1);
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

/*统计某用户总使用时长*/
void TotalUseTime()
{
	char username[20];

	unsigned int total = 0;
	while (true)
	{
		printf("请选择查询的用户名(输入-1退出)：");
		scanf("%s", username);
		if (strcmp(username,"-1")==0)
		{
			break;
		}
		if (findUsername(UserRoot,username)!=NULL)
		{
			for (int i = 0; Reservations[i].idx != 0; i++)
			{
				if (strcmp(Reservations[i].owner, username) == 0)
				{
					total += calculateTime(Reservations[i].time);
				}
			}
			printf("该用户使用时长为：%.2lf小时\n", total/60.0);
		}
		else
		{
			printf("未查询到该用户!请重新输入!\n");
		}
		

	}
	
}