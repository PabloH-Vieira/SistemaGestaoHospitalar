#ifndef WAIT_LIST_H
#define WAIT_LIST_H

typedef struct patient{
    string name;
    int id;
}Patient;

typedef struct Node(){
    Patient patient;
    Node *next;
}Node;

typedef struct WaitList(){
    Node *head;
    Node *tail;
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
