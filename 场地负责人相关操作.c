#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<window.h>

//登记//
void registration()				
{
	printf("预定用户姓名\n");
	//后接查询函数
	FILE* Fregistration;
	Fregistration = fopen("registration.txt", "a");
	char fieldName[50] = {"text"};
	char Blankspace[5]={"     "}
	char owner[50] = {"text"};
	fputs(owner, Fregistration);
	fputs(Blankspace, Fregistration);
	fputs(fieldName, Fregistration);
	fputs(Blankspace, Fregistration);
	fprintf(Fregistration, "\n");
	fclose(Fregistration);
}


//场地空余查询//
void site_query(int Site_type)		//Site_type为希望查询的场地类型
{
	FILE* fField;
	FILE* ftext;
	fField = fopen("Field.txt", "r+");		//打开场地结构体文件   Field.txt
	ftext = fopen("Field.txt", "w");		//打开辅助文件
	if (fField == NULL)				//在程序测试中判断是否打开结构体文件
	{							//在程序测试中判断是否打开结构体文件
		printf("错误");			//在程序测试中判断是否打开结构体文件
	}							//在程序测试中判断是否打开结构体文件
	else                        //在程序测试中判断是否打开结构体文件
	{			                //在程序测试中判断是否打开结构体文件
		while (!feof(fField))	//未到结构体文件末尾
		{
			int temporary_site_type;
			fseek(fField,   ， 1);				//将指针从当前位置移动至文件中存放场地类型的信息（固定值  数据一）
			fscanf(fField, "%c", &temporary_site_type);		//读文件中场地类型信息
			if (temporary_site_type == Site_type)			//若是读取的该行场地信息中的场地类型是目标类型，则用一个新的TXT文件来存放（用“w”模式打开，作为辅助文件存在）
			{
				fseek(fField,    , 1);			//将指针从当前位置移动至该行行头（固定值  负的数据一）
				char text[   ]；				//将这行信息复制到新文件中（固定值  一行数据的字符长度）同时指针移动至下一行行头(+1)
				fgets(text,    , fField);
				fputs(text,    , ftext);
				fseek(fField,1,1);
			}
			else   fseek(fField,    , 1);				//将指针从当前位置移动至下一行行头（固定值  数据二）
		}


		int* page[50] = { 0 };
		int j = 0;
		int temporary_number = 0;
		char temporary_rented='1';
		char temporary_char[] = { 0 };			//临时存放输出字符串（场地信息   固定值    一行数据的字符长度）
		fseek(ftext,0,0);		//辅助文件指针回到第一行行头
		int i = 0;
		while(i<10 && !feof(ftext))		//一次输出10行
		{
			fseek(ftext, , 1);		//辅助文件指针指向存放出租状态的信息位置（固定值    数据三）
			temporary_rented=fgetc(ftext);
			if (temporary_rented == 0)		//判断是否出租
			{
				page[j] = ftext;
				j++;
				fseek(ftext,  ,1);			//回到行头（固定值    负的数据三）
				fgets(temporary_char,    ,ftext);			//(固定值    一行数据的字符长度）
				printf("%s\n", temporary_char);
				i++;
			}
			else fseek(ftext,  ,1);				//移动辅助文件指针至下一行(固定值    数据四）
		}
		i = 0;
		printf("\n");
		scanf("%d", &temporary_number);
		if (temporary_number == 1)
			printf_ten_line(int i, int j, int* page[50], FILE * ftext, char temporary_rented, char temporary_char[]);
		else if (temporary_number == -1)
		{
			j--;			//辅助文件指针回到上一页
			printf_ten_line(int i, int j, int* page[50], FILE * ftext, char temporary_rented, char temporary_char[]);
		}
		else				//将编号为输入数据的场地的出租状态改为1
		{


		}
	}							//在程序测试中判断是否打开结构体文件
}


void printf_ten_line(int i,int j, int* page[50], FILE* ftext, char temporary_rented, char temporary_char[])
{
	system("cls");				//清屏
	while (i < 10 && !feof(ftext))		//一次输出10行
	{
		fseek(ftext, , 1);		//辅助文件指针指向存放出租状态的信息位置（固定值    数据三）
		temporary_rented = fgetc(ftext);
		if (temporary_rented == 0)		//判断是否出租
		{
			page[j] = ftext;
			j++;
			fseek(ftext, ,1);			//回到行头（固定值    负的数据三）
			fgets(temporary_char, , ftext);			//输出该行信息(固定值    一行数据的字符长度）同时指针移动至下一行行头(+1)
			printf("%s", temporary_char);
			fseek(ftext,1,1);
			i++;
		}
		else fseek(ftext, , 1);				//移动辅助文件指针至下一行行头(固定值    数据四）
	}
	i = 0;
}