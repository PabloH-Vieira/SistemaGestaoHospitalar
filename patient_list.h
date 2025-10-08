#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H
#include "patient.h"
#include <string>

//Nó para a lista de pacientes
typedef struct NodeList{
    Patient patient;
    struct NodeList *next;
    struct NodeList *prev;

    //Define valores pré-definidos
    NodeList(){
        next = nullptr;
        prev = nullptr;
    }
}NodeList;

//Guarda as informações dos pacientes e o histórico de tratamento
//Dinâmica e ordenada por id
typedef struct PatientList{
    NodeList *head;
    NodeList *tail;
    int qtd;

    //Construtor
    PatientList();
    //Destrutor
    ~PatientList();

    //MÉTODOS
    bool isEmpty();
    int getID(); //Identfica o próximo ID disponível
    bool addPatient(char name[100]);
    bool searchPatient(int id, NodeList *p);
    bool removePatient(int id);
    void printPatient(int id);
    void printAll();

}PatientList;

#endif //PATIENT_LIST_H
