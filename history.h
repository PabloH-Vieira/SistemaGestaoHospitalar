#ifndef HISTORY_H
#define HISTORY_H
#include <string>

typedef struct NodeH{
    std::string procedure;
    struct NodeH *next;

    NodeH(){ next = nullptr; }
    void set(std::string p){ procedure = p; }
} NodeH;

typedef struct history{
    int cont_procedures;
    NodeH *top;

    history();
    ~history();

    bool isEmpty();
    bool isFull();
    bool insertProcedure(std::string procedure);
    std::string undoProcedure();
    void printProcedures();
} History;

#endif
