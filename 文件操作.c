#define _CRT_SECURE_NO_WARNINGS
#include"�û�.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern int UserNum;


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
		filePointer = fopen(filePath, "r");
		if (filePointer==NULL)
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