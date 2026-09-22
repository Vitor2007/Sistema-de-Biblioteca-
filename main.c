#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int book_code;
    int book_amount;
    char *book_author;
    char *book_title;
} Book;

typedef struct {
    int user_phone;
    int user_code;
    char *user_name;
} User;

Book *book = NULL;
User *user = NULL;

/* Limpa o que ficou no teclado depois de um scanf */
void clear_buffer() {
    int character;

    while ((character = getchar()) != '\n' && character != EOF);
}

/* ================= CADASTRAR LIVRO ================= */

void register_book(int *book_quantity) {

    book = realloc(book, (*book_quantity + 1) * sizeof(Book));

    if (book == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    Book *new_book = &book[*book_quantity];

    printf("\nDigite o codigo do livro: ");
    scanf("%d", &new_book->book_code);
    clear_buffer();

    printf("Digite a quantidade de exemplares: ");
    scanf("%d", &new_book->book_amount);
    clear_buffer();

    char buffer[256];

    printf("Digite o nome do autor: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    new_book->book_author = malloc(strlen(buffer) + 1);

    if (new_book->book_author == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    strcpy(new_book->book_author, buffer);

    printf("Digite o titulo do livro: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    new_book->book_title = malloc(strlen(buffer) + 1);

    if (new_book->book_title == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(new_book->book_author);
        return;
    }

    strcpy(new_book->book_title, buffer);

    *book_quantity += 1;

    printf("\nLivro cadastrado com sucesso!\n");
}

/* ================= CADASTRAR USUARIO ================= */

void register_user(int *user_quantity) {

    user = realloc(user, (*user_quantity + 1) * sizeof(User));

    if (user == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    User *new_user = &user[*user_quantity];

    printf("\nDigite o codigo do usuario: ");
    scanf("%d", &new_user->user_code);
    clear_buffer();

    char buffer[256];

    printf("Digite o nome do usuario: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    new_user->user_name = malloc(strlen(buffer) + 1);

    if (new_user->user_name == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    strcpy(new_user->user_name, buffer);

    printf("Digite o telefone do usuario: ");
    scanf("%d", &new_user->user_phone);
    clear_buffer();

    *user_quantity += 1;

    printf("\nUsuario cadastrado com sucesso!\n");
}

/* ================= EMPRESTAR LIVRO ================= */

void borrow_book(int book_quantity) {

    if (book_quantity == 0) {
        printf("\nAinda nao ha nenhum livro cadastrado no sistema.\n");
        return;
    }

    int book_code_query;

    printf("\nDigite o codigo do livro que deseja pegar emprestado: ");
    scanf("%d", &book_code_query);
    clear_buffer();

    for (int index = 0; index < book_quantity; index++) {

        if (book[index].book_code == book_code_query) {

            if (book[index].book_amount > 0) {

                book[index].book_amount--;

                printf("O emprestimo do livro foi realizado com sucesso.\n");
                printf("Ainda ha %d exemplar(es) restante(s).\n",
                       book[index].book_amount);
            }
            else {
                printf("Desculpe, este livro esta esgotado no momento.\n");
            }

            return;
        }
    }

    printf("Nao foi possivel encontrar um livro com o codigo %d.\n",
           book_code_query);
}

/* ================= DEVOLVER LIVRO ================= */

void return_book(int book_quantity) {

    if (book_quantity == 0) {
        printf("\nAinda nao ha nenhum livro cadastrado no sistema.\n");
        return;
    }

    int book_code_query;

    printf("\nDigite o codigo do livro que deseja devolver: ");
    scanf("%d", &book_code_query);
    clear_buffer();

    for (int index = 0; index < book_quantity; index++) {

        if (book[index].book_code == book_code_query) {

            book[index].book_amount++;

            printf("Devolucao realizada com sucesso!\n");
            printf("Agora ha %d exemplar(es) disponivel(is).\n",
                   book[index].book_amount);

            return;
        }
    }

    printf("Nao foi possivel encontrar um livro com o codigo %d.\n",
           book_code_query);
}

/* ================= BUSCAR LIVRO ================= */

void search_book(int book_quantity) {

    if (book_quantity == 0) {
        printf("\nAinda nao ha nenhum livro cadastrado no sistema.\n");
        return;
    }

    int opcao;

    printf("\n===== BUSCAR LIVRO =====\n");
    printf("[1] Buscar por codigo\n");
    printf("[2] Buscar por titulo\n");
    printf("[0] Voltar\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    clear_buffer();

    int achou = 0;

    /* Ponteiro para percorrer os livros */
    Book *pont = book;

    /* Buscar por codigo */
    if (opcao == 1) {

        int codigoLivro;

        printf("Digite o codigo do livro: ");
        scanf("%d", &codigoLivro);
        clear_buffer();

        for (int i = 0; i < book_quantity; i++) {

            if ((pont + i)->book_code == codigoLivro) {

                printf("\n--- Livro encontrado ---\n");
                printf("Codigo: %d\n", (pont + i)->book_code);
                printf("Titulo: %s\n", (pont + i)->book_title);
                printf("Autor: %s\n", (pont + i)->book_author);
                printf("Disponiveis: %d\n", (pont + i)->book_amount);

                achou = 1;
            }
        }
    }

    /* Buscar por titulo */
    else if (opcao == 2) {

        char title_query[100];

        printf("Digite o titulo do livro: ");
        fgets(title_query, sizeof(title_query), stdin);
        title_query[strcspn(title_query, "\n")] = '\0';

        for (int i = 0; i < book_quantity; i++) {

            if (strcmp((pont + i)->book_title, title_query) == 0) {

                printf("\n--- Livro encontrado ---\n");
                printf("Codigo: %d\n", (pont + i)->book_code);
                printf("Titulo: %s\n", (pont + i)->book_title);
                printf("Autor: %s\n", (pont + i)->book_author);
                printf("Disponiveis: %d\n", (pont + i)->book_amount);

                achou = 1;
            }
        }
    }

    else if (opcao == 0) {
        return;
    }

    else {
        printf("Opcao invalida.\n");
        return;
    }

    if (!achou) {
        printf("\nNenhum livro encontrado.\n");
    }
}

/* ================= LISTAR LIVROS ================= */

void book_listing(int book_quantity) {

    printf("\n--- Lista de Livros ---\n");

    if (book_quantity == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < book_quantity; i++) {

        printf(
            "ID: %d | Titulo: %s | Autor: %s | Quantidade Disponivel: %d\n",
            book[i].book_code,
            book[i].book_title,
            book[i].book_author,
            book[i].book_amount
        );
    }
}

/* ================= MAIN ================= */

int main(int argc, char *argv[]) {

    int book_quantity = 0;
    int user_quantity = 0;
    int menu;

    do {

        printf("\n========== MENU ==========\n");
        printf("1. Cadastrar livro\n");
        printf("2. Cadastrar usuario\n");
        printf("3. Listar livros\n");
        printf("4. Buscar livro\n");
        printf("5. Emprestimo de livro\n");
        printf("6. Devolucao de livro\n");
        printf("7. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        clear_buffer();

        switch (menu) {

            case 1:
                register_book(&book_quantity);
                break;

            case 2:
                register_user(&user_quantity);
                break;

            case 3:
                book_listing(book_quantity);
                break;

            case 4:
                search_book(book_quantity);
                break;

            case 5:
                borrow_book(book_quantity);
                break;

            case 6:
                return_book(book_quantity);
                break;

            case 7:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (menu != 7);

    /* Liberando memoria dos livros */
    for (int i = 0; i < book_quantity; i++) {
        free(book[i].book_author);
        free(book[i].book_title);
    }

    free(book);

    /* Liberando memoria dos usuarios */
    for (int i = 0; i < user_quantity; i++) {
        free(user[i].user_name);
    }

    free(user);

    return EXIT_SUCCESS;
}
