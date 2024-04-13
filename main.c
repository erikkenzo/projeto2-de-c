//Projeto 2 de C

//Erik Kenzo Hashizume RA- 24.223.001-9
//Gustavo Lima de Azevedo RA- 24.123.096.0
//Rafael Vianna Maistro RA-24223011-8


#include <stdio.h>
#include "tarefas.h" // Inclui o cabeçalho que contém as definições das funções e estruturas utilizadas

int main() {  
    // Array de ponteiros para funções que lidam com tarefas
    funcao *fs[] = {criar, deletar, listar, salvar, carregar, exportarTarefas};

    // Array de tarefas
    Tarefa tarefas[TOTAL];
    int pos = 0; // Variável para acompanhar a posição atual no array de tarefas

    // Carrega tarefas do arquivo
    ERROS erro = carregar(tarefas, &pos);
    if (erro == ABRIR) { // Se houve erro ao abrir o arquivo
        pos = 0; // Reinicia a posição das tarefas
        printf("Arquivo não encontrado\n");
    } else if (erro == LER || erro == FECHAR) { // Se houve erro ao ler ou fechar o arquivo
        printf("Arquivo vazio\n");
    }

    int opcao;
    do {
        // Menu principal
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para arquivo\n");
        printf("5 - Carregar tarefas do arquivo\n");
        printf("6 - Salvar tarefas em arquivo binário\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer(); // Limpa o buffer do teclado para evitar erros de entrada

        // Executa a opção escolhida pelo usuário
        if (opcao == 1) {
            fs[0](tarefas, &pos); // Chama a função para criar uma tarefa
        } else if (opcao == 2) {
            fs[1](tarefas, &pos); // Chama a função para deletar uma tarefa
        } else if (opcao == 3) {
            fs[2](tarefas, pos); // Chama a função para listar as tarefas
        } else if (opcao == 4) {
            fs[5](tarefas, &pos); // Chama a função para exportar as tarefas para arquivo
        } else if (opcao == 5) {
            erro = carregar(tarefas, &pos); // Chama a função para carregar tarefas do arquivo
            // Lida com os possíveis erros durante o carregamento
            if (erro == ABRIR)
                printf("Erro ao abrir o arquivo para leitura.\n");
            else if (erro == LER)
                printf("Erro ao ler o arquivo.\n");
            else if (erro == FECHAR)
                printf("Erro ao fechar o arquivo.\n");
            else
                printf("Tarefas carregadas com sucesso do arquivo.\n");
        } else if (opcao == 6) {
            erro = salvar(tarefas, &pos); // Chama a função para salvar tarefas em arquivo binário
            // Lida com os possíveis erros durante o salvamento
            if (erro == ABRIR)
                printf("Erro ao abrir o arquivo para escrita.\n");
            else if (erro == ESCREVER)
                printf("Erro ao escrever no arquivo.\n");
            else if (erro == FECHAR)
                printf("Erro ao fechar o arquivo.\n");
            else
                printf("Tarefas salvas com sucesso no arquivo.\n");
        } else if (opcao == 0) {
            printf("Sair...\n");
            break; // Sai do loop
        } else {
            printf("opção inválida\n");
        }
    } while (opcao != 0); // Repete até o usuário escolher a opção de sair

    return 0;
}

