#ifndef LIVRO_H
#define LIVRO_H

// Definicao da estrutura do livro (agora sem o campo emprestimo)
typedef struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char editora[100];
    char categoria[50];
    char isbn[20];
    int quantidade;
    struct Livro* prox;
    struct Livro* ant;
} Livro;

// Funcoes para manipulacao de livros
Livro* criarLivro(int id, char* titulo, char* autor, int ano, 
                 char* editora, char* categoria, char* isbn, 
                 int quantidade);
Livro* adicionarLivro(Livro* lista, Livro* novoLivro);
void liberarLivros(Livro* lista);

// Funções para navegação bidirecional
Livro* obterPrimeiro(Livro* lista);
Livro* obterUltimo(Livro* lista);

// Funções para ordenação (removida a ordenação por empréstimo)
Livro* ordenarPorId(Livro* lista, int crescente);
Livro* ordenarPorTitulo(Livro* lista, int crescente);
Livro* ordenarPorAutor(Livro* lista, int crescente);
Livro* ordenarPorAno(Livro* lista, int crescente);
Livro* ordenarPorEditora(Livro* lista, int crescente);
Livro* ordenarPorCategoria(Livro* lista, int crescente);
Livro* ordenarPorISBN(Livro* lista, int crescente);
Livro* ordenarPorQuantidade(Livro* lista, int crescente);


// Funções para Busca 
Livro* buscarPorId(Livro* lista, int id);
Livro* buscarPorTitulo(Livro* lista, char* texto);
Livro* buscarPorAutor(Livro* lista, char* texto);
Livro* buscarPorAno(Livro* lista, int ano);
Livro* buscarPorEditora(Livro* lista, char* texto);
Livro* buscarPorCategoria(Livro* lista, char* texto);
Livro* buscarPorISBN(Livro* lista, char* texto);
#endif