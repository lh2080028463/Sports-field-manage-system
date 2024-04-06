#pragma once
#include"结构体信息.h"


char* getUserdataPath(const User user);
void inputUserdata(User* userRoot);
void editUserdata(unsigned int idx,char username[], char password[], char name[], char phone[], unsigned int time);
void initNum();
void editUserNum();