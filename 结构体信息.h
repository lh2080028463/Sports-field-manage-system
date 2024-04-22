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
	unsigned int deleted;                 //��ɾ��״̬

	struct Field* left;            //��ڵ�
	struct Field* right;           //�ҽڵ�
	int Fieldheight;
}Field;

/*���ظ����˽ṹ��*/
typedef struct Respondent
{
	char username[20];     //�˺�
	char password[20];     //����
	char name[10];		   //����
	char phone[20];        //��ϵ��ʽ
	int managedField[10];  //�����ر��
	char username[20];     //�˺�
	char password[20];     //����
}Respondent;

/*�û��ṹ��*/
typedef struct User
{
	int idx;               //�û����
	char name[10];         //����
	char phone[20];        //��ϵ��ʽ
	char username[20];     //�˺�
	char password[20];     //����
	unsigned int time;     //��ʹ��ʱ��
	unsigned int deleted;                 //��ɾ��״̬
	struct User* left;            //��ڵ�
	struct User* right;           //�ҽڵ�
	int height;
}User;

/*Ԥ����Ϣ�ṹ��*/
typedef struct Reservation
{
	int idx;              //���
	char fieldName[50];  //Ԥ������
	Duration time;      //Ԥ��ʱ��
	char owner[50];    //Ԥ���� 
	bool deleted;     //ɾ�����
}Reservation;

/*����Ա�ṹ��*/
typedef struct Manager
{
	char name[10];
	char password[20];
}Manager;