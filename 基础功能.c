#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"结构体信息.h"
#include"管理员.h"
#include<string.h>

extern Reservation Reservations[10000];

/*预定时间合理*/
bool checkTime(const Duration reservedTime,const Duration openTime)
{
	if (reservedTime.start.hour >= openTime.start.hour && reservedTime.end.hour <= openTime.end.hour)
	{
		if (reservedTime.start.minute<openTime.start.minute || reservedTime.end.minute > openTime.end.minute) 
			return false;
		return true;
	}
	else return false;
}

/*场地查询*/
Field* findFieldname(const Field* FieldRoot, const char name[])
{
	if (FieldRoot == NULL)
		return FieldRoot;
	Field* temp = FieldRoot;
	if (strcmp(name, FieldRoot->name) < 0)
	{
		temp = findFieldname(FieldRoot->left, name);
	}
	else if (strcmp(name, FieldRoot->name) > 0)
	{
		temp = findFieldname(FieldRoot->right, name);
	}
	else
		return temp;
}

/*账号查询*/
User* findUsername(const User* userRoot,const char username[])
{
	if (userRoot == NULL) 
		return userRoot;
	User* temp = userRoot;
	if (strcmp(username, userRoot->username) < 0)
	{
		temp = findUsername(userRoot->left, username);
	}
	else if (strcmp(username, userRoot->username) > 0)
	{
		temp = findUsername(userRoot->right, username);
	}
	else
		return temp;
}

/*检查是否被预定*/
bool rented(Reservation newReservation)
{
	for (int i = 0; i < Reservations[i].idx!=0; i++)
	{
		if (strcmp(newReservation.fieldName, Reservations[i].fieldName) != 0||Reservations[i].deleted)
		{
			continue;
		}
		if ((newReservation.time.start.hour < Reservations[i].time.end.hour ||
			(newReservation.time.start.hour == Reservations[i].time.end.hour &&
				newReservation.time.start.minute < Reservations[i].time.end.minute)) &&
			(newReservation.time.end.hour > Reservations[i].time.start.hour ||
				(newReservation.time.end.hour == Reservations[i].time.start.hour &&
					newReservation.time.end.minute > Reservations[i].time.start.minute)))
		{
			return true; 
		}
	}
	return false; 
}

/*比较函数根据排序条件进行比较*/
int compareFields(const void* a, const void* b, int conditon) 
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;

	switch (conditon) {
	case 0:  // 按编号排序
		return fieldB->idx - fieldA->idx;
	case 1:  // 按名称排序
		return strcmp(fieldA->name, fieldB->name);
	case 2:  // 按面积排序
		if (fieldA->area < fieldB->area) return -1;
		if (fieldA->area > fieldB->area) return 1;
		return 0;
	case 3://按早晨价格排序
		return fieldA->price[0] - fieldB->price[0];
	case 4://按下午价格排序
		return fieldA->price[1] - fieldB->price[1];
	case 5://按晚上价格排序
		return fieldA->price[2] - fieldB->price[2];
	case 6://按开放时间排序
		if (fieldA->openTime.start.hour < fieldB->openTime.start.hour) return -1;
		if (fieldA->openTime.start.hour > fieldB->openTime.start.hour) return 1;
		if (fieldA->openTime.start.minute < fieldB->openTime.start.minute) return -1;
		if (fieldA->openTime.start.minute > fieldB->openTime.start.minute) return 1;
	case 7://按照结束时间排序
		if (fieldA->openTime.end.hour < fieldB->openTime.end.hour) return -1;
		if (fieldA->openTime.end.hour > fieldB->openTime.end.hour) return 1;
		if (fieldA->openTime.end.minute < fieldB->openTime.end.minute) return -1;
		if (fieldA->openTime.end.minute > fieldB->openTime.end.minute) return 1;
	default:
		return 0;
	}
}

/*场地信息排序函数*/
void sortFields(Field** fields, int numFields, int conditon) 
{
	qsort(fields, numFields, sizeof(Field*),(int (*)(const void*, const void*))compareFields, conditon);
}

/*信息统计*/
void statistic()
{

}

/*初始化预定信息数组*/
void initReservations(Reservation r)
{
	r.deleted = 0;
	strcpy(r.fieldName, "\0");
	strcpy(r.owner, "\0");
	r.idx = 0;
}