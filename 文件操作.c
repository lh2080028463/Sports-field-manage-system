#define _CRT_SECURE_NO_WARNINGS
#include"�û�.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*��ȡ�û����ݵ�ַ*/
char* getUserdataPath(const User user)
{
    char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
    char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����

    // ��ȡ��ǰ����Ŀ¼
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        // ����ǰ����Ŀ¼���ļ���ƴ�ӳ��������ļ�·��
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
        perror("getcwd() ����");
        return 1;
    }
}