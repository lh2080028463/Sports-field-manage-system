#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<window.h>

//�Ǽ�//
void registration()				
{
	printf("Ԥ���û�����\n");
	//��Ӳ�ѯ����
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


//���ؿ����ѯ//
void site_query(int Site_type)		//Site_typeΪϣ����ѯ�ĳ�������
{
	FILE* fField;
	FILE* ftext;
	fField = fopen("Field.txt", "r+");		//�򿪳��ؽṹ���ļ�   Field.txt
	ftext = fopen("Field.txt", "w");		//�򿪸����ļ�
	if (fField == NULL)				//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	{							//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
		printf("����");			//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	}							//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	else                        //�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
	{			                //�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
		while (!feof(fField))	//δ���ṹ���ļ�ĩβ
		{
			int temporary_site_type;
			fseek(fField,   �� 1);				//��ָ��ӵ�ǰλ���ƶ����ļ��д�ų������͵���Ϣ���̶�ֵ  ����һ��
			fscanf(fField, "%c", &temporary_site_type);		//���ļ��г���������Ϣ
			if (temporary_site_type == Site_type)			//���Ƕ�ȡ�ĸ��г�����Ϣ�еĳ���������Ŀ�����ͣ�����һ���µ�TXT�ļ�����ţ��á�w��ģʽ�򿪣���Ϊ�����ļ����ڣ�
			{
				fseek(fField,    , 1);			//��ָ��ӵ�ǰλ���ƶ���������ͷ���̶�ֵ  ��������һ��
				char text[   ]��				//��������Ϣ���Ƶ����ļ��У��̶�ֵ  һ�����ݵ��ַ����ȣ�ͬʱָ���ƶ�����һ����ͷ(+1)
				fgets(text,    , fField);
				fputs(text,    , ftext);
				fseek(fField,1,1);
			}
			else   fseek(fField,    , 1);				//��ָ��ӵ�ǰλ���ƶ�����һ����ͷ���̶�ֵ  ���ݶ���
		}


		int* page[50] = { 0 };
		int j = 0;
		int temporary_number = 0;
		char temporary_rented='1';
		char temporary_char[] = { 0 };			//��ʱ�������ַ�����������Ϣ   �̶�ֵ    һ�����ݵ��ַ����ȣ�
		fseek(ftext,0,0);		//�����ļ�ָ��ص���һ����ͷ
		int i = 0;
		while(i<10 && !feof(ftext))		//һ�����10��
		{
			fseek(ftext, , 1);		//�����ļ�ָ��ָ���ų���״̬����Ϣλ�ã��̶�ֵ    ��������
			temporary_rented=fgetc(ftext);
			if (temporary_rented == 0)		//�ж��Ƿ����
			{
				page[j] = ftext;
				j++;
				fseek(ftext,  ,1);			//�ص���ͷ���̶�ֵ    ������������
				fgets(temporary_char,    ,ftext);			//(�̶�ֵ    һ�����ݵ��ַ����ȣ�
				printf("%s\n", temporary_char);
				i++;
			}
			else fseek(ftext,  ,1);				//�ƶ������ļ�ָ������һ��(�̶�ֵ    �����ģ�
		}
		i = 0;
		printf("\n");
		scanf("%d", &temporary_number);
		if (temporary_number == 1)
			printf_ten_line(int i, int j, int* page[50], FILE * ftext, char temporary_rented, char temporary_char[]);
		else if (temporary_number == -1)
		{
			j--;			//�����ļ�ָ��ص���һҳ
			printf_ten_line(int i, int j, int* page[50], FILE * ftext, char temporary_rented, char temporary_char[]);
		}
		else				//�����Ϊ�������ݵĳ��صĳ���״̬��Ϊ1
		{


		}
	}							//�ڳ���������ж��Ƿ�򿪽ṹ���ļ�
}


void printf_ten_line(int i,int j, int* page[50], FILE* ftext, char temporary_rented, char temporary_char[])
{
	system("cls");				//����
	while (i < 10 && !feof(ftext))		//һ�����10��
	{
		fseek(ftext, , 1);		//�����ļ�ָ��ָ���ų���״̬����Ϣλ�ã��̶�ֵ    ��������
		temporary_rented = fgetc(ftext);
		if (temporary_rented == 0)		//�ж��Ƿ����
		{
			page[j] = ftext;
			j++;
			fseek(ftext, ,1);			//�ص���ͷ���̶�ֵ    ������������
			fgets(temporary_char, , ftext);			//���������Ϣ(�̶�ֵ    һ�����ݵ��ַ����ȣ�ͬʱָ���ƶ�����һ����ͷ(+1)
			printf("%s", temporary_char);
			fseek(ftext,1,1);
			i++;
		}
		else fseek(ftext, , 1);				//�ƶ������ļ�ָ������һ����ͷ(�̶�ֵ    �����ģ�
	}
	i = 0;
}