#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<direct.h>
#include"�ṹ����Ϣ.h"


/*��ӳ�����Ϣ*/
void addField()
{
	Field* newField=(Field*)malloc(sizeof(Field));
	printf("\n�������ͣ�");
	scanf("%s", newField->name);
	printf("\n���������");
	scanf("%lf", newField->area);
	printf("\n����������۸�");
	printf("\n�磺");
	scanf("%s", newField->price[0]);
	printf("\n�У�");
	scanf("%s", newField->price[1]);
	printf("\n��");
	scanf("%s", newField->price[2]);
	printf("\n����ʱ�䣺\n��ʼʱ�䣺\nСʱ��");
	scanf("%d", newField->openTime.start.hour);
	printf("���ӣ�");
	scanf("%d", newField->openTime.start.minute);
	printf("\n����ʱ�䣺\nСʱ��");
	scanf("%d", newField->openTime.end.hour);
	printf("���ӣ�");
	scanf("%d", newField->openTime.end.minute);
	printf("�Ʒ�ʱ����\n");
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

/*��¼����ʹ�����*/
void recordUserField()
{

}

/*�޸ĳ�����Ϣ*/
void editField(Field* innerField)
{
	
}

/*ɾ��������Ϣ*/
void deleteField()
{

}

void createBiTreeField(Field* innerField) 
{
	
}

char* getFielddataPath(const Field field)
{
	char cwd[100] = { '\0' };      // ���ڴ洢��ǰ����Ŀ¼���ַ�����
	char filePath[100] = { '\0' }; // ���ڴ洢�ļ�·�����ַ�����

	// ��ȡ��ǰ����Ŀ¼
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		// ����ǰ����Ŀ¼���ļ���ƴ�ӳ��������ļ�·��
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
		perror("getcwd() ����");
		return 1;
	}
}
