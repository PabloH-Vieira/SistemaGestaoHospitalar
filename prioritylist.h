#ifndef PRIORITYLIST_H
#define PRIORITYLIST_H

#include "patient.h"

struct NodeHeap {
	Patient* patient;
	NodeHeap* parent;
	NodeHeap* left;
	NodeHeap* right;
	NodeHeap(Patient* p, NodeHeap* par = nullptr)
		: patient(p), parent(par), left(nullptr), right(nullptr) {}
};

typedef struct PriorityList {
	NodeHeap *root;
	int nodeCount;
	int sequenceCounter;

	PriorityList();
	~PriorityList();

	// restoredSeq: Se != -1, usa esse valor em vez de gerar novo (para Load)
	void addPatient(Patient* p, int restoredSeq = -1);
	Patient* removeHighestPriority();

	bool isEmpty();
	int size();
	bool search(int id);
	bool searchRecursive(NodeHeap* node, int id);

	void siftUp(NodeHeap* node);
	void siftDown(NodeHeap* node);
	void clear(NodeHeap* node);

	// Imprime ordenado para visualização
	void printList();

} PriorityList;

#endif