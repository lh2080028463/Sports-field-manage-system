#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include<string.h>

/*Ԥ��ʱ�����*/
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

/*�˺Ų�ѯ*/
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

/*��Ϣ��ѯ*/
void find()
{

}

/*��Ϣ����*/
void sort()
{

}

/*��Ϣͳ��*/
void statistic()
{

}

void initReservations(Reservation r)
{
	r.deleted = 0;
	strcpy(r.fieldName, "\0");
	strcpy(r.owner, "\0");
	r.idx = 0;
}