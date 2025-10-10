#include "patient_list.h"
#include <string>
#include <cstdio>

//Construtor
PatientList::PatientList(){
    head = nullptr;
    tail = nullptr;
    qtd = 0;
}

//Destrutor
PatientList::~PatientList(){
    NodeList *current = head;
    while(current != nullptr){
        NodeList *next = current->next;
        delete current;
        current = next;
    }
}
// Pré-condição: A lista existe.
// Pós-condição: Retorna true se a lista estiver vazia, false caso contrário.
bool PatientList::isEmpty(){
    return qtd == 0;
}


// Pré-condição: A lista existe.
// Pós-condição: Retorna o próximo ID de paciente disponível.
int PatientList::getID(){
    if (isEmpty()) return 1;
    return tail->patient.id + 1;
}


// Pré-condição: 'name' é um ponteiro válido para uma string C.
// Pós-condição: Um novo paciente é adicionado ao final da lista e retorna true.
bool PatientList::addPatient(const char* name){
    Patient new_patient; //Cria um novo paciente
    int id = getID();
    new_patient.set(name, id); //Adicione o nome e o ID ao paciente

    NodeList *newNode = new NodeList;
    newNode->patient = new_patient;

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    qtd++;
    return true;
}

// Pré-condição: 'id' é o ID a ser pesquisado. 'p_out' é uma referência a um ponteiro NodeList.
// Pós-condição: Se o paciente for encontrado, 'p_out' aponta para o nó do paciente e retorna true. Caso contrário, ...
// ... 'p_out' é nullptr e retorna false.
bool PatientList::searchPatient(int id, NodeList*& p_out){
    if (isEmpty() || id < 1) return false;

    NodeList *aux = head;
    while(aux != nullptr){
        if(id == aux->patient.id){
            p_out = aux;
            return true;
        }
        aux = aux->next;
    }
    //Se não encontrar o paciente, retorna false
    p_out = nullptr;
    return false;
}

// Pré-condição: 'id' é o ID do paciente a ser removido.
// Pós-condição: Se o paciente for encontrado, ele é removido da lista e retorna true. Caso contrário, retorna false.
bool PatientList::removePatient(int id){
    NodeList *node_to_remove = nullptr;
    // para se nao encontrar
    if (!searchPatient(id, node_to_remove) || node_to_remove == nullptr) {
        return false;
    }

    // reorganiza ponteiros
    if (node_to_remove->prev != nullptr) {
        node_to_remove->prev->next = node_to_remove->next;
    }

    if (node_to_remove->next != nullptr) {
        node_to_remove->next->prev = node_to_remove->prev;
    }

    if (node_to_remove == head) {
        head = node_to_remove->next;
    }

    if (node_to_remove == tail) {
        tail = node_to_remove->prev;
    }

    // deleta node e atualiza qtd
    delete node_to_remove;
    qtd--;
    return true;
}

// Pré-condição: 'id' é o ID do paciente.
// Pós-condição: O histórico do paciente é impresso na tela. Se o paciente não for encontrado, uma mensagem de erro ...
// ... é exibida.
void PatientList::printPatientHistory(int id){
    NodeList *p = nullptr;
    if (searchPatient(id, p)) {
        printf("\n--- Historico Medico ---\n");
        printf("ID do paciente: %d\n", p->patient.getID());
        printf("Nome do paciente: %s\n", p->patient.get().c_str());
        printf("Procedimentos: \n");
        p->patient.history.printProcedures();
        printf("------------------------\n");
    } else { // adicionei caso de erro
        printf("ERRO: Paciente com ID %d nao encontrado.\n", id);
    }
}
