#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------
// Struct Territorio
// Agrupa informações relacionadas a cada território do jogo.
// -----------------------------------------------------------
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;

int main() {

    // Vetor que armazena 5 territórios
    Territorio t[5];

    printf("=== Cadastro de Territórios - Projeto WAR ===\n\n");

    // -----------------------------------------------------------
    // Entrada de dados
    // Solicita ao usuário que informe os dados dos 5 territórios.
    // -----------------------------------------------------------
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d\n", i + 1);

        printf("Nome do território: ");
        scanf("%s", t[i].nome);

        printf("Cor do exército: ");
        scanf("%s", t[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &t[i].tropas);

        printf("\n");
    }

    // -----------------------------------------------------------
    // Exibição dos dados cadastrados
    // Percorre o vetor e mostra os valores armazenados.
    // -----------------------------------------------------------
    printf("\n=== Territórios Cadastrados ===\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor do exército: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
