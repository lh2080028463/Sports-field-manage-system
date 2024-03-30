#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include"结构体信息.h"


/*添加场地信息*/
void addField()
{
	Field* newField=(Field*)malloc(sizeof(Field));
	printf("\n场地类型：");
	scanf("%s", newField->name);
	printf("\n场地面积：");
	scanf("%lf", newField->area);
	printf("\n场地早中晚价格：");
	printf("\n早：");
	scanf("%s", newField->price[0]);
	printf("\n中：");
	scanf("%s", newField->price[1]);
	printf("\n晚：");
	scanf("%s", newField->price[2]);
	printf("\n开放时间：\n起始时间：\n小时：");
	scanf("%d", newField->openTime.start.hour);
	printf("分钟：");
	scanf("%d", newField->openTime.start.minute);
	printf("\n结束时间：\n小时：");
	scanf("%d", newField->openTime.end.hour);
	printf("分钟：");
	scanf("%d", newField->openTime.end.minute);
	printf("计费时长：\n");
	scanf("%u", newField->time);
	newField->rented = false;
	FILE* fp;
	char ch; 
	for (int i = 0; i < 1000; i++)
	{
		char n[999];
		char name[150];
		_itoa(i, n, 10);
		char cwd[100] = { '\0' };
		getcwd(cwd, sizeof(cwd));
		strcpy(name, cwd);
		strcat(name, &n[0]);
		strcat(name, ".txt");
		if ((fp = fopen("name", "w+")) == NULL)
		{
			printf("Error!\n");
			exit(0);
		}
		ch = fgetc(fp);
		if (ch == EOF)
		{
			newField->idx = i;
			fprintf(fp, "%d %s %lf %lf %lf %lf %d %d %d %d %d %u", newField->idx, newField->name, newField->area, newField->price[0], newField->price[1], newField->price[2], newField->openTime.start.hour, newField->openTime.start.minute, newField->openTime.end.hour, newField->openTime.end.minute,newField->rented,newField->time);
			break;
		}
	}
}

/*记录场地使用情况*/
void recordUserField()
{

}

/*修改场地信息*/
void editField(Field* innerField)
{
	
}

/*删除场地信息*/
void deleteField()
{

}

void createBiTreeField(Field* innerField) 
{
	
}

char* getFielddataPath(const Field field)
{
	char cwd[100] = { '\0' };      // 用于存储当前工作目录的字符数组
	char filePath[100] = { '\0' }; // 用于存储文件路径的字符数组

	// 获取当前工作目录
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// 将当前工作目录与文件名拼接成完整的文件路径
		strcpy(filePath, cwd);
		strcat(filePath, "\\fielddata\\field");
		char fieldIdx[10] = { '\0' };
		_itoa(field.idx, fieldIdx, 10);
		strcat(filePath, fieldIdx);
		strcat(filePath, ".txt");
		return filePath;
	}
	else
	{
		perror("getcwd() 错误");
		return 1;
	}
}
