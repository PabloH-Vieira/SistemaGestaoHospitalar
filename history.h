#ifndef HISTORY_H

typedef struct NodeH(int id){
    char procedure[10]; //Matriz de procedimentos
    Node *next;

    NodeH(){
        next = nullptr;
        qtd = 0;
    }

    bool set(char p[10]){
        procedure = p;
    }
}NodeH;

typedef struct history(int size){
    int cont_procedures; //Deve chegar no máximo a 10 procedimentos
    Node *top;

    //Construtor
    history();
    //Destrutor
    ~history();

    bool isEmpty();
    bool isFull();
    bool insertProcedure(char procedure[10]);
    bool removeProcedure(char procedure[10]);
    bool searchProcedure(char procedure[10]);
}History;

#define HISTORY_H

#endif //HISTORY_H
