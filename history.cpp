#include "history.h"
#include <string>

//Construtor
history::history(){
    top = nullptr;
}

bool history::isEmpty(){
    if (cont_procedures == 0) return true; else return false;
}

bool history::removeProcedure(std::string procedure){
    if (isEmpty()) return false;
    if (top -> procedure != procedure) return false;

    NodeH *aux = top;
    top = top -> next;
    delete aux;
    cont_procedures--;
    return true;
}

//Destrutor
history::~history(){
    while(!isEmpty()) {
        NodeH *aux = top;
        top = top -> next;
        delete aux;
    }
    delete top;
    cont_procedures = 0;
}

bool history::isFull(){
    if (cont_procedures == 10) return true; else return false;
}

bool history::insertProcedure(std::string procedure){
    if (isFull()) return false;

    NodeH *p = new NodeH;
    p -> set(procedure);
    if (isEmpty()){
        top = p;
        top -> next = nullptr;
        cont_procedures++;
        return true;
    }

    p-> next = top;
    top = p;
    cont_procedures++;
    return true;
}

bool history::searchProcedure(std::string procedure){
    //Percorre todas as linhas
    for (int i = 0; i < cont_procedures; i++){
        //Usamos a classe string para comparar os procedimentos
        std::string s2 = top -> procedure;
        if (procedure == s2) return true;
    }
    //Se percorreu todas as linhas e não encontrar o procedimento, retorna false
    return false;
}

void history::printProcedures(){
    for (int i = 0; i < cont_procedures; i++){
        printf("%p\n", top -> procedure);
    }
}