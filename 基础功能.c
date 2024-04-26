#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"�ṹ����Ϣ.h"
#include"����Ա.h"
#include<string.h>
#include<math.h>
#include<search.h>

extern Reservation Reservations[10000];
extern Field* FieldRoot;

/*Ԥ��ʱ�����*/
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

/*���ز�ѯ*/
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

/*�˺Ų�ѯ*/
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

/*����Ƿ�Ԥ��*/
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
/*�ȽϺ������������������бȽ�*/
int compareFields1(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;
	return strcmp(fieldA->name, fieldB->name);
}

/*�ȽϺ������������������бȽ�*/
int compareFields2(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;



	if (fieldA->area < fieldB->area) return -1;
	if (fieldA->area > fieldB->area) return 1;
	return 0;

}
/*�ȽϺ������������������бȽ�*/
int compareFields3(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[0] < fieldB->price[0]) return -1;
	if (fieldA->price[0] > fieldB->price[0]) return 1;

}/*�ȽϺ������������������бȽ�*/
int compareFields4(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[1] < fieldB->price[1]) return -1;
	if (fieldA->price[1] > fieldB->price[1]) return 1;
}/*�ȽϺ������������������бȽ�*/
int compareFields5(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->price[2] < fieldB->price[2]) return -1;
	if (fieldA->price[2] > fieldB->price[2]) return 1;

}/*�ȽϺ������������������бȽ�*/
int compareFields6(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->openTime.start.hour < fieldB->openTime.start.hour) return -1;
	if (fieldA->openTime.start.hour > fieldB->openTime.start.hour) return 1;
	if (fieldA->openTime.start.minute < fieldB->openTime.start.minute) return -1;
	if (fieldA->openTime.start.minute > fieldB->openTime.start.minute) return 1;

}/*�ȽϺ������������������бȽ�*/
int compareFields7(const void* a, const void* b)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;


	if (fieldA->openTime.end.hour < fieldB->openTime.end.hour) return -1;
	if (fieldA->openTime.end.hour > fieldB->openTime.end.hour) return 1;
	if (fieldA->openTime.end.minute < fieldB->openTime.end.minute) return -1;
	if (fieldA->openTime.end.minute > fieldB->openTime.end.minute) return 1;

}/*�ȽϺ������������������бȽ�*/
int compareFields(const void* a, const void* b, int conditon)
{
	const Field* fieldA = (const Field*)a;
	const Field* fieldB = (const Field*)b;

	switch (conditon) {
	case 0:  // ���������
		return fieldB->idx - fieldA->idx;
	case 1:  // ����������
		return strcmp(fieldA->name, fieldB->name);
	case 2:  // ���������
		if (fieldA->area < fieldB->area) return -1;
		if (fieldA->area > fieldB->area) return 1;
		return 0;
	case 3://���糿�۸�����
		if (fieldA->price[0] < fieldB->price[0]) return -1;
		if (fieldA->price[0] > fieldB->price[0]) return 1;
	case 4://������۸�����
		if (fieldA->price[1] < fieldB->price[1]) return -1;
		if (fieldA->price[1] > fieldB->price[1]) return 1;
	case 5://�����ϼ۸�����
		if (fieldA->price[2] < fieldB->price[2]) return -1;
		if (fieldA->price[2] > fieldB->price[2]) return 1;
	case 6://������ʱ������
		if (fieldA->openTime.start.hour < fieldB->openTime.start.hour) return -1;
		if (fieldA->openTime.start.hour > fieldB->openTime.start.hour) return 1;
		if (fieldA->openTime.start.minute < fieldB->openTime.start.minute) return -1;
		if (fieldA->openTime.start.minute > fieldB->openTime.start.minute) return 1;
	case 7://���ս���ʱ������
		if (fieldA->openTime.end.hour < fieldB->openTime.end.hour) return -1;
		if (fieldA->openTime.end.hour > fieldB->openTime.end.hour) return 1;
		if (fieldA->openTime.end.minute < fieldB->openTime.end.minute) return -1;
		if (fieldA->openTime.end.minute > fieldB->openTime.end.minute) return 1;
	default:
		return 0;
	}
}

/*������Ϣ������*/
void sortFields(Field* tempField, int num)
{
	int conditon;
	while (true)
	{
		printf(" ******************������Ϣ����****************\n");
		printf("                 0.ȡ������\n");
		printf("                 1.����\n");
		printf("                 2.���\n");
		printf("                 3.���ϼ۸�\n");
		printf("                 4.����۸�\n");
		printf("                 5.���ϼ۸�\n");
		printf("                 6.����ʱ��\n");
		printf("                 7.�ر�ʱ��\n");
		printf(" ******************************************\n");
		printf("��ѡ�񳡵���Ϣ�����ܣ�");
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
			printf("��������ȷ�����!");
			Sleep(500);
			system("cls");
		}
	}
}


/*��ʼ��Ԥ����Ϣ����*/
void initReservations(Reservation r)
{
	r.deleted = 0;
	strcpy(r.fieldName, "\0");
	strcpy(r.owner, "\0");
	r.idx = 0;
}

/*����ʹ��ʱ��(min)*/
unsigned int calculateTime(Duration dur)
{
	return (dur.end.hour - dur.start.hour) * 60 + dur.end.minute - dur.start.minute;
}

/*����Ԥ����Ϣ�ļ۸�*/
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