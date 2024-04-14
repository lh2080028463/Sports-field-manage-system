#pragma once
void menu();
void managerMenu();
void editManagerMenu();
Manager* managerLogin();
Respondent* responLogin();
User* userLogin();
void userMenu();
User* userRegister(User* userRoot);
void editMessageMenu(User* user);
