#ifndef WAIT_LIST_H
#define WAIT_LIST_H
#include "patient.h"

typedef struct NodeHeap{
    Patient patient;
    struct NodeHeap *next;
} NodeHeap;

typedef struct WaitList{
    NodeHeap *head;
    NodeHeap *tail;
    int size;
    int max_size;

    //Construtor
    WaitList();
    //Destrutor
    ~WaitList();


    // mudei pra passar o paciente direto e adicionei +2
    //MÉTODOS
    bool addPatient(Patient p);
    Patient removePatient();
    bool full();
    bool empty();
    void printWaitList();
    bool searchPatient(int id);

} WaitList;

#endif //WAIT_LIST_H
