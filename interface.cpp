#include "patient_list.h"
#include "wait_list.h"
#include <cstdio>

int main(){
    PatientList patientList;
    //WaitList WaitList;

    printf("\nSISTEMA HIGIA DE GESTAO HOSPITALAR\n"
           "\nSelecione uma das opcoes abaixo:\n"
           "-------------------------------------\n"
           "1 - Registrar paciente\n"
           "2 - Registrar obito\n"
           "3 - Adicionar procedimento do historico medico\n"
           "4 - Remover procedimento do historico medico\n"
           "5 - Chamar para atendimento\n"
           "6 - Exibir fila de espera\n"
           "7 - Exibir historico\n");

    int opcao;
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            char name[100];
            printf("Digite o nome do paciente: ");
            scanf("%s", name);
            patientList.addPatient(name);
            printf("Paciente cadastrado com sucesso!\n\n");
            break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;

    }
    return true;
}