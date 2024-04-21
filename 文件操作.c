#define _CRT_SECURE_NO_WARNINGS
#include"�û�.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"����Ա.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation Reservations[10000];

/*��ȡ�û����ݵ�ַ*/
char* getUserdataPath(const User user)
{
    char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
    char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����

	// ��ȡ��ǰ����Ŀ¼
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// ����ǰ����Ŀ¼���ļ���ƴ�ӳ��������ļ�·��
		strcpy(filePath, cwd);
		strcat(filePath, "\\userdata\\user");
		char userIdx[10] = { '\0' };
		_itoa(user.idx, userIdx, 10);
		strcat(filePath, userIdx);
		strcat(filePath, ".txt");
		return filePath;
	}
	else
	{
		perror("getcwd() ����");
		return 1;
	}
}

/*���������û�����*/
void inputUserdata(User* userRoot)
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����

	for (int i = 1; i <= UserNum; i++)
	{
		//�����ļ�·��
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\userdata\\user");
			char userIdx[10] = { '\0' };
			_itoa(i, userIdx, 10);
			strcat(filePath, userIdx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() ����");
			return 1;
		}
		//����txt���û�����
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n",i);
			return 1;
		}
		User* newUser = (User*)malloc(sizeof(User));
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n",&newUser->idx, newUser->name, newUser->phone, newUser->username, newUser->password, &newUser->time,&newUser->deleted);
		if (newUser->deleted == 0)
		{
			UserRoot = insertUser(UserRoot, newUser->idx, newUser->username, newUser->password, newUser->name, newUser->phone, newUser->time, newUser->deleted);
			UserNum--;
		}
		fflush(filePointer);
		fclose(filePointer);
	}
}

/*�༭�ļ��û���Ϣ*/
void editUserdata(unsigned int idx,char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	//���ļ���д���û�����
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
	//�����ļ�·��
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		strcpy(filePath, cwd);
		strcat(filePath, "\\userdata\\user");
		char userIdx[10] = { '\0' };
		_itoa(idx, userIdx, 10);
		strcat(filePath, userIdx);
		strcat(filePath, ".txt");
	}
	else
	{
		perror("getcwd() ����");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n",idx,name, phone, username, password, time,deleted);
	fflush(filePointer);
	fclose(filePointer);
}

/*�༭�ļ�������Ϣ*/
void editFielddata(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted)
{
	//���ļ���д�볡������
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
	//�����ļ�·��
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		strcpy(filePath, cwd);
		strcat(filePath, "\\fielddata\\field");
		char fieldIdx[10] = { '\0' };
		_itoa(idx, fieldIdx, 10);
		strcat(filePath, fieldIdx);
		strcat(filePath, ".txt");
	}
	else
	{
		perror("getcwd() ����");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%u\n%s\n%lf\n%lf %lf %lf\n%d:%d\n%d:%d\n%d\n%u\n%u\n", idx, name, area, price[0], price[1], price[2], openTime.start.hour, openTime.start.minute, openTime.end.hour, openTime.end.minute, rented, time,deleted);
	fflush(filePointer);
	fclose(filePointer);
}

/*��ʼ��ʱ�����������*/
void initNum()
{
	FILE* filePointer; // �ļ�ָ��
	// ���ļ��Խ��ж�ȡ
	filePointer = fopen("data.txt", "r");
	// ����ļ��Ƿ�ɹ���
	if (filePointer == NULL)
	{
		printf("�޷����ļ���\n");
		return 1;
	}
	//�������������
	fscanf(filePointer, "UserNum %u\nManagerNum %u\nResponNum %u\nReservationNum %u\nFieldNum %u", &UserNum, &ManagerNum, &ResponNum, &ReservationNum, &FieldNum);
	fflush(filePointer);
	// �ر��ļ�
	fclose(filePointer);
}

/*����ʱ�����ļ����û�����*/
void editUserNum()
{
	FILE* filePointer; // �ļ�ָ��
	// ���ļ��Խ��ж�ȡ
	filePointer = fopen("data.txt", "r+");
	// ����ļ��Ƿ�ɹ���
	if (filePointer == NULL)
	{
		printf("�޷����ļ���\n");
		return 1;
	}
	char numName[50];
	int num;
	while (fscanf(filePointer, "%s %d", numName, &num) != EOF)
	{
		if (strcmp(numName, "UserNum") == 0)
		{
			char tempNum[64] = { '\0' };
			_itoa(num, tempNum, 10);
			int len = strlen(tempNum);
			fseek(filePointer, -len, SEEK_CUR);
			fprintf(filePointer, "%d", UserNum);
			break;
		}
	}
	// �ر��ļ�
	fflush(filePointer);
	fclose(filePointer);
}

/*��������Ԥ����Ϣ*/
void inputReservation()
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����

	for (int i = 1; i <= ReservationNum; i++)
	{
		//�����ļ�·��
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\reservations\\reservation");
			char reservationIdx[10] = { '\0' };
			_itoa(i, reservationIdx, 10);
			strcat(filePath, reservationIdx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() ����");
			return 1;
		}
		//����txt�г���Ԥ������
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n", i);
			return 1;
		}
		Reservation* tempr = (Reservation*)malloc(sizeof(Reservation));
		fscanf(filePointer, "%d\n%s\n%d:%d\n%d:%d\n%s\n%u",&tempr->idx,tempr->fieldName,&tempr->time.start.hour, &tempr->time.start.minute, &tempr->time.end.hour, &tempr->time.end.minute,tempr->owner,&tempr->deleted);
		if (tempr->deleted) continue;
		Reservations[i-1] = *tempr;
		fflush(filePointer);
		fclose(filePointer);
	}
}

/*�༭�ļ�Ԥ����Ϣ*/
void editReservations(unsigned int idx,char fieldName[],Duration time,char owner[])
{
	//���ļ���д��Ԥ����Ϣ����
	FILE* filePointer;
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����
	//�����ļ�·��
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		strcpy(filePath, cwd);
		strcat(filePath, "\\reservations\\reservation");
		char reservationIdx[10] = { '\0' };
		_itoa(idx, reservationIdx, 10);
		strcat(filePath, reservationIdx);
		strcat(filePath, ".txt");
	}
	else
	{
		perror("getcwd() ����");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%d\n%s\n%d:%d\n%d:%d\n%s", idx,fieldName,time.start.hour,time.start.minute,time.end.hour,time.end.minute,owner);
	fflush(filePointer);
	fclose(filePointer);
}

/*����ʱ�����ļ���Ԥ����Ϣ����*/
void editReservationNum()
{
	FILE* filePointer; // �ļ�ָ��
	// ���ļ��Խ��ж�ȡ
	filePointer = fopen("data.txt", "r+");
	// ����ļ��Ƿ�ɹ���
	if (filePointer == NULL)
	{
		printf("�޷����ļ���\n");
		return 1;
	}
	char numName[50];
	int num;
	while (fscanf(filePointer, "%s %d", numName, &num) != EOF)
	{
		if (strcmp(numName, "ReservationNum") == 0)
		{
			char tempNum[64] = { '\0' };
			_itoa(num, tempNum, 10);
			int len = strlen(tempNum);
			fseek(filePointer, -len, SEEK_CUR);
			fprintf(filePointer, "%d", UserNum);
			break;
		}
	}
	// �ر��ļ�
	fflush(filePointer);
	fclose(filePointer);
}