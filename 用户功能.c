#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"�ṹ����Ϣ.h"
#include"�ļ�����.h"
#include"��������.h"
#include<Windows.h>

extern unsigned int ManagerNum, UserNum, ResponNum, ReservationNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation Reservations[10000];

/*�������û�*/
User* newUser(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	User* newUser = (User*)malloc(sizeof(User));
	//�û����ݶ���
	newUser->idx = idx;
	strcpy(newUser->username, username);
	strcpy(newUser->password, password);
	strcpy(newUser->name, name);
	strcpy(newUser->phone, phone);
	newUser->time = time;
	newUser->deleted = deleted;
	//�����������ڵ�
	newUser->left = NULL;
	newUser->right = NULL;
	newUser->height = 1;
	return newUser;
}

/*�������ĸ߶�*/
int height(User* node)
{
	if (node == NULL) return 0;
	return node->height;
}

/*��ȡƽ������*/
int getBalance(User* node)
{
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

/*����*/

User* rightRotate(User* x)
{
	User* y = x->left;
	User* t = y->right;
	y->right = x;
	x->left = t;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

/*����*/
User* leftRotate(User* x)
{
	User* y = x->right;
	User* t = y->left;
	y->left = x;
	x->right = t;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

/*�û�ע��*/
User* insertUser(User* node, unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted)
{
	if (node == NULL)
	{
		UserNum++;
		if (UserNum == 1)
			editUserdata(1, username, password, name, phone, time, deleted);
		return newUser(idx, username, password, name, phone, time, deleted);
	}


	if (strcmp(username, node->username) < 0)
	{
		node->left = insertUser(node->left, idx, username, password, name, phone, time, deleted);
	}
	else if (strcmp(username, node->username) > 0)
	{
		node->right = insertUser(node->right, idx, username, password, name, phone, time, deleted);
	}
	else
		return node;
	//���½ڵ�߶�
	node->height = max(height(node->left), height(node->right)) + 1;

	//��ȡƽ������
	int balance = getBalance(node);

	//��ƽ��ʱ�������ڵ�
	//LL
	if (balance > 1 && strcmp(username, node->left->username) < 0)
	{
		return rightRotate(node);
	}
	//RR
	if (balance < -1 && strcmp(username, node->right->username) > 0)
	{
		return leftRotate(node);
	}
	// LR
	if (balance > 1 && strcmp(username, node->left->username) > 0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	//RL
	if (balance < -1 && strcmp(username, node->left->username) < 0)
	{
		node->right = rightRotate(node->left);
		return leftRotate(node);
	}

	editUserdata(idx, username, password, name, phone, time, deleted);
	return node;
}

/*ȡ������Сֵ*/
User* minValueNode(User* node) {
	User* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*ɾ���û����еĽڵ�*/
User* deleteUserNode(User* root, char username[])
{
	if (root == NULL)
		return root;

	if (strcmp(username, root->username) < 0)
	{
		root->left = deleteUserNode(root->left, username);
	}

	else if (strcmp(username, root->username) > 0)
	{
		root->right = deleteUserNode(root->right, username);
	}
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			User* temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			User* temp = minValueNode(root->right);

			root->idx = temp->idx;
			strcpy(root->username, temp->username);
			strcpy(root->password, temp->password);
			strcpy(root->name, temp->name);
			strcpy(root->phone, temp->phone);
			root->time = temp->time;

			root->right = deleteUserNode(root->right, temp->username);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

/*��λ����ָ��*/
Field* findField(Field* root, char fieldName[])
{
	if (root == NULL) return root;
	Field* temp = root;
	if (strcmp(fieldName, root->name) < 0)
	{
		temp = findField(root->left, fieldName);
	}
	else if (strcmp(fieldName, root->name) > 0)
	{
		temp = findField(root->right, fieldName);
	}
	else
	{
		return temp;
	}
}

/*�û�Ԥ������*/
void makeReservation(Reservation* reserv, Field* root, char username[])
{
	Reservation reservation;
	reservation.idx = ReservationNum+1;
	printf("��������ҪԤ���ĳ������ƣ�����0ȡ��Ԥ������");
	scanf("%s", reservation.fieldName);
	if (strcmp(reservation.fieldName, "0") == 0)
	{
		return;
	}
	//��鳡���Ƿ����
	Field* temp = findField(FieldRoot, reservation.fieldName);
	if (temp == NULL)
	{
		printf("�޸ó������ƣ�������Ԥ����\n");
		makeReservation(reserv, root, username);
	}
	else
	{

		printf("��������ʼʱ�䣺");
		scanf("%d:%d", &reservation.time.start.hour, &reservation.time.start.minute);
		printf("�������ֹʱ�䣺");
		scanf("%d:%d", &reservation.time.end.hour, &reservation.time.end.minute);
		if (checkTime(reservation.time,temp->openTime))
		{
			if (!rented(reservation))
			{
				reservation.cost = calculatePrice(reservation);
				strcpy(reservation.owner, username);
				reserv[ReservationNum].idx = reservation.idx;
				reserv[ReservationNum].time = reservation.time;
				strcpy(reserv[ReservationNum].owner, reservation.owner);
				reserv[ReservationNum].cost = reservation.cost;
				strcpy(reserv[ReservationNum].fieldName, reservation.fieldName);
				ReservationNum++;
				
				editReservations(ReservationNum, reservation.fieldName, reservation.time, reservation.owner, 0,reservation.cost);
				printf("����Ԥ���ɹ���\n");
				Sleep(500);
			}
			else
			{
				printf("�ó���Ŀǰ�ѱ�Ԥ����\n������ѡ��\n");
				makeReservation(reserv, root, username);
			}
		}
		else
		{
			printf("��ʱ��γ���δ���ţ�������Ԥ����\n");
			makeReservation(reserv, root, username);
		}
		
	}

}

void queryField(Field* root, const char* query, Field fields[], int* count) 
{
	if (root == NULL) return;

	// ����������ư�����ѯ�����ַ������򽫸ó��ؼ�����������
	if (strstr(root->name, query) != NULL) {
		fields[*count] = *root;
		(*count)++;
	}
	// �ݹ��ѯ��������������
	queryField(root->left, query, fields, count);
	queryField(root->right, query, fields, count);
}

/*��������*/
void traverseField(Field* root, Field fields[], int* count)
{
	if (root == NULL) return;
		fields[*count] = *root;
	(*count)++;
	traverseField(root->left, fields, count);
	traverseField(root->right, fields, count);
}


/*���������Ϣ*/
void putFieldMessage(Field tempField[])
{
	printf("   ��������             �������             ���ϼ۸�             ����۸�             ���ϼ۸�              ����ʱ���\n");
	for (int i = 0; tempField[i].idx != NULL; i++)
	{
		printf("%12s %13.2lfƽ���� %18.2lfԪ %18.2lfԪ %18.2lfԪ            %02d:%02d~%02d:%02d\n", tempField[i].name, tempField[i].area, tempField[i].price[0], tempField[i].price[1], tempField[i].price[2], tempField[i].openTime.start.hour, tempField[i].openTime.start.minute, tempField[i].openTime.end.hour, tempField[i].openTime.end.minute);

	}
	printf("\n");
}
/*���Ԥ����Ϣ*/
void putReservation(Reservation tempReservation)
{
	printf("%s ", tempReservation.fieldName);
	printf("%02d:%02d~%02d:%02d\n", tempReservation.time.start.hour, tempReservation.time.start.minute, tempReservation.time.end.hour, tempReservation.time.end.minute);
	printf("\n");
}

/*ɾ��Ԥ��������Ϣ*/
void deleteReservation(char username[])
{
	bool flag = 1;
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0)
		{
			flag = 0;
			putReservation(Reservations[i]);
		}
	}
	if (flag)
	{
		printf("��ǰ����Ԥ����Ϣ!\n");
		Sleep(500);
		return;
	}

	Reservation tempReserve;

	printf("�밴�����ϸ�ʽ������Ҫɾ����Ԥ����Ϣ��");
	scanf("%s %02d:%02d~%02d:%02d", tempReserve.fieldName, &tempReserve.time.start.hour, &tempReserve.time.start.minute, &tempReserve.time.end.hour, &tempReserve.time.end.minute);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0 &&
			strcmp(tempReserve.fieldName, Reservations[i].fieldName) == 0 &&
			tempReserve.time.start.hour == Reservations[i].time.start.hour &&
			tempReserve.time.start.minute == Reservations[i].time.start.minute &&
			tempReserve.time.end.hour == Reservations[i].time.end.hour &&
			tempReserve.time.end.minute == Reservations[i].time.end.minute)
		{
			Reservations[i].deleted = 1;
			printf("�ѳɹ�ȡ����Ԥ����\n");
			editReservations(Reservations[i].idx, Reservations[i].fieldName, Reservations[i].time, Reservations[i].owner, Reservations[i].deleted,Reservations[i].cost);
			Sleep(500);
			
		}
	}
	
}

/*�û����ܣ���������*/
void resetUserPass(User* curUser,bool forget)
{
	char password0[20];
	char newPass[20];
	if (!forget)
	{
		printf("����������룺");
		scanf("%s", password0);
	}
	
	printf("�����������룺");
	scanf("%s", newPass);
	if (forget||strcmp(curUser->password, password0) == 0)
	{
		strcpy(curUser->password, newPass);
		char path[100] = { '\0' };
		strcpy(path, getUserdataPath(*curUser));
		FILE* filePointer = fopen(path, "r+");
		// ����ļ��Ƿ�ɹ���
		if (filePointer == NULL)
		{
			printf("�޷����ļ���\n");
			return 1;
		}
		else
		{
			fprintf(filePointer, "%u\n%s\n%s\n%s\n%s\n%u\n%u\n", curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, curUser->deleted);
			system("cls");
			printf("�����޸ĳɹ�!\n");
			Sleep(500);
		}
		fflush(filePointer);
		// �ر��ļ�
		fclose(filePointer);
	}
	else
	{
		printf("�����������\n");
	}
}

/*ע���û�*/
void deleteUser(User* curUser)
{
	editUserdata(curUser->idx, curUser->name, curUser->phone, curUser->username, curUser->password, curUser->time, 1);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, curUser->username) == 0)
		{
			Reservations[i].deleted = 1;
			editReservations(Reservations[i].idx, Reservations[i].fieldName, Reservations[i].time, Reservations[i].owner, Reservations[i].deleted,Reservations[i].cost);
		}
	}

	system("cls");
	printf("�˻�ע���ɹ�!\n");
	Sleep(500);
}

/*�û���������*/
void userForget()
{
	char username[20];
	while (true)
	{
		printf("�������˺ţ�����0�˳���:");
		scanf("%s", username);
		if (strcmp(username, "0") == 0)
		{
			break;
		}
		User* currentUser = findUsername(UserRoot, username);
		if (currentUser != NULL)
		{
			char currentPhone[20];
			while (true)
			{
				printf("�����������ϵ��ʽ������0�˳�����");
				scanf("%s", &currentPhone);
				if (strcmp(currentPhone, "0") == 0)
				{
					break;
				}
				else
				{
					if (strcmp(currentPhone, currentUser->phone) == 0)
					{
						resetUserPass(currentUser, 1);
						break;
					}
					else
					{
						printf("��ϵ��ʽ�������\n");
						Sleep(1000);
						system("cls");
					}
				}
			}

		}
		else
		{
			printf("δ��ѯ�����˺���Ϣ�����������룡\n");
		}
	}
}

/*ͳ�ƣ��û���֧�����*/
unsigned int countAllCost(char username[])
{
	unsigned int allCost = 0;
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0&&!Reservations[i].deleted)
		{
			allCost += Reservations[i].cost;
		}
	}
	return allCost;
}

/*ͳ�ƣ��û�ĳʱ���֧�����*/
void periodCost(char username[])
{
	unsigned int cost = 0;
	Duration tempd;
	printf("��������Ҫ��ѯ����ʼʱ��:");
	scanf("%02d:%02d", &tempd.start.hour, &tempd.start.minute);
	printf("��������Ҫ��ѯ�Ľ���ʱ��:");
	scanf("%02d:%02d", &tempd.end.hour, &tempd.end.minute);
	for (int i = 0; Reservations[i].idx != 0; i++)
	{
		if (strcmp(Reservations[i].owner, username) == 0 && !Reservations[i].deleted)
		{
			if (checkTime(Reservations[i].time, tempd))
			{
				cost += Reservations[i].cost;
			}
		}
	}
	
	
	printf("��ʱ��������ѣ�%uԪ\n", cost);
	
	
}