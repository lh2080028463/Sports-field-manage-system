#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"基础功能.h"
#include"界面.h"
#include"结构体信息.h"
#include"文件处理.h"

unsigned int ManagerNum, UserNum, ResponNum;
User* UserRoot;

int main()
{
	initNum();
	inputUserdata(UserRoot);

	while (true)
	{
		menu();
		int cmd;
		printf("请选择功能：");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 0:
		{
			return 0;
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
				while (true)
				{
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
						makeReservation(reservations[ReservationNum++], FieldRoot, currentUser->username);
					}
					else if (userCmd == 3)
					{
						if (ReservationNum > 0)
						{
							for (int i = 0; i < ReservationNum; i++)
							{
								if (strcmp(reservations[i].owner, currentUser->username) == 0)
								{
									putReservation(reservations[i]);
								}
							}
						}
						else
						{
							printf("目前暂无预订信息！\n");
						}

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
			printf("请选择正确的功能！\n");
			break;
		}

		editUserNum();
	}


	return 0;
}
