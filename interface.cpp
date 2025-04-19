#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "livro.h"
#include "emprestimo.h"
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

// Funcao para cadastrar um novo livro (atualizada)
Livro* cadastrarLivro(Livro* lista) {
    limparTela();
    
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char editora[100];
    char categoria[50];
    char isbn[20];
    int quantidade;
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
        printf("ID: %d (gerado automaticamente)\n", id);
        
        printf("Titulo: ");
        getchar(); // Limpar o buffer do teclado
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = '\0'; // Remover a quebra de linha
        
        printf("Autor: ");
        fgets(autor, sizeof(autor), stdin);
        autor[strcspn(autor, "\n")] = '\0'; // Remover a quebra de linha
        
        printf("Ano: ");
        scanf("%d", &ano);
        getchar(); // Limpar o buffer
        
        printf("Editora: ");
        fgets(editora, sizeof(editora), stdin);
        editora[strcspn(editora, "\n")] = '\0';
        
        printf("Categoria: ");
        fgets(categoria, sizeof(categoria), stdin);
        categoria[strcspn(categoria, "\n")] = '\0';
        
        printf("ISBN: ");
        fgets(isbn, sizeof(isbn), stdin);
        isbn[strcspn(isbn, "\n")] = '\0';
        
        printf("Quantidade disponivel: ");
        scanf("%d", &quantidade);
        
        // Criar e adicionar o livro
        Livro* novoLivro = criarLivro(id, titulo, autor, ano, editora, categoria, isbn, quantidade);
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
void pausar() {
    printf("\nPressione Enter para retornar...");
    getchar(); // Limpar qualquer caractere pendente
    getchar(); // Aguardar o Enter
}

// Funcao para exibir todos os livros (com navegação bidirecional)
void exibirLivros(Livro* lista, Emprestimo* listaEmprestimos) {
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
        printf("ID    | Titulo                      | Autor                       | Ano    | Editora                     | Categoria             | ISBN               | Qtd | Emprestados\n");
        printf("------+-----------------------------+-----------------------------+--------+-----------------------------+----------------------+--------------------+-----+------------\n");
        
        // Exibe os livros da página atual
        int contador = 0;
        Livro* paginaAtual = atual;
        
        while (paginaAtual != NULL && contador < livrosPorPagina) {
            // Contar quantos exemplares deste livro estão emprestados
            int emprestados = 0;
            Emprestimo* empAtual = listaEmprestimos;
            while (empAtual != NULL) {
                if (empAtual->idLivro == paginaAtual->id) {
                    emprestados++;
                }
                empAtual = empAtual->prox;
            }
            
            printf("%-5d | %-28s | %-28s | %-7d | %-28s | %-21s | %-19s | %-4d | %-11d\n", 
                   paginaAtual->id, paginaAtual->titulo, paginaAtual->autor, 
                   paginaAtual->ano, paginaAtual->editora, paginaAtual->categoria,
                   paginaAtual->isbn, paginaAtual->quantidade, emprestados);
            
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

// Funcao para o menu de ordenacao
Livro* menuOrdenacao(Livro* lista) {
    if (lista == NULL) {
        limparTela();
        printf("\nNenhum livro cadastrado para ordenar!\n");
        pausar();
        return lista;
    }
    
    int opcao;
    int subOpcao;
    Livro* listaOrdenada = lista;
    
    limparTela();
    printf("\n=== Ordenacao de Livros ===\n");
    printf("1. Ordenar por ID\n");
    printf("2. Ordenar por Titulo\n");
    printf("3. Ordenar por Autor\n");
    printf("4. Ordenar por Ano\n");
    printf("5. Ordenar por Editora\n");
    printf("6. Ordenar por Categoria\n");
    printf("7. Ordenar por ISBN\n");
    printf("8. Ordenar por Quantidade\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    switch (opcao) {
        case 1:
            printf("\nOrdem: 1-Crescente | 2-Decrescente: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorId(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por ID (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 2:
            printf("\nOrdem: 1-Alfabetica crescente | 2-Alfabetica decrescente: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorTitulo(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Titulo (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 3:
            printf("\nOrdem: 1-Alfabetica crescente | 2-Alfabetica decrescente: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorAutor(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Autor (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 4:
            printf("\nOrdem: 1-Do menor para o maior | 2-Do maior para o menor: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorAno(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Ano (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 5:
            printf("\nOrdem: 1-Alfabetica crescente | 2-Alfabetica decrescente: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorEditora(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Editora (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 6:
            printf("\nOrdem: 1-Alfabetica crescente | 2-Alfabetica decrescente: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorCategoria(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Categoria (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 7:
            printf("\nOrdem: 1-Do menor para o maior | 2-Do maior para o menor: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorISBN(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por ISBN (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 8:
            printf("\nOrdem: 1-Do menor para o maior | 2-Do maior para o menor: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1 || subOpcao == 2) {
                listaOrdenada = ordenarPorQuantidade(lista, subOpcao == 1);
                lista = listaOrdenada; // Atualiza a lista original
                printf("\nLivros ordenados por Quantidade (%s).\n", 
                       (subOpcao == 1) ? "crescente" : "decrescente");
                pausar();
            } else {
                printf("\nOpcao invalida!\n");
                pausar();
            }
            break;
            
        case 0:
            return lista;
            
        default:
            printf("\nOpcao invalida!\n");
            pausar();
    }
    
    return lista;
}

// Função para exibir o resultado da busca
int exibirResultadoBusca(Livro* lista, char* criterioBusca, char* textoBusca) {
    limparTela();
    
    if (lista == NULL) {
        printf("\nNenhum livro encontrado para a busca: '%s' em %s!\n", textoBusca, criterioBusca);
        printf("\nDeseja realizar uma nova busca? (s/n): ");
        char resposta;
        scanf(" %c", &resposta);
        // Retorna 1 se deseja nova busca, 0 caso contrário
        return (resposta == 's' || resposta == 'S');
    }
    
    // Obtém o primeiro livro da lista
    Livro* atual = obterPrimeiro(lista);
    int pagina = 1;
    int livrosPorPagina = 5;
    char opcao;
    
    // Contar total de livros encontrados
    int totalLivros = 0;
    Livro* contador = atual;
    while (contador != NULL) {
        totalLivros++;
        contador = contador->prox;
    }
    
    int totalPaginas = (totalLivros + livrosPorPagina - 1) / livrosPorPagina;
    
    do {
        limparTela();
        printf("\n=== Resultados da Busca por '%s' em %s (Pagina %d de %d) ===\n", 
               textoBusca, criterioBusca, pagina, totalPaginas);
        printf("ID    | Titulo                      | Autor                       | Ano    | Editora                     | Categoria             | ISBN               | Qtd\n");
        printf("------+-----------------------------+-----------------------------+--------+-----------------------------+----------------------+--------------------+------\n");
        
        // Exibe os livros da página atual
        int contador = 0;
        Livro* paginaAtual = atual;
        
        while (paginaAtual != NULL && contador < livrosPorPagina) {
            printf("%-5d | %-28s | %-28s | %-7d | %-28s | %-21s | %-19s | %-5d\n", 
                   paginaAtual->id, paginaAtual->titulo, paginaAtual->autor, 
                   paginaAtual->ano, paginaAtual->editora, paginaAtual->categoria,
                   paginaAtual->isbn, paginaAtual->quantidade);
            
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
                // Liberar memória da lista de resultados
                liberarLivros(lista);
                
                // Perguntar se deseja fazer nova busca
                printf("\nDeseja realizar uma nova busca? (s/n): ");
                char resposta;
                scanf(" %c", &resposta);
                
                // Retorna 1 se deseja nova busca, 0 caso contrário
                return (resposta == 's' || resposta == 'S');
        }
        
    } while (1);
}

// Funcao para o menu de busca avancada (modificada para implementar o loop de busca)
void menuBusca(Livro* lista) {
    if (lista == NULL) {
        limparTela();
        printf("\nNenhum livro cadastrado para buscar!\n");
        pausar();
        return;
    }
    
    int novaBusca = 1;
    
    while (novaBusca) {
        int opcao;
        Livro* resultado = NULL;
        
        limparTela();
        printf("\n=== Busca Avancada de Obras ===\n");
        printf("1. Buscar por ID\n");
        printf("2. Buscar por Titulo\n");
        printf("3. Buscar por Autor\n");
        printf("4. Buscar por Ano\n");
        printf("5. Buscar por Editora\n");
        printf("6. Buscar por Categoria\n");
        printf("7. Buscar por ISBN\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 0) {
            return;
        }
        
        // Variáveis para armazenar os dados de busca
        int idBusca;
        int anoBusca;
        char textoBusca[100];
        char criterioBusca[20];
        
        switch (opcao) {
            case 1:
                strcpy(criterioBusca, "ID");
                printf("\nDigite o ID a ser buscado: ");
                scanf("%d", &idBusca);
                resultado = buscarPorId(lista, idBusca);
                sprintf(textoBusca, "%d", idBusca); // Converte o ID para string para exibição
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 2:
                strcpy(criterioBusca, "Titulo");
                printf("\nDigite o termo a ser buscado no titulo: ");
                getchar(); // Limpar o buffer do teclado
                fgets(textoBusca, sizeof(textoBusca), stdin);
                textoBusca[strcspn(textoBusca, "\n")] = '\0'; // Remover a quebra de linha
                resultado = buscarPorTitulo(lista, textoBusca);
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 3:
                strcpy(criterioBusca, "Autor");
                printf("\nDigite o termo a ser buscado no autor: ");
                getchar(); // Limpar o buffer do teclado
                fgets(textoBusca, sizeof(textoBusca), stdin);
                textoBusca[strcspn(textoBusca, "\n")] = '\0'; // Remover a quebra de linha
                resultado = buscarPorAutor(lista, textoBusca);
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 4:
                strcpy(criterioBusca, "Ano");
                printf("\nDigite o ano a ser buscado: ");
                scanf("%d", &anoBusca);
                resultado = buscarPorAno(lista, anoBusca);
                sprintf(textoBusca, "%d", anoBusca); // Converte o ano para string para exibição
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 5:
                strcpy(criterioBusca, "Editora");
                printf("\nDigite o termo a ser buscado na editora: ");
                getchar(); // Limpar o buffer do teclado
                fgets(textoBusca, sizeof(textoBusca), stdin);
                textoBusca[strcspn(textoBusca, "\n")] = '\0'; // Remover a quebra de linha
                resultado = buscarPorEditora(lista, textoBusca);
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 6:
                strcpy(criterioBusca, "Categoria");
                printf("\nDigite o termo a ser buscado na categoria: ");
                getchar(); // Limpar o buffer do teclado
                fgets(textoBusca, sizeof(textoBusca), stdin);
                textoBusca[strcspn(textoBusca, "\n")] = '\0'; // Remover a quebra de linha
                resultado = buscarPorCategoria(lista, textoBusca);
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            case 7:
                strcpy(criterioBusca, "ISBN");
                printf("\nDigite o termo a ser buscado no ISBN: ");
                getchar(); // Limpar o buffer do teclado
                fgets(textoBusca, sizeof(textoBusca), stdin);
                textoBusca[strcspn(textoBusca, "\n")] = '\0'; // Remover a quebra de linha
                resultado = buscarPorISBN(lista, textoBusca);
                novaBusca = exibirResultadoBusca(resultado, criterioBusca, textoBusca);
                break;
                
            default:
                printf("\nOpcao invalida!\n");
                pausar();
                novaBusca = 1; // Mantém o loop
        }
    }
}


Emprestimo* registrarEmprestimo(Livro* listaLivros, Emprestimo* listaEmprestimos) {
    limparTela();
    
    if (listaLivros == NULL) {
        printf("\nNenhum livro cadastrado para emprestar!\n");
        pausar();
        return listaEmprestimos;
    }
    
    int idLivro;
    char nomePessoa[100];
    char telefone[20];
    int diasEmprestimo = 14; // Padrão: 14 dias
    
    printf("\n=== Registrar Emprestimo ===\n");
    
    // Solicitar ID do livro
    printf("Digite o ID do livro a ser emprestado: ");
    scanf("%d", &idLivro);
    
    // Verificar se o livro existe e está disponível
    Livro* livro = NULL;
    Livro* atual = obterPrimeiro(listaLivros);
    while (atual != NULL) {
        if (atual->id == idLivro) {
            livro = atual;
            break;
        }
        atual = atual->prox;
    }
    
    if (livro == NULL) {
        printf("\nLivro com ID %d nao encontrado!\n", idLivro);
        pausar();
        return listaEmprestimos;
    }
    
    // Verificar quantos exemplares já estão emprestados
    int emprestados = 0;
    Emprestimo* empAtual = listaEmprestimos;
    while (empAtual != NULL) {
        if (empAtual->idLivro == idLivro) {
            emprestados++;
        }
        empAtual = empAtual->prox;
    }
    
    // Verificar se ainda há exemplares disponíveis
    if (emprestados >= livro->quantidade) {
        printf("\nNao ha exemplares disponiveis deste livro!\n");
        printf("Total de exemplares: %d\n", livro->quantidade);
        printf("Exemplares emprestados: %d\n", emprestados);
        pausar();
        return listaEmprestimos;
    }
    
    // Solicitar dados da pessoa
    printf("Nome da pessoa: ");
    getchar(); // Limpar buffer
    fgets(nomePessoa, sizeof(nomePessoa), stdin);
    nomePessoa[strcspn(nomePessoa, "\n")] = '\0'; // Remover quebra de linha
    
    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0'; // Remover quebra de linha
    
    printf("Dias de emprestimo (padrao: 14): ");
    int temp;
    if (scanf("%d", &temp) == 1 && temp > 0) {
        diasEmprestimo = temp;
    } else {
        getchar(); // Limpar buffer em caso de entrada inválida
    }
    
    // Gerar ID para o empréstimo
    int idEmprestimo = 1;
    empAtual = listaEmprestimos;
    while (empAtual != NULL) {
        if (empAtual->id >= idEmprestimo) {
            idEmprestimo = empAtual->id + 1;
        }
        empAtual = empAtual->prox;
    }
    
    // Obter datas
    time_t dataEmprestimo = obterDataAtual();
    time_t dataDevolucao = calcularDataDevolucao(dataEmprestimo, diasEmprestimo);
    
    // Criar e adicionar o empréstimo
    Emprestimo* novoEmprestimo = criarEmprestimo(idEmprestimo, idLivro, livro->titulo, 
                                                nomePessoa, telefone, dataEmprestimo, dataDevolucao);
    listaEmprestimos = adicionarEmprestimo(listaEmprestimos, novoEmprestimo);
    
    // Salvar alterações
    salvarEmprestimos(listaEmprestimos);
    
    // Exibir resumo do empréstimo
    limparTela();
    char dataEmpStr[20], dataDevStr[20];
    
    printf("\n=== Emprestimo Registrado com Sucesso ===\n");
    printf("ID do Emprestimo: %d\n", idEmprestimo);
    printf("Livro: %s (ID: %d)\n", livro->titulo, livro->id);
    printf("Pessoa: %s\n", nomePessoa);
    printf("Telefone: %s\n", telefone);
    printf("Data do Emprestimo: %s\n", formatarData(dataEmprestimo, dataEmpStr));
    printf("Data de Devolucao: %s\n", formatarData(dataDevolucao, dataDevStr));
    printf("Dias de Emprestimo: %d\n", diasEmprestimo);
    printf("Exemplares disponiveis: %d de %d\n", livro->quantidade - emprestados - 1, livro->quantidade);
    
    pausar();
    return listaEmprestimos;
}

// Função para exibir todos os empréstimos
void exibirEmprestimos(Emprestimo* lista) {
    limparTela();
    
    if (lista == NULL) {
        printf("\nNenhum emprestimo registrado!\n");
        pausar();
        return;
    }
    
    // Obtém o primeiro empréstimo da lista
    Emprestimo* atual = obterPrimeiroEmprestimo(lista);
    int pagina = 1;
    int empPorPagina = 5; // Número de empréstimos exibidos por página
    char opcao;
    
    // Contar total de empréstimos
    int totalEmp = 0;
    Emprestimo* contador = atual;
    while (contador != NULL) {
        totalEmp++;
        contador = contador->prox;
    }
    
    int totalPaginas = (totalEmp + empPorPagina - 1) / empPorPagina; // Arredonda para cima
    
    do {
        limparTela();
        printf("\n=== Emprestimos Registrados (Pagina %d de %d) ===\n", pagina, totalPaginas);
        printf("ID    | Livro                       | ID Livro | Pessoa                      | Telefone        | Emprestimo   | Devolucao\n");
        printf("------+-----------------------------+----------+-----------------------------+-----------------+--------------+-------------\n");
        
        // Exibe os empréstimos da página atual
        int contador = 0;
        Emprestimo* paginaAtual = atual;
        
        while (paginaAtual != NULL && contador < empPorPagina) {
            char dataEmpStr[20], dataDevStr[20];
            
            printf("%-5d | %-28s | %-8d | %-28s | %-15s | %-12s | %-12s\n", 
                   paginaAtual->id, paginaAtual->nomeLivro, paginaAtual->idLivro, 
                   paginaAtual->nomePessoa, paginaAtual->telefone, 
                   formatarData(paginaAtual->dataEmprestimo, dataEmpStr),
                   formatarData(paginaAtual->dataDevolucao, dataDevStr));
            
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
                if (pagina < totalPaginas) {
                    for (int i = 0; i < empPorPagina && atual != NULL; i++) {
                        if (atual->prox != NULL) {
                            atual = atual->prox;
                        }
                    }
                    pagina++;
                }
                break;
            
            case 'A':
            case 'a':
                if (pagina > 1) {
                    for (int i = 0; i < empPorPagina && atual != NULL; i++) {
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

// Função para registrar devolução de livro
void registrarDevolucao(Livro* listaLivros, Emprestimo** listaEmprestimos) {
    limparTela();
    
    if (*listaEmprestimos == NULL) {
        printf("\nNenhum emprestimo registrado para devolver!\n");
        pausar();
        return;
    }
    
    int idEmprestimo;
    printf("\n=== Registrar Devolucao ===\n");
    printf("Digite o ID do emprestimo a ser devolvido: ");
    scanf("%d", &idEmprestimo);
    
    // Buscar o empréstimo
    Emprestimo* emprestimo = NULL;
    Emprestimo* atual = obterPrimeiroEmprestimo(*listaEmprestimos);
    
    while (atual != NULL) {
        if (atual->id == idEmprestimo) {
            emprestimo = atual;
            break;
        }
        atual = atual->prox;
    }
    
    if (emprestimo == NULL) {
        printf("\nEmprestimo com ID %d nao encontrado!\n", idEmprestimo);
        pausar();
        return;
    }
    
    // Buscar o livro para exibir informações
    Livro* livro = NULL;
    Livro* livroAtual = obterPrimeiro(listaLivros);
    
    while (livroAtual != NULL) {
        if (livroAtual->id == emprestimo->idLivro) {
            livro = livroAtual;
            break;
        }
        livroAtual = livroAtual->prox;
    }
    
    // Contar quantos exemplares estão emprestados (incluindo este)
    int emprestados = 0;
    atual = obterPrimeiroEmprestimo(*listaEmprestimos);
    while (atual != NULL) {
        if (atual->idLivro == emprestimo->idLivro) {
            emprestados++;
        }
        atual = atual->prox;
    }
    
    // Remover o empréstimo da lista
    if (*listaEmprestimos == emprestimo && emprestimo->prox == NULL) {
        // É o único elemento da lista
        free(emprestimo);
        *listaEmprestimos = NULL;
    } else if (*listaEmprestimos == emprestimo) {
        // É o primeiro elemento
        *listaEmprestimos = emprestimo->prox;
        (*listaEmprestimos)->ant = NULL;
        free(emprestimo);
    } else {
        // Está no meio ou no final
        Emprestimo* anterior = emprestimo->ant;
        Emprestimo* proximo = emprestimo->prox;
        
        if (anterior != NULL) {
            anterior->prox = proximo;
        }
        if (proximo != NULL) {
            proximo->ant = anterior;
        }
        
        free(emprestimo);
    }
    
    // Exibir informações da devolução
    char dataEmpStr[20], dataDevStr[20];
    printf("\n=== Devolucao Registrada com Sucesso ===\n");
    printf("Livro: %s (ID: %d)\n", emprestimo->nomeLivro, emprestimo->idLivro);
    printf("Pessoa: %s\n", emprestimo->nomePessoa);
    printf("Data do Emprestimo: %s\n", formatarData(emprestimo->dataEmprestimo, dataEmpStr));
    printf("Data de Devolucao Prevista: %s\n", formatarData(emprestimo->dataDevolucao, dataDevStr));
    
    if (livro != NULL) {
        printf("Exemplares disponiveis: %d de %d\n", livro->quantidade - emprestados + 1, livro->quantidade);
    }
    
    // Verificar atraso
    time_t dataAtual = obterDataAtual();
    if (dataAtual > emprestimo->dataDevolucao) {
        int diasAtraso = (dataAtual - emprestimo->dataDevolucao) / (24 * 60 * 60);
        printf("\nATENCAO: Devolucao com %d dias de atraso!\n", diasAtraso);
    } else {
        printf("\nDevolucao realizada dentro do prazo.\n");
    }
    
    // Salvar alterações
    salvarEmprestimos(*listaEmprestimos);
    
    pausar();
}

// Função para o menu de empréstimos
Emprestimo* menuEmprestimos(Livro* listaLivros, Emprestimo* listaEmprestimos) {
    int opcao;
    
    do {
        limparTela();
        printf("\n=== Controle de Emprestimos ===\n");
        printf("1. Registrar Emprestimo\n");
        printf("2. Registrar Devolucao\n");
        printf("3. Exibir Emprestimos\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                listaEmprestimos = registrarEmprestimo(listaLivros, listaEmprestimos);
                break;
                
            case 2:
                registrarDevolucao(listaLivros, &listaEmprestimos);
                break;
                
            case 3:
                exibirEmprestimos(listaEmprestimos);
                break;
                
            case 0:
                return listaEmprestimos;
                
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
    
    return listaEmprestimos;
}



