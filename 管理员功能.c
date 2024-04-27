#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <io.h>
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"
#include"��������.h"
#include"����Ա.h"
#include"�û�.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
extern Reservation Reservations[10000];



/*�������ظ����˽ڵ�*/
Respondent* createRespondentNode(unsigned int idx, const char* username, const char* password, const char* name, const char* phone, bool deleted)
{
	Respondent* newNode = (Respondent*)malloc(sizeof(Respondent));
	if (newNode == NULL)
	{
		fprintf(stderr, "�ڴ����ʧ��\n");
		exit(1);
	}
	newNode->idx = idx;
	strcpy(newNode->username, username);
	strcpy(newNode->password, password);
	strcpy(newNode->name, name);
	strcpy(newNode->phone, phone);
	newNode->deleted = deleted;
	newNode->next = NULL;
	editRespondents(idx, username, password, name, phone, deleted);
	return newNode;

}

/*���볡�ظ����˽ڵ㵽������*/
void insertRespondentNode(Respondent** head, Respondent* newNode)
{
	if (*head == NULL) 
	{
		*head = newNode;
	}
	else {
		newNode->next = *head;
		*head = newNode;
	}
}

/*ɾ�����ظ����˽ڵ�*/
void deleteRespondentNode(Respondent** head, const char* username)
{
	if (*head == NULL)
	{
		return;
	}
	Respondent* current = *head;
	Respondent* prev = NULL;

	while (current != NULL) {
		if (strcmp(current->username, username) == 0)
		{
			if (prev == NULL) 
			{
				*head = current->next;
			}
			else 
			{
				prev->next = current->next;
			}
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

/*���ҳ��ظ����˽ڵ�*/
Respondent* findRespondentNode(Respondent* head, const char* username)
{
	Respondent* current = head;
	while (current != NULL)
	{
		if (strcmp(current->username, username) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/*��ӡ���ظ���������*/
void printRespondentList(Respondent* head)
{
	printf("���ظ�������Ϣ��\n");
	Respondent* current = head;
	while (current != NULL) 
	{
		printf("�˺ţ�%s�����룺%s��������%s����ϵ��ʽ��%s��ɾ�������%s\n",
			current->username, current->password, current->name,
			current->phone, current
			->deleted ? "��ɾ��" : "δɾ��");
		current = current->next;
	}
}

/*����Ա�����ز�ѯ*/
int managerputFieldMessage(Field* tempField[], int temp)
{
	for (int i = 0; tempField[i] != NULL; i++)
	{
		printf("�������ƣ�%s\n", tempField[i]->name);
		printf("���������%.2lfƽ����\n", tempField[i]->area);
		printf("���ϼ۸�%.2lfԪ ����۸�%.2lfԪ ���ϼ۸�%.2lfԪ\n", tempField[i]->price[0], tempField[i]->price[1], tempField[i]->price[2]);
		printf("����ʱ��Σ�%02d:%02d~%02d:%02d\n", tempField[i]->openTime.start.hour, tempField[i]->openTime.start.minute, tempField[i]->openTime.end.hour, tempField[i]->openTime.end.minute);
		printf("\n");
		temp++;
	}
	return temp;
}

/*ɾ�����ظ�����*/
void deleteRespondent()
{
	int temp = 0;
	char responname[20];
	Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
	printf("*****���ظ�����ɾ��*****\n");
	printf("��������Ҫɾ���ĳ��ظ������˺ţ�");
	scanf("%s", responname);
	for (int i = 1; i <= ResponNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respondent");
			char fieldIdx[10] = { '\0' };
			_itoa(i, fieldIdx, 10);
			strcat(filePath, fieldIdx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() ����");
			return 1;
		}
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n", i);
			return 1;
		}
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, &queryRespondent->deleted);
		if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
		{
			temp = 1;
			break;
		}
		else
			temp = 0;
	}
	if (temp == 0)
	{
		system("cls");
		printf("�ø����˲����ڣ����������룡\n");
		Sleep(1000);
		system("cls");
		deleteRespondent();
	}
	else
	{
		filePointer = fopen(filePath, "w");
		queryRespondent->deleted = 1;
		deleteRespondentNode(&RespondentsHead, queryRespondent->username);
		fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, queryRespondent->deleted);
		fclose(filePointer);
		system("cls");
		printf("�ѳɹ�ɾ����\n");
		Sleep(2000);
		system("cls");
	}
}

/*�޸ĳ��ظ�������Ϣ*/
void editRespondent()
{
	int temp = 0;
	char responname[20];
	Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
	printf("*****���ظ�������Ϣ�޸�*****\n");
	printf("��������Ҫ�޸ĵĳ��ظ������˺ţ�");
	scanf("%s", responname);
	for (int i = 1; i <= ResponNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respondent");
			char fieldIdx[10] = { '\0' };
			_itoa(i, fieldIdx, 10);
			strcat(filePath, fieldIdx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() ����");
			return 1;
		}
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n", i);
			return 1;
		}
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username, queryRespondent->password, &queryRespondent->deleted);
		if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
		{
			temp = 1;
			break;
		}
		else
			temp = 0;
	}
	if (temp == 0)
	{
		system("cls");
		printf("�ø����˲����ڣ����������룡\n");
		Sleep(1000);
		system("cls");
		deleteRespondent();
	}
	else
	{
		while (true)
		{
			system("cls");
			filePointer = fopen(filePath, "w");
			Respondent* fileRespondent = findRespondentNode(RespondentsHead, responname);
			printf("��ѡ���޸ĵĸ�������Ϣ��\n");
			printf("	1.�˺�\n");
			printf("	2.����\n");
			printf("	3.����\n");
			printf("	4.��ϵ��ʽ\n");
			printf("��ѡ��");
			scanf("%d", &temp);
			system("cls");
			if (temp == 1)
			{
				printf("��������ĺ����Ϣ��");
				scanf("%s", fileRespondent->username);
			}
			if (temp == 2)
			{
				printf("��������ĺ����Ϣ��");
				scanf("%s", fileRespondent->password);
			}
			if (temp == 3)
			{
				printf("��������ĺ����Ϣ��");
				scanf("%s", fileRespondent->name);
			}
			if (temp == 4)
			{
				printf("��������ĺ����Ϣ��");
				scanf("%s", fileRespondent->phone);
			}
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%d\n", queryRespondent->idx, fileRespondent->name, fileRespondent->phone, fileRespondent->username, fileRespondent->password, queryRespondent->deleted);
			fclose(filePointer);
			system("cls");
			printf("�޸ĳɹ���\n");
			Sleep(2000);
			system("cls");
			printf("1.�޸�������Ϣ\n");
			printf("2.�˳�\n");
			printf("��ѡ��");
			scanf("%d", &temp);
			if (temp == 2)
			{
				system("cls");
				break;
			}
		}
	}
}

/*��ѯ�û�Ԥ����Ϣ*/
void queryUserReservation()
{
	system("cls");
	printf("���������ѯ���û���(����0ȡ��):");
			char tempUsername[50];
			while (true)
			{
				scanf("%s", tempUsername);
				if (strcmp(tempUsername, "0") == 0) 
					break;
				User* currentUser = findUsername(UserRoot, tempUsername);
				if (currentUser == NULL)
				{
					system("cls");
					printf("���û���δע�ᣡ\n�����������û�����");
				}
				else
				{
					int temp = 1;
					for (int i = 0; Reservations[i].idx != 0; i++)
					{
						if (Reservations[i].deleted)
						{
							continue;
						}
						if (strcmp(currentUser->username, Reservations[i].owner) == 0)
						{
							temp = 0;
							putReservation(Reservations[i]);
						}
					}
					if (temp == 0)
					{
						printf("�������������˳���");
						scanf("%d", &temp);
						system("cls");
						break;
					}
					if (temp == 1)
					{
						system("cls");
						printf("��ǰ����Ԥ�����أ�\n");
						Sleep(1000);
						break;
					}
				}
			}
}

void FieldtoRespondent(Field* fieldRoot)
{
	int temp;
	char fieldname[20];
	printf("*****���䳡�ظ����ظ�����*****\n");
	printf("�����뱻����ĳ������ƣ�");
	scanf("%s", fieldname);
	Field* tempField = findFieldname(fieldRoot, fieldname);
	if (fieldRoot != NULL && tempField != NULL)
	{
		char responname[20];
		Respondent* queryRespondent = (Respondent*)malloc(sizeof(Respondent));
		FILE* filePointer;
		char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
		char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
		printf("��������䵽�ĳ��ظ������˺ţ�");
		scanf("%s", responname);
		for (int i = 1; i <= ResponNum; i++)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				strcpy(filePath, cwd);
				strcat(filePath, "\\respondata\\respondent");
				char fieldIdx[10] = { '\0' };
				_itoa(i, fieldIdx, 10);
				strcat(filePath, fieldIdx);
				strcat(filePath, ".txt");
			}
			else
			{
				perror("getcwd() ����");
				return 1;
			}
			filePointer = fopen(filePath, "r");
			if (filePointer == NULL)
			{
				printf("��ʼ����������%dʱ�޷����ļ���\n", i);
				return 1;
			}
			fscanf(filePointer, "%u\n%s\n%s\n%s\n", &queryRespondent->idx, queryRespondent->name, queryRespondent->phone, queryRespondent->username);
			if (strcmp(queryRespondent->username, responname) == 0 && queryRespondent->deleted != 1)
			{
				temp = 1;
				break;
			}
			else
				temp = 0;
		}
		if (temp == 0)
		{
			system("cls");
			printf("�ø����˲����ڣ����������룡\n");
			Sleep(1000);
			system("cls");
			FieldtoRespondent(fieldRoot);
		}
		else
		{
			tempField->respondentIdx = queryRespondent->idx;
			editFielddata(tempField->idx, tempField->name, tempField->area, tempField->price, tempField->openTime, tempField->rented, tempField->time, tempField->deleted, tempField->respondentIdx);
			system("cls");
			printf("����ɹ���\n");
			Sleep(1000);
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("�ó��ز����ڣ����������룡\n");
		Sleep(1000);
		system("cls");
		FieldtoRespondent(fieldRoot);
	}
}