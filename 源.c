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
								mangerqueryfield();
							}
						}
					}
					if (managerCmd == 2)
					{
						system("cls");
						
						int cmd;
						
						while (true)
						{
							responManageMenu();
							printf("��ѡ���ܣ�");
							scanf("%d", &cmd);
							if (cmd==0)
							{
								break;
							}
							else if (cmd==1)
							{
								addRespondent();
							}
							else if (cmd==2)
							{
								 
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
				Sleep(2000);
				system("cls");
			}
			break;
		}
		case 2:
		{
			system("cls");
			Respondent* currentrespon =  responLogin(); 
			if (currentrespon != NULL)
			{
				responMenu();
				int i;
				scanf("%d", &i);
				switch (i)
				{
					case 1:
					{
						printf("�������û���:");
						char tempUsername[50];
						scanf("%s", tempUsername);
						makeReservation(Reservations[ReservationNum], FieldRoot, tempUsername);
						/*if (j == 0)
						{
							printf("δ�ҵ���Ԥ����Ԥ����Ϣ\n");
							Sleep(2000); break;
						}
						else
						{
							printf("Ԥ����������Ϊ%c\n", j);
							Sleep(2000);
						}*/
					}
					case 2:
					{

						break;
					}
					case 3:
					{
						break;
					}
					case 4:
					{
						break;
					}
					case 5:
					{
						break;
					}
					default:
					{
						system("cls");
					}
				}
			}
			else
				system("cls");
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
		default:
			system("cls");
			printf("��ѡ����ȷ����ţ�\n");
			Sleep(1000);
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