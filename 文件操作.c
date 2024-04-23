#define _CRT_SECURE_NO_WARNINGS
#include"用户.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include"管理员.h"
#include"场地负责人.h"

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum, FieldNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
extern Reservation Reservations[10000];

/*编辑文件管理员密码*/
void editManagerpassword()
{
	char managername[10] = { '\0' };
	char password[20] = { '\0' };
	int temp = 0;
	printf(" ********管理员密码更改********|\n");
	printf("请输入账号：");
	scanf("%s", managername);
	FILE* managerPointer;
	char cwd[100] = { '\0' };
	char filePath[100] = { '\0' };
	for (int i = 1; i <= ManagerNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\managerdata\\manager");
			char Idx[10] = { '\0' };
			_itoa(i, Idx, 10);
			strcat(filePath, Idx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() 错误");
			return 1;
		}
		managerPointer = fopen(filePath, "r");
		if (managerPointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		Manager* manager = (Manager*)malloc(sizeof(Manager));
		fscanf(managerPointer, "%s\n%s\n", &manager->name, &manager->password);
		if (strcmp(manager->name, managername) != 0)
		{
			temp = 1;
		}
		else
		{
			temp = 0;
			while (true)
			{
				system("cls");
				printf("请输入旧密码：");
				scanf("%s", password);
				if (strcmp(manager->password, password) != 0)
				{
					printf("密码错误，请重新输入！\n");
					Sleep(1000);
					system("cls");
					fclose(managerPointer);
				}
				else
				{
					printf("请输入新密码：");
					scanf("%s", password);
					managerPointer = fopen(filePath, "w+");
					fprintf(managerPointer, "%s\n%s\n", &manager->name, password);
					system("cls");
					printf("修改成功！\n");
					Sleep(2000);
					system("cls");
					fclose(managerPointer);
					break;
				}
			}
			break;
		}
	}
	if (temp == 1)
	{
		system("cls");
		printf("不存在该账号，请重新输入！");
		Sleep(1000);
		system("cls");
		editManagerpassword();
	}
}




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

/*获取场地数据地址*/
char* getFielddataPath(const Field field)
{
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	// 获取当前工作目录
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// 将当前工作目录与文件名拼接成完整的文件路径
		strcpy(filePath, cwd);
		strcat(filePath, "\\fielddata\\field");
		char fieldIdx[10] = { '\0' };
		_itoa(field.idx, fieldIdx, 10);
		strcat(filePath, fieldIdx);
		strcat(filePath, ".txt");
		return filePath;
	}
	else
	{
		perror("getcwd() 错误");
		return 1;
	}
}

/*获取场地负责人数据地址*/
char* getRespondataPath(const Respondent* respondent)
{
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	// 获取当前工作目录
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// 将当前工作目录与文件名拼接成完整的文件路径
		strcpy(filePath, cwd);
		strcat(filePath, "\\respondata\\respondent");
		char responIdx[10] = { '\0' };
		_itoa(respondent->idx, responIdx, 10);
		strcat(filePath, responIdx);
		strcat(filePath, ".txt");
		return filePath;
	}
	else
	{
		perror("getcwd() 错误");
		return 1;
	}
}

/*编辑文件用户信息*/
void editUserdata(unsigned int idx,char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
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
	fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n",idx,name, phone, username, password, time,deleted);
	fflush(filePointer);
	fclose(filePointer);
}

/*编辑文件场地信息*/
void editFielddata(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted)
{
	//向文件中写入场地数据
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	//更新文件路径
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
		perror("getcwd() 错误");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%u\n%s\n%.2lf\n%.2lf %.2lf %.2lf\n%02d:%02d\n%02d:%02d\n%d\n%u\n%u\n", idx, name, area, price[0], price[1], price[2], openTime.start.hour, openTime.start.minute, openTime.end.hour, openTime.end.minute, rented, time,deleted);
	fflush(filePointer);
	fclose(filePointer);
}

