#pragma once
#include"�ṹ����Ϣ.h"

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
void editField();
void deleteField();
void addManager();
void editManager();
void deleteManager();