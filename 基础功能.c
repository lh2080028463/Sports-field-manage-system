#include<stdio.h>
#include"�ṹ����Ϣ.h"


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
	User* temp = NULL;
	if (strcmp(userRoot->name, username) < 0)
	{
		temp = findUsername(userRoot->left, username);
	}
	else if (strcmp(userRoot->name, username) > 0)
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