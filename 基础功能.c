#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include"����Ա.h"
#include<string.h>

extern Reservation Reservations[10000];

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

/*����Ƿ�Ԥ��*/
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

/*��Ϣ����*/
void sort()
{

}

/*��Ϣͳ��*/
void statistic()
{

}

/*��ʼ��Ԥ����Ϣ����*/
void initReservations(Reservation r)
{
	r.deleted = 0;
	strcpy(r.fieldName, "\0");
	strcpy(r.owner, "\0");
	r.idx = 0;
}