#ifndef LIVRO_H
#define LIVRO_H

// Definicao da estrutura do livro (agora duplamente encadeada)
typedef struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char emprestimo;
    struct Livro* prox; // Ponteiro para o próximo
    struct Livro* ant;  // Ponteiro para o anterior
} Livro;

// Funcoes para manipulacao de livros
Livro* criarLivro(int id, char* titulo, char* autor, int ano, char emprestimo);
Livro* adicionarLivro(Livro* lista, Livro* novoLivro);
void liberarLivros(Livro* lista);

// Novas funções para navegação bidirecional
Livro* obterPrimeiro(Livro* lista);
Livro* obterUltimo(Livro* lista);

#endif