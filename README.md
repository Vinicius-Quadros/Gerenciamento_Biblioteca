# Sistema de Gerenciamento de Biblioteca

Um sistema completo de gerenciamento de biblioteca implementado em C, utilizando estruturas de dados dinâmicas (listas duplamente encadeadas) para armazenamento e manipulação eficiente dos dados.

## Autores

- Vinicius Ribas Quadros
- Giovanni Antonietto Rosa
- Lucas Antonio Ribeiro
- Gustavo Fortunato

## Sobre o Projeto

Este sistema foi desenvolvido como parte de um projeto acadêmico da disciplina de Estruturas de Dados. O objetivo principal foi criar uma aplicação que demonstrasse o uso prático de listas duplamente encadeadas em um cenário real de gerenciamento de informações.

## Funcionalidades

O sistema oferece as seguintes funcionalidades:

- **Cadastro de livros**: Registro completo de livros com os campos:
  - ID (gerado automaticamente)
  - Título
  - Autor
  - Ano
  - Editora
  - Categoria
  - ISBN
  - Quantidade disponível

- **Exibição de livros**: Visualização paginada do acervo, com possibilidade de navegação para frente e para trás entre as páginas.

- **Ordenação por diferentes critérios**: Reorganização da lista de livros por:
  - ID
  - Título
  - Autor
  - Ano
  - Editora
  - Categoria
  - ISBN
  - Quantidade

- **Busca avançada**: Localização de livros por qualquer um dos campos, incluindo busca por termos parciais e insensível a maiúsculas/minúsculas.

- **Controle de empréstimos**: Gestão completa de empréstimos de livros:
  - Registro de empréstimos com data automática do sistema
  - Cálculo da data de devolução
  - Verificação de disponibilidade de exemplares
  - Registro de devoluções com verificação de atraso

- **Remoção de livros**: Possibilidade de remover exemplares ou livros completos, com verificação de empréstimos ativos.

## Estrutura de Dados

O projeto utiliza listas duplamente encadeadas como estrutura de dados principal, oferecendo:

- Navegação bidirecional entre nós da lista
- Inserção e remoção eficientes
- Flexibilidade para reordenação
- Facilidade na implementação de paginação

Definição da estrutura principal:

```c
typedef struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    char editora[100];
    char categoria[50];
    char isbn[20];
    int quantidade;
    struct Livro* prox;  // Ponteiro para o próximo nó
    struct Livro* ant;   // Ponteiro para o nó anterior
} Livro;
```

## Organização do Código

O projeto está organizado de forma modular, dividido em múltiplos arquivos:

### Arquivos de Cabeçalho (.h)

- **livro.h**: Define a estrutura `Livro` e protótipos das funções para manipulação de livros
- **emprestimo.h**: Define a estrutura `Emprestimo` e funções relacionadas
- **interface.h**: Protótipos das funções da interface com o usuário
- **arquivo.h**: Funções para persistência de dados

### Arquivos de Implementação (.c)

- **livro.c**: Implementação das funções de manipulação e ordenação de livros
- **emprestimo.c**: Implementação do controle de empréstimos
- **interface.c**: Implementação dos menus e interação com o usuário
- **arquivo.c**: Implementação da persistência em arquivos
- **main.c**: Função principal e loop do programa

## Persistência de Dados

O sistema utiliza arquivos de texto para armazenamento persistente dos dados:

- **biblioteca.txt**: Armazena o acervo de livros
- **emprestimo_livro.txt**: Registra os empréstimos ativos

Os arquivos seguem um formato CSV simples, permitindo fácil leitura e escrita dos dados.

## Compilação e Execução

### Requisitos
- Compilador C (GCC recomendado)
- Make (opcional, para usar o Makefile)

### Compilação Manual
```bash
gcc -o biblioteca main.c livro.c emprestimo.c interface.c arquivo.c -Wall
```

### Usando Makefile
```bash
make
```

### Execução
```bash
./biblioteca
```

## Aspectos Técnicos

### Algoritmos Implementados

- **Bubble Sort adaptado**: Para ordenação da lista duplamente encadeada
- **Busca linear com correspondência parcial**: Para funções de busca avançada
- **Gerenciamento de ponteiros bidirecionais**: Para manutenção da integridade da lista

### Tratamento de Erros

- Verificação de alocação de memória
- Validação de entradas do usuário
- Tratamento de arquivos inexistentes
- Verificações de disponibilidade para empréstimos

## Contribuições

O projeto está aberto para contribuições. Algumas possíveis melhorias:

- Implementação de interface gráfica
- Adição de funcionalidades de relatórios
- Otimização dos algoritmos de busca e ordenação
- Expansão do sistema de controle de usuários

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
