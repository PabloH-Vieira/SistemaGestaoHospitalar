#include "patient.h"
#include <string>

//Construtor
Patient::Patient() {
    name = "";
    id = 0;
}

//Destrutor
Patient::~Patient() {}

void Patient::set(const char* new_name, int new_id){
    name = new_name;
    id = new_id;
}

std::string Patient::get(){
    return name;
}

int Patient::getID(){
    return id;
}
