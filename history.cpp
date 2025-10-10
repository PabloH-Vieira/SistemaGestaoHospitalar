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
    // a quantidade de procedimentos maximo é 10
    return cont_procedures >= 10;
}

// Pré-condição: O histórico foi criado.
// Pós-condição: O procedimento é inserido no topo do histórico e retorna true. Se o histórico estiver cheio, ...
// ... retorna false.
bool history::insertProcedure(std::string procedure){
    if (isFull()) return false;

    NodeH *p = new NodeH;
    p->set(procedure);

    p->next = top;
    top = p;
    cont_procedures++;
    return true;
}

// Pré-condição: O histórico foi criado.
// Pós-condição: Se o histórico não estiver vazio, o procedimento do topo é removido e retornado.
// ... caso contrário, retorna uma string vazia.
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

// Pré-condição: O histórico foi criado.
// Pós-condição: Os procedimentos do histórico são impressos na tela.
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
