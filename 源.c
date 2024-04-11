#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"基础功能.h"
#include"界面.h"
#include"结构体信息.h"
#include"文件处理.h"
#include"用户.h"

unsigned int ManagerNum,UserNum, ResponNum,ReservationNum;
User* UserRoot;
Field* FieldRoot;
Reservation reservations[10000];

int main()
{
	initNum();
	inputUserdata(UserRoot);

	while (true)
	{
		system("cls");
		menu();
		int cmd;
		printf("请选择功能：");
		scanf("%d", &cmd);
		if (cmd == 0)
			break;
		switch (cmd)
		{
		case 0:
		{

			break;
		}

		case 1:
		{

			break;
		}

		case 2:
		{

			break;
		}
		case 3:
		{
			User* currentUser=userLogin();
			if (currentUser!=NULL)
			{
				userMenu();
				int userCmd;
				printf("请选择功能：");
				scanf("%d", &userCmd);
				if (userCmd==0)
				{
					continue;
				}
				else if (userCmd == 1)
				{
					editMessageMenu(currentUser);
				}
				else if (userCmd == 2)
				{
					makeReservation(reservations[ReservationNum++], FieldRoot, currentUser->username);
				}
			}
			break;
		}
		case 4:
		{
			UserRoot = userRegister(UserRoot);
			break;
		}

		default:
			system("cls");
			printf("请选择正确的序号！\n");
			Sleep(1000);
			break;
		}
		
		editUserNum();
	}
	return 0;
}