/*编辑场地负责人信息*/
void editRespondents(unsigned int idx, char username[], char password[], char name[], char phone[], bool deleted)
{
	//向文件中写入用户数据
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组
	//更新文件路径
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		strcpy(filePath, cwd);
		strcat(filePath, "\\respondata\\respondent");
		char respondentIdx[10] = { '\0' };
		_itoa(idx, respondentIdx, 10);
		strcat(filePath, respondentIdx);
		strcat(filePath, ".txt");
	}
	else
	{
		perror("getcwd() 错误");
		return 1;
	}
	filePointer = fopen(filePath, "w");
	fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n", idx, name, phone, username, password, deleted);
	fflush(filePointer);
	fclose(filePointer);
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
	fscanf(filePointer, "UserNum %u\nManagerNum %u\nResponNum %u\nReservationNum %u\nFieldNum %u", &UserNum, &ManagerNum, &ResponNum, &ReservationNum, &FieldNum);
	fflush(filePointer);
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
	fflush(filePointer);
	fclose(filePointer);
}

/*读入已有用户数据*/
void inputUserdata()
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
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		User* newUser = (User*)malloc(sizeof(User));
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n", &newUser->idx, newUser->name, newUser->phone, newUser->username, newUser->password, &newUser->time, &newUser->deleted);
		if (newUser->deleted == 0)
		{
			UserRoot = insertUser(UserRoot, newUser->idx, newUser->username, newUser->password, newUser->name, newUser->phone, newUser->time, newUser->deleted);
			UserNum--;
		}
		fflush(filePointer);
		fclose(filePointer);
	}
}

/*读入已有预定信息*/
void inputReservation()
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
		fscanf(filePointer, "%d\n%s\n%d:%d\n%d:%d\n%s\n%u",&tempr->idx,tempr->fieldName,&tempr->time.start.hour, &tempr->time.start.minute, &tempr->time.end.hour, &tempr->time.end.minute,tempr->owner,&tempr->deleted);
		//if (tempr->deleted) continue;
		Reservations[i-1] = *tempr;
		fflush(filePointer);
		fclose(filePointer);
	}
}



/*编辑文件预定信息*/
void editReservations(unsigned int idx,char fieldName[],Duration time,char owner[],bool deleted)
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
	fprintf(filePointer, "%d\n%s\n%02d:%02d\n%02d:%02d\n%s\n%u", idx,fieldName,time.start.hour,time.start.minute,time.end.hour,time.end.minute,owner,deleted);
	fflush(filePointer);
	fclose(filePointer);
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
			fprintf(filePointer, "%d", ReservationNum);
			break;
		}
	}
	// 关闭文件
	fflush(filePointer);
	fclose(filePointer);
}

/*结束时更新文件中场地数量*/
void editFieldNum()
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
		if (strcmp(numName, "FieldNum") == 0)
		{
			char tempNum[64] = { '\0' };
			_itoa(num, tempNum, 10);
			int len = strlen(tempNum);
			fseek(filePointer, -len, SEEK_CUR);
			fprintf(filePointer, "%d", FieldNum);
			break;
		}
	}
	// 关闭文件
	fflush(filePointer);
	fclose(filePointer);
}

/*读入已有场地负责人信息*/
void inputRespondata()
{
	FILE* filePointer;
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	for (int i = 1; i <= ResponNum; i++)
	{
		//更新文件路径
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respondent");
			char responIdx[10] = { '\0' };
			_itoa(i, responIdx, 10);
			strcat(filePath, responIdx);
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
			printf("初始化读入数据%d时无法打开文件！\n", i);
			return 1;
		}
		Respondent* newRespondent = (Respondent*)malloc(sizeof(Respondent));
		fscanf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n",&newRespondent->idx, newRespondent->name, newRespondent->phone, newRespondent->username, newRespondent->password, &newRespondent->deleted);
		if (newRespondent->deleted == 0)
		{
			insertRespondentNode(&RespondentsHead, createRespondentNode(newRespondent->idx,newRespondent->username, newRespondent->password, newRespondent->name, newRespondent->phone, newRespondent->deleted));
		}
		fflush(filePointer);
		fclose(filePointer);
	}
}

/*结束时更新文件中场地负责人数量*/
void editResponNum()
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
		if (strcmp(numName, "ResponNum") == 0)
		{
			char tempNum[64] = { '\0' };
			_itoa(num, tempNum, 10);
			int len = strlen(tempNum);
			fseek(filePointer, -len, SEEK_CUR);
			fprintf(filePointer, "%d", ResponNum);
			break;
		}
	}
	// 关闭文件
	fflush(filePointer);
	fclose(filePointer);
}