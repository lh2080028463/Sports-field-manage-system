#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//����//
static void SetPos(int x, int y)//SetPos(0, 0)����
{
	COORD point = { x, y };//���Ҫ���õ�λ��x,y
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ʹ��GetStdHandle(STD_OUTPUT_HANDLE)����ȡ��׼����ľ��
	SetConsoleCursorPosition(HOutput, point);//���ù��λ��
}


//���//
void pput(FILE* ftext)
{
	for (int i = 0; i < 10; i++)
	{
		char a[147] = { 0 };
		fscanf(ftext, "%s", a);
		printf("%s", a);
	}
}


//�Ǽ�//
void registration()
{
	printf("Ԥ���û�����\n");
	//��Ӳ�ѯ����
	FILE* Fregistration;
	Fregistration = fopen("registration.txt", "a");
	char fieldName[50] = { "text" };
	char Blankspace[5] = { "     " };
	char owner[50] = { "text" };
	fputs(owner, Fregistration);
	fputs(Blankspace, Fregistration);
	fputs(fieldName, Fregistration);
	fputs(Blankspace, Fregistration);
	fprintf(Fregistration, "\n");
	fclose(Fregistration);
}


//����//
void fenpei(FILE* ftext)
{
	int num = 0;
	scanf("%d", &num);
	if (num == 1)
	{
		SetPos(0, 0);
		pput(ftext);
		fenpei(ftext);
	}
	else if (num == -1)
	{
		SetPos(0, 0);
		fseek(ftext, -147 * 10 * 2, 1);
		pput(ftext);
		fenpei(ftext);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			char b[8] = { 0 };
			fgets(b, 8, ftext);
			int c=0;
			for (int j = 0; j < 8; j++)
			{
				c = 10 * c + (int)b[j];
			}
			if (c == num)
			{
				fseek(ftext, -8, 1);
				fseek(ftext, 124, 1);
				fputc("1", ftext); break;
			}
			else
			{
				fseek(ftext, -8, 1);			//ָ���ƶ�����һ��
				fseek(ftext, 147, 1);
			}
		}
	}
}


//���ؿ����ѯ����䳡��//
void site_query(char Site_type)		//Site_typeΪϣ����ѯ�ĳ�������
{
	FILE* fField;
	FILE* ftext;
	fField = fopen("E:\\c++\\exe\\Field.txt", "r+");		//�򿪳��ؽṹ���ļ�   Field.txt
	ftext = fopen("E:\\c++\\exe\\����.txt", "w");		//�򿪸����ļ�
	if (fField == NULL)				//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	{							//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
		printf("����");			//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	}							//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	else                        //�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	{			                //�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
		while (!feof(fField))	//δ���ṹ���ļ�ĩβ
		{
			char a[147] = { 0 };
			fgets(a, 147, fField);
			if (a[145] == Site_type && (int)a[124] == 0)
			{
				fputs(a, ftext);
			}
		}
		rewind(ftext);
		SetPos(0, 0);
		pput(ftext);
		fenpei(ftext);
	}
	fclose(fField);
	fclose(ftext);
}
