#pragma once
#include"结构体信息.h"

Field* addField(Field* node, unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);
void inputFielddata(Field* FieldRoot);
void editField();
void deleteField();
void addManager();
void editManager();
void deleteManager();