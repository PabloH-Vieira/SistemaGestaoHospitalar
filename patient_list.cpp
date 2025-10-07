#include "patient_list.h"

PatientList::PatientList(){
    head = nullptr;
    TailP = nullptr;
    qtd = 0;
}

PatientList::~PatientList(){
    Node *aux;
    aux = head;
    while(aux != nullptr){
        Node *p = aux;
        aux = aux->next;
        delete p;
        qtd--;
    }
}

bool PatientList::isEmpty(){
    if qtd == 0 : return true ? return false;
}

int PatientList::getID(){
    if (isEmpty()) return 1;
    return tail -> patient -> id + 1;
}


//Adiciona um paciente no fim da lista
bool PatientList::addPatient(char name[100]){
    Patient *patient = new Patient; //Cria um novo paciente
    id = getID();
    patient->set(name, id); //Adicione o nome e o ID ao paciente

    Node *no = new Node;
    no -> patient = *patient;
    no -> next = nullptr;
    if (isEmpty()) head = no;
    tailP -> next = no;
    tailP = no;
    qtd++
    return true;
}

bool PatientList::removePatient(int id){
    if (isEmpty() || id < 1 || id > qtd) return false;

    //Remove o primeiro paciente da lista
    if (id == head -> patient -> id){
        Node *p = head;
        head = p -> next;
        //Se houver apenas um paciente
        if (head -> prox == nullptr)
            tail = nullptr;
        else head -> prev = nullptr;
        delete p;
        qtd--;
        return true;
    }

    //Remove o último paciente da lista
    if (id == tail -> patient -> id){
        Node *p = tail;
        tail = p -> prev;
        //Se a lista tiver somente um paciente
        if (head -> prox == nullptr)
            head = nullptr;
        else tail -> next = nullptr;
        delete p;
        qtd--;
        return true;
    }

    //Demais casos
    Patient *p = new Patient; //Cria um ponteiro para o paciente
    searchPacient(id, p);

    Patient *aux = p -> prev; //Nó anterior do paciente a ser removido
    //Remove as ligações com o paciente a ser removido
    aux -> next = p -> next;
    p -> next -> prev = aux;
    delete p;
    return true;
}

bool PatientList::searchPacient(int id, Pacient *p){
//Como a nossa lista é ordenada, podemos fazer uma busca binária


}