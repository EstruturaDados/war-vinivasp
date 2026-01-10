#include <stdio.h>
#include <string.h>

// Definição da constante para o número de territórios
#define MAX 5

// REQUISITO: Criação da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // REQUISITO: Vetor de structs
    struct Territorio lista[MAX];
    int i;

    printf("=============================================================\n\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    // REQUISITO: Entrada de dados com laço for
    for (i = 0; i < MAX; i++) {
        printf("\n--- Cadastrando do Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        fgets(lista[i].nome, 30, stdin);

        printf("Cor do exercito (ex Azul, Verde): ");
        fgets(lista[i].cor, 10, stdin);

        printf("DNúmero de tropas: ");
        scanf("%d", &lista[i].tropas);

        // --- Limpeza do buffer do teclado ---
        while (getchar() != '\n'); 
    }
    printf("\nCadastro inicial concluído com sucesso!\n");

    // --- Exibição dos dados cadastrados ---
    printf("==================================================\n");
    printf("          MAPA MUNDO - ESTADO ATUAL          \n");
    printf("==================================================\n");

    for (i = 0; i < MAX; i++) {
        printf("\nTERRITÓRIO %d:", i + 1);
        printf("\n- Nome: %s", lista[i].nome); // O nome já terá o "Enter" automático
        printf("- Cor: %s", lista[i].cor);   // A cor também terá o "Enter" automático
        printf("- Tropas: %d\n\n", lista[i].tropas);
        
    }

    return 0;
}