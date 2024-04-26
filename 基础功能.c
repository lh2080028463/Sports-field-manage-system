#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"结构体信息.h"
#include"管理员.h"
#include<string.h>
#include<math.h>
#include<search.h>

extern Reservation Reservations[10000];
extern Field* FieldRoot;

/*预定时间合理*/
bool checkTime(const Duration reservedTime, const Duration openTime)
{
	if (reservedTime.start.hour > openTime.start.hour ||
		(reservedTime.start.hour == openTime.start.hour && reservedTime.start.minute >= openTime.start.minute))
	{
		if (reservedTime.end.hour < openTime.end.hour ||
			(reservedTime.end.hour == openTime.end.hour && reservedTime.end.minute <= openTime.end.minute))
		{
			return true;
		}
	}
	return false;
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
User* findUsername(const User* userRoot, const char username[])
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
	for (int i = 0; i < Reservations[i].idx != 0; i++)
	{
		if (strcmp(newReservation.fieldName, Reservations[i].fieldName) != 0 || Reservations[i].deleted)
		{
			continue;
		}
		if ((newReservation.time.start.hour < Reservations[i].time.end.hour ||
			(newReservation.time.start.hour == Reservations[i].time.end.hour &&
				newReservation.time.start.minute <= Reservations[i].time.end.minute)) &&
			(newReservation.time.end.hour > Reservations[i].time.start.hour ||
				(newReservation.time.end.hour == Reservations[i].time.start.hour &&
					newReservation.time.end.minute >= Reservations[i].time.start.minute)))
		{
			return true;
		}

	}
	return false;
}


int compareFields0(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;
	return fieldB->idx - fieldA->idx;
}
/*比较函数根据排序条件进行比较*/
int compareFields1(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;
	return strcmp(fieldA->name, fieldB->name);
}

/*比较函数根据排序条件进行比较*/
int compareFields2(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;



	if (fieldA->area < fieldB->area) return -1;
	if (fieldA->area > fieldB->area) return 1;
	return 0;

}
/*比较函数根据排序条件进行比较*/
int compareFields3(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[0] < fieldB->price[0]) return -1;
	if (fieldA->price[0] > fieldB->price[0]) return 1;

}/*比较函数根据排序条件进行比较*/
int compareFields4(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[1] < fieldB->price[1]) return -1;
	if (fieldA->price[1] > fieldB->price[1]) return 1;
}/*比较函数根据排序条件进行比较*/
int compareFields5(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[2] < fieldB->price[2]) return -1;
	if (fieldA->price[2] > fieldB->price[2]) return 1;

}/*比较函数根据排序条件进行比较*/
int compareFields6(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->openTime.start.hour < fieldB->openTime.start.hour) return -1;
	if (fieldA->openTime.start.hour > fieldB->openTime.start.hour) return 1;
	if (fieldA->openTime.start.minute < fieldB->openTime.start.minute) return -1;
	if (fieldA->openTime.start.minute > fieldB->openTime.start.minute) return 1;

}/*比较函数根据排序条件进行比较*/
int compareFields7(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->openTime.end.hour < fieldB->openTime.end.hour) return -1;
	if (fieldA->openTime.end.hour > fieldB->openTime.end.hour) return 1;
	if (fieldA->openTime.end.minute < fieldB->openTime.end.minute) return -1;
	if (fieldA->openTime.end.minute > fieldB->openTime.end.minute) return 1;

}/*比较函数根据排序条件进行比较*/
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
		if (fieldA->price[0] < fieldB->price[0]) return -1;
		if (fieldA->price[0] > fieldB->price[0]) return 1;
	case 4://按下午价格排序
		if (fieldA->price[1] < fieldB->price[1]) return -1;
		if (fieldA->price[1] > fieldB->price[1]) return 1;
	case 5://按晚上价格排序
		if (fieldA->price[2] < fieldB->price[2]) return -1;
		if (fieldA->price[2] > fieldB->price[2]) return 1;
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
void sortFields(Field* tempField, int num)
{
	int conditon;
	while (true)
	{
		printf(" ******************场地信息排序****************\n");
		printf("                 0.取消排序\n");
		printf("                 1.名称\n");
		printf("                 2.面积\n");
		printf("                 3.早上价格\n");
		printf("                 4.下午价格\n");
		printf("                 5.晚上价格\n");
		printf("                 6.开放时间\n");
		printf("                 7.关闭时间\n");
		printf(" ******************************************\n");
		printf("请选择场地信息排序功能：");
		scanf("%d", &conditon);
		if (conditon == 0)
		{
			break;
		}
		else if (conditon > 0 && conditon < 8)
		{
			if (conditon == 1)
			{
				qsort(tempField, num, sizeof(Field), compareFields1);
				putFieldMessage(tempField);
			}
			else if (conditon == 2)
			{
				qsort(tempField, num, sizeof(Field), compareFields2);
				putFieldMessage(tempField);
			}
			else if (conditon == 3)
			{
				qsort(tempField, num, sizeof(Field), compareFields3);
				putFieldMessage(tempField);
			}
			else if (conditon == 4)
			{
				qsort(tempField, num, sizeof(Field), compareFields4);
				putFieldMessage(tempField);
			}
			else if (conditon == 5)
			{
				qsort(tempField, num, sizeof(Field), compareFields5);
				putFieldMessage(tempField);
			}
			else if (conditon == 6)
			{
				qsort(tempField, num, sizeof(Field), compareFields6);
				putFieldMessage(tempField);
			}
			else if (conditon == 7)
			{
				qsort(tempField, num, sizeof(Field), compareFields7);
				putFieldMessage(tempField);
			}

		}
		else
		{
			system("cls");
			printf("请输入正确的序号!");
			Sleep(500);
			system("cls");
		}
	}
}


/*初始化预定信息数组*/
void initReservations(Reservation r)
{
	r.deleted = 0;
	strcpy(r.fieldName, "\0");
	strcpy(r.owner, "\0");
	r.idx = 0;
}

/*计算使用时长(min)*/
unsigned int calculateTime(Duration dur)
{
	return (dur.end.hour - dur.start.hour) * 60 + dur.end.minute - dur.start.minute;
}

/*计算预定信息的价格*/
unsigned int calculatePrice(Reservation reservation)
{
	Duration morning = { {0,0},{12,0} };
	Duration afternoon = { {12,0},{18,0} };
	Duration night = { {18,0} ,{23,59} };
	Field* tempField = findFieldname(FieldRoot, reservation.fieldName);

	unsigned int cost = 0;
	unsigned int x = ceil(calculateTime(reservation.time) / 30.0);
	if (checkTime(reservation.time, morning))
	{
		cost = x * tempField->price[0];
	}
	else if (checkTime(reservation.time, afternoon))
	{
		cost = x * tempField->price[1];
	}
	else if (checkTime(reservation.time, night))
	{
		cost = x * tempField->price[2];
	}
	return cost;
}