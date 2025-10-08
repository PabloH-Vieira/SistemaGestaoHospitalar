#ifndef PATIENT_H
#define PATIENT_H
#include "history.h"

typedef struct Patient{
    std::string name;
    int id;
    History history;

    Patient();
    ~Patient();
    void set(char new_name[], int new_id);
    std::string get();
    int getID();
}Patient;

#endif //PATIENT_H
