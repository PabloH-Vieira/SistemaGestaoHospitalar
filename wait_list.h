#ifndef WAIT_LIST_H
#define WAIT_LIST_H
#include "patient.h"

typedef struct NodeHeap{
    Patient patient;
    struct NodeHeap *next;
}NodeHeap;

typedef struct WaitList{
    NodeHeap *head;
    NodeHeap *tail;
    int size;

    //Construtor
    WaitList(int size);
    //Destrutor
    ~WaitList();

    //MÉTODOS
    bool addPatient(int id);
    bool removePatient(int id);
    bool full();
    bool empty();

}WaitList;

#endif //WAIT_LIST_H
