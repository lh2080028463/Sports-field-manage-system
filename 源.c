#define _CRT_SECURE_NO_WARNINGS
#include"基础功能.h"
#include"文件处理.h"
#include"用户.h"
#include"界面.h"
#include"结构体信息.h"
#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int ManagerNum,UserNum, ResponNum,ReservationNum, FieldNum;
User* UserRoot;
Field* FieldRoot;
Reservation reservations[10000];

int main()
{
	initNum();
	inputUserdata(UserRoot);
	inputReservation(reservations);

	while (true)
	{
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
			managerLogin();
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
				
				int userCmd;
				while (true)
				{
					system("cls");
					userMenu();
					printf("请选择功能：");
					scanf("%d", &userCmd);
					if (userCmd == 0)
					{
						break;
					}
					else if (userCmd == 1)
					{
						editMessageMenu(currentUser);
					}
					else if (userCmd == 2)
					{
						int reserveCmd;
						while (true)
						{
							system("cls");
							reserveMenu();
							printf("请选择功能：");
							scanf("%d", &reserveCmd);
							if (reserveCmd==0)
							{
								break;
							}
							else if (reserveCmd == 1)
							{
								makeReservation(reservations[ReservationNum++], FieldRoot, currentUser->username);
							}
							else if (reserveCmd == 2)
							{

							}
							else if (reserveCmd == 3)
							{

							}
						}
						
					}
					else if (userCmd == 3)
					{
						if (ReservationNum > 0)
						{
							bool flag = true;
							for (int i = 0; i < ReservationNum; i++)
							{
								if (strcmp(reservations[i].owner, currentUser->username) == 0)
								{
									putReservation(reservations[i]);
									flag = false;
								}
							}
							if (flag)
							{
								printf("目前暂无预订信息！\n");
							}
						}
						else
						{
							printf("目前暂无预订信息！\n");
						}

					}
					else if (userCmd == 4)
					{

					}
					else if (userCmd == 5)
					{
						resetUserPass(currentUser);
					}
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
			getchar();
			break;
		}
		
		editUserNum();
	}
	return 0;
}
