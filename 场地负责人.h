#pragma once
void recordUserField();
void  responMenu();

Respondent* createRespondentNode(unsigned int idx, const char* username, const char* password, const char* name, const char* phone, bool deleted);
void insertRespondentNode(Respondent* head, Respondent* newNode);
void deleteRespondentNode(Respondent* head, const char* username);
Respondent* findRespondentNode(Respondent* head, const char* username);
void printRespondentList(Respondent* head);

void registerUser();
void responQueryMessage();
void resetResponPass(Respondent* curRespondent);