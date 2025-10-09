#ifndef IO_H
#define IO_H

#include "patient_list.h"
#include "wait_list.h"

void saveAll(PatientList* pList, WaitList* wList);
void loadAll(PatientList* pList, WaitList* wList);

#endif
