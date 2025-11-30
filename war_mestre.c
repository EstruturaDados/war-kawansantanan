#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --------------------------------------------------------------
// Struct Território
// --------------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// --------------------------------------------------------------
// Função: atacar
// Simula o ataque entre dois territórios usando dados (1 a 6)
// Se o atacante vencer, assume o território defensor
// --------------------------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Simulação de Ataque ===\n");

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("%s (%s) ataca %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado atacante: %d\n", dadoAtk);
    printf("Dado defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\nAtacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("Território %s agora pertence a %s.\n",
               defensor->nome, defensor->cor);
    }
    else {
        printf("\nDefensor resistiu!\n");
        atacante->tropas--;

        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("O atacante perdeu 1 tropa (restantes: %d).\n", atacante->tropas);
    }

    printf("==========================\n\n");
}


// --------------------------------------------------------------
// Exibe o mapa completo
// --------------------------------------------------------------
void exibirMapa(Territorio* mapa, int n) {
    printf("\n===== ESTADO DO MAPA =====\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome : %s\n", mapa[i].nome);
        printf("Cor  : %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n===========================\n");
}


// --------------------------------------------------------------
// Exibe missão (por valor)
// --------------------------------------------------------------
void exibirMissao(char* missao) {
    printf("\n=== Sua Missão Estratégica ===\n");
    printf("%s\n", missao);
    printf("================================\n\n");
}


// --------------------------------------------------------------
// Atribui missão dinamicamente (por referência)
// --------------------------------------------------------------
void atribuirMissao(char* destino, char* missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}


// --------------------------------------------------------------
// Verifica se a missão foi cumprida
// Aqui usamos uma lógica simples só para cumprir o requisito
// --------------------------------------------------------------
int verificarMissao(char* missao, Territorio* mapa, int n) {

    // MISSÃO 1: "Conquistar 1 território da cor vermelha"
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "vermelha") != 0) {
                return 0; // ainda existe território vermelho → não cumpriu
            }
        }
        return 1;
    }

    // MISSÃO 2: "Conquistar 3 territórios"
    if (strstr(missao, "3 territórios") != NULL) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                count++;
            }
        }
        if (count >= 3) return 1;
        return 0;
    }

    // MISSÃO 3: "Ter mais de 20 tropas no total"
    if (strstr(missao, "20 tropas") != NULL) {
        int total = 0;
        for (int i = 0; i < n; i++) total += mapa[i].tropas;
        return total >= 20;
    }

    // MISSÕES adicionais podem ser incluídas aqui

    return 0;
}


// --------------------------------------------------------------
// Libera toda a memória alocada (mapa + missões)
// --------------------------------------------------------------
void liberarMemoria(Territorio* mapa, char* m1, char* m2) {
    free(mapa);
    free(m1);
    free(m2);
    printf("\nMemória liberada com sucesso!\n");
}


// --------------------------------------------------------------
// MAIN
// --------------------------------------------------------------
int main() {

    srand(time(NULL));

    int n;
    printf("Quantidade de territórios: ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }


    // ----------------------------------------------------------
    // MISSÕES PRÉ-DEFINIDAS
    // ----------------------------------------------------------
    char* missoes[] = {
        "Eliminar todos os territórios da cor vermelha.",
        "Conquistar 3 territórios.",
        "Acumular mais de 20 tropas no total.",
        "Dominar todos os territórios azuis.",
        "Controlar pelo menos 2 territórios com mais de 5 tropas."
    };

    int totalMissoes = 5;

    // Missão dinâmica de dois jogadores
    char* missaoJog1 = (char*) malloc(200);
    char* missaoJog2 = (char*) malloc(200);

    atribuirMissao(missaoJog1, missoes, totalMissoes);
    atribuirMissao(missaoJog2, missoes, totalMissoes);

    printf("\nJOGADOR 1:");
    exibirMissao(missaoJog1);

    printf("\nJOGADOR 2:");
    exibirMissao(missaoJog2);


    // ----------------------------------------------------------
    // Loop simples (1 turno) para ataque
    // ----------------------------------------------------------
    int atk, def;

    exibirMapa(mapa, n);

    printf("\nJogador 1, escolha seu território atacante (1-%d): ", n);
    scanf("%d", &atk);

    printf("Escolha o território defensor (1-%d): ", n);
    scanf("%d", &def);

    atk--; def--;

    if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
        printf("ERRO: Não é possível atacar a si mesmo!\n");
    } else {
        atacar(&mapa[atk], &mapa[def]);
    }

    exibirMapa(mapa, n);

    // ----------------------------------------------------------
    // Verificação de vitória
    // ----------------------------------------------------------
    if (verificarMissao(missaoJog1, mapa, n)) {
        printf("🎉 Jogador 1 cumpriu a missão e VENCEU!\n");
    }
    else if (verificarMissao(missaoJog2, mapa, n)) {
        printf("🎉 Jogador 2 cumpriu a missão e VENCEU!\n");
    }
    else {
        printf("\nNenhum jogador cumpriu a missão neste turno.\n");
    }

    // Libera memória
    liberarMemoria(mapa, missaoJog1, missaoJog2);

    return 0;
}