#define _CRT_SECURE_NO_WARNINGS 1  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <io.h>
//�Ǽ�//
int registration()			//Reservation	
{
	char cwd[100] = { '\0' };
	char fileReservation[100] = { '\0' };
	char fileRegistration[100] = { '\0' };
	getcwd(cwd, sizeof(cwd));
	strcpy(fileReservation, cwd);
	strcpy(fileRegistration, cwd);
	strcat(fileReservation, "\\reservation\\reservation.txt");
	strcat(fileRegistration, "\\reservation\\registration.txt");
	FILE* Reservation;//Ԥ����Ϣ
	Reservation = fopen(fileReservation, "r+");
	FILE* Registration;//�Ǽ�
	Registration = fopen(fileRegistration, "a");
	printf("������Ԥ��������");
	char owner[50] = {'\0'};
	scanf("%s,owner");
	int i = 0;
	while (!feof(Reservation))
	{
		fseek(Reservation, 65*4, 1);
		char name[51] = { '\0'};
		fgets(name, 51, Reservation);//fget����ֻ��������н���
		int a = strcmp(name, owner);
		if (a == 0)
		{
			fseek(Reservation, -(65+50) * 4, 1);
			fseek(Reservation,63 * 4, 1);
			i = fgetc(Reservation);
			fseek(Reservation, -64 * 4, 1);
			char share[130] = { '\0'};
			fgets(share, 130, Reservation);
			fputs(share, Registration);

			break;
		}
	}
	fclose(Reservation);
	fclose(Registration);
	return i;
}





//��ʾ��ѯ���//
int displaying(FILE* text)
{
	for (int i = 0; i < 10; i++)
	{
		if (!feof(text))
		{
			char Displaying[130] = { '\0' };
			fgets(Displaying, 129, text);
			printf("%s", Displaying);
		}
		else
			break;
	}
	int id = page(text);
	return id;
}





//��ҳ//
int page(FILE* text)
{
	int ID = 0;
	printf("�����볡�ر��ʱ����\n");
	printf("1 ��һҳ   -1 ��һҳ\n");
	printf("�����볡�ر�ţ�");
	scanf("%d", &ID);
	if (ID == 1)
	{
		fseek(text, 0, 1);
		ID = displaying(text);
	}
	else if (ID == -1)
	{
		fseek(text, -(10 * 128 * 4), 1);
		ID = displaying(text);
	}
	return ID;//��֪������ĺ��������ܷ��������س���ID,��������ǲ���Ҫ��break��
}




//�޸ĳ��س���״̬//
void Rewrite(int siteID, FILE* Field)
{
	fseek(Field, 0, 0);
	while (!feof(Field))
	{
		char thisfieldID[10] = { '\0' };
		fgets(thisfieldID, 8, Field);
		int thisID = 0;
		for (int x = 0; x < 8; x++)
		{
			thisID = 10 * thisID + thisfieldID[x];
		}
		fseek(Field, -8 * 4, 1);
		if (thisID == siteID)
		{
			fseek(Field, 108 * 4, 1);
			fprintf(Field, "1"); break;
		}
		else
		{
			fseek(Field, 128 * 4, 1);
		}
	}
}






//��ѯ����//
void site_query(char sitetype)
{
	char cwd[100] = { '\0' };
	char fileField[100] = { '\0' };
	char Text[50] = { '\0' };
	getcwd(cwd, sizeof(cwd));
	strcpy(fileField, cwd);
	strcat(fileField, "\\Field\\allfield.txt");
	strcpy(Text, cwd);
	strcat(Text, "\\Field\\text.txt");
	FILE* Field;
	Field = fopen(fileField, "r+");
	FILE* text;
	text = fopen(Text, "w+");
	fseek(Field, 0, 0);
	while (!feof(Field))
	{
		char type =sitetype;
		char thisfield[129] = { '\0' };
		fgets(thisfield, 129, Field);
		if (thisfield[108] == '0'&& thisfield[127] == type)
		{
			fputs(thisfield, text);
		}
	}
	fseek(text, 0, 0);
	int siteID = displaying(text);
	Rewrite(siteID, Field);
	fclose(Field);
	fclose(text);
	remove(Text);//ɾ��txet�ļ�
}




