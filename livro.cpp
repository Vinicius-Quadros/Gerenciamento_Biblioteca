#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

// Funcao para criar um novo livro
Livro* criarLivro(int id, char* titulo, char* autor, int ano, char emprestimo) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    if (novoLivro == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    
    novoLivro->id = id;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    novoLivro->emprestimo = emprestimo;
    novoLivro->prox = NULL;
    novoLivro->ant = NULL; // Inicializa ponteiro anterior como NULL
    
    return novoLivro;
}

// Funcao para adicionar um livro a lista (agora duplamente encadeada)
Livro* adicionarLivro(Livro* lista, Livro* novoLivro) {
    // Se a lista estiver vazia
    if (lista == NULL) {
        return novoLivro;
    }
    
    // Adiciona no final da lista
    Livro* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    atual->prox = novoLivro;
    novoLivro->ant = atual; // Liga o novo livro ao anterior
    
    return lista;
}

// Funcao para liberar memoria da lista de livros
void liberarLivros(Livro* lista) {
    Livro* atual = lista;
    while (atual != NULL) {
        Livro* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

// Função para obter o primeiro livro da lista
Livro* obterPrimeiro(Livro* lista) {
    if (lista == NULL) {
        return NULL;
    }
    
    Livro* atual = lista;
    while (atual->ant != NULL) {
        atual = atual->ant;
    }
    
    return atual;
}

// Função para obter o último livro da lista
Livro* obterUltimo(Livro* lista) {
    if (lista == NULL) {
        return NULL;
    }
    
    Livro* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    return atual;
}