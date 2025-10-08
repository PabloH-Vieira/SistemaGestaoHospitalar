#ifndef HISTORY_H
#include <string>

typedef struct NodeH{
    std::string procedure; //Matriz de procedimentos
    struct NodeH *next;


    NodeH(){
        next = nullptr;
    }

    bool set(std::string p){
        procedure = p;
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
    bool insertProcedure(std::string procedure);
    bool removeProcedure(std::string procedure);
    bool searchProcedure(std::string procedure);
    void printProcedures();
}History;

#define HISTORY_H

#endif //HISTORY_H
