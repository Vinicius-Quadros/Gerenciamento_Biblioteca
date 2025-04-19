#ifndef INTERFACE_H
#define INTERFACE_H

#include "livro.h"

// Funcoes de interface
void limparTela();
void pausar();
int continuarOperacao();
Livro* cadastrarLivro(Livro* lista);
void exibirLivros(Livro* lista);
void menuEmprestimos(Livro* lista);
Livro* menuOrdenacao(Livro* lista);
void menuBusca(Livro* lista);
int exibirResultadoBusca(Livro* lista, char* criterioBusca, char* textoBusca);

#endif