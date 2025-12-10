#ifndef PRIORITYLIST_H
#define PRIORITYLIST_H

#include "patient.h"

// Nó da árvore/heap
struct NodeHeap {
	Patient patient;
	NodeHeap* parent;
	NodeHeap* left;
	NodeHeap* right;

	// Construtor do nó
	NodeHeap(const Patient& p, NodeHeap* par = nullptr)
		: patient(p), parent(par), left(nullptr), right(nullptr) {}
};

typedef struct PriorityList {
	NodeHeap
	* root;
	int nodeCount;

	// Construtor
	PriorityList();
	// Destrutor
	~PriorityList();

	void addPatient(const Patient& p);
	bool isEmpty();
	int size();
	Patient removeHighestPriority();
	Patient getHighestPriority();

	// Funções auxiliares para manter a propriedade do heap
	void siftUp(NodeHeap* node);
	void siftDown(NodeHeap* node);

	// Função auxiliar para o destrutor
	void clear(NodeHeap* node);
} PriorityList;

#endif //PRIORITYLIST_H
