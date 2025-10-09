#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H
#include "patient.h"

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
} NodeList;

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
    bool addPatient(const char* name);
    // to passando por ref pra ver fora da funcao
    bool searchPatient(int id, NodeList*& p_out);
    bool removePatient(int id);
    void printPatientHistory(int id);

} PatientList;

#endif //PATIENT_LIST_H
