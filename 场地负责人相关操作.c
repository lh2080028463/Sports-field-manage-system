#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//清屏//
static void SetPos(int x, int y)//SetPos(0, 0)清屏
{
	COORD point = { x, y };//光标要设置的位置x,y
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
	SetConsoleCursorPosition(HOutput, point);//设置光标位置
}


//输出//
void pput(FILE* ftext)
{
	for (int i = 0; i < 10; i++)
	{
		char a[147] = { 0 };
		fscanf(ftext, "%s", a);
		printf("%s", a);
	}
}


//登记//
void registration()
{
	printf("预定用户姓名\n");
	//后接查询函数
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


//分配//
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
				fseek(ftext, -8, 1);			//指针移动至下一行
				fseek(ftext, 147, 1);
			}
		}
	}
}


//场地空余查询兼分配场地//
void site_query(char Site_type)		//Site_type为希望查询的场地类型
{
	FILE* fField;
	FILE* ftext;
	fField = fopen("E:\\c++\\exe\\Field.txt", "r+");		//打开场地结构体文件   Field.txt
	ftext = fopen("E:\\c++\\exe\\辅助.txt", "w");		//打开辅助文件
	if (fField == NULL)				//在程序测试中判断是否打开结构体文件
	{							//在程序测试中判断是否打开结构体文件
		printf("错误");			//在程序测试中判断是否打开结构体文件
	}							//在程序测试中判断是否打开结构体文件
	else                        //在程序测试中判断是否打开结构体文件
	{			                //在程序测试中判断是否打开结构体文件
		while (!feof(fField))	//未到结构体文件末尾
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
