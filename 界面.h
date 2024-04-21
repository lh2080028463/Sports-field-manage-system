#pragma once
void menu();
void magnagerMenu();
void managerFieldMenu();
Manager* managerLogin();
void responLogin();
User* userLogin();
void userMenu();
Field* FieldRegister(Field* FieldRoot);
User* userRegister(User* userRoot);
void editMessageMenu(User* user);
void reserveMenu();
void queryMessageMenu(User* user);
void editReservationMenu(char username[]);