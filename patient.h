#ifndef PATIENT_H
#define PATIENT_H
#include "history.h"
#include <string>

typedef struct Patient{
    std::string name;
    int id;
    History history;
    int priority;        // 1 (Emergencia) a 5 (Nao urgente)
    int arrivalSequence; // Desempate de chegada

    Patient();
    Patient(const Patient& other); // Construtor de Cópia
    ~Patient();

    void set(const char* new_name, int new_id, int new_priority);
    std::string get();
    int getID();
} Patient;

#endif