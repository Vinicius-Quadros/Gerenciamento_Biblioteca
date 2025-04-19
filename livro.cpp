#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include <ctype.h>

// Funcao para criar um novo livro
// Funcao para criar um novo livro (atualizada)
Livro* criarLivro(int id, char* titulo, char* autor, int ano, 
                 char* editora, char* categoria, char* isbn, 
                 int quantidade) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    if (novoLivro == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    
    novoLivro->id = id;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    strcpy(novoLivro->editora, editora);
    strcpy(novoLivro->categoria, categoria);
    strcpy(novoLivro->isbn, isbn);
    novoLivro->quantidade = quantidade;
    novoLivro->prox = NULL;
    novoLivro->ant = NULL;
    
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

// Função auxiliar para trocar dois nós em uma lista duplamente encadeada
void trocarNos(Livro** lista, Livro* a, Livro* b) {
    // Se os nós forem adjacentes
    if (a->prox == b) {
        // Ajustar ponteiros para trocar nós adjacentes
        a->prox = b->prox;
        b->prox = a;
        b->ant = a->ant;
        a->ant = b;
        
        if (a->prox)
            a->prox->ant = a;
        
        if (b->ant)
            b->ant->prox = b;
        else
            *lista = b; // Se b se tornar o primeiro nó
    }
    else if (b->prox == a) {
        // Caso b seja adjacente a a
        b->prox = a->prox;
        a->prox = b;
        a->ant = b->ant;
        b->ant = a;
        
        if (b->prox)
            b->prox->ant = b;
        
        if (a->ant)
            a->ant->prox = a;
        else
            *lista = a;
    }
    else {
        // Se não forem adjacentes
        Livro* tempAnt = a->ant;
        Livro* tempProx = a->prox;
        
        a->ant = b->ant;
        a->prox = b->prox;
        
        b->ant = tempAnt;
        b->prox = tempProx;
        
        if (a->ant)
            a->ant->prox = a;
        else
            *lista = a;
        
        if (a->prox)
            a->prox->ant = a;
        
        if (b->ant)
            b->ant->prox = b;
        else
            *lista = b;
        
        if (b->prox)
            b->prox->ant = b;
    }
}

// Função auxiliar para ordenação por bubble sort (algoritmo mais simples para listas ligadas)
Livro* bubbleSort(Livro* lista, int (*compara)(Livro*, Livro*, int), int parametro) {
    int trocou;
    Livro* ultimo = NULL;
    
    // Se a lista estiver vazia ou tiver apenas um elemento
    if (lista == NULL || lista->prox == NULL)
        return lista;
    
    // Obtém uma cópia da lista para manipulação
    Livro* head = obterPrimeiro(lista);
    
    do {
        trocou = 0;
        Livro* atual = head;
        
        while (atual->prox != ultimo) {
            if (compara(atual, atual->prox, parametro) > 0) {
                trocarNos(&head, atual, atual->prox);
                trocou = 1;
            } else {
                atual = atual->prox;
            }
        }
        ultimo = atual;
    } while (trocou);
    
    return head;
}

// Funções de comparação para cada critério
int comparaId(Livro* a, Livro* b, int crescente) {
    if (crescente)
        return a->id - b->id;
    else
        return b->id - a->id;
}

int comparaTitulo(Livro* a, Livro* b, int crescente) {
    int resultado = strcasecmp(a->titulo, b->titulo);
    return crescente ? resultado : -resultado;
}

int comparaAutor(Livro* a, Livro* b, int crescente) {
    int resultado = strcasecmp(a->autor, b->autor);
    return crescente ? resultado : -resultado;
}

int comparaAno(Livro* a, Livro* b, int crescente) {
    if (crescente)
        return a->ano - b->ano;
    else
        return b->ano - a->ano;
}

int comparaQuantidade(Livro* a, Livro* b, int crescente) {
    if (crescente)
        return a->quantidade - b->quantidade;
    else
        return b->quantidade - a->quantidade;
}

int comparaEditora(Livro* a, Livro* b, int crescente) {
    int resultado = strcasecmp(a->editora, b->editora);
    return crescente ? resultado : -resultado;
}

int comparaCategoria(Livro* a, Livro* b, int crescente) {
    int resultado = strcasecmp(a->categoria, b->categoria);
    return crescente ? resultado : -resultado;
}

int comparaISBN(Livro* a, Livro* b, int crescente) {
    int resultado = strcmp(a->isbn, b->isbn);
    return crescente ? resultado : -resultado;
}


// Implementação das funções de ordenação
Livro* ordenarPorId(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaId, crescente);
}

Livro* ordenarPorTitulo(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaTitulo, crescente);
}

Livro* ordenarPorAutor(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaAutor, crescente);
}

Livro* ordenarPorAno(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaAno, crescente);
}

Livro* ordenarPorQuantidade(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaQuantidade, crescente);
}

Livro* ordenarPorEditora(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaEditora, crescente);
}

Livro* ordenarPorCategoria(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaCategoria, crescente);
}

Livro* ordenarPorISBN(Livro* lista, int crescente) {
    return bubbleSort(lista, comparaISBN, crescente);
}

// Função para buscar por ID
Livro* buscarPorId(Livro* lista, int id) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (atual->id == id) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função auxiliar para verificar se uma string contém outra (ignorando maiúsculas/minúsculas)
int contemString(char* str, char* busca) {
    char strLower[256] = {0};
    char buscaLower[256] = {0};
    
    // Convertendo para minúsculas
    for (int i = 0; str[i] != '\0'; i++) {
        strLower[i] = tolower(str[i]);
    }
    
    for (int i = 0; busca[i] != '\0'; i++) {
        buscaLower[i] = tolower(busca[i]);
    }
    
    // Verifica se a string de busca está contida na string original
    return strstr(strLower, buscaLower) != NULL;
}

// Função para buscar por Título
Livro* buscarPorTitulo(Livro* lista, char* texto) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (contemString(atual->titulo, texto)) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função para buscar por Autor
Livro* buscarPorAutor(Livro* lista, char* texto) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (contemString(atual->autor, texto)) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função para buscar por Ano
Livro* buscarPorAno(Livro* lista, int ano) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (atual->ano == ano) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função para buscar por Editora
Livro* buscarPorEditora(Livro* lista, char* texto) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (contemString(atual->editora, texto)) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função para buscar por Categoria
Livro* buscarPorCategoria(Livro* lista, char* texto) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (contemString(atual->categoria, texto)) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}

// Função para buscar por ISBN
Livro* buscarPorISBN(Livro* lista, char* texto) {
    Livro* resultado = NULL;
    Livro* atual = obterPrimeiro(lista);
    
    while (atual != NULL) {
        if (contemString(atual->isbn, texto)) {
            // Cria uma cópia do livro encontrado
            Livro* copiaLivro = criarLivro(atual->id, atual->titulo, atual->autor, atual->ano, 
                                          atual->editora, atual->categoria, atual->isbn, 
                                          atual->quantidade);
            resultado = adicionarLivro(resultado, copiaLivro);
        }
        atual = atual->prox;
    }
    
    return resultado;
}
