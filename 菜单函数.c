#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include"�û�.h"
#include<Windows.h>
#include"��������.h"
#include"�ļ�����.h"

extern unsigned int ManagerNum, UserNum, ResponNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation reservations[10000];
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
Respondent* responLogin()
{
	char responname[10] = { '\0' };
	char password[20] = { '\0' };
	int temp = 0;
	printf(" ********���ظ����˵�¼*********\n");
	printf(" ***���˺������� 0 ������һ��***\n");
	printf(" ��  �ţ�");
	scanf("%s", responname);
	if (strcmp(responname, "0") == 0)
	{
		return NULL;
	}
	FILE* responPointer;
	char cwd[100] = { '\0' };
	char filePath[100] = { '\0' };
	for (int i = 0; i <= ResponNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\respondata\\respon");
			char Idx[10] = { '\0' };
			_itoa(i, Idx, 10);
			strcat(filePath, Idx);
			strcat(filePath, ".txt");
		}
		else
		{
			perror("getcwd() ����");
			return 1;
		}
		responPointer = fopen(filePath, "r");
		if (responPointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n", i);
			return 1;
		}
		Respondent* respon = (Respondent*)malloc(sizeof(Respondent));
		fscanf(responPointer, "%s\n%s\n", &respon->name, &respon->password);
		if (strcmp(respon->name, responname) != 0)
		{
			temp = 1;
			system("cls");
		}
		else
		{
			printf(" ��  �룺");
			scanf("%s", password);
			if (strcmp(respon->password, password) != 0)
			{
				temp = 1;
				fclose(responPointer);
				break;
			}
			else
			{
				temp = 0;
				system("cls");
				printf("��¼�ɹ���\n");
				Sleep(2000);
				fclose(responPointer);
				return respon;
				break;
			}
		}

		if (temp = 1)
		{
			system("cls");
			printf("�˺Ż�����������������룡");
			Sleep(2000);
			system("cls");
			responLogin();
		}
		printf(" **************************\n");
	}
}

/*�û���¼����*/
User* userLogin()
{
	char username[20] = { '\0' };  //�˺�
	char password[20] = { '\0' };  //����
	printf(" ******�û���¼******\n");
	printf(" ��  �ţ�");
	scanf("%s", username);
	User* tempUser = findUsername(UserRoot, username);
	if (tempUser == NULL)
	{
		system("cls");
		printf("���˺�δע�ᣬ�뷵�غ�ע�ᣡ\n");
		Sleep(2000);
		system("cls");
		return NULL;
	}
	printf(" ��  �룺");
	scanf("%s", password);
	printf(" ********************\n");
	system("cls");
	
	if (strcmp(tempUser->password,password)==0)
	{
		printf("��¼�ɹ���\n");
		Sleep(2000);
		return tempUser;
	}
	else
	{
		printf("�û�����������������µ�¼��\n");
		Sleep(2000);
		system("cls");
		userLogin();
	}
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
void  responMenu()
{
	printf(" ******************���ظ����˹���****************\n");
	printf("                 1.�Ǽ�\n");
	printf("                 2.���䳡��\n");
	printf("                 3.��Ϣ��ѯ\n");
	printf("                 4.��Ϣͳ��\n");
	printf("                 5.��������\n");
	printf("                 �������֣��˳�\n");
	printf(" ************************************************\n");
	printf("�����빦�����֣�");
	printf("\n");
}

/*�û����ܲ˵�*/
void userMenu()
{
	printf(" ******************�û�����****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.������Ϣ����\n");
	printf("                 2.����Ԥ��\n");
	printf("                 3.��Ϣ��ѯ\n");
	printf("                 4.��Ϣ����\n");
	printf("                 5.��Ϣͳ��\n");
	printf("                 6.��������\n");
	
	printf(" ******************************************\n");
	printf("\n");
}

/*�û�������Ϣ����*/
void editMessageMenu(User* user)
{
	printf(" ******************�û�������Ϣ����****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.������");
	printf("%s\n", user->name);
	printf("                 2.��ϵ��ʽ��");
	printf("%s\n", user->phone);
	
	while (true)
	{
		printf("������Ҫ�޸ĵ���ţ�");
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 0)
		{
			break;
		}
		else if (cmd == 1)
		{
			printf("�������µ�������");
			scanf("%s", user->name);
			printf("�޸ĳɹ�����ǰ��Ϣ���£�\n");
			printf("                 1.������");
			printf("%s\n", user->name);
			printf("                 2.��ϵ��ʽ��");
			printf("%s\n", user->phone);
		}
		else if (cmd == 2)
		{
			printf("�������µ���ϵ��ʽ��");
			scanf("%s", user->phone);
			printf("                 1.������");
			printf("%s\n", user->name);
			printf("                 2.��ϵ��ʽ��");
			printf("%s\n", user->phone);
		}
		else
		{
			system("cls");
			printf("��������ȷ�����!");
			Sleep(1000);
			system("cls");
		}
	}
	editUserdata(user->idx, user->username, user->password, user->name, user->phone, user->time);
	printf(" ******************************************\n");
	
	printf("\n");
}

/*�û����ܣ���Ϣ��ѯ*/
void queryMessageMenu()
{
	int querycmd;
	printf(" ******************��Ϣ��ѯ****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.������Ϣ��ѯ\n");
	printf("                 2.����Ԥ����Ϣ��ѯ\n");
	printf(" ******************************************\n");
	printf("\n");
	while (true)
	{
		printf("��ѡ���ܣ�");
		scanf("%d", &querycmd);
		if (querycmd == 0)
		{
			break;
		}
		else if (querycmd == 1)
		{
			Field* tempField[100] = { NULL };
			char query[100];
			printf("�������ѯ��������");
			scanf("%s", query);
			queryField(FieldRoot, query, tempField);
			putFieldMessage(tempField);
		}
		else if (querycmd == 2)
		{
			for (int i = 0; reservations[i].owner!=NULL; i++)
			{
				putReservation(reservations[i]);
			}
		}
		else
		{
			system("cls");
			printf("��������ȷ�����!");
			Sleep(1000);
			system("cls");
		}
		
	}
	
}