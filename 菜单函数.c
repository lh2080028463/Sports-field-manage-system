#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"�ṹ����Ϣ.h"
#include"�û�.h"
#include<Windows.h>
#include"��������.h"
#include"�ļ�����.h"
#include"����Ա.h"
#include"���ظ�����.h"

extern unsigned int ManagerNum, UserNum, ResponNum, FieldNum, ReservationNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
extern Reservation Reservations[10000];
/*��ʼ����*/
void menu()
{
	printf("********��ӭʹ���˶����ݹ���ϵͳ********\n");
	printf("       0.�˳�\n");
	printf("       1.����Ա\n");
	printf("       2.���ظ�����\n");
	printf("       3.�û���¼\n");
	printf("       4.���û�ע��\n");
	printf("       5.�һ�����\n");
	printf("****************************************\n");
	printf("\n");
}

/*����Ա��¼����*/
Manager* managerLogin()
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
	for (int i = 1; i <= ManagerNum; i++)
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
			temp = 1;
		}
		else
		{
			printf(" ��  �룺");
			scanf("%s", password);
			if (strcmp(manager->password, password) != 0)
			{
				temp = 1;
				fclose(managerPointer);
				break;
			}
			else
			{
				temp = 0;
				system("cls");
				printf("��¼�ɹ���\n");
				Sleep(500);
				fclose(managerPointer);
				return manager;
				break;
			}
		}
	}
	if (temp = 1)
	{
		system("cls");
		printf("�˺Ż�����������������룡");
		Sleep(500);
		system("cls");
		managerLogin();
	}
}

