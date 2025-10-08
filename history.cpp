#include "history.h"
#include <string>

//Construtor
history::history(){
    top = nullptr;
}

bool isEmpty::history(){
    if (qtd == 0) : return true ? return false;
}

//Destrutor
~history::history(){
    NodeH *aux = top;
    while(!isEmpty())
        removeProcedure();
    qtd = 0;
}

bool isFull::history(){
    if (qtd == 10) return true ? return false;
}

bool insertProcedure::history(char procedure[10]){
    if (isFull()) return false;

    NodeH *p = new NodeH;
    p -> set(procedure);
    if (isEmpty()){
        top = *p;
        top -> next = nullptr;
        cont_procedures++;
        return true;
    }

    p-> next = top;
    top = p;
    cont_procedures++;
    return true;
}

bool removeProcedure::history(char procedure[10]){
    if (isEmpty()) return false;
    if (top -> procedure != procedure) return false;

    NodeH *aux = top;
    top = top -> next;
    delete aux;
    qtd_procedures--;
    return true;
}

bool searchProcedure::history(char procedure[10]){
    std::string s1 = procedure;
    //Percorre todas as linhas
    for (int i = 0; i < qtd_procedures; i++){
        //Usamos a classe string para comparar os procedimentos
        std::string s2 = top -> procedure;
        if (s1 == s2) : return true;
    }
    //Se percorreu todas as linhas e não encontrar o procedimento, retorna false
    return false;
}

void printProcedures::history(){
    for (int i = 0; i < qtd_procedures; i++){
        printf("%s\n", top -> procedure);
    }
}