#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"��������.h"
#include"����.h"
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"

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
		printf("��ѡ���ܣ�");
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
