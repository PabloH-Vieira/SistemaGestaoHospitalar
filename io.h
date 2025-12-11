#ifndef IO_H
#define IO_H
#include "patient_list.h"
#include "prioritylist.h"

void saveAll(PatientList* pList, PriorityList* wList);
void loadAll(PatientList* pList, PriorityList* wList);
#endif