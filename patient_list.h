#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

typedef struct NodeH(){
    char procedure[10];
    int id;
    Node *next;
}NodeH;

typedef struct history(int size){
	int cont_procedures; //Deve chegar no máximo a 10 procedimentos
    Node *head;
    //Construtor
    history();
    //Destrutor
    ~history();

    bool insertProcedure(char procedure[10]);
    bool removeProcedure(char procedure[10]);
    bool searchProcedure(char procedure[10]);
    bool historyIsEmpty();
    bool historyIsFull();
}History;

typedef struct patient{
    char name[100];
    int id;
	History history;
}Patient;

//Nó para a lista de pacientes
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
