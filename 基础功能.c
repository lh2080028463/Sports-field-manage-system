#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include"����Ա.h"

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
	printf("123\n");
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