#include "history.h"
#include <string>
#include <iostream>

//Construtor
history::history(){
    top = nullptr;
    cont_procedures = 0;
}

//Destrutor
history::~history(){
    while(!isEmpty()) {
        NodeH *aux = top;
        top = top -> next;
        delete aux;
    }
    cont_procedures = 0;
}

bool history::isEmpty(){
    return cont_procedures == 0;
}

bool history::isFull(){
    // a quantidade de procedimentos maximo eh 10
    return cont_procedures >= 10;
}

bool history::insertProcedure(std::string procedure){
    if (isFull()) return false;

    NodeH *p = new NodeH;
    p->set(procedure);

    p->next = top;
    top = p;
    cont_procedures++;
    return true;
}

// remove o procedimento do topo da pilha (LIFO) e retorna
std::string history::undoProcedure(){
    if (isEmpty()) {
        return ""; // Retorna string vazia se não houver o que remover
    }

    NodeH *aux = top;
    std::string procedure = top->procedure;
    top = top->next;

    delete aux;
    cont_procedures--;
    return procedure;
}

void history::printProcedures(){
    if(isEmpty()){
        printf("Nenhum procedimento no historico.\n");
        return;
    }
    NodeH* current = top;
    int count = 1;
    while(current != nullptr){
        printf("  %d. %s\n", count, current->procedure.c_str());
        current = current->next;
        count++;
    }
}
