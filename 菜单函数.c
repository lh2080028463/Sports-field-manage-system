#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"结构体信息.h"
#include"用户.h"
#include<Windows.h>
#include"基础功能.h"
#include"文件处理.h"

extern unsigned int ManagerNum, UserNum, ResponNum;
extern User* UserRoot;
extern Field* FieldRoot;
extern Reservation reservations[10000];
/*初始界面*/
void menu()
{
	printf("********欢迎使用运动场馆管理系统********\n");
	printf("       0.退出\n");
	printf("       1.管理员\n");
	printf("       2.场地负责人\n");
	printf("       3.用户登录\n");
	printf("       4.新用户注册\n");
	printf("****************************************\n");
	printf("\n");
}

/*管理员登录界面*/
void managerLogin()
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
			printf("账号输入错误！请重新输入！\n");
			temp = 1;
			fclose(managerPointer);
			break;
		}
		else
		{
			printf(" 密  码：");
			scanf("%s", password);
			if (strcmp(manager->password, password) != 0)
			{
				printf("密码错误！请重新输入！\n");
				temp = 1;
				fclose(managerPointer);
				break;
			}
			else
			{
				printf("登录成功！\n");
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

/*场地负责人登录界面*/
void responLogin()
{
	printf(" ******场地负责人登录******\n");
	printf(" 账  号：");
	printf(" \n");
	printf(" 密  码：");
	printf(" \n");
	printf(" **************************\n");
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
	if (tempUser == NULL)
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
	if (userRoot != NULL && findUsername(userRoot, username) != NULL)
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
		return insertUser(userRoot,UserNum+1, username, password, name, phone,0);
		Sleep(500);
		userLogin(userRoot,username);
	}
}

/*管理员功能菜单*/
void magnagerMenu()
{
	printf(" ******************管理员功能****************\n");
	printf("                 1.信息管理\n");
	printf("                 2.场地负责人管理\n");
	printf("                 3.信息查询\n");
	printf("                 4.信息排序\n");
	printf("                 5.信息统计\n");
	printf("                 6.重置密码\n");
	printf("                 7.退出\n");
	printf(" ********************************************\n");
	printf("\n");
}

/*场地负责人功能菜单*/
void responMenu()
{
	printf(" ******************场地负责人功能****************\n");
	printf("                 1.场地管理\n");
	printf("                 2.信息查询\n");
	printf("                 3.信息排序\n");
	printf("                 4.信息统计\n");
	printf("                 5.重置密码\n");
	printf("                 6.退出\n");
	printf(" ************************************************\n");
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
	editUserdata(user->idx, user->username, user->password, user->name, user->phone, user->time);
	printf(" ******************************************\n");
	
	printf("\n");
}

/*用户功能：信息查询*/
void queryMessageMenu()
{
	int querycmd;
	printf(" ******************信息查询****************\n");
	printf("                 0.退出\n");
	printf("                 1.场地信息查询\n");
	printf("                 2.个人预定信息查询\n");
	printf(" ******************************************\n");
	printf("\n");
	while (true)
	{
		printf("请选择功能：");
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