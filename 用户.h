#pragma once
#include"结构体信息.h"
void makeReservation(Reservation reservation,Field* root, char username[]);
User* insertUser(User* node, unsigned int idx, char username[], char password[], char name[], char phone[], unsigned int time, bool deleted);
void queryField(Field* root, const char* query, Field* fields[]);
void putFieldMessage(Field* tempField[]);
void putReservation(Reservation tempReservation);
void resetUserPass(User* curUser);
void deleteUser(User* user);