/*����Ա���ܲ˵�*/
void managerMenu()
{
	printf(" ******************����Ա����****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.���ع���\n");
	printf("                 2.���ظ����˹���\n");
	printf("                 3.�û�����\n");
	printf("                 4.��������\n");
	printf("                 5.\n");
	printf("                 6.\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*����Ա���ܣ����ع���*/
void managerFieldMenu()
{
	printf(" ******************����Ա���ع���****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.�������\n");
	printf("                 2.������Ϣ�޸�\n");
	printf("                 3.����ɾ��\n");
	printf("                 4.���ز�ѯ\n");
	printf("                 5.��������\n");
	printf("                 6.\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*����Ա���ܣ����ظ����˹���*/
void responManageMenu()
{
	printf(" ******************����Ա����****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.��ӳ��ظ�����\n");
	printf("                 2.�޸ĳ��ظ�������Ϣ\n");
	printf("                 3.ɾ�����ظ�����\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*����Ա��ӳ��ظ�����*/
void addRespondent()
{
	char username[50];
	char password[50];
	char name[20];
	char phone[20];

	printf("�û�����");
	scanf("%s", username);
	if (findRespondentNode(RespondentsHead, username) == NULL)
	{
		printf("���룺");
		scanf("%s", password);
		printf("������");
		scanf("%s", name);
		printf("��ϵ��ʽ��");
		scanf("%s", phone);
		ResponNum++;
		insertRespondentNode(RespondentsHead, createRespondentNode(ResponNum, username, password, name, phone, 0));
		system("cls");
		printf("���ظ�������ӳɹ���\n");
		Sleep(500);
	}
	else
	{
		printf("���û����Ѵ��ڣ���������ӣ�\n");
		addRespondent();
	}

	
}	

/*������ӽ���*/
Field* FieldRegister(Field* fieldRoot)
{
	Field* newfield = (Field*)malloc(sizeof(Field));
	printf(" *****�������*****|\n");
	printf("�³������ƣ�");
	scanf("%s", newfield->name);
	Field* tempField = findFieldname(fieldRoot, newfield->name);
	if (fieldRoot != NULL && tempField != NULL)
	{
		system("cls");
		printf("�ó����Ѵ��ڣ���������ӣ�\n");
		Sleep(500);
		system("cls");
		FieldRegister(fieldRoot);
	}
	else
	{
		printf("�����");
		scanf("%lf", &newfield->area);
		printf("�۸�\n��䣺");
		scanf("%lf", &newfield->price[0]);
		printf("��䣺");
		scanf("%lf", &newfield->price[1]);
		printf("��䣺");
		scanf("%lf", &newfield->price[2]);
		printf("����ʱ��\n��ʼʱ�䣺");
		scanf("%d:%d", &newfield->openTime.start.hour, &newfield->openTime.start.minute);
		printf("����ʱ�䣺");
		scanf("%d:%d", &newfield->openTime.end.hour, &newfield->openTime.end.minute);
		system("cls");
		printf(" ������ӳɹ���\n");
		return addField(fieldRoot, FieldNum + 1, newfield->name, newfield->area, newfield->price, newfield->openTime, 0, 0, 0);
		Sleep(500);
	}
}

/*���ظ����˵�¼����*/
Respondent* responLogin()
{
	char username[20] = { '\0' };  //�˺�
	char password[20] = { '\0' };  //����
	printf(" ******���ظ����˵�¼******\n");
	printf(" ��  �ţ�");
	scanf("%s", username);
	Respondent* tempRespon = findRespondentNode(RespondentsHead, username);
	if (RespondentsHead == NULL || (RespondentsHead != NULL && (tempRespon == NULL || tempRespon->deleted)))
	{
		system("cls");
		printf("���˺�δע�ᣬ����ϵ����Աע�ᣡ\n");
		Sleep(500);
		system("cls");
		return NULL;
	}
	printf(" ��  �룺");
	scanf("%s", password);
	printf(" ********************\n");
	system("cls");

	if (strcmp(tempRespon->password, password) == 0)
	{
		printf("��¼�ɹ���\n");
		Sleep(500);
		return tempRespon;
	}
	else
	{
		printf("�û�����������������µ�¼��\n");
		Sleep(500);
		system("cls");
		responLogin();
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
	if (UserRoot == NULL || (UserRoot != NULL&&(tempUser == NULL||tempUser->deleted)))
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
	User* tempUser = findUsername(userRoot, username);
	if (userRoot != NULL && tempUser != NULL)
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
		return insertUser(userRoot,UserNum+1, username, password, name, phone,0,0);
		Sleep(500);
		userLogin(userRoot,username);
	}
}

/*���ظ����˹��ܲ˵�*/
void  responMenu()
{
	printf(" ******************���ظ����˹���****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.�Ǽ��û�\n");
	printf("                 2.��Ϣ��ѯ\n");
	printf("                 3.��Ϣͳ��\n");
	printf("                 4.��������\n");
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
	printf("                 4.��Ϣͳ��\n");
	printf("                 5.��������\n");
	printf("                 6.ע���˻�\n");
	
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
	editUserdata(user->idx, user->username, user->password, user->name, user->phone, user->time,user->deleted);
	printf(" ******************************************\n");
	
	printf("\n");
}

/*�û����ܣ���Ϣ��ѯ*/
void queryMessageMenu(User* user)
{
	int querycmd;

	while (true)
	{
		printf(" ******************��Ϣ��ѯ****************\n");
		printf("                 0.�˳�\n");
		printf("                 1.������Ϣ��ѯ\n");
		printf("                 2.����Ԥ����Ϣ��ѯ\n");
		printf(" ******************************************\n");
		printf("\n");
		printf("��ѡ����Ϣ��ѯ���ܣ�");
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
			int num=queryField(FieldRoot, query, tempField);
			sortFields(tempField, num, 0);
			putFieldMessage(tempField);

		
			int conditon;
			while (true)
			{
				printf(" ******************������Ϣ����****************\n");
				printf("                 0.ȡ������\n");
				printf("                 1.����\n");
				printf("                 2.���\n");
				printf("                 3.���ϼ۸�\n");
				printf("                 4.����۸�\n");
				printf("                 5.���ϼ۸�\n");
				printf("                 6.����ʱ��\n");
				printf("                 7.�ر�ʱ��\n");
				printf(" ******************************************\n");
				printf("��ѡ�񳡵���Ϣ�����ܣ�");
				scanf("%d", &conditon);
				if (conditon == 0)
				{
					break;
				}
				else if(conditon>0&&conditon<8)
				{
					sortFields(tempField, num, conditon);
					putFieldMessage(tempField);
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
		else if (querycmd == 2)
		{
			int flag = 1;
			for (int i = 0; Reservations[i].idx!=0; i++)
			{
				if (Reservations[i].deleted)
				{
					continue;
				}
				if (strcmp(user->username,Reservations[i].owner)==0)
				{
					flag = 0;
					putReservation(Reservations[i]);
				}
			}
			if (flag)
			{
				printf("��ǰ����Ԥ�����أ�\n");
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

/*�û�Ԥ����Ϣ�޸�*/
void editReservationMenu(char username[])
{
	int cnt = 0;
	Reservation* reservationp[100];
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0)
		{
			printf("%d. ", cnt+1);
			reservationp[cnt++] = &Reservations[i];
			putReservation(Reservations[i]);
		}
	}
	
	printf("������Ҫ�޸ĵ�Ԥ����ţ�");
	int idx;
	while (true)
	{
		scanf("%d", &idx);
		if (idx > cnt)
		{
			printf("��������ȷ�ı�ţ�");
			continue;
		}
		else
		{
			printf(" ******************�޸�Ԥ����Ϣ****************\n");
			printf("                 0.�˳�\n");
			printf("                 1.�޸�Ԥ������\n");
			printf("                 2.�޸�Ԥ��ʱ��\n");
			printf(" ******************************************\n");
			printf("\n");

			break;
		}
	}
	
	while (true)
	{

		Reservation newReservation = *reservationp[idx - 1];
		int cmd;
		printf("��ѡ���ܣ�");
		scanf("%d", &cmd);
		if (cmd == 0)
		{
			break;
		}
		else if (cmd==1)
		{
			printf("�������µĳ�������");
			scanf("%s", newReservation.fieldName);
			Field* temp = findField(FieldRoot, newReservation.fieldName);
			if (checkTime(newReservation.time,temp->openTime))
			{
				if (!rented(newReservation))
				{
					*reservationp[idx - 1] = newReservation;
					printf("Ԥ����Ϣ�޸ĳɹ���");
					editReservations(reservationp[idx - 1]->idx, reservationp[idx - 1]->fieldName, reservationp[idx - 1]->time, reservationp[idx - 1]->owner, reservationp[idx - 1]->deleted,reservationp[idx-1]->cost);
					Sleep(500);
					system("cls");
					break;
				}
				else
				{
					printf("�ó����ѱ�Ԥ����������ѡ��\n");
					Sleep(500);
					system("cls");
				}
			}
			else
			{
				printf("��ʱ��γ���δ���ţ�������Ԥ����\n");
			}
			
		}
		else if (cmd==2)
		{
			printf("�������µ�ʱ��Σ�");
			scanf("%02d:%02d~%02d:%02d",&newReservation.time.start.hour,&newReservation.time.start.minute,&newReservation.time.end.hour,&newReservation.time.end.minute );

			Field* temp = findField(FieldRoot, newReservation.fieldName);
			if (checkTime(newReservation.time, temp->openTime))
			{
				if (!rented(newReservation))
				{
					*reservationp[idx - 1] = newReservation;
					printf("Ԥ����Ϣ�޸ĳɹ���");
					editReservations(reservationp[idx - 1]->idx, reservationp[idx - 1]->fieldName, reservationp[idx - 1]->time, reservationp[idx - 1]->owner, reservationp[idx - 1]->deleted,reservationp[idx-1]->cost);
					Sleep(500);
					system("cls");
					break;
				}
			}
			else
			{
				printf("��ʱ��γ���δ���ţ�������Ԥ����\n");
			}
			
		}
		else
		{
			printf("��������ȷ�ı��:");
		}
	}
	
}

/*�һ�����*/
void forgetPassMenu()
{
	printf(" ******************�һ�����****************\n");
	printf("                 0.�˳�\n");
	printf("                 1.����Ա\n");
	printf("                 2.���ظ�����\n");
	printf("                 3.�û�\n");
	printf(" ******************************************\n");
	printf("\n");
}