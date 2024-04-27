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
#include"��������.h"
#include"����Ա.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
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
		User* user = findUsername(UserRoot, tempUsername);
		if (user == NULL)
		{
			printf("���û���δע�ᣡ\n�����������û�����");
		}
		else
		{
			
			if (user->timed >= 10)
			{
				system("cls");
				printf("ԤԼ�����Ѵﵽ���ޣ�");
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

/*���ظ����˹��ܣ���Ϣ��ѯ*/
void responQueryMessage()
{
	int querycmd;
	while (true)
	{
		printf(" ******************��Ϣ��ѯ****************\n");
		printf("                 0.�˳�\n");
		printf("                 1.������Ϣ��ѯ\n");
		printf("                 2.����Ԥ����Ϣ��ѯ\n");
		printf(" ******************************************\n");
		printf("\n");
		printf("��ѡ����Ϣ��ѯ���ܣ�");
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
				printf("�������ѯ��������");
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
					printf("δ��ѯ�����ùؼ��ʵĳ���!���������룡\n");
					Sleep(500);
					system("cls");
				}
			}
			sortFields(tempField, num);
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
void resetResponPass(Respondent* curRespondent,bool forget)
{
	char password0[20];
	char newPass[20];
	if (!forget)
	{
		printf("����������룺");
		scanf("%s", password0);
	}
	
	printf("�����������룺");
	scanf("%s", newPass);
	if (forget||strcmp(curRespondent->password, password0) == 0)
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

/*���ظ�������������*/
void responForget()
{
	char username[20];
	while (true)
	{
		printf("�������˺ţ�����0�˳���:");
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
				printf("�����������ϵ��ʽ������0�˳�����");
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
						printf("��ϵ��ʽ�������\n");
						Sleep(1000);
						system("cls");
					}
				}
			}

		}
		else
		{
			printf("δ��ѯ�����˺���Ϣ�����������룡\n");
		}
	}
}

/*ͳ��ĳ�û���ʹ��ʱ��*/
void TotalUseTime()
{
	char username[20];

	unsigned int total = 0;
	while (true)
	{
		printf("��ѡ���ѯ���û���(����-1�˳�)��");
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
			printf("���û�ʹ��ʱ��Ϊ��%.2lfСʱ\n", total/60.0);
		}
		else
		{
			printf("δ��ѯ�����û�!����������!\n");
		}
		

	}
	
}