#define _CRT_SECURE_NO_WARNINGS
#include"用户.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation reservations[10000];

/*获取用户数据地址*/
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
			printf("初始化读入数据%d时无法打开文件！\n",i);
			return 1;
		}
		User* newUser = (User*)malloc(sizeof(User));
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n",&newUser->idx, newUser->name, newUser->phone, newUser->username, newUser->password, &newUser->time);
		UserRoot=insertUser(UserRoot, newUser->idx,newUser->username, newUser->password, newUser->name, newUser->phone,newUser->time);
		UserNum--;
		fclose(filePointer);
	}
}

/*编辑文件用户信息*/
void editUserdata(unsigned int idx,char username[], char password[], char name[], char phone[], unsigned int time)
{
	//向文件中写入用户数据
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	//更新文件路径
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
		perror("getcwd() 错误");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n",idx,name, phone, username, password, time);
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
	fscanf(filePointer, "UserNum %u\nManagerNum %u\nResponNum %u\nReservationNum %u", &UserNum, &ManagerNum, &ResponNum, &ReservationNum);
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

/*读入已有预定信息*/
void inputReservation(Reservation r[])
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	for (int i = 1; i <= ReservationNum; i++)
	{
		//更新文件路径
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
			perror("getcwd() 错误");
			return 1;
		}
		//读入txt中场地预定数据
		filePointer = fopen(filePath, "r");
		if (filePointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		Reservation* tempr = (Reservation*)malloc(sizeof(Reservation));
		fscanf(filePointer, "%d\n%s\n%d:%d\n%d:%d\n%s",&tempr->idx,tempr->fieldName,&tempr->time.start.hour, &tempr->time.start.minute, &tempr->time.end.hour, &tempr->time.end.minute,tempr->owner);
		reservations[i-1] = *tempr;
		fclose(filePointer);
	}
}

/*编辑文件预定信息*/
void editReservations(unsigned int idx,char fieldName[],Duration time,char owner[])
{
	//向文件中写入预定信息数据
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	//更新文件路径
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
		perror("getcwd() 错误");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%d\n%s\n%d:%d\n%d:%d\n%s", idx,fieldName,time.start.hour,time.start.minute,time.end.hour,time.end.minute,owner);
}

/*结束时更新文件中预定信息数量*/
void editReservationNum()
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
	// 关闭文件
	fclose(filePointer);
}