#include <stdio.h>
#include <stdlib.h>
#include "oq_vcs_decidirem.h" // Alguma biblioteca de Strings? Não sei

// Casos da pagina inicial:
#define FECHAR_PROGRAMA 0
#define CADASTRAR_USUARIO 1
#define CADASTRAR_LIVRO 2
#define LISTAR_LIVROS 3
#define BUSCAR_LIVRO 4
#define EMPRESTAR_LIVRO 5
#define DEVOLVER_LIVRO 6

// Tipos principais:
struct Usuario {
    int token;
    char nome[50];
    int telefone;
    struct VetorEmprestado emprestados; // Algum tipo de referencia aos livros originais emprestados pelo VetorLivro.
    // Pode ser que seja um Vetor(struct Livro*), para que se possa ler qual foi o livro da lista total empretado (referenciado por um '&').
};
struct Livro {
    char titulo[50];
    char autor[50];
    int ano_publicado;
    int qt_total;
    int qt_disponivel;
};

// Execução:
int main() {

    struct VetorLivro livros = newLivros();
    struct VetorUsuario usuarios = newUsuarios();

    int escolha_inicio = 1;

    while(escolha_inicio) {
        printf("Qual ação deseja executar? (Digite um valor alternativo para sair)\n");
        printf(
            "[1] Cadastrar novo livro;\n", 
            "[2] Cadastrar novo usuário;\n", 
            "[3] Listar livros disponíveis\n", 
            "[4] Buscar novo livro\n"
            "[5] Pedir livro emprestado\n",
            "[6]  Devolver livro\n\n"
        );
        scanf("%d", &escolha_inicio);


        switch escolha_inicio {
            case CADASTRAR_USUARIO:
                struct Usuario novo;

                printf("Digite o numero de identificação do usuário:\n");
                scanf("%d", novo->token);
                printf("Digite o nome do usuário:\n");
                scanf("%49s", novo->nome);
                printf("Digite o numero de telefone do usuário:\n");
                scanf("%d", novo->telefone);
                // Não é necessário alocar memoria para os livros emprestados enquanto não se há nenhum ainda.

                adicionarUsuario(&usuarios, &novo); // É como se fosse um vetor.push(novo_usuario) referente ao vetor global de usuarios;
                break;

            case CADASTRAR_LIVRO:
                struct Livro novo;

                printf("Digite o título do livro:\n");
                scanf("%49s", novo->titulo);
                printf("Digite o autor do livro:\n");
                scanf("%49s", novo->autor);
                printf("Digite o ano de publicação do livro:\n");
                scanf("%d", novo->ano_publicado);
                printf("Digite a quantidade do livro adquirida:\n");
                scanf("%d", novo->qt_total);
                novo.qt_disponivel = novo.qt_total;

                adicionarLivro(&usuarios, &novo); // É como se fosse um vetor.push(novo_livro) referente ao vetor global de livros;
                break;

            case LISTAR_LIVROS:
                listarLivros(&livros);
                /* 
                    Faz um 'for_loop' que traz cada informação interna das 'struct livro' armazenadas na biblioteca (vetorLivro). 
                    talvez se (item.qt_disponivel == 0), imprime um "INDISPONIVEL"
                */
                break;

            case BUSCAR_LIVRO:
                int escolha_busca;
                printf("Qual filtro desejas utilizar para buscar o livro? (Digite um valor alternativo para sair)\n")
                printf(
                    "[1] Título da obra;",
                    "[2] Nome do autor;",
                    "[3] Data de publicação;"
                )
                scanf("%d", &escolha_busca);
                
                switch escolha_busca {
                    case 1:
                        char titulo_escolha[50];

                        printf("Digite o nome do autor que procura:")
                        scanf("%49s", titulo_escolha);

                        listarLivros__titulo(&livros, titulo_escolha); 
                        // Função 'listarLivros()' com um 'if (string_cmp(item.titulo, titulo_escolha))' para cada item.
                        break;

                    case 2:
                        char autor_escolha[50];

                        printf("Digite o nome do autor que procura:")
                        scanf("%49s", autor_escolha);

                        listarLivros__autor(&livros, autor_escolha);
                        // Função 'listarLivros()' com um 'if (string_cmp(item.autor, autor_escolha))' para cada item.
                        break;

                    case 3:
                        int data_de_publicacao_escolha;

                        printf("Digite o nome do autor que procura:")
                        scanf("%d", data_de_publicacao_escolha);
                        listarLivros__ano_publicado(&livros, data_de_publicacao_escolha);
                        // Função 'listarLivros()' com um 'if (item.data_de_publicacao == data_de_publicacao_escolha)' para cada item.
                        break;
                }

                printf("\n");
                break;

            case EMPRESTAR_LIVRO:
                int token_procurado;
                char titulo_procurado[50];

                printf("Qual o token do usuario a qual emprestará o livro?\n")
                scanf("%d", &token);

                printf("Qual o título do livro que deseja emprestar?\n");
                scanf("%49s", titulo);

                emprestarLivro(token_procurado, titulo_procurado, &usuarios, &livros);
                /*
                    1: Procurará um 'Usuario' em 'usuarios' que contém (item.token == token_procurado);
                    2: Procurará um 'Livro' em 'livros' que contém (str_cmp(item.titulo, titulo_procurado));
                    3: Checará se o 'Livro' tem seu (.qt_disponivel) diferente de zero;
                    Se um dos requisitos não for satisfeito, aborta a operação e comunica falha;
                    Se ambos forem satisfeitos:
                        1: será adicionado 1 espaço de memória aos titulos emprestados do 'Usuario';
                        2: será adicionada a referencia ao livro.titulo;
                        3: será decrementado o (.qt_disponivel) do livro;
                        4: sinalizará sucesso.
                */
                break;

            case DEVOLVER_LIVRO:
                int token_procurado;
                char titulo_procurado[50];

                printf("Qual o token do usuario que devolverá o livro?\n")
                scanf("%d", &token);

                printf("Qual o título do livro que será devolvido?\n");
                scanf("%49s", titulo);

                emprestarLivro(token_procurado, titulo_procurado, &usuarios, &livros);
                /*
                    1: Procurará um 'Usuario' em 'usuarios' que contém (item.token == token_procurado);
                    2: Procurará um 'Livro' em 'livros' que contém (str_cmp(item.titulo, titulo_procurado));
                    3: Checará se o 'Usuario' tem, em seus (.emprestados) um livro correspondente ao 'titulo_procurado';
                    Se um dos requisitos não for satisfeito, aborta a operação e comunica falha;
                    Se ambos forem satisfeitos:
                        1: será liberado o espaço de memória dos titulos emprestados do 'Usuario' responsável por conter um 'titulo_procurado';
                        3: será incrementado o (.qt_disponivel) do livro;
                        4: sinalizará sucesso.
                */                
                break;
                
            default:
                escolha_inicio = FECHAR_PROGRAMA;
                printf("Obrigado pela disposição.\n");
                break;
        }
    }

    freeLivros(&livros);
    freeUsuarios(&usuarios);
    return 0;
}