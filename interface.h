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
void menuOrdenacao(Livro* lista);
void menuBusca(Livro* lista);

#endif