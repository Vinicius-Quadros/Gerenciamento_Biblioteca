#ifndef INTERFACE_H
#define INTERFACE_H

#include "livro.h"
#include "emprestimo.h"

// Funcoes de interface
void limparTela();
void pausar();
int continuarOperacao();
Livro* cadastrarLivro(Livro* lista);
void exibirLivros(Livro* lista, Emprestimo* listaEmprestimos);
Emprestimo* menuEmprestimos(Livro* listaLivros, Emprestimo* listaEmprestimos);
Livro* menuOrdenacao(Livro* lista);
void menuBusca(Livro* lista);
int exibirResultadoBusca(Livro* lista, char* criterioBusca, char* textoBusca);
void registrarDevolucao(Livro* listaLivros, Emprestimo** listaEmprestimos);
#endif