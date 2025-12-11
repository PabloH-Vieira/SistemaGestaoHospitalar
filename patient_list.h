#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H
#include "patient.h"

struct NodeTree{
    Patient patient;
    NodeTree *left;
    NodeTree *right;
    NodeTree(){ left = nullptr; right = nullptr; }
};

typedef struct PatientList{
    NodeTree *root;
    int qtd;

    PatientList();
    ~PatientList();

    void destroyTree(NodeTree* node);
    NodeTree* insertRecursive(NodeTree* node, Patient p);
    NodeTree* searchRecursive(NodeTree* node, int id);
    NodeTree* removeRecursive(NodeTree* node, int id, bool &success);
    NodeTree* findMin(NodeTree* node);
    void printInOrder(NodeTree* node);

    bool isEmpty();
    int getNextID();

    Patient* getPatientPtr(int id); // Retorna ponteiro para Heap

    int addPatient(const char* name, int priority); // Retorna ID
    bool addPatientDirect(Patient p); // Para IO

    bool searchPatient(int id);
    bool removePatient(int id);
    void printPatientHistory(int id);
    void listAllPatients();

} PatientList;

#endif