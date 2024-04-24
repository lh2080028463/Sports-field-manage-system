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
#include"场地负责人.h"

unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
User* UserRoot;
Field* FieldRoot;
Respondent* RespondentsHead;
Reservation Reservations[10000];

int main()
{
	initNum();
	inputFielddata(FieldRoot);
	inputUserdata();
	inputRespondata();

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
					managerMenu();
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
								editFieldNum();
							}
							if (managerCmd == 2)
							{
								system("cls");
								editField(FieldRoot);
							}
							if (managerCmd == 3)
							{
								system("cls");
								deleteField(FieldRoot);
							}
							if (managerCmd == 4)
							{
								system("cls");
								managerqueryfield();
							}
							if (managerCmd == 5)
							{
								system("cls");
								managersortfield();
							}
						}
					}
					if (managerCmd == 2)
					{
						system("cls");
						while (true)
						{
							responManageMenu();
							printf("请选择功能：");
							scanf("%d", &managerCmd);
							if (managerCmd == 0)
							{
								break;
							}
							else if (managerCmd == 1)
							{
								system("cls");
								addRespondent();
							}
							else if (managerCmd == 2)
							{
								 
							}
							else if (managerCmd == 3)
							{
								system("cls");
								deleteRespondent();
							}
						}

					}
					if (managerCmd == 3)
					{
						system("cls");

					}
					if (managerCmd == 4)
					{
						system("cls");
						editManagerpassword();
					}
				}
			}
			else
			{
				system("cls");
				printf("请选择正确的序号！\n");
				Sleep(500);
				system("cls");
			}
			break;
		}
		case 2:
		{
			Respondent* currentrespon =  responLogin(); 
			if (currentrespon != NULL)
			{
				
				int i;
				while (true)
				{
					responMenu();
					scanf("%d", &i);
					if (i==0)
					{
						break;
					}
					if (i == 1)
					{
						registerUser();
					}
					else if (i == 2)
					{
						responQueryMessage();
					}
					else if (i==3)
					{

					}
					else if (i==4)
					{
						resetResponPass(currentrespon);
					}
					else
					{
						printf("请选择正确的序号：");
					}
				}		
			}
			else
			{
				
			}
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
						statisticMenu();
						int cmd;
						
						while (true)
						{
							printf("请选择功能：");
							scanf("%d", &cmd);
							if (cmd==0)
							{
								break;
							}
							if (cmd==1)
							{
								printf("当前总支出金额为：%u元\n", countAllCost(currentUser->username));
							}
							else if (cmd==2)
							{
								periodCost(currentUser->username);
							}
						}
					}
					else if (userCmd == 5)
					{
						resetUserPass(currentUser,0);
					}
					else if (userCmd == 6)
					{
						deleteUser(currentUser);
						UserRoot = deleteUserNode(UserRoot, currentUser->username);
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
		case 5:
		{
			int forget;
			while (true)
			{
				forgetPassMenu();
				printf("请输入身份：");
				scanf("%d", &forget);
				if (forget==0)
				{
					break;
				}
				else if(forget==1)
				{

				}
				else if (forget == 2)
				{

				}
				else if (forget==3)
				{
					userForget();
				}
			}
			break;
		}
		default:
			system("cls");
			printf("请选择正确的序号！\n");
			Sleep(500);
			system("cls");
			getchar();
			break;
		}
		editUserNum();
		editFieldNum();
		editReservationNum();
		editResponNum();
	}
	return 0;
}