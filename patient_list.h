#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H
#include "history.h"

typedef struct patient{
    char name[100];
    int id;
	History history;

    void set(char name[100], int id){
        name = name;
        id = id;
    }
    char get(){
        return name;
    }
    int getID(){
        return id;
    }
}
//Nó para a lista de pacientes
typedef struct Node(){
    Patient patient;
    Node *next;
    Node *prev;

    //Define valores pré-definidos
    Node(){
        next = nullptr;
        prev = nullptr;
    }
}Node;

//Guarda as informações dos pacientes e o histórico de tratamento
//Dinâmica e ordenada por id
typedef struct PatientList{
    Node *head;
    Node *tail;
    int qtd;

    //Construtor
    PatientList();
    //Destrutor
    ~PatientList();

    //MÉTODOS
    bool isEmpty();
    int getID(); //Identfica o próximo ID disponível
    bool addPatient(char name[100], int id);
    bool searchPacient(int id, Pacient *p);
    bool removePatient(int id);
    void printPacient(int id);
    void printAll();

}PatientList;

#endif //PATIENT_LIST_H
