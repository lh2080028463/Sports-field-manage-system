#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include"�û�.h"
#include<Windows.h>
#include"��������.h"

extern unsigned int ManagerNum, UserNum, ResponNum;
/*��ʼ����*/
void menu()
{
	printf("********��ӭʹ���˶����ݹ���ϵͳ********\n");
	printf("       0.�˳�\n");
	printf("       1.����Ա\n");
	printf("       2.���ظ�����\n");
	printf("       3.�û���¼\n");
	printf("       4.���û�ע��\n");
	printf("****************************************\n");
	printf("\n");
}

/*����Ա��¼����*/
void managerLogin()
{
	
	printf(" ********����Ա��¼********|\n");
	printf(" ��  �ţ�");
	printf(" \n");
	printf(" ��  �룺");
	printf(" \n");
	printf(" **************************\n");
}

/*���ظ����˵�¼����*/
void responLogin()
{
	printf(" ******���ظ����˵�¼******\n");
	printf(" ��  �ţ�");
	printf(" \n");
	printf(" ��  �룺");
	printf(" \n");
	printf(" **************************\n");
}

/*�û���¼����*/
void userLogin(User* userRoot,char username[])
{
	printf(" ******�û���¼******\n");
	printf(" ��  �ţ�");
	printf(" \n");
	printf(" ��  �룺");
	printf(" \n");
	printf(" ********************\n");
}

/*���û�ע����漰����*/
User* userRegister(User* userRoot)
{
	char username[20] = { '\0' };  //�˺�
	char password[20] = { '\0' };  //����
	char phone[20] = { '\0' };
	char name[20] = { '\0' };
	printf(" *****���û�ע��*****|\n");
	printf(" �� �� �ţ�");
	scanf("%s", username);
	if (userRoot != NULL && findUsername(userRoot, username) != NULL)
	{
		system("cls");
		printf("���˺��Ѵ��ڣ�������ע�ᣡ\n");
		Sleep(1000);
		userRegister(userRoot);
	}
	else
	{
		printf(" �� �� �룺");
		scanf("%s", password);
		printf(" �� ����");
		scanf("%s", name);
		printf(" ��ϵ��ʽ��");
		scanf("%s", phone);
		printf(" *******************\n");
		printf(" ע��ɹ����뷵�ص�¼��\n");
		return insertUser(userRoot,UserNum+1, username, password, name, phone,0);
		Sleep(2000);
		userLogin(userRoot,username);
	}
}

/*����Ա���ܲ˵�*/
void magnagerMenu()
{
	printf(" ******************����Ա����****************\n");
	printf("                 1.��Ϣ����\n");
	printf("                 2.���ظ����˹���\n");
	printf("                 3.��Ϣ��ѯ\n");
	printf("                 4.��Ϣ����\n");
	printf("                 5.��Ϣͳ��\n");
	printf("                 6.��������\n");
	printf("                 7.�˳�\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*���ظ����˹��ܲ˵�*/
void responMenu()
{
	printf(" ******************���ظ����˹���****************\n");
	printf("                 1.���ع���\n");
	printf("                 2.��Ϣ��ѯ\n");
	printf("                 3.��Ϣ����\n");
	printf("                 4.��Ϣͳ��\n");
	printf("                 5.��������\n");
	printf("                 6.�˳�\n");
	printf(" ************************************************\n");
	printf("\n");
}

/*�û����ܲ˵�*/
void userMenu()
{
	printf(" ******************�û�����****************\n");
	printf("                 1.������Ϣ����\n");
	printf("                 2.����Ԥ��\n");
	printf("                 3.��Ϣ��ѯ\n");
	printf("                 4.��Ϣ����\n");
	printf("                 5.��Ϣͳ��\n");
	printf("                 6.��������\n");
	printf("                 7.�˳�\n");
	printf(" ******************************************\n");
	printf("\n");
}
