#include "io.h"
#include <fstream>
#include <vector>
#include <string>

#define PATIENT_FILE "patients_v2.dat"
#define WAITLIST_FILE "queue_v2.dat"

void saveTree(NodeTree* node, std::ofstream& file) {
    if (!node) return;
    file << node->patient.id << std::endl;
    file << node->patient.name << std::endl;
    file << node->patient.priority << std::endl;
    file << node->patient.arrivalSequence << std::endl;

    file << node->patient.history.cont_procedures << std::endl;
    NodeH* cur = node->patient.history.top;
    std::vector<std::string> procs;
    while(cur){
        procs.push_back(cur->procedure);
        cur = cur->next;
    }
    for(int i = procs.size()-1; i>=0; i--) file << procs[i] << std::endl;

    saveTree(node->left, file);
    saveTree(node->right, file);
}

void saveAll(PatientList* pList, PriorityList* wList) {
    std::ofstream pFile(PATIENT_FILE);
    if (pFile.is_open()) {
        saveTree(pList->root, pFile);
        pFile.close();
    }
    std::ofstream wFile(WAITLIST_FILE);
    if (wFile.is_open()) {
        if (wList->root) {
            std::vector<NodeHeap*> q;
            q.push_back(wList->root);
            int head = 0;
            while(head < (int)q.size()){
                 NodeHeap* curr = q[head++];
                 wFile << curr->patient->id << std::endl;
                 if(curr->left) q.push_back(curr->left);
                 if(curr->right) q.push_back(curr->right);
            }
        }
        wFile.close();
    }
}

void loadAll(PatientList* pList, PriorityList* wList) {
    std::ifstream pFile(PATIENT_FILE);
    std::string line;
    if (pFile.is_open()) {
        while (getline(pFile, line)) {
            if(line.empty()) continue;
            Patient p;
            p.id = std::stoi(line);
            getline(pFile, p.name);
            getline(pFile, line);
            p.priority = std::stoi(line);
            getline(pFile, line);
            p.arrivalSequence = std::stoi(line);

            getline(pFile, line);
            int n = std::stoi(line);

            // Insere primeiro na árvore
            pList->addPatientDirect(p);
            // Pega o ponteiro final
            Patient* storedP = pList->getPatientPtr(p.id);
            // Carrega historico direto no ponteiro final
            if (storedP) {
                for(int i=0; i<n; i++){
                    getline(pFile, line);
                    storedP->history.insertProcedure(line);
                }
            } else {
                for(int i=0; i<n; i++) getline(pFile, line);
            }
        }
        pFile.close();
    }

    std::ifstream wFile(WAITLIST_FILE);
    if (wFile.is_open()) {
        while (getline(wFile, line)) {
            if(line.empty()) continue;
            int id = std::stoi(line);
            Patient* pPtr = pList->getPatientPtr(id);
            if (pPtr) {
                // Restaura na fila com a sequência original
                wList->addPatient(pPtr, pPtr->arrivalSequence);
            }
        }
        wFile.close();
    }
}