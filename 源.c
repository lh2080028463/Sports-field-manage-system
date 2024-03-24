#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


/*ʱ��ṹ��*/
typedef struct Clock
{
	int hour, minute;//ʱ����
}Clock;

/*ʱ������ṹ��*/
typedef struct Duration
{
	Clock start, end; //��ʼʱ�䡢����ʱ��
}Duration;

/*���ؽṹ��*/
typedef struct Field
{
	unsigned int idx;           //���ر��
	char name[50];     //����
	double area;	   //���	
	double price[3];   //������۸�
	Duration openTime; //����ʱ��
	bool rented;       //����״̬
	unsigned int time; //�Ʒ�ʱ��(min)
}Field;

/*���ظ����˽ṹ��*/
typedef struct Manager
{
	char name[10];		   //����
	char phone[20];        //��ϵ��ʽ
	int managedField[10];  //�����ر��
	char username[20];     //�˺�
	char password[20];     //����
}Manager;

/*�û��ṹ��*/
typedef struct User
{
	int idx;               //�û����
	char name[10];         //����
	char phone[20];        //��ϵ��ʽ
	char username[20];     //�˺�
	char password[20];     //����
	unsigned int time;              //��ʹ��ʱ��
}User;

/*Ԥ����Ϣ�ṹ��*/
typedef struct Reservation
{
	Duration time;     //Ԥ��ʱ��
	int fieldIdx;   //Ԥ������
	int owner;      //Ԥ���� 
}Reservation;

int main()
{
	menu();
	int cmd;
	scanf("&d", &cmd);
	switch (cmd)
	{
	case 0:
	{
		
		break;
	}
		
	case 1:
	{
		
		break;
	}
		
	case 2:
	{
		
		break;
	}
	case 3:
	{
		
		break;
	}
		

	default:
		break;
	}
	return 0;
}
