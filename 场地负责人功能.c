#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include<Windows.h>
#include"�ṹ����Ϣ.h"
#include"����Ա.h"
#include"�û�.h"
#include"�ļ�����.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation Reservations[10000];

/*���ظ����˹��ܣ��Ǽ��û�*/
void registerUser()
{
	printf("�������û���(����0ȡ��):");
	char tempUsername[50];
	while (true)
	{
		scanf("%s", tempUsername);
		if (strcmp(tempUsername, "0") == 0) break;
		if (findUsername(UserRoot, tempUsername) == NULL)
		{
			printf("���û���δע�ᣡ\n�����������û�����");
		}
		else
		{
			makeReservation(Reservations[ReservationNum], FieldRoot, tempUsername);
			break;
		}
	}
}

/*���ظ����˹��ܣ���Ϣ��ѯ*/
void responQueryMessage()
{
	int querycmd;
	printf(" ******************��Ϣ��ѯ****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.������Ϣ��ѯ\n");
	printf("                 2.����Ԥ����Ϣ��ѯ\n");
	printf(" ******************************************\n");
	printf("\n");
	printf("��ѡ����Ϣ��ѯ���ܣ�");

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
			printf("�������ѯ��������");
			scanf("%s", query);
			int num = 0;
			queryField(FieldRoot, query, tempField,&num);
			sortFields(tempField, num, 0);
			putFieldMessage(tempField);


			int conditon;
			while (true)
			{
				printf(" ******************������Ϣ����****************\n");
				printf("                 0.ȡ������\n");
				printf("                 1.����\n");
				printf("                 2.���\n");
				printf("                 3.���ϼ۸�\n");
				printf("                 4.����۸�\n");
				printf("                 5.���ϼ۸�\n");
				printf("                 6.����ʱ��\n");
				printf("                 7.�ر�ʱ��\n");
				printf(" ******************************************\n");
				printf("��ѡ�񳡵���Ϣ�����ܣ�");
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
					printf("��������ȷ�����!");
					Sleep(500);
					system("cls");
				}
			}


		}
		else if (querycmd == 2)
		{
			printf("���������ѯ���û���(����0ȡ��):");
			char tempUsername[50];

			while (true)
			{
				scanf("%s", tempUsername);
				if (strcmp(tempUsername, "0") == 0) break;
				User* currentUser = findUsername(UserRoot, tempUsername);
				if (currentUser == NULL)
				{
					printf("���û���δע�ᣡ\n�����������û�����");
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
						printf("��ǰ����Ԥ�����أ�\n");
						Sleep(1000);
						break;
					}
				}
			}
		}
		else
		{
			system("cls");
			printf("��������ȷ�����!");
			Sleep(500);
			system("cls");
		}

	}
}

/*���ظ����˹��ܣ���������*/
void resetResponPass(Respondent* curRespondent)
{
	char password0[20];
	char newPass[20];
	printf("����������룺");
	scanf("%s", password0);
	printf("�����������룺");
	scanf("%s", newPass);
	if (strcmp(curRespondent->password, password0) == 0)
	{
		strcpy(curRespondent->password, newPass);
		char path[100] = { '\0' };
		strcpy(path, getRespondataPath(curRespondent));
		FILE* filePointer = fopen(path, "r+");
		// ����ļ��Ƿ�ɹ���
		if (filePointer == NULL)
		{
			printf("�޷����ļ���\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n", curRespondent->idx, curRespondent->name, curRespondent->phone, curRespondent->username, curRespondent->password, curRespondent->deleted);
			system("cls");
			printf("�����޸ĳɹ�!\n");
			Sleep(500);
		}
		fflush(filePointer);
		// �ر��ļ�
		fclose(filePointer);
	}
	else
	{
		printf("�����������\n");
	}
}

