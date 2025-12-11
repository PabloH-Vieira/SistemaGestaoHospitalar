#include "patient.h"

Patient::Patient() {
    name = "";
    id = 0;
    priority = 5;
    arrivalSequence = 0;
}

// Construtor de Cópia: Evita que o programa feche ao copiar pacientes temporários
Patient::Patient(const Patient& other) {
    name = other.name;
    id = other.id;
    priority = other.priority;
    arrivalSequence = other.arrivalSequence;

    // Inicializa histórico vazio na cópia para evitar duplicidade de ponteiros
    history.top = nullptr;
    history.cont_procedures = 0;

}

Patient::~Patient() {
    // Destrutor da history é chamado automaticamente
}

void Patient::set(const char* new_name, int new_id, int new_priority){
    name = new_name;
    id = new_id;
    priority = new_priority;
}

std::string Patient::get(){ return name; }
int Patient::getID(){ return id; }