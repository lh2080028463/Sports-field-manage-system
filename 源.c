#define _CRT_SECURE_NO_WARNINGS
#include"基础功能.h"
#include"文件处理.h"
#include"用户.h"
#include"界面.h"
#include"管理员.h"
#include"结构体信息.h"
#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>

unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
User* UserRoot;
Field* FieldRoot;
Reservation Reservations[10000];

int main()
{
	initNum();
	inputFielddata(FieldRoot);
	inputUserdata(UserRoot);

	for (int i = 0; i < 10000; i++)
	{
		initReservations(Reservations[i]);
	}
	inputReservation(Reservations);

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
		case 1:
		{
			system("cls");
			Manager* currentManager = managerLogin();
			if (currentManager != NULL)
			{
				system("cls");
				int managerCmd;
				while (true)
				{
					magnagerMenu();
					printf("请选择功能：");
					scanf("%d", &managerCmd);
					if (managerCmd == 0)
					{
						system("cls");
						break;
					}
					if (managerCmd == 1)
					{
						system("cls");
						while (true)
						{
							managerFieldMenu();
							printf("请选择功能：");
							scanf("%d", &managerCmd);
							if (managerCmd == 0)
							{
								system("cls");
								break;
							}
							if (managerCmd == 1)
							{
								system("cls");
								FieldRegister(FieldRoot);
							}
							if (managerCmd == 2)
							{
								system("cls");

							}
							if (managerCmd == 3)
							{
								system("cls");

							}

						}
					}
					if (managerCmd == 2)
					{
						system("cls");

					}
					if (managerCmd == 3)
					{
						system("cls");

					}
					if (managerCmd == 4)
					{
						system("cls");

					}
				}
			}
			else
			{
				system("cls");
				printf("请选择正确的序号！\n");
				Sleep(2000);
				system("cls");
			}
			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{
			User* currentUser = userLogin();
			if (currentUser != NULL)
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
							if (reserveCmd == 0)
							{
								break;
							}
							else if (reserveCmd == 1)
							{
								makeReservation(Reservations[ReservationNum], FieldRoot, currentUser->username);

							}
							else if (reserveCmd == 2)
							{
								editReservationMenu(currentUser->username);
							}
							else if (reserveCmd == 3)
							{
								deleteReservation(currentUser->username);
							}
						}

					}
					else if (userCmd == 3)
					{

						queryMessageMenu(currentUser);

					}
					else if (userCmd == 4)
					{

					}
					else if (userCmd == 5)
					{
						resetUserPass(currentUser);
					}
					else if (userCmd == 6)
					{
						deleteUser(currentUser);
						UserRoot = deleteUserNode(UserRoot, currentUser->username);
						
						break;
					}
					else
					{
						system("cls");
						printf("请选择正确的功能！\n");
						Sleep(500);

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
		editFieldNum();
		editReservationNum();
	}
	return 0;
}