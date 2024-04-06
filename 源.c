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
	initNum();
	inputUserdata(UserRoot);

	while (true)
	{
		menu();
		int cmd;
		printf("请选择功能：");
		scanf("%d", &cmd);
		if (cmd == 0)
			break;
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
			UserRoot = userRegister(UserRoot);
			break;
		}

		default:
			break;
		}
		
		editUserNum();
	}
	return 0;
}
