#pragma once
#include"结构体信息.h"


char* getUserdataPath(const User user);
void inputUserdata(User* userRoot);
void editUserdata(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted);
void initNum();
void editUserNum();
void inputReservation(Reservation r[]);
void editReservations(unsigned int idx, char fieldName[], Duration time, char owner[]);
void editFieldData(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);