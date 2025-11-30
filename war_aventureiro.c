#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------------------------------------
// Struct Territorio
// Representa um território no jogo WAR com nome, cor e tropas
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// -----------------------------------------------------------
// Função: atacar
// Realiza uma simulação de ataque entre dois territórios
// usando dados aleatórios (1 a 6). Caso o atacante vença,
// ele assume o território do defensor e transfere metade
// de suas tropas.
// -----------------------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Iniciando Ataque ===\n");
    printf("%s (%s) ATACANDO %s (%s)\n\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtaque = (rand() % 6) + 1;   // random 1–6
    int dadoDefesa = (rand() % 6) + 1;

    printf("Dado do Atacante: %d\n", dadoAtaque);
    printf("Dado do Defensor: %d\n", dadoDefesa);

    // Atacante vence
    if (dadoAtaque > dadoDefesa) {
        printf("\nResultado: O atacante venceu!\n");

        // Muda cor (território trocado de dono)
        strcpy(defensor->cor, atacante->cor);

        // Transferência de tropas (metade)
        defensor->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);

    } else {
        // Defensor vence
        printf("\nResultado: O defensor resistiu ao ataque!\n");

        // Atacante perde uma tropa
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("O atacante perdeu 1 tropa. Tropas restantes: %d\n",
               atacante->tropas);
    }

    printf("=== Fim da Simulação ===\n\n");
}


// -----------------------------------------------------------
// Função: exibirTerritorios
// Exibe as informações completas de todos os territórios
// -----------------------------------------------------------
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n=============================\n");
}


// -----------------------------------------------------------
// Função: liberarMemoria
// Libera a memória alocada dinamicamente
// -----------------------------------------------------------
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}


int main() {

    srand(time(NULL));   // Garante aleatoriedade dos dados

    int n;

    printf("=== WAR ESTRUTURADO - Nível Aventureiro ===\n");
    printf("Informe o número de territórios que deseja cadastrar: ");
    scanf("%d", &n);

    // -----------------------------------------------------------
    // Alocação dinâmica do vetor de territórios
    // -----------------------------------------------------------
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // -----------------------------------------------------------
    // Cadastro dos territórios
    // -----------------------------------------------------------
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do Território %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    exibirTerritorios(mapa, n);

    // -----------------------------------------------------------
    // Seleção de ataque
    // -----------------------------------------------------------
    int atk, def;

    printf("\nEscolha o território ATACANTE (1 a %d): ", n);
    scanf("%d", &atk);

    printf("Escolha o território DEFENSOR (1 a %d): ", n);
    scanf("%d", &def);

    atk--; // transformando índices para 0-based
    def--;

    // Validação para impedir ataque ao próprio território
    if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
        printf("\nERRO: O atacante não pode atacar um território da mesma cor!\n");
    } else {
        atacar(&mapa[atk], &mapa[def]);
    }

    // Exibir resultados após a batalha
    exibirTerritorios(mapa, n);

    // Libera memória alocada
    liberarMemoria(mapa);

    return 0;
}