#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"��������.h"
#include"����.h"
#include"�ṹ����Ϣ.h"

unsigned int ManagerNum,UserNum, ResponNum;
User* UserRoot;

int main()
{
	addField();
	menu();
	int cmd;
	printf("��ѡ���ܣ�");
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
