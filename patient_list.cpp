#include "patient_list.h"
#include <string>

PatientList::PatientList(){
    head = nullptr;
    tail = nullptr;
    qtd = 0;
}

PatientList::~PatientList(){
    NodeList *aux;
    aux = head;
    while(aux != nullptr){
        NodeList *p = aux;
        aux = aux->next;
        delete p;
        qtd--;
    }
}

bool PatientList::isEmpty(){
    if (qtd == 0) return true; else return false;
}

int PatientList::getID(){
    if (isEmpty()) return 1;
    return tail -> patient.id + 1;
}


//Adiciona um paciente no fim da lista
bool PatientList::addPatient(char name[100]){
    Patient *patient = new Patient; //Cria um novo paciente
    int id = getID();
    patient->set(name, id); //Adicione o nome e o ID ao paciente

    NodeList *no = new NodeList;
    no -> patient = *patient;
    no -> next = nullptr;
    if (isEmpty()) head = no;
    tail -> next = no;
    tail = no;
    qtd++;
    return true;
}

bool PatientList::searchPatient(int id, NodeList *p){
    if (isEmpty() || id < 1 || id > qtd) return false;
    if (id < 1 || id > tail -> patient.id) return false;

    NodeList *aux = head;
    while(aux != nullptr && id >= aux -> patient.id){
        if(id == aux -> patient.id){
            p = aux;
            return true;
        }
        aux = aux -> next;
    }
    //Se não encontrar o paciente, retorna false
    if (aux == nullptr || id < aux -> patient.id)
        return false;
}

bool PatientList::removePatient(int id){
    if (isEmpty() || id < 1 || id > qtd) return false;

    //Remove o primeiro paciente da lista
    if (id == head -> patient.id){
        NodeList *p = head;
        head = p -> next;
        //Se houver apenas um paciente
        if (head -> next == nullptr)
            tail = nullptr;
        else head -> prev = nullptr;
        delete p;
        qtd--;
        return true;
    }

    //Remove o último paciente da lista
    if (id == tail -> patient.id){
        NodeList *p = tail;
        tail = p -> prev;
        //Se a lista tiver somente um paciente
        if (head -> next == nullptr)
            head = nullptr;
        else tail -> next = nullptr;
        delete p;
        qtd--;
        return true;
    }

    //Demais casos
    NodeList *p = new NodeList; //Cria um ponteiro para o nó do paciente
    searchPatient(id, p);

    NodeList *aux = p -> prev; //Nó anterior do paciente a ser removido
    //Remove as ligações com o paciente a ser removido
    aux -> next = p -> next;
    p -> next -> prev = aux;
    delete p;
    return true;
}

void PatientList::printPatient(int id){
    NodeList *p;
    searchPatient(id, p);
    printf("Nome do paciente: %s\n", p -> patient.get());
    printf("ID do paciente: %d\n", p -> patient.getID());;
    printf("Historico de procedimentos: \n");
    p -> patient.history.printProcedures();
}