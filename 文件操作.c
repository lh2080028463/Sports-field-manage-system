#define _CRT_SECURE_NO_WARNINGS
#include"用户.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern unsigned int ManagerNum, UserNum, ResponNum;


/*获取用户数据路径*/
char* getUserdataPath(const User user)
{
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	// 获取当前工作目录
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// 将当前工作目录与文件名拼接成完整的文件路径
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
		perror("getcwd() 错误");
		return 1;
	}
}

/*读入已有用户数据*/
void inputUserdata(User* userRoot)
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	for (int i = 1; i <= UserNum; i++)
	{
		//更新文件路径
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
			perror("getcwd() 错误");
			return 1;
		}
		//读入txt中用户数据
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("初始化读入数据时无法打开文件！\n");
			return 1;
		}
		User* newUser = (User*)malloc(sizeof(User));
		fscanf(filePointer, "%d\n%s\n%s\n%s\n%s\n%u\n", &newUser->idx, newUser->name, newUser->phone, newUser->username, newUser->password, &newUser->time);
		insertUser(userRoot, newUser->username, newUser->password, newUser->name, newUser->phone);
		fclose(filePointer);
	}
}

/*初始化时读入对象数量*/
void initNum()
{
	FILE* filePointer; // 文件指针
	// 打开文件以进行读取
	filePointer = fopen("data.txt", "r");
	// 检查文件是否成功打开
	if (filePointer == NULL)
	{
		printf("无法打开文件。\n");
		return 1;
	}
	//读入各对象数量
	fscanf(filePointer, "UserNum %u\nManagerNum %u\nResponNum %u", &UserNum, &ManagerNum, &ResponNum);
	// 关闭文件
	fclose(filePointer);
}

/*结束时更新文件中用户数量*/
void editUserNum()
{
	FILE* filePointer; // 文件指针
	// 打开文件以进行读取
	filePointer = fopen("data.txt", "r+");
	// 检查文件是否成功打开
	if (filePointer == NULL)
	{
		printf("无法打开文件。\n");
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
	// 关闭文件
	fclose(filePointer);
}