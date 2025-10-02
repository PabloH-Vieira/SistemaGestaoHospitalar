#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

typedef struct patient{
    char name[100];
    int id;
}Patient;

typedef struct Node(){
    Patient patient;
    Node *next;
}Node;

//Guarda as informações dos pacientes e o histórico de tratamento
//Dinâmica e ordenada por id
typedef struct PatientList{
    Node *headP;
    Node *tailP;

    //Construtor
    PatientList();
    //Destrutor
    ~PatientList();

    //MÉTODOS
    bool addPatient(Patient patient);
    bool removePatient(int id);
    void printPacient(int id);
    bool searchPacient(int id);
    void printAll();

}PatientList;

#endif //PATIENT_LIST_H
