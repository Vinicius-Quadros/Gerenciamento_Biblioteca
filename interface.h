#ifndef INTERFACE_H
#define INTERFACE_H

#include "livro.h"
#include "emprestimo.h"

// Funções de Interface Geral
void limparTela();
void pausar();
int continuarOperacao();

// Cadastro e Exibição de Livros
Livro* cadastrarLivro(Livro* lista);
void exibirLivros(Livro* lista, Emprestimo* listaEmprestimos);

// Operações de Empréstimo
Emprestimo* menuEmprestimos(Livro* listaLivros, Emprestimo* listaEmprestimos);
void registrarDevolucao(Livro* listaLivros, Emprestimo** listaEmprestimos);

// Ordenação e Busca
Livro* menuOrdenacao(Livro* lista);
void menuBusca(Livro* lista);
int exibirResultadoBusca(Livro* lista, char* criterioBusca, char* textoBusca);

// Remoção de Livro
void removerLivro(Livro** listaLivros, Emprestimo* listaEmprestimos);

#endif