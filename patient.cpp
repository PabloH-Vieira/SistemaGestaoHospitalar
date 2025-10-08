#include "patient.h"

//Construtor
Patient::Patient() {
    name = "";
    id = 0;
}

//Destrutor
~Patient::Patient() {}

void Patient::set(char new_name[], int new_id){
    std::string p = new_name;
    name = p;
    id = new_id;
}

std::string Patient::get(){
    return name;
}

int getID(){
    return id;
}
