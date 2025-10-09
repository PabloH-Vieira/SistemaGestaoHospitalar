#ifndef HISTORY_H
#include <string>
#include <cstdio>

typedef struct NodeH{
    std::string procedure; //Matriz de procedimentos
    struct NodeH *next;

    NodeH(){
        next = nullptr;
    }

    void set(std::string p){
        procedure = p;
    }
} NodeH;

typedef struct history{
    int cont_procedures; //Deve chegar no máximo a 10 procedimentos
    NodeH *top;

    //Construtor
    history();
    //Destrutor
    ~history();

    bool isEmpty();
    bool isFull();
    bool insertProcedure(std::string procedure);
    std::string undoProcedure();
    void printProcedures();
} History;

#define HISTORY_H

#endif //HISTORY_H
