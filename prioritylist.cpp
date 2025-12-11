#include "prioritylist.h"
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>

bool hasHigherPriority(Patient* p1, Patient* p2) {
    if (p1->priority < p2->priority) return true;
    if (p1->priority == p2->priority && p1->arrivalSequence < p2->arrivalSequence) return true;
    return false;
}

void swapPatients(Patient*& p1, Patient*& p2) {
    Patient* temp = p1;
    p1 = p2;
    p2 = temp;
}

NodeHeap* findIndex(NodeHeap* node, int targetIndex) {
    if (targetIndex <= 1) return node;
    for (int mask = 1 << ((int)floor(log2(targetIndex)) - 1); mask > 0; mask >>= 1) {
        if (targetIndex & mask) node = node->right;
        else node = node->left;
    }
    return node;
}

PriorityList::PriorityList() {
    root = nullptr;
    nodeCount = 0;
    sequenceCounter = 0;
}

PriorityList::~PriorityList() { clear(root); }

void PriorityList::clear(NodeHeap* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

bool PriorityList::isEmpty() { return nodeCount == 0; }
int PriorityList::size() { return nodeCount; }

bool PriorityList::searchRecursive(NodeHeap* node, int id) {
    if (!node) return false;
    if (node->patient->id == id) return true;
    return searchRecursive(node->left, id) || searchRecursive(node->right, id);
}
bool PriorityList::search(int id) { return searchRecursive(root, id); }

void PriorityList::addPatient(Patient* p, int restoredSeq) {
    if (restoredSeq != -1) {
        p->arrivalSequence = restoredSeq;
        if (restoredSeq > sequenceCounter) sequenceCounter = restoredSeq;
    } else {
        sequenceCounter++;
        p->arrivalSequence = sequenceCounter;
    }

    NodeHeap* newNode = new NodeHeap(p);

    if (root == nullptr) {
        root = newNode;
        nodeCount = 1;
        return;
    }

    nodeCount++;
    NodeHeap* parent = findIndex(root, nodeCount / 2);
    newNode->parent = parent;
    if (nodeCount % 2 == 0) parent->left = newNode;
    else parent->right = newNode;

    siftUp(newNode);
}

Patient* PriorityList::removeHighestPriority() {
    if (isEmpty()) return nullptr;
    Patient* highest = root->patient;

    if (nodeCount == 1) {
        delete root;
        root = nullptr;
        nodeCount = 0;
        return highest;
    }

    NodeHeap* lastNode = findIndex(root, nodeCount);
    root->patient = lastNode->patient;

    if (lastNode->parent->left == lastNode) lastNode->parent->left = nullptr;
    else lastNode->parent->right = nullptr;

    delete lastNode;
    nodeCount--;
    siftDown(root);
    return highest;
}

void PriorityList::siftUp(NodeHeap* node) {
    while (node->parent && hasHigherPriority(node->patient, node->parent->patient)) {
        swapPatients(node->patient, node->parent->patient);
        node = node->parent;
    }
}

void PriorityList::siftDown(NodeHeap* root) {
    while (true) {
        NodeHeap* top = root;
        NodeHeap* left = root->left;
        NodeHeap* right = root->right;

        if (left && hasHigherPriority(left->patient, top->patient)) top = left;
        if (right && hasHigherPriority(right->patient, top->patient)) top = right;

        if (top == root) break;

        swapPatients(root->patient, top->patient);
        root = top;
    }
}

// Auxiliar para coletar nós
void collectNodes(NodeHeap* node, std::vector<Patient*>& lista) {
    if (!node) return;
    lista.push_back(node->patient);
    collectNodes(node->left, lista);
    collectNodes(node->right, lista);
}

void PriorityList::printList() {
    if (isEmpty()) {
        printf("\nFila de espera vazia.\n");
        return;
    }
    std::vector<Patient*> snapshot;
    collectNodes(root, snapshot);

    std::sort(snapshot.begin(), snapshot.end(), [](Patient* a, Patient* b) {
        return hasHigherPriority(a, b);
    });

    printf("\n--- Fila de Prioridade (Ordenada) ---\n");
    for (const auto& p : snapshot) {
        printf("Prioridade: %d (Seq: %d) - Nome: %s (ID: %d)\n",
               p->priority, p->arrivalSequence, p->name.c_str(), p->id);
    }
    printf("-------------------------------------\n");
}