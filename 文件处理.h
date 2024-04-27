#pragma once
#include"结构体信息.h"


char* getUserdataPath(const User user);
void inputUserdata();
void editUserdata(unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, unsigned int deleted,unsigned int timed);
void initNum();
void editUserNum();
void inputReservation(Reservation r[]);
void editReservations(unsigned int idx, char fieldName[], Duration time, char owner[], bool deleted,unsigned int cost);
void editFieldData(unsigned int idx, char name[], double area, double price[], Duration openTime, bool rented, unsigned int time, unsigned int deleted);
void editFieldNum();
void editReservationNum();

void inputRespondata();
char* getFielddataPath(const Field field);
void editRespondents(unsigned int idx, char username[], char password[], char name[], char phone[], bool deleted);
void editResponNum();
char* getRespondataPath(const Respondent* respondent);