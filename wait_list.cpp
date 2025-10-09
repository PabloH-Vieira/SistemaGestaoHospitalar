#include "wait_list.h"
#include <cstdio>

// no maximo 42 vagas na emergencia do hospital
#define MAX_WAIT_LIST_SIZE 42

WaitList::WaitList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
    max_size = MAX_WAIT_LIST_SIZE;
}

WaitList::~WaitList(){
    NodeHeap *current = head;
    while(current != nullptr){
        NodeHeap *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

bool WaitList::full(){
    return size >= max_size;
}

bool WaitList::empty(){
    return size == 0;
}

// adiciona paciente no final da fila
bool WaitList::addPatient(Patient p){
    if (full()) {
        printf("ERRO: Fila de espera esta cheia!\n");
        return false;
    }

    NodeHeap* newNode = new NodeHeap;
    newNode->patient = p;
    newNode->next = nullptr;

    if (empty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
    return true;
}

// remove paciente do inicio, se der erro volta null
Patient WaitList::removePatient(){
    if (empty()) {
        Patient emptyPatient;
        return emptyPatient;
    }

    NodeHeap* nodeToRemove = head;
    Patient removedPatient = head->patient;

    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }

    delete nodeToRemove;
    size--;

    return removedPatient;
}

// imprime a fila de espera
void WaitList::printWaitList() {
    if (empty()) {
        printf("\nFila de espera esta vazia.\n");
        return;
    }

    printf("\n--- Fila de Espera ---\n");
    NodeHeap* current = head;
    int position = 1;
    while (current != nullptr) {
        printf("%d. ID: %d, Nome: %s\n", position, current->patient.getID(), current->patient.get().c_str());
        current = current->next;
        position++;
    }
    printf("----------------------\n");
}


// checa existencia
bool WaitList::searchPatient(int id) {
    if (empty()) {
        return false;
    }

    NodeHeap* current = head;
    while (current != nullptr) {
        if (current->patient.getID() == id) {
            return true;
        }
        current = current->next;
    }

    return false;
}
