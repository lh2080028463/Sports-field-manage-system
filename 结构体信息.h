#pragma once
#include<stdio.h>
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
	unsigned int idx;   //场地编号
	char name[50];     //名称
	double area;	   //面积
	double price[3];   //早中晚价格
	Duration openTime; //开放时间
	bool rented;       //租用状态
	unsigned int time; //计费时长(min)
	unsigned int deleted;                 //被删除状态

	struct Field* left;            //左节点
	struct Field* right;           //右节点
	int Fieldheight;
}Field;

/*场地负责人结构体*/
typedef struct Respondent
{
	char username[20];     //账号
	char password[20];     //密码
	char name[10];		   //姓名
	char phone[20];        //联系方式
	int managedField[10];  //管理场地编号
	char username[20];     //账号
	char password[20];     //密码
}Respondent;

/*用户结构体*/
typedef struct User
{
	int idx;               //用户编号
	char name[10];         //姓名
	char phone[20];        //联系方式
	char username[20];     //账号
	char password[20];     //密码
	unsigned int time;     //总使用时长
	unsigned int deleted;                 //被删除状态
	struct User* left;            //左节点
	struct User* right;           //右节点
	int height;
}User;

/*预定信息结构体*/
typedef struct Reservation
{
	int idx;              //序号
	char fieldName[50];  //预定场地
	Duration time;      //预定时间
	char owner[50];    //预订者 
	bool deleted;     //删除情况
}Reservation;

/*管理员结构体*/
typedef struct Manager
{
	char name[10];
	char password[20];
}Manager;