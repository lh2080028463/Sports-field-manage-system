#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"��������.h"
#include"����.h"
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"
#include"�û�.h"

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
		printf("��ѡ���ܣ�");
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
			system("cls");
			Respondent* currentrespon = responLogin(); 
			if (currentrespon != NULL)
			{
				responMenu();
				int i;
				scanf("%d", &i);
				switch (i)
				{
					case 1:
					{
						registration();
						break;
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
				userMenu();
				int userCmd;
				while (true)
				{
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
							printf("Ŀǰ����Ԥ����Ϣ��\n");
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
			system("cls");
			printf("��ѡ����ȷ����ţ�\n");
			Sleep(1000);
			break;
		}
		
		editUserNum();
	}
	return 0;
}
