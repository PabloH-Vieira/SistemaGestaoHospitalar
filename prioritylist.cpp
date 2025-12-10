#include "prioritylist.h"
#include <cmath>

#include "patient_list.h"

// Função para comparar a prioridade de dois pacientes
// Retorna true se p1 tem maior prioridade que p2
// Também retorna true se as prioridades forem iguais, mas p1 possuir um ID mais antigo (menor)
bool hasHigherPriority(Patient& p1, Patient& p2) {
    if (p1.priority > p2.priority) {
        return true;
    }
    if (p1.priority == p2.priority && p1.id < p2.id) {
        return true;
    }
    return false;
}

//Função que troca a posição entre dois nós da heap
void swapPatients(Patient& p1, Patient& p2) {
    Patient temp = p1;
    p1 = p2;
    p2 = temp;
}

//Função que percorre a árvore até chegar na posição do nó na função de remoção ou inserção
//Navega na árvore a partir do índice binário da raiz
// 1. Queremos acessar o índice do nó pai ou do último nó
// 2. mask representa o segundo bit mais significativo a cada chamada do loop
// 3. Realizamos um AND entre os bits de mask e dos bits do índice alvo (pai ou último index)
// 4. Se ao menos um dos bits resultar em 1 (ex: 001, 100, 010), vamos para a direita. Caso contrário, para a esquerda
// 5. Deslocamos o bit de mask uma vez para a direita
// 6. Repetimos o loop
// 7. Paramos quando todos os bits de mask estiverem zerados

NodeHeap* findIndex(NodeHeap* node, int targetIndex) {
    for (int mask = 1 << ((int)floor(log2(targetIndex)) - 1); mask > 0; mask >>= 1) {
        if (targetIndex & mask) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
}



// Construtor
PriorityList::PriorityList() {
    root = nullptr;
    nodeCount = 0;
}

// Destrutor
PriorityList::~PriorityList() {
    clear(root);
}

// Função auxiliar recursiva para liberar os nós
void PriorityList::clear(NodeHeap* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Verifica se a fila está vazia
bool PriorityList::isEmpty() {
    return nodeCount == 0;
}

// Retorna o número de pacientes na fila
int PriorityList::size() {
    return nodeCount;
}

// Retorna o paciente de maior prioridade sem removê-lo
Patient PriorityList::getHighestPriority() {
    if (!isEmpty())
        return root->patient;
}

// Adiciona um novo paciente à fila de prioridade
void PriorityList::addPatient(const Patient& p) {
    nodeCount++;
    NodeHeap* newNode = new NodeHeap(p);

    if (isEmpty()) {
        root = newNode;
        return;
    }

    // Encontra o nó pai onde o novo nó será inserido
    NodeHeap* parent = root;
    int parentIndex = nodeCount / 2;
    parent = findIndex(parent, parentIndex);

    // Conecta o novo nó como filho esquerdo ou direito
    newNode->parent = parent;
    if (nodeCount % 2 == 0) { // o índice do filho da esquerda é dado por 2n, sendo n o índice do pai
        parent->left = newNode;
    } else {
        parent->right = newNode; //o índice do filho da direita é dado por 2n+1, sendo n o índice do pai
    }

    // Mantém a propriedade do heap subindo o nó
    siftUp(newNode);
}

// Remove e retorna o paciente com a maior prioridade
Patient PriorityList::removeHighestPriority() {
    if (!isEmpty()) {
        Patient highestPriorityPatient = root->patient;

        //Se a árvore tiver apenas um elemento, a esvaziamos
        if (nodeCount == 1) {
            delete root;
            root = nullptr;
            nodeCount = 0;
            return highestPriorityPatient;
        }

        // Encontra o último nó da árvore (o mais à direita no último nível)
        NodeHeap* lastNode = root;
        int targetIndex = nodeCount;
        lastNode = findIndex(lastNode, targetIndex);

        // Move os dados do último nó para a raiz.
        root->patient = lastNode->patient;

        // Identifica se o último nó está na esquerda ou na direita e então o remove da árvore
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = nullptr;
        } else {
            lastNode->parent->right = nullptr;
        }
        delete lastNode;
        nodeCount--;

        // Mantém a propriedade do heap descendo a partir da raiz
        siftDown(root);

        return highestPriorityPatient;
    }
}

// Move um elemento para cima no heap para manter a propriedade
void PriorityList::siftUp(NodeHeap* node) {
    // Sobe enquanto o nó não for a raiz e tiver maior prioridade que seu pai.
    while (node->parent && hasHigherPriority(node->patient, node->parent->patient)) {
        swapPatients(node->patient, node->parent->patient);
        node = node->parent; // Move para a posição do pai para continuar
    }
}

// Move um elemento para baixo no heap para manter a propriedade
void PriorityList::siftDown(NodeHeap* root) {
    while (true) {
        NodeHeap* top = root;
        NodeHeap* left = root->left;
        NodeHeap* right = root->right;

        // Verifica se o filho esquerdo existe e tem maior prioridade
        if (left && hasHigherPriority(left->patient, top->patient)) {
            top = left;
        }

        // Verifica se o filho direito existe e tem maior prioridade
        if (right && hasHigherPriority(right->patient, top->patient)) {
            top = right;
        }

        // Se o nó já está na posição correta (é maior que seus filhos), o loop termina
        if (top == root) {
            break;
        }

        swapPatients(root->patient, top->patient);
        root = top; // Continua a descida a partir da nova posição
    }
}

Patient* PriorityList::find(NodeHeap* root, int id) {
    // Se a árvore é vazia, retorna null
    if (!root) {
        return nullptr;
    }

    //Se o ID do paciente está no nó atual, encontramos
    if (root->patient.id == id) {
        return &(root->patient);
    }

    //Busca recursivamente na subárvore esquerda
    Patient* foundLeft = find(root->left, id);
    if (foundLeft) {
        return foundLeft;
    }

    // Se não foi encontrado à esquerda, busca na subárvore direita
    return find(root->right, id);
}
