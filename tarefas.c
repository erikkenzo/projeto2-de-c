#include "tarefas.h" // Inclui o cabeçalho que contém as definições das funções e estruturas utilizadas
#include <stdio.h>
#include <string.h>

// Função auxiliar para remover a quebra de linha de uma string
void tira_quebra_linha(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função auxiliar para limpar o buffer do teclado
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

// Função para criar uma nova tarefa
ERROS criar(Tarefa tarefas[], int *pos) {
    // Verifica se há espaço disponível para criar uma nova tarefa
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    // Solicita informações da tarefa ao usuário
    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
        printf("Prioridade inválida, o limite é entre 1 e 10. Tente novamente!\n");
        return OK; // Retorna OK aqui para indicar que a tarefa não foi criada devido à prioridade inválida
    }

    clearBuffer(); // Limpa o buffer do teclado para evitar problemas de entrada

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);
    tira_quebra_linha(tarefas[*pos].categoria);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);
    tira_quebra_linha(tarefas[*pos].descricao);

    *pos = *pos + 1; // Atualiza a posição para a próxima tarefa

    return OK;
}

// Função para deletar uma tarefa
ERROS deletar(Tarefa tarefas[], int *pos) {
    // Verifica se há tarefas para deletar
    if (*pos == 0)
        return SEM_TAREFAS;

    // Solicita a posição da tarefa a ser deletada
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // Ajusta a posição para corresponder ao índice no array
    if (pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    // Remove a tarefa e ajusta as posições das tarefas restantes
    for (int i = pos_deletar; i < *pos - 1; i++) {
        tarefas[i].prioridade = tarefas[i + 1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
        strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
    }

    *pos = *pos - 1; // Atualiza a posição para refletir a exclusão da tarefa

    return OK;
}

// Função para listar tarefas
ERROS listar(Tarefa tarefas[], int pos) {
    if (pos == 0)
        return SEM_TAREFAS;

    char categoria[100];
    printf("Entre com a categoria das tarefas que deseja listar (ou deixe vazio para listar todas as tarefas: ");
    fgets(categoria, 100, stdin);
    tira_quebra_linha(categoria);

    int encontradas = 0;
    // Itera sobre as tarefas e as imprime se correspondem à categoria especificada
    for (int i = 0; i < pos; i++) {
        if (categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Posição da tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
            encontradas++;
        }
    }

    if (encontradas == 0)
        printf("Nenhuma tarefa encontrada com a categoria especificada.\n");

    return OK;
}

// Função para salvar as tarefas em um arquivo binário
ERROS salvar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "wb");
    if (f == NULL)
        return ABRIR;

    // Escreve as tarefas no arquivo
    int qtd = fwrite(tarefas, *pos, sizeof(Tarefa), f);
    if (qtd != *pos)
        return ESCREVER;

    // Escreve a posição atual no arquivo
    qtd = fwrite(pos, sizeof(int), 1, f);
    if (qtd != 1)
        return ESCREVER;

    if (fclose(f) != 0)
        return FECHAR;

    return OK;
}

// Função para carregar as tarefas de um arquivo binário
ERROS carregar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "rb");
    if (f == NULL)
        return ABRIR;

    // Lê as tarefas do arquivo
    int qtd = fread(tarefas, *pos, sizeof(Tarefa), f);
    if (qtd == 0)
        return LER;

    // Lê a posição atual do arquivo
    qtd = fread(pos, sizeof(int), 1, f);
    if (qtd != 1)
        return LER;

    if (fclose(f) != 0)
        return FECHAR;

    return OK;
}

// Função para exportar as tarefas para um arquivo de texto
ERROS exportarTarefas(Tarefa tarefas[], int *pos) {
    printf("Entre com o nome do arquivo para exportacao: ");
    char nomeArquivo[100];
    scanf("%s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return ABRIR;
    }

    // Escreve as tarefas no arquivo de texto
    for (int i = 0; i < *pos; i++) {
        fprintf(arquivo, "Posição da tarefa: %d\n", i + 1);
        fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(arquivo, "Categoria: %s\n", tarefas[i].categoria);
        fprintf(arquivo, "Descrição: %s\n\n", tarefas[i].descricao);
    }

    fclose(arquivo);
    printf("Tarefas exportadas com sucesso para o arquivo: %s\n", nomeArquivo);
    return OK;
}
