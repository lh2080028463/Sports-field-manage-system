#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


/*时间结构体*/
typedef struct Clock
{
	int hour, minute;//时、分
}Clock;

/*时间区间结构体*/
typedef struct Duration
{
	Clock start, end; //起始时间、结束时间
}Duration;

/*场地结构体*/
typedef struct Field
{
	unsigned int idx;           //场地编号
	char name[50];     //名称
	double area;	   //面积	
	double price[3];   //早中晚价格
	Duration openTime; //开放时间
	bool rented;       //租用状态
	unsigned int time; //计费时长(min)
}Field;

/*场地负责人结构体*/
typedef struct Manager
{
	char name[10];		   //姓名
	char phone[20];        //联系方式
	int managedField[10];  //管理场地编号
	char username[20];     //账号
	char password[20];     //密码
}Manager;

/*用户结构体*/
typedef struct User
{
	int idx;               //用户编号
	char name[10];         //姓名
	char phone[20];        //联系方式
	char username[20];     //账号
	char password[20];     //密码
	unsigned int time;              //总使用时长
}User;

/*预定信息结构体*/
typedef struct Reservation
{
	Duration time;     //预定时间
	int fieldIdx;   //预定场地
	int owner;      //预订者 
}Reservation;

int main()
{
	menu();
	int cmd;
	scanf("&d", &cmd);
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
		

	default:
		break;
	}
	return 0;
}
