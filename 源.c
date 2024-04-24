#define _CRT_SECURE_NO_WARNINGS
#include"��������.h"
#include"�ļ�����.h"
#include"�û�.h"
#include"����.h"
#include"����Ա.h"
#include"�ṹ����Ϣ.h"
#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include"���ظ�����.h"

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
		printf("��ѡ���ܣ�");
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
					printf("��ѡ���ܣ�");
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
							printf("��ѡ���ܣ�");
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
							printf("��ѡ���ܣ�");
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
				printf("��ѡ����ȷ����ţ�\n");
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
						printf("��ѡ����ȷ����ţ�");
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
					printf("��ѡ���ܣ�");
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
							printf("��ѡ���ܣ�");
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
							printf("��ѡ���ܣ�");
							scanf("%d", &cmd);
							if (cmd==0)
							{
								break;
							}
							if (cmd==1)
							{
								printf("��ǰ��֧�����Ϊ��%uԪ\n", countAllCost(currentUser->username));
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
						printf("��ѡ����ȷ�Ĺ��ܣ�\n");
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
				printf("��������ݣ�");
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
			printf("��ѡ����ȷ����ţ�\n");
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