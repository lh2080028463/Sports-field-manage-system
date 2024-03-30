#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"基础功能.h"
#include"界面.h"
#include"结构体信息.h"
#include"文件处理.h"
unsigned int ManagerNum,UserNum, ResponNum;
User* UserRoot;

int main()
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
	// 逐行读取文件内容
	fscanf(filePointer, "%d", &UserNum);
	// 关闭文件
	fclose(filePointer);

	inputUserdata(UserRoot);
	menu();
	int cmd;
	printf("请选择功能：");
	scanf("%d", &cmd);
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
		
		break;
	}
	case 3:
	{
		
		break;
	}
	case 4:
	{
		userRegister(UserRoot);
		break;
	}

	default:
		break;
	}
	return 0;
}
