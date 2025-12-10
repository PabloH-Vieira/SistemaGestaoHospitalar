#ifndef PATIENT_H
#define PATIENT_H
#include "history.h"
#include <string>

typedef struct Patient{
    std::string name;
    int id;
    History history;
    int priority;

    Patient();
    ~Patient();
    void set(const char* new_name, int new_id, int priority);
    std::string get();
    int getID();
} Patient;

#endif
