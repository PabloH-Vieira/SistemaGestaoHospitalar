#ifndef HISTORY_H
#define HISTORY_H

typedef struct Node(){
    char procedures[10][10];
    int id;
    Node *next;
}Node;

//Assim como a lista de pacientes, o histórico é dinâmico
typedef struct history{
    Node *head;

    //Construtor
    history();
    //Destrutor
    ~history();

    bool insertProcedure(char procedure[10]);
    bool removeProcedure(char procedure[10]);
    bool searchProcedure(char procedure[10]);
    bool historyIsEmpty();
    bool historyIsFull();
}History;


#endif //HISTORY_H
