#include<stdio.h>
#include"结构体信息.h"


/*预定时间合理*/
bool checkTime(const Duration reservedTime, const Duration openTime)
{
	if (reservedTime.start.hour >= openTime.start.hour && reservedTime.end.hour <= openTime.end.hour)
	{
		if (reservedTime.start.minute<openTime.start.minute || reservedTime.end.minute > openTime.end.minute)
			return false;
		return true;
	}
	else return false;
}

/*账号查询*/
User* findUsername(const User* userRoot, const char username[])
{
	if (userRoot == NULL)
		return userRoot;
	User* temp = NULL;
	if (strcmp(userRoot->username, username) == 0)
	{
		return userRoot;
	}
	if (strcmp(userRoot->username, username) < 0)
	{
		temp = findUsername(userRoot->left, username);
	}
	else if (strcmp(userRoot->username, username) > 0)
	{
		temp = findUsername(userRoot->right, username);
	}

}

/*信息查询*/
void find()
{

}

/*信息排序*/
void sort()
{

}

/*信息统计*/
void statistic()
{

}