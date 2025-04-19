#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include "livro.h"
#include <time.h>

// Definição da estrutura de empréstimo (duplamente encadeada)
typedef struct Emprestimo {
    int id;                 // ID do empréstimo
    int idLivro;            // ID do livro emprestado
    char nomeLivro[100];    // Nome do livro (para facilitar a exibição)
    char nomePessoa[100];   // Nome da pessoa que pegou emprestado
    char telefone[20];      // Telefone da pessoa
    time_t dataEmprestimo;  // Data do empréstimo (timestamp)
    time_t dataDevolucao;   // Data prevista para devolução (timestamp)
    struct Emprestimo* prox;
    struct Emprestimo* ant;
} Emprestimo;

// Funções para manipulação de empréstimos
Emprestimo* criarEmprestimo(int id, int idLivro, char* nomeLivro, char* nomePessoa, 
                           char* telefone, time_t dataEmprestimo, time_t dataDevolucao);
Emprestimo* adicionarEmprestimo(Emprestimo* lista, Emprestimo* novoEmprestimo);
void liberarEmprestimos(Emprestimo* lista);

// Funções para navegação bidirecional
Emprestimo* obterPrimeiroEmprestimo(Emprestimo* lista);
Emprestimo* obterUltimoEmprestimo(Emprestimo* lista);

// Funções para carregar e salvar empréstimos
Emprestimo* carregarEmprestimos();
void salvarEmprestimos(Emprestimo* lista);

// Funções de utilidade para data
char* formatarData(time_t timestamp, char* buffer);
time_t obterDataAtual();
time_t calcularDataDevolucao(time_t dataEmprestimo, int diasEmprestimo);

#endif