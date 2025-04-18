#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "livro.h"

// Funcao para carregar livros do arquivo
Livro* carregarLivros() {
    FILE* arquivo = fopen("biblioteca.txt", "r");
    if (arquivo == NULL) {
        return NULL; // Arquivo nao existe
    }
    
    Livro* lista = NULL;
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char emprestimo;
    
    while (fscanf(arquivo, "%d,%[^,],%[^,],%d,%c\n", &id, titulo, autor, &ano, &emprestimo) == 5) {
        Livro* novoLivro = criarLivro(id, titulo, autor, ano, emprestimo);
        lista = adicionarLivro(lista, novoLivro);
    }
    
    fclose(arquivo);
    return lista;
}

// Funcao para salvar livros no arquivo
void salvarLivros(Livro* lista) {
    FILE* arquivo = fopen("biblioteca.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    
    Livro* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%s,%d,%c\n", 
                atual->id, atual->titulo, atual->autor, atual->ano, atual->emprestimo);
        atual = atual->prox;
    }
    
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}