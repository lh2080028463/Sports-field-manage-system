#pragma once
#include"结构体信息.h"

void editManagerpassword();
Field* addField(Field* node, unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);
Field* FieldleftRotate(Field* x);
Field* FieldrightRotate(Field* x);
int getFieldBalence(Field* node);
int Fieldheight(Field* node);
void inputFielddata(Field* FieldRoot);
void editFielddata(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);
Field* newField(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);
Field* findFieldname(const Field* FieldRoot, const char name[]);
Field* FieldRegister(Field* FieldRoot);
void editField(Field* fieldRoot);
void deleteField();
void managerqueryfield();
void managersortfield();
void traverseField(Field* root, Field fields[], int* count);
void editRespondent();
void deleteRespondent();
void queryUserReservation();
Respondent* findRespondentNode(Respondent* head, const char* username);