#define _CRT_SECURE_NO_WARNINGS
#include"�û�.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern unsigned int ManagerNum, UserNum, ResponNum;


/*��ȡ�û�����·��*/
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
			printf("��ʼ����������ʱ�޷����ļ���\n");
			return 1;
		}
		User* newUser = (User*)malloc(sizeof(User));
		fscanf(filePointer, "%d\n%s\n%s\n%s\n%s\n%u\n", &newUser->idx, newUser->name, newUser->phone, newUser->username, newUser->password, &newUser->time);
		insertUser(userRoot, newUser->username, newUser->password, newUser->name, newUser->phone);
		fclose(filePointer);
	}
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
	fscanf(filePointer, "UserNum %u\nManagerNum %u\nResponNum %u", &UserNum, &ManagerNum, &ResponNum);
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
	fclose(filePointer);
}