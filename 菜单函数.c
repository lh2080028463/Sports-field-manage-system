#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"结构体信息.h"
#include"用户.h"
#include<Windows.h>
#include"基础功能.h"
#include"文件处理.h"
#include"管理员.h"
#include"场地负责人.h"

extern unsigned int ManagerNum, UserNum, ResponNum, FieldNum, ReservationNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Respondent* RespondentsHead;
extern Reservation Reservations[10000];
/*初始界面*/
void menu()
{
	printf("********欢迎使用运动场馆管理系统********\n");
	printf("       0.退出\n");
	printf("       1.管理员\n");
	printf("       2.场地负责人\n");
	printf("       3.用户登录\n");
	printf("       4.新用户注册\n");
	printf("       5.找回密码\n");
	printf("****************************************\n");
	printf("\n");
}

/*管理员登录界面*/
Manager* managerLogin()
{
	char managername[10] = { '\0' };
	char password[20] = { '\0' };
	int temp = 0;
	printf(" ********管理员登录********|\n");
	printf(" 账  号：");
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
			perror("getcwd() 错误");
			return 1;
		}
		managerPointer = fopen(filePath, "r");
		if (managerPointer == NULL)
		{
			printf("初始化读入数据%d时无法打开文件！\n", i);
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
			printf(" 密  码：");
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
				printf("登录成功！\n");
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
		printf("账号或密码错误，请重新输入！");
		Sleep(500);
		system("cls");
		managerLogin();
	}
}

/*管理员功能菜单*/
void managerMenu()
{
	printf(" ******************管理员功能****************\n");
	printf("                 0.退出\n");
	printf("                 1.场地管理\n");
	printf("                 2.场地负责人管理\n");
	printf("                 3.用户管理\n");
	printf("                 4.重置密码\n");
	printf("                 5.\n");
	printf("                 6.\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*管理员功能：场地管理*/
void managerFieldMenu()
{
	printf(" ******************管理员场地管理****************\n");
	printf("                 0.退出\n");
	printf("                 1.场地添加\n");
	printf("                 2.场地信息修改\n");
	printf("                 3.场地删除\n");
	printf("                 4.场地查询\n");
	printf("                 5.场地排序\n");
	printf("                 6.\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*管理员功能：场地负责人管理*/
void responManageMenu()
{
	printf(" ******************管理员功能****************\n");
	printf("                 0.退出\n");
	printf("                 1.添加场地负责人\n");
	printf("                 2.修改场地负责人信息\n");
	printf("                 3.删除场地负责人\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*管理员添加场地负责人*/
void addRespondent()
{
	char username[50];
	char password[50];
	char name[20];
	char phone[20];

	printf("用户名：");
	scanf("%s", username);
	if (findRespondentNode(RespondentsHead, username) == NULL)
	{
		printf("密码：");
		scanf("%s", password);
		printf("姓名：");
		scanf("%s", name);
		printf("联系方式：");
		scanf("%s", phone);
		ResponNum++;
		insertRespondentNode(RespondentsHead, createRespondentNode(ResponNum, username, password, name, phone, 0));
		system("cls");
		printf("场地负责人添加成功！\n");
		Sleep(500);
	}
	else
	{
		printf("该用户名已存在，请重新添加！\n");
		addRespondent();
	}

	
}	

/*场地添加界面*/
Field* FieldRegister(Field* fieldRoot)
{
	Field* newfield = (Field*)malloc(sizeof(Field));
	printf(" *****场地添加*****|\n");
	printf("新场地名称：");
	scanf("%s", newfield->name);
	Field* tempField = findFieldname(fieldRoot, newfield->name);
	if (fieldRoot != NULL && tempField != NULL)
	{
		system("cls");
		printf("该场地已存在，请重新添加！\n");
		Sleep(500);
		system("cls");
		FieldRegister(fieldRoot);
	}
	else
	{
		printf("面积：");
		scanf("%lf", &newfield->area);
		printf("价格\n早间：");
		scanf("%lf", &newfield->price[0]);
		printf("午间：");
		scanf("%lf", &newfield->price[1]);
		printf("晚间：");
		scanf("%lf", &newfield->price[2]);
		printf("开放时间\n起始时间：");
		scanf("%d:%d", &newfield->openTime.start.hour, &newfield->openTime.start.minute);
		printf("结束时间：");
		scanf("%d:%d", &newfield->openTime.end.hour, &newfield->openTime.end.minute);
		system("cls");
		printf(" 场地添加成功！\n");
		return addField(fieldRoot, FieldNum + 1, newfield->name, newfield->area, newfield->price, newfield->openTime, 0, 0, 0);
		Sleep(500);
	}
}

/*场地负责人登录界面*/
Respondent* responLogin()
{
	char username[20] = { '\0' };  //账号
	char password[20] = { '\0' };  //密码
	printf(" ******场地负责人登录******\n");
	printf(" 账  号：");
	scanf("%s", username);
	Respondent* tempRespon = findRespondentNode(RespondentsHead, username);
	if (RespondentsHead == NULL || (RespondentsHead != NULL && (tempRespon == NULL || tempRespon->deleted)))
	{
		system("cls");
		printf("该账号未注册，请联系管理员注册！\n");
		Sleep(500);
		system("cls");
		return NULL;
	}
	printf(" 密  码：");
	scanf("%s", password);
	printf(" ********************\n");
	system("cls");

	if (strcmp(tempRespon->password, password) == 0)
	{
		printf("登录成功！\n");
		Sleep(500);
		return tempRespon;
	}
	else
	{
		printf("用户名或密码错误，请重新登录！\n");
		Sleep(500);
		system("cls");
		responLogin();
	}

}

/*用户登录界面*/
User* userLogin()
{
	char username[20] = { '\0' };  //账号
	char password[20] = { '\0' };  //密码
	printf(" ******用户登录******\n");
	printf(" 账  号：");
	scanf("%s", username);
	User* tempUser = findUsername(UserRoot, username);
	if (UserRoot == NULL || (UserRoot != NULL&&(tempUser == NULL||tempUser->deleted)))
	{
		system("cls");
		printf("该账号未注册，请返回后注册！\n");
		Sleep(500);
		system("cls");
		return NULL;
	}
	printf(" 密  码：");
	scanf("%s", password);
	printf(" ********************\n");
	system("cls");
	
	if (strcmp(tempUser->password,password)==0)
	{
		printf("登录成功！\n");
		Sleep(500);
		return tempUser;
	}
	else
	{
		printf("用户名或密码错误，请重新登录！\n");
		Sleep(500);
		system("cls");
		userLogin();
	}
}

/*新用户注册界面及功能*/
User* userRegister(User* userRoot)
{
	char username[20] = { '\0' };  //账号
	char password[20] = { '\0' };  //密码
	char phone[20] = { '\0' };
	char name[20] = { '\0' };
	printf(" *****新用户注册*****|\n");
	printf(" 新 账 号：");
	scanf("%s", username);
	User* tempUser = findUsername(userRoot, username);
	if (userRoot != NULL && tempUser != NULL)
	{
		system("cls");
		printf("该账号已存在，请重新注册！\n");
		Sleep(500);
		userRegister(userRoot);
	}
	else
	{
		printf(" 新 密 码：");
		scanf("%s", password);
		printf(" 姓 名：");
		scanf("%s", name);
		printf(" 联系方式：");
		scanf("%s", phone);
		printf(" *******************\n");
		printf(" 注册成功，请返回登录！\n");
		return insertUser(userRoot,UserNum+1, username, password, name, phone,0,0);
		Sleep(500);
		userLogin(userRoot,username);
	}
}

/*场地负责人功能菜单*/
void  responMenu()
{
	printf(" ******************场地负责人功能****************\n");
	printf("                 0.退出\n");
	printf("                 1.登记用户\n");
	printf("                 2.信息查询\n");
	printf("                 3.信息统计\n");
	printf("                 4.重置密码\n");
	printf(" ************************************************\n");
	printf("请输入功能数字：");
	printf("\n");
}

/*用户功能菜单*/
void userMenu()
{
	printf(" ******************用户功能****************\n");
	printf("                 0.退出\n");
	printf("                 1.个人信息管理\n");
	printf("                 2.场地预定\n");
	printf("                 3.信息查询\n");
	printf("                 4.信息统计\n");
	printf("                 5.重置密码\n");
	printf("                 6.注销账户\n");
	
	printf(" ******************************************\n");
	printf("\n");
}

/*用户个人信息管理*/
void editMessageMenu(User* user)
{
	printf(" ******************用户个人信息管理****************\n");
	printf("                 0.退出\n");
	printf("                 1.姓名：");
	printf("%s\n", user->name);
	printf("                 2.联系方式：");
	printf("%s\n", user->phone);
	
	while (true)
	{
		printf("请输入要修改的序号：");
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 0)
		{
			break;
		}
		else if (cmd == 1)
		{
			printf("请输入新的姓名：");
			scanf("%s", user->name);
			printf("修改成功！当前信息如下：\n");
			printf("                 1.姓名：");
			printf("%s\n", user->name);
			printf("                 2.联系方式：");
			printf("%s\n", user->phone);
		}
		else if (cmd == 2)
		{
			printf("请输入新的联系方式：");
			scanf("%s", user->phone);
			printf("                 1.姓名：");
			printf("%s\n", user->name);
			printf("                 2.联系方式：");
			printf("%s\n", user->phone);
		}
		else
		{
			system("cls");
			printf("请输入正确的序号!");
			Sleep(500);
			system("cls");
		}
	}
	editUserdata(user->idx, user->username, user->password, user->name, user->phone, user->time,user->deleted);
	printf(" ******************************************\n");
	
	printf("\n");
}

/*用户功能：信息查询*/
void queryMessageMenu(User* user)
{
	int querycmd;

	while (true)
	{
		printf(" ******************信息查询****************\n");
		printf("                 0.退出\n");
		printf("                 1.场地信息查询\n");
		printf("                 2.个人预定信息查询\n");
		printf(" ******************************************\n");
		printf("\n");
		printf("请选择信息查询功能：");
		scanf("%d", &querycmd);
		if (querycmd == 0)
		{
			break;
		}
		else if (querycmd == 1)
		{
			Field* tempField[100] = { NULL };
			char query[100];
			printf("请输入查询场地名：");
			scanf("%s", query);
			int num=queryField(FieldRoot, query, tempField);
			sortFields(tempField, num, 0);
			putFieldMessage(tempField);

		
			int conditon;
			while (true)
			{
				printf(" ******************场地信息排序****************\n");
				printf("                 0.取消排序\n");
				printf("                 1.名称\n");
				printf("                 2.面积\n");
				printf("                 3.早上价格\n");
				printf("                 4.下午价格\n");
				printf("                 5.晚上价格\n");
				printf("                 6.开放时间\n");
				printf("                 7.关闭时间\n");
				printf(" ******************************************\n");
				printf("请选择场地信息排序功能：");
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
					printf("请输入正确的序号!");
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
				printf("当前暂无预定场地！\n");
			}
		}
		else
		{
			system("cls");
			printf("请输入正确的序号!");
			Sleep(500);
			system("cls");
		}
		
	}
	
}

/*用户功能：场地预定*/
void reserveMenu()
{
	printf(" ******************场地预定****************\n");
	printf("                 0.退出\n");
	printf("                 1.预定场地\n");
	printf("                 2.修改预定信息\n");
	printf("                 3.取消预定\n");
	printf(" ******************************************\n");
	printf("\n");
}

/*用户预订信息修改*/
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
	
	printf("请输入要修改的预定编号：");
	int idx;
	while (true)
	{
		scanf("%d", &idx);
		if (idx > cnt)
		{
			printf("请输入正确的编号：");
			continue;
		}
		else
		{
			printf(" ******************修改预定信息****************\n");
			printf("                 0.退出\n");
			printf("                 1.修改预定场地\n");
			printf("                 2.修改预定时间\n");
			printf(" ******************************************\n");
			printf("\n");

			break;
		}
	}
	
	while (true)
	{

		Reservation newReservation = *reservationp[idx - 1];
		int cmd;
		printf("请选择功能：");
		scanf("%d", &cmd);
		if (cmd == 0)
		{
			break;
		}
		else if (cmd==1)
		{
			printf("请输入新的场地名：");
			scanf("%s", newReservation.fieldName);
			Field* temp = findField(FieldRoot, newReservation.fieldName);
			if (checkTime(newReservation.time,temp->openTime))
			{
				if (!rented(newReservation))
				{
					*reservationp[idx - 1] = newReservation;
					printf("预订信息修改成功！");
					editReservations(reservationp[idx - 1]->idx, reservationp[idx - 1]->fieldName, reservationp[idx - 1]->time, reservationp[idx - 1]->owner, reservationp[idx - 1]->deleted,reservationp[idx-1]->cost);
					Sleep(500);
					system("cls");
					break;
				}
				else
				{
					printf("该场地已被预定！请重新选择！\n");
					Sleep(500);
					system("cls");
				}
			}
			else
			{
				printf("该时间段场地未开放！请重新预定！\n");
			}
			
		}
		else if (cmd==2)
		{
			printf("请输入新的时间段：");
			scanf("%02d:%02d~%02d:%02d",&newReservation.time.start.hour,&newReservation.time.start.minute,&newReservation.time.end.hour,&newReservation.time.end.minute );

			Field* temp = findField(FieldRoot, newReservation.fieldName);
			if (checkTime(newReservation.time, temp->openTime))
			{
				if (!rented(newReservation))
				{
					*reservationp[idx - 1] = newReservation;
					printf("预订信息修改成功！");
					editReservations(reservationp[idx - 1]->idx, reservationp[idx - 1]->fieldName, reservationp[idx - 1]->time, reservationp[idx - 1]->owner, reservationp[idx - 1]->deleted,reservationp[idx-1]->cost);
					Sleep(500);
					system("cls");
					break;
				}
			}
			else
			{
				printf("该时间段场地未开放！请重新预定！\n");
			}
			
		}
		else
		{
			printf("请输入正确的编号:");
		}
	}
	
}

/*找回密码*/
void forgetPassMenu()
{
	printf(" ******************找回密码****************\n");
	printf("                 0.退出\n");
	printf("                 1.管理员\n");
	printf("                 2.场地负责人\n");
	printf("                 3.用户\n");
	printf(" ******************************************\n");
	printf("\n");
}