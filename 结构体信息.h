#pragma once
#include<stdio.h>
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
	unsigned int idx;   //���ر��
	char name[50];     //����
	double area;	   //���	
	double price[3];   //������۸�
	Duration openTime; //����ʱ��
	bool rented;       //����״̬
	unsigned int time; //�Ʒ�ʱ��(min)
	char Site_type;  	 //��������(��abc�����棩

	struct Field* left;            //��ڵ�
	struct Field* right;           //�ҽڵ�
	int height;
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
	unsigned int time;     //��ʹ��ʱ��
	
	struct User* left;            //��ڵ�
	struct User* right;           //�ҽڵ�
	int height;
}User;

/*Ԥ����Ϣ�ṹ��*/
typedef struct Reservation
{
	Duration time;   //Ԥ��ʱ��
	char fieldName[50];  //Ԥ������
	char owner[50];  //Ԥ���� 
}Reservation;
