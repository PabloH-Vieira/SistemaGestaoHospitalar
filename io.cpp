#include "io.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define PATIENT_FILE "patients.dat"
#define WAITLIST_FILE "waitlist.dat"

// ao sair do programa armazena tudo
void saveAll(PatientList* pList, WaitList* wList) {
    std::ofstream patientFile(PATIENT_FILE);
    if (patientFile.is_open()) {
        NodeList* current = pList->head;
        while (current != nullptr) {
            patientFile << current->patient.id << std::endl;
            patientFile << current->patient.name << std::endl;

            NodeH* historyNode = current->patient.history.top;
            patientFile << current->patient.history.cont_procedures << std::endl;

            std::vector<std::string> procedures;
            while(historyNode != nullptr){
                procedures.push_back(historyNode->procedure);
                historyNode = historyNode->next;
            }
            // salva ao contrario pra recarregar na ordem certa
            std::reverse(procedures.begin(), procedures.end());
            for(const auto& proc : procedures){
                patientFile << proc << std::endl;
            }
            current = current->next;
        }
        patientFile.close();
    }

    // salva os id's da lista de espera
    std::ofstream waitListFile(WAITLIST_FILE);
    if (waitListFile.is_open()) {
        NodeHeap* current = wList->head;
        while (current != nullptr) {
            waitListFile << current->patient.id << std::endl;
            current = current->next;
        }
        waitListFile.close();
    }
}

// recarrega ao abrir o programa
void loadAll(PatientList* pList, WaitList* wList) {
    std::ifstream patientFile(PATIENT_FILE);
    std::string line;
    if (patientFile.is_open()) {
        while (getline(patientFile, line)) {
            Patient p;
            p.id = std::stoi(line);
            getline(patientFile, p.name);

            getline(patientFile, line);
            int numProcedures = std::stoi(line);
            for (int i = 0; i < numProcedures; ++i) {
                getline(patientFile, line);
                p.history.insertProcedure(line);
            }

            NodeList* newNode = new NodeList();
            newNode->patient = p;
            if(pList->isEmpty()){
                pList->head = newNode;
                pList->tail = newNode;
            } else {
                pList->tail->next = newNode;
                newNode->prev = pList->tail;
                pList->tail = newNode;
            }
            pList->qtd++;
        }
        patientFile.close();
    }

    // recarrega a fila de espera
    std::ifstream waitListFile(WAITLIST_FILE);
    if (waitListFile.is_open()) {
        while (getline(waitListFile, line)) {
            int id = std::stoi(line);
            NodeList* pNode = nullptr;
            if (pList->searchPatient(id, pNode)) {
                wList->addPatient(pNode->patient);
            }
        }
        waitListFile.close();
    }
}
