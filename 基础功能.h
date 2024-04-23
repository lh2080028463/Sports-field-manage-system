#pragma once

#include"结构体信息.h"
User* findUsername(User* userRoot, char username[]);
void find();
void sort();
void statistic();
void initReservations(Reservation r);
bool rented(Reservation newReservation);
bool checkTime(const Duration reservedTime, const Duration openTime);
int compareFields(const void* a, const void* b, int conditon);
void sortFields(Field** fields, int numFields, int conditon);
unsigned int calculatePrice(Reservation reservation);
unsigned int calculateTime(Duration dur);