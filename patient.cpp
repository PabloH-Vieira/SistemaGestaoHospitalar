#include "patient.h"
#include <string>

//Construtor
Patient::Patient() {
    name = "";
    id = 0;
}

//Destrutor
Patient::~Patient() {}

// Pré-condição: 'new_name' é um ponteiro para uma string C válida, 'new_id' é um inteiro.
// Pós-condição: O nome e o ID do paciente são atualizados.
void Patient::set(const char* new_name, int new_id){
    name = new_name;
    id = new_id;
}

// Pré-condição: O paciente existe.
// Pós-condição: Retorna o nome do paciente.
std::string Patient::get(){
    return name;
}

// Pré-condição: O paciente existe.
// Pós-condição: Retorna o ID do paciente.
int Patient::getID(){
    return id;
}
