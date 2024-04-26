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

unsigned int calculatePrice(Reservation reservation);
unsigned int calculateTime(Duration dur);

int compareFields0(const void* a, const void* b);
int compareFields1(const void* a, const void* b);
int compareFields2(const void* a, const void* b);
int compareFields3(const void* a, const void* b);
int compareFields4(const void* a, const void* b);
int compareFields5(const void* a, const void* b);
int compareFields6(const void* a, const void* b);
int compareFields7(const void* a, const void* b);
void sortFields(Field* tempField, int num);
