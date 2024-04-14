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
	char managername[10] = { '\0' };
	char password[20] = { '\0' };
	int temp = 0;
	printf(" ********����Ա��¼********|\n");
	printf(" ��  �ţ�");
	scanf("%s", managername);
	FILE* managerPointer;
	char cwd[100] = { '\0' };
	char filePath[100] = { '\0' };
	for (int i = 0; i <= ManagerNum; i++)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			strcpy(filePath, cwd);
			strcat(filePath, "\\managerdata\\manager");
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
		managerPointer = fopen(filePath, "r");
		if (managerPointer == NULL)
		{
			printf("��ʼ����������%dʱ�޷����ļ���\n", i);
			return 1;
		}
		Manager* manager = (Manager*)malloc(sizeof(Manager));
		fscanf(managerPointer, "%s\n%s\n", &manager->name, &manager->password);
		if (strcmp(manager->name, managername) != 0)
		{
			printf("�˺�����������������룡\n");
			temp = 1;
			fclose(managerPointer);
			break;
		}
		else
		{
			printf(" ��  �룺");
			scanf("%s", password);
			if (strcmp(manager->password, password) != 0)
			{
				printf("����������������룡\n");
				temp = 1;
				fclose(managerPointer);
				break;
			}
			else
			{
				printf("��¼�ɹ���\n");
				fclose(managerPointer);
				return manager;
				break;
			}
		}
	}
	if (temp = 1)
	{
		managerLogin();
	}
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
		Sleep(500);
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
		Sleep(500);
		return tempUser;
	}
	else
	{
		printf("�û�����������������µ�¼��\n");
		Sleep(500);
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
		Sleep(500);
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
		Sleep(500);
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
	printf("                 0.�˳�\n");
	printf("                 1.������Ϣ����\n");
	printf("                 2.����Ԥ��\n");
	printf("                 3.��Ϣ��ѯ\n");
	printf("                 4.��Ϣͳ��\n");
	printf("                 5.��������\n");
	
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
			Sleep(500);
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
			Sleep(500);
			system("cls");
		}
		
	}
	
}

/*�û����ܣ�����Ԥ��*/
void reserveMenu()
{
	printf(" ******************����Ԥ��****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.Ԥ������\n");
	printf("                 2.�޸�Ԥ����Ϣ\n");
	printf("                 3.ȡ��Ԥ��\n");
	printf(" ******************************************\n");
	printf("\n");
}