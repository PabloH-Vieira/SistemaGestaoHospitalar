#include "patient_list.h"
#include "wait_list.h"
#include <cstdio>
#include "io.h"
#include <limits>



//Limpa buffer
void clean_stdin() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    PatientList patientList;
    WaitList waitList;

    loadAll(&patientList, &waitList);

    int opcao = 0;
    while(opcao != 9){
        printf("\nSISTEMA DE GESTAO HOSPITALAR\n"
        "-------------------------------------\n"
        "1 - Registrar novo paciente\n"
        "2 - Registrar obito de paciente\n"
        "3 - Adicionar paciente ja registrado a fila de espera\n"
        "4 - Adicionar procedimento ao historico medico\n"
        "5 - Desfazer procedimento do historico medico\n"
        "6 - Chamar paciente para atendimento\n"
        "7 - Mostrar fila de espera\n"
        "8 - Mostrar historico do paciente\n"
        "9 - Sair\n"
        "-------------------------------------\n"
        "Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // entrada inválida, reseta a opção
        }
        clean_stdin();

        switch (opcao) {
            case 1: { // registrar paciente
                char name[100];
                printf("Digite o nome do paciente: ");
                scanf("%99[^\n]", name);
                clean_stdin();

                patientList.addPatient(name);
                // colocar paciente na lista e na fila de espera
                waitList.addPatient(patientList.tail->patient);

                printf("Paciente '%s' (ID: %d) registrado e adicionado a fila de espera.\n", name, patientList.tail->patient.id);
                break;
            }
            case 2: { // registrar óbito de paciente
                int id;
                printf("Digite o ID do paciente que faleceu: ");
                scanf("%d", &id);
                clean_stdin();

                // paciente existe ?
                NodeList* pNode = nullptr;
                if (!patientList.searchPatient(id, pNode)) {
                    printf("ERRO: Paciente com ID %d nao encontrado no sistema.\n", id);
                    break;
                }


                // na fila ?
                if (waitList.searchPatient(id)) {
                    printf("ERRO: O paciente com ID %d ainda esta na fila de espera e nao pode morrer.\n", id);
                } else {
                    // Se não estiver na fila, pode morrer
                    if (patientList.removePatient(id)) {
                        printf("Registro do paciente com ID %d removido (obito).\n", id);
                    }
                }
                break;
            }
            case 3: { //adicionar paciente a fila de espera
                int id;
                printf("Digite o ID do paciente para readicionar a fila: ");
                scanf("%d", &id);
                clean_stdin();

                NodeList* pNode = nullptr;
                if (!patientList.searchPatient(id, pNode)) {
                    printf("ERRO: Paciente com ID %d nao encontrado no sistema.\n", id);
                    break;
                }

                if (waitList.searchPatient(id)) {
                    printf("ERRO: Paciente com ID %d ja esta na fila de espera.\n", id);
                } else {
                    waitList.addPatient(pNode->patient);
                    printf("Paciente '%s' (ID: %d) foi readicionado a fila de espera.\n", pNode->patient.get().c_str(), id);
                }
                break;
            }
            case 4: { // adicionar procedimento ao histórico médico
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                clean_stdin();

                NodeList* pNode = nullptr;
                if (patientList.searchPatient(id, pNode)) {
                    if(pNode->patient.history.isFull()){
                        printf("ERRO: O historico do paciente esta cheio (max 10).\n");
                        break;
                    }
                    char proc[101];
                    printf("Digite o procedimento (max 100 caracteres): ");
                    scanf("%100[^\n]", proc);
                    clean_stdin();

                    pNode->patient.history.insertProcedure(std::string(proc));
                    printf("Procedimento adicionado.\n");
                } else {
                    printf("ERRO: Paciente com ID %d nao encontrado.\n", id);
                }
                break;
            }
            case 5: { // desfazer procedimento do histórico médico
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                clean_stdin();

                NodeList* pNode = nullptr;
                if (patientList.searchPatient(id, pNode)) {
                    if(pNode->patient.history.isEmpty()){
                        printf("Nao ha procedimentos no historico para desfazer.\n");
                    } else {
                        std::string desfeito = pNode->patient.history.undoProcedure();
                        printf("Procedimento desfeito: '%s'\n", desfeito.c_str());
                    }
                } else {
                    printf("ERRO: Paciente com ID %d nao encontrado.\n", id);
                }
                break;
            }
            case 6: { // chamar paciente para atendimento
                if (waitList.empty()) {
                    printf("Fila de espera esta vazia.\n"); //
                } else {
                    // tirar o paciente da fila
                    Patient chamado = waitList.removePatient();
                    printf("Chamando para atendimento: Paciente '%s' (ID: %d)\n", chamado.get().c_str(), chamado.getID());
                }
                break;
            }
            case 7: { // mostrar fila de espera
                waitList.printWaitList();
                break;
            }
            case 8: { // mostrar histórico do paciente
                int id;
                printf("Digite o ID do paciente para ver o historico: ");
                scanf("%d", &id);
                clean_stdin();

                patientList.printPatientHistory(id);
                break;
            }
            case 9: { // sair
                printf("Salvando dados e encerrando o sistema...\n");
                saveAll(&patientList, &waitList);
                break;
            }
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}
