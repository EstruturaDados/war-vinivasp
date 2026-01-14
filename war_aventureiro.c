#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da constante para o número de territórios
#define MAX 5

// Criação da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
// Limpar buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// --- FUNÇÃO DE ATAQUE ---
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtacante, dadoDefensor;    
    printf("\n--- RESULTADO DA BATALHA ---\n");

    // Rolando os dados (1 a 6)
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;    
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    // Lógica de Vitória ou Derrota
    if (dadoAtacante > dadoDefensor) {        
        printf("VITORIA DO ATAQUE! O defensor foi conquistado.\n");        
        strcpy(defensor->cor, atacante->cor);
        
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas = atacante->tropas - tropasMovidas;
        
    } else {        
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("\nDERROTA DO ATAQUE! O atacante perdeu 1 tropa.\n");
        } else {
            printf("\nDERROTA DO ATAQUE! (Sem tropas para perder)\n");
        }
    }

    printf("\nPressione Enter para continuar para o proximo turno...");
    limparBuffer();
}

// --- FUNÇÃO EXIBIR MAPA ---
void exibirMapa(struct Territorio *lista) {
    int i;
    printf("\n==================================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL       \n");
    printf("==================================================\n\n");
    
    for (i = 0; i < MAX; i++) {        
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 
               i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }
}

void liberarMemoria(struct Territorio *mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}

int main() {
    struct Territorio *lista;
    int i, indiceAtk, indiceDef;

    srand(time(NULL));

    // --- ALOCAÇÃO DE MEMÓRIA ---
    lista = (struct Territorio*) calloc(MAX, sizeof(struct Territorio));
    
    if (lista == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    // CADASTRO DOS TERRITÓRIOS
    for (i = 0; i < MAX; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome: ");
        fgets(lista[i].nome, 30, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = 0; 

        printf("Cor: ");
        fgets(lista[i].cor, 10, stdin);
        lista[i].cor[strcspn(lista[i].cor, "\n")] = 0; 

        printf("Tropas: ");
        scanf("%d", &lista[i].tropas);
        limparBuffer();
    }
    //LOOP DO JOGO
    while (1) {
        
        exibirMapa(lista);

        // MENU DE ATAQUE
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", MAX);
        scanf("%d", &indiceAtk);
        limparBuffer();

        // IF PARA SAIR DO JOGO CASO QUEIRA
        if (indiceAtk == 0) {
            printf("Saindo do jogo...\n");
            break; 
        }

        // ESCOLHER DEFENSOR
        printf("Escolha o territorio defensor (1 a %d): ", MAX);
        scanf("%d", &indiceDef);
        limparBuffer();
        
        indiceAtk--; 
        indiceDef--;

        // VALIDANDO O ATAQUE
        if (indiceAtk >= 0 && indiceAtk < MAX && indiceDef >= 0 && indiceDef < MAX) {
             if (strcmp(lista[indiceAtk].cor, lista[indiceDef].cor) != 0) {
                atacar(&lista[indiceAtk], &lista[indiceDef]);
             } else {
                 printf("\n[!] Voce nao pode atacar seu proprio exercito!\n");
                 printf("Pressione Enter...");
                 getchar();
             }
        } else {
            printf("\n[!] Territorio invalido.\n");
            printf("Pressione Enter...");
            getchar();
        }
    }

    liberarMemoria(lista);
    return 0;
}