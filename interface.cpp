#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "livro.h"
#include "arquivo.h"

// Funcao para limpar a tela (compativel com Windows e sistemas Unix)
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Funcao para pausar e perguntar se deseja continuar
int continuarOperacao() {
    char resposta;
    printf("\nDeseja continuar? (s/n): ");
    scanf(" %c", &resposta);
    return (resposta == 's' || resposta == 'S');
}

// Funcao para cadastrar um novo livro
Livro* cadastrarLivro(Livro* lista) {
    limparTela();
    
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char emprestimo;
    int continuar = 1;
    
    while (continuar) {
        // Gerar ID automatico
        id = 1;
        Livro* atual = lista;
        while (atual != NULL) {
            if (atual->id >= id) {
                id = atual->id + 1;
            }
            atual = atual->prox;
        }
        
        // Obter dados do livro
        printf("\n=== Cadastro de Livro ===\n");
		        
        printf("Titulo: ");
        getchar(); // Limpar o buffer do teclado
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = '\0'; // Remover a quebra de linha
        
        printf("Autor: ");
        fgets(autor, sizeof(autor), stdin);
        autor[strcspn(autor, "\n")] = '\0'; // Remover a quebra de linha
        
        printf("Ano: ");
        scanf("%d", &ano);
        
        printf("Emprestado (s/n): ");
        getchar(); // Limpar o buffer do teclado
        scanf("%c", &emprestimo);
        
        // Criar e adicionar o livro
        Livro* novoLivro = criarLivro(id, titulo, autor, ano, emprestimo);
        lista = adicionarLivro(lista, novoLivro);
        
        printf("\nLivro cadastrado com sucesso!\n");
        
        // Salvar imediatamente
        salvarLivros(lista);
        
        // Perguntar se deseja cadastrar outro livro
        continuar = continuarOperacao();
        if (continuar) {
            limparTela();
        }
    }
    
    return lista;
}

// Funcao para pausar e aguardar um Enter
// Funcao para pausar e aguardar um Enter
void pausar() {
    printf("\nPressione Enter para retornar...");
    getchar(); // Limpar qualquer caractere pendente
    getchar(); // Aguardar o Enter
}

// Funcao para exibir todos os livros (com navegação bidirecional)
void exibirLivros(Livro* lista) {
    limparTela();
    
    if (lista == NULL) {
        printf("\nNenhum livro cadastrado!\n");
        pausar();
        return;
    }
    
    // Obtém o primeiro livro da lista
    Livro* atual = obterPrimeiro(lista);
    int pagina = 1;
    int livrosPorPagina = 5; // Número de livros exibidos por página
    char opcao;
    
    // Contar total de livros para determinar o número de páginas
    int totalLivros = 0;
    Livro* contador = atual;
    while (contador != NULL) {
        totalLivros++;
        contador = contador->prox;
    }
    
    int totalPaginas = (totalLivros + livrosPorPagina - 1) / livrosPorPagina; // Arredonda para cima
    
    do {
        limparTela();
        printf("\n=== Livros Cadastrados (Pagina %d de %d) ===\n", pagina, totalPaginas);
        printf("ID  | Titulo                         | Autor                          | Ano  | Emprestado\n");
        printf("----+--------------------------------+--------------------------------+------+-----------\n");
        
        // Exibe os livros da página atual
        int contador = 0;
        Livro* paginaAtual = atual;
        
        while (paginaAtual != NULL && contador < livrosPorPagina) {
            printf("%-3d | %-30s | %-30s | %-4d | %c\n", 
                   paginaAtual->id, paginaAtual->titulo, paginaAtual->autor, 
                   paginaAtual->ano, paginaAtual->emprestimo);
            
            paginaAtual = paginaAtual->prox;
            contador++;
        }
        
        // Verificar se estamos na primeira ou última página para mostrar orientações apropriadas
        if (pagina == 1 && pagina == totalPaginas) {
            printf("\nNavegacao: [S] Sair\n");
        } else if (pagina == 1) {
            printf("\nNavegacao: [P] Proximo | [S] Sair\n");
        } else if (pagina == totalPaginas) {
            printf("\nNavegacao: [A] Anterior | [S] Sair\n");
        } else {
            printf("\nNavegacao: [A] Anterior | [P] Proximo | [S] Sair\n");
        }
        
        printf("Opcao: ");
        scanf(" %c", &opcao);
        
        switch(opcao) {
            case 'P':
            case 'p':
                // Avança para a próxima página apenas se não estiver na última
                if (pagina < totalPaginas) {
                    for (int i = 0; i < livrosPorPagina && atual != NULL; i++) {
                        if (atual->prox != NULL) {
                            atual = atual->prox;
                        }
                    }
                    pagina++;
                }
                break;
            
            case 'A':
            case 'a':
                // Volta para a página anterior apenas se não estiver na primeira
                if (pagina > 1) {
                    for (int i = 0; i < livrosPorPagina && atual != NULL; i++) {
                        if (atual->ant != NULL) {
                            atual = atual->ant;
                        }
                    }
                    pagina--;
                }
                break;
                
            case 'S':
            case 's':
                return;
                
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
        
    } while (1); // Loop infinito, sai apenas com a opção 'S'
}

// Funcao para o menu de emprestimos (a ser implementado)
void menuEmprestimos(Livro* lista) {
    limparTela();
    printf("\n=== Controle de Emprestimos ===\n");
    printf("Funcionalidade em desenvolvimento.\n");
    continuarOperacao();
}

// Funcao para o menu de ordenacao (a ser implementado)
void menuOrdenacao(Livro* lista) {
    limparTela();
    printf("\n=== Ordenacao de Livros ===\n");
    printf("Funcionalidade em desenvolvimento.\n");
    continuarOperacao();
}

// Funcao para o menu de busca (a ser implementado)
void menuBusca(Livro* lista) {
    limparTela();
    printf("\n=== Busca Avancada ===\n");
    printf("Funcionalidade em desenvolvimento.\n");
    continuarOperacao();
}
