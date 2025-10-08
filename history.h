#ifndef HISTORY_H
#include <string>

typedef struct NodeH{
    std::string procedure[10]; //Matriz de procedimentos
    struct NodeH *next;


    NodeH(){
        next = nullptr;
    }

    bool set(char p[10]){
        std::string procedure = p;
        procedure = procedure;
        return true;
    }
}NodeH;

typedef struct history{
    int cont_procedures; //Deve chegar no máximo a 10 procedimentos
    NodeH *top;

    //Construtor
    history();
    //Destrutor
    ~history();

    bool isEmpty();
    bool isFull();
    bool insertProcedure(char procedure[10]);
    bool removeProcedure(char procedure[10]);
    bool searchProcedure(char procedure[10]);
    void printProcedures();
}History;

#define HISTORY_H

#endif //HISTORY_H
