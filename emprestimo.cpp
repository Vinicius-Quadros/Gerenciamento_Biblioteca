#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emprestimo.h"

// Função para criar um novo empréstimo
Emprestimo* criarEmprestimo(int id, int idLivro, char* nomeLivro, char* nomePessoa, 
                           char* telefone, time_t dataEmprestimo, time_t dataDevolucao) {
    Emprestimo* novoEmprestimo = (Emprestimo*)malloc(sizeof(Emprestimo));
    if (novoEmprestimo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    
    novoEmprestimo->id = id;
    novoEmprestimo->idLivro = idLivro;
    strcpy(novoEmprestimo->nomeLivro, nomeLivro);
    strcpy(novoEmprestimo->nomePessoa, nomePessoa);
    strcpy(novoEmprestimo->telefone, telefone);
    novoEmprestimo->dataEmprestimo = dataEmprestimo;
    novoEmprestimo->dataDevolucao = dataDevolucao;
    novoEmprestimo->prox = NULL;
    novoEmprestimo->ant = NULL;
    
    return novoEmprestimo;
}

// Função para adicionar um empréstimo à lista
Emprestimo* adicionarEmprestimo(Emprestimo* lista, Emprestimo* novoEmprestimo) {
    // Se a lista estiver vazia
    if (lista == NULL) {
        return novoEmprestimo;
    }
    
    // Adiciona no final da lista
    Emprestimo* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    atual->prox = novoEmprestimo;
    novoEmprestimo->ant = atual;
    
    return lista;
}

// Função para liberar memória da lista de empréstimos
void liberarEmprestimos(Emprestimo* lista) {
    Emprestimo* atual = lista;
    while (atual != NULL) {
        Emprestimo* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

// Função para obter o primeiro empréstimo da lista
Emprestimo* obterPrimeiroEmprestimo(Emprestimo* lista) {
    if (lista == NULL) {
        return NULL;
    }
    
    Emprestimo* atual = lista;
    while (atual->ant != NULL) {
        atual = atual->ant;
    }
    
    return atual;
}

// Função para obter o último empréstimo da lista
Emprestimo* obterUltimoEmprestimo(Emprestimo* lista) {
    if (lista == NULL) {
        return NULL;
    }
    
    Emprestimo* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    return atual;
}

// Função para formatar uma data a partir de um timestamp
char* formatarData(time_t timestamp, char* buffer) {
    struct tm* timeinfo = localtime(&timestamp);
    strftime(buffer, 20, "%d/%m/%Y", timeinfo);
    return buffer;
}

// Função para obter a data atual
time_t obterDataAtual() {
    return time(NULL);
}

// Função para calcular a data de devolução (padrão: 14 dias)
time_t calcularDataDevolucao(time_t dataEmprestimo, int diasEmprestimo) {
    return dataEmprestimo + (diasEmprestimo * 24 * 60 * 60); // dias * horas * minutos * segundos
}

// Função para carregar empréstimos do arquivo
Emprestimo* carregarEmprestimos() {
    FILE* arquivo = fopen("emprestimo_livro.txt", "r");
    if (arquivo == NULL) {
        return NULL; // Arquivo não existe
    }
    
    Emprestimo* lista = NULL;
    int id;
    int idLivro;
    char nomeLivro[100];
    char nomePessoa[100];
    char telefone[20];
    char dataEmprestimoStr[20];
    char dataDevolucaoStr[20];
    
    while (fscanf(arquivo, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n", 
                 &id, &idLivro, nomeLivro, nomePessoa, telefone, 
                 dataEmprestimoStr, dataDevolucaoStr) == 7) {
        
        // Converter as datas de string para timestamp
        struct tm tmEmprestimo = {0};
        struct tm tmDevolucao = {0};
        
        // Formato no arquivo: DD/MM/AAAA
        sscanf(dataEmprestimoStr, "%d/%d/%d", 
               &tmEmprestimo.tm_mday, &tmEmprestimo.tm_mon, &tmEmprestimo.tm_year);
        sscanf(dataDevolucaoStr, "%d/%d/%d", 
               &tmDevolucao.tm_mday, &tmDevolucao.tm_mon, &tmDevolucao.tm_year);
        
        // Ajustes necessários: mês começa em 0, ano é relativo a 1900
        tmEmprestimo.tm_mon -= 1;
        tmEmprestimo.tm_year -= 1900;
        tmDevolucao.tm_mon -= 1;
        tmDevolucao.tm_year -= 1900;
        
        time_t dataEmprestimo = mktime(&tmEmprestimo);
        time_t dataDevolucao = mktime(&tmDevolucao);
        
        Emprestimo* novoEmprestimo = criarEmprestimo(id, idLivro, nomeLivro, nomePessoa, 
                                                   telefone, dataEmprestimo, dataDevolucao);
        lista = adicionarEmprestimo(lista, novoEmprestimo);
    }
    
    fclose(arquivo);
    return lista;
}

// Função para salvar empréstimos no arquivo
void salvarEmprestimos(Emprestimo* lista) {
    FILE* arquivo = fopen("emprestimo_livro.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    
    Emprestimo* atual = lista;
    while (atual != NULL) {
        char dataEmprestimoStr[20];
        char dataDevolucaoStr[20];
        
        formatarData(atual->dataEmprestimo, dataEmprestimoStr);
        formatarData(atual->dataDevolucao, dataDevolucaoStr);
        
        fprintf(arquivo, "%d,%d,%s,%s,%s,%s,%s\n", 
                atual->id, atual->idLivro, atual->nomeLivro, atual->nomePessoa, 
                atual->telefone, dataEmprestimoStr, dataDevolucaoStr);
        
        atual = atual->prox;
    }
    
    fclose(arquivo);
    printf("Dados de emprestimos salvos com sucesso!\n");
}