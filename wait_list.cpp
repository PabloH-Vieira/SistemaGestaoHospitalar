#include "wait_list.h"
#include <cstdio>

// no maximo 42 vagas na emergencia do hospital
#define MAX_WAIT_LIST_SIZE 42

//Construtor
WaitList::WaitList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
    max_size = MAX_WAIT_LIST_SIZE;
}

//Destrutor
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

// Pré-condição: A lista de espera não está cheia. 'p' é um paciente válido.
// Pós-condição: O paciente é adicionado ao final da fila e retorna true. Se a fila estiver cheia, retorna false.
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

// Pré-condição: A pilha existe.
// Pós-condição: Se a fila não estiver vazia, remove e retorna o primeiro paciente. Caso contrário, retorna um ...
// ... paciente vazio.
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

// Pré-condição: A pilha existe.
// Pós-condição: Imprime os pacientes na fila de espera.
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


// Pré-condição: A pilha existe e 'id' é um inteiro válido (maior ou igual a 0).
// Pós-condição: Retorna true se um paciente com o ID especificado for encontrado, false caso contrário.
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
