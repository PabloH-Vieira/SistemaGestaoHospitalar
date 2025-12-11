#include "patient_list.h"
#include "prioritylist.h" // Alterado para usar a lista de prioridade correta
#include <cstdio>
#include "io.h"
#include <limits>

// Limpa buffer
void clean_stdin() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    PatientList patientList;
    PriorityList waitList; // Alterado de WaitList para PriorityList

    // Carrega os dados persistidos
    loadAll(&patientList, &waitList);

    int opcao = -1;
    while(opcao != 0){
        printf("\n=== PRONTO SOCORRO SUS V2 ===\n"
        "-------------------------------------\n"
        "1 - Registrar novo paciente (Triagem)\n"
        "2 - Registrar obito (Remover do Hospital)\n"
        "3 - Adicionar paciente a fila de espera\n"
        "4 - Adicionar procedimento ao historico\n"
        "5 - Desfazer procedimento do historico\n"
        "6 - Chamar paciente (Atendimento/Alta da Fila)\n"
        "7 - Mostrar fila de espera (Prioridade)\n"
        "8 - Mostrar historico do paciente\n"
        "9 - Salvar dados\n"
        "10 - Listar TODOS os pacientes (Arvore)\n"
        "0 - Sair\n"
        "-------------------------------------\n"
        "Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            clean_stdin();
        } else {
            clean_stdin();
        }

        switch (opcao) {
            case 1: { // Registrar paciente (Automático)
                char name[100];
                int priority;

                printf("Digite o nome do paciente: ");
                scanf("%99[^\n]", name);
                clean_stdin();

                printf("Digite a prioridade (1-Emergencia ... 5-Nao Urgente): ");
                scanf("%d", &priority);
                clean_stdin();

                if(priority < 1 || priority > 5) priority = 5;

                // ALTERAÇÃO AQUI: Captura o ID retornado
                int newID = patientList.addPatient(name, priority);

                if (newID > 0) {
                    printf("\nPaciente cadastrado com sucesso! ID Gerado: %d\n", newID);

                    // Busca o ponteiro usando o ID que acabamos de receber
                    Patient* pPtr = patientList.getPatientPtr(newID);

                    if (pPtr) {
                        // Insere automaticamente na fila
                        waitList.addPatient(pPtr);
                        printf("Paciente inserido automaticamente na fila de espera.\n");
                    } else {
                        printf("ERRO CRITICO: Paciente registrado mas ponteiro nao encontrado.\n");
                    }
                } else {
                    printf("Erro ao registrar paciente.\n");
                }
                break;
            }
            case 2: { // Registrar óbito (Remover)
                int id;
                printf("Digite o ID do paciente para remover: ");
                scanf("%d", &id);
                clean_stdin();

                // Verifica se está na fila de espera (Heap)
                if (waitList.search(id)) {
                    printf("ERRO: Paciente esta na fila de espera. Atenda-o (Opcao 6) antes de remover.\n");
                } else {
                    // Tenta remover da Árvore
                    if (patientList.removePatient(id)) {
                        printf("Paciente ID %d removido do sistema (obito/transferencia).\n", id);
                    } else {
                        printf("ERRO: Paciente nao encontrado.\n");
                    }
                }
                break;
            }
            case 3: { // Adicionar à fila manualmente
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                clean_stdin();

                // Busca ponteiro na Árvore
                Patient* pPtr = patientList.getPatientPtr(id);

                if (!pPtr) {
                    printf("ERRO: Paciente nao encontrado no cadastro.\n");
                    break;
                }

                if (waitList.search(id)) {
                    printf("ERRO: Paciente ja esta na fila.\n");
                } else {
                    waitList.addPatient(pPtr); // Passa o ponteiro
                    printf("Paciente '%s' readicionado a fila.\n", pPtr->name.c_str());
                }
                break;
            }
            case 4: { // Add procedimento
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                clean_stdin();

                Patient* pPtr = patientList.getPatientPtr(id);
                if (pPtr) {
                    if(pPtr->history.isFull()){
                        printf("ERRO: Historico cheio.\n");
                    } else {
                        char proc[101];
                        printf("Descricao do procedimento: ");
                        scanf("%100[^\n]", proc);
                        clean_stdin();
                        pPtr->history.insertProcedure(std::string(proc));
                        printf("Procedimento registrado.\n");
                    }
                } else {
                    printf("ERRO: Paciente nao encontrado.\n");
                }
                break;
            }
            case 5: { // Undo procedimento
                int id;
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                clean_stdin();

                Patient* pPtr = patientList.getPatientPtr(id);
                if (pPtr) {
                    if(pPtr->history.isEmpty()){
                        printf("Historico vazio.\n");
                    } else {
                        std::string desfeito = pPtr->history.undoProcedure();
                        printf("Desfeito: '%s'\n", desfeito.c_str());
                    }
                } else {
                    printf("ERRO: Paciente nao encontrado.\n");
                }
                break;
            }
            case 6: { // Chamar (Atender)
                Patient* chamado = waitList.removeHighestPriority();
                if (chamado) {
                    printf("\n*** ATENDIMENTO ***\n");
                    printf("Chamando: %s (ID: %d)\n", chamado->name.c_str(), chamado->id);
                    printf("Prioridade: %d\n", chamado->priority);
                    printf("Paciente retirado da fila de espera.\n");
                } else {
                    printf("A fila de espera esta vazia.\n");
                }
                break;
            }
            case 7: { // Mostrar fila
                waitList.printList();
                break;
            }
            case 8: { // Mostrar histórico
                int id;
                printf("Digite o ID: ");
                scanf("%d", &id);
                clean_stdin();
                patientList.printPatientHistory(id);
                break;
            }
            case 9: { // Salvar
                printf("Salvando dados em disco...\n");
                saveAll(&patientList, &waitList);
                printf("Concluido.\n");
                break;
            }
            case 10: { // Listar Todos (Novo requisito Projeto 2)
                patientList.listAllPatients();
                break;
            }
            case 0: { // Sair
                printf("Salvando e saindo...\n");
                saveAll(&patientList, &waitList);
                break;
            }
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
    return 0;
}