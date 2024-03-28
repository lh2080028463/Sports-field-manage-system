#define _CRT_SECURE_NO_WARNINGS
#include"用户.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*获取用户数据地址*/
char* getUserdataPath(const User user)
{
    char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
    char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

    // 获取当前工作目录
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        // 将当前工作目录与文件名拼接成完整的文件路径
        strcpy(filePath, cwd);
        strcat(filePath, "\\userdata\\user");
        char userIdx[10] = { '\0' };
        _itoa(user.idx,userIdx,10);
        strcat(filePath, userIdx);
        strcat(filePath, ".txt");
        return filePath;
    }
    else 
    {
        perror("getcwd() 错误");
        return 1;
    }
}