#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "arquivo.h"
#include "interface.h"

// Funcao principal
int main() {
    Livro* biblioteca = carregarLivros();
    int opcao;
    
    do {
        limparTela();
        printf("\n=== Sistema de Gerenciamento de Biblioteca ===\n");
        printf("1. Cadastro de livros\n");
        printf("2. Controle de emprestimos\n");
        printf("3. Ordenacao por diferentes criterios\n");
        printf("4. Busca avancada de obras\n");
        printf("5. Exibir todos os livros\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                biblioteca = cadastrarLivro(biblioteca);
                break;
            case 2:
                menuEmprestimos(biblioteca);
                break;
            case 3:
                biblioteca = menuOrdenacao(biblioteca);
                break;
            case 4:
                menuBusca(biblioteca);
                break;
            case 5:
                exibirLivros(biblioteca);
                break;
            case 0:
                limparTela();
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                continuarOperacao();
        }
    } while (opcao != 0);
    
    // Liberar memoria alocada
    liberarLivros(biblioteca);
    
    return 0;
}