#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Bibliotecas de variáveis:
#define tamanho_tabuleiro 10//define um valor constante para o tabuleiro
#define valor_habilidade 5//define um valor constante para o valor das habilidades

int primeiro_golpe = 0;//variável para evitar erro na primeira execução de ataque
int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro];//matriz representando o tabuleiro
int navio_1[3] = {3, 3, 3};//vetores representando o navio
int navio_2[3] = {3, 3, 3};
int navio_3[3] = {3, 3, 3};
int navio_4[3] = {3, 3, 3};

//matriz que representa as áreas de efeito de cada golpe
int hab_triangulo[valor_habilidade][valor_habilidade] = {
    {0, 0, 0, 0, 0},
    {0, 0, 5, 0, 0},
    {0, 5, 5, 5, 0},
    {5, 5, 5, 5, 5},
    {0, 0, 0, 0, 0}
};
int hab_cruz[valor_habilidade][valor_habilidade] = {
    {0, 0, 5, 0, 0},
    {0, 0, 5, 0, 0},
    {5, 5, 5, 5, 5},
    {0, 0, 5, 0, 0},
    {0, 0, 5, 0, 0}
};
int hab_octaedro[valor_habilidade][valor_habilidade] = {
    {0, 0, 5, 0, 0},
    {0, 5, 5, 5, 0},
    {5, 5, 5, 5, 5},
    {0, 5, 5, 5, 0},
    {0, 0, 5, 0, 0}
};

void zerar_tabuleiro() {
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostrar_resultados() {
    
    for(int i = 0; i < tamanho_tabuleiro; i++){
        for(int j = 0; j < tamanho_tabuleiro; j++){
            if(tabuleiro[i][j] > 5){
                printf("x\t");
            }else if(tabuleiro[i][j] == 5){
                printf("o\t");
            }else{
                printf("*\t");
            }
        }
        printf("\n");
    }
    
    
    /*for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d\t", tabuleiro[i][j]);
        }
        printf("\n"); // Adiciona quebra de linha após cada linha
    }*/

}

int validar_coordenadas(int nx, int ny) {
    return (nx >= 0 && nx < tamanho_tabuleiro && ny >= 0 && ny < tamanho_tabuleiro);
}

void aplicar_ataque(int x, int y, int habilidade[valor_habilidade][valor_habilidade]) {
    for (int i = 0; i < valor_habilidade; i++) {
        for (int j = 0; j < valor_habilidade; j++) {
            int new_x = x - 2 + i;
            int new_y = y - 2 + j; // Corrigido o cálculo de new_y

            if (validar_coordenadas(new_x, new_y)) {
                if(tabuleiro[new_x][new_y] < valor_habilidade || primeiro_golpe == 0){
                    tabuleiro[new_x][new_y] += habilidade[i][j];
                }
            }
        }
    }
    mostrar_resultados();
}

void habilidade_triangulo(int x, int y) {
    aplicar_ataque(x, y, hab_triangulo);
}

void habilidade_cruz(int x, int y) {
    aplicar_ataque(x, y, hab_cruz);
}

void habilidade_octa(int x, int y) {
    aplicar_ataque(x, y, hab_octaedro);
}

void space() {
    printf("\n---------------------------------------------\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void posicionar_navios() {
    for (int i = 0; i < 3; i++) {
        tabuleiro[4][3 + i] = navio_1[i];
        tabuleiro[6 + i][2] = navio_2[i];
        tabuleiro[8 - i][7 - i] = navio_3[i];
        tabuleiro[1 + i][3 - i] = navio_4[i];
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int menu_choice = 0;
    int x = 0;
    int y = 0;
    int escolha_da_habilidade = 0;
    int menu_ext = 0;
    posicionar_navios();
    do {
        space();
        printf("Menu Principal:\n");
        printf("1- Iniciar Jogo\n");
        printf("2- Mais Informações\n");
        printf("3- Zerar tabuleiro\n");
        printf("4- Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &menu_choice) != 1) { // Valida entrada
            limparBuffer();
            printf("Entrada inválida. Por favor, insira um número.\n");
            continue;
        }
        limparBuffer();

        switch (menu_choice) {
        case 1:
            
            mostrar_resultados();

            int i = 0;
            do {
                printf("Agora escolha uma posição para iniciar um tiro: \n");
                printf("Linha (0-9): ");
                if (scanf("%d", &x) != 1) { // Valida entrada
                    limparBuffer();
                    printf("Entrada inválida. Por favor, insira um número.\n");
                    continue;
                }
                limparBuffer();
                printf("Coluna (0-9): ");
                if (scanf("%d", &y) != 1) { // Valida entrada
                    limparBuffer();
                    printf("Entrada inválida. Por favor, insira um número.\n");
                    continue;
                }
                limparBuffer();

                if (validar_coordenadas(x, y)) {
                    printf("Foi escolhido a posição (%d, %d)\n", x, y);
                    printf("Selecione a habilidade que deseja usar: \n");
                    printf("1- Habilidade Cruz\n");
                    printf("2- Habilidade Octa\n");
                    printf("3- Habilidade Triângulo\n");
                    if (scanf("%d", &escolha_da_habilidade) != 1) { // Valida entrada
                        limparBuffer();
                        printf("Entrada inválida. Por favor, insira um número.\n");
                        continue;
                    }
                    limparBuffer();

                    switch (escolha_da_habilidade) {
                    case 1:
                        habilidade_cruz(x, y);
                        i++;
                        break;
                    case 2:
                        habilidade_octa(x, y);
                        i++;
                        break;
                    case 3:
                        habilidade_triangulo(x, y);
                        i++;
                        break;
                    default:
                        printf("Opção inválida\n");
                        break;
                    }
                } else {
                    printf("Posição inválida!\n");
                }
            } while (i != 1);
            primeiro_golpe = 1;
            break;

        case 2:
            space();
            printf("Mais informações sobre o jogo:\n");
            printf("- O tabuleiro é de 10x10.\n");
            printf("- Você pode usar habilidades para atacar áreas específicas.\n");
            printf("- Cada habilidade tem um formato de ataque diferente.\n");
            printf("* = área não atacada\n");
            printf("x = navio acertado\n");
            printf("o = área atacada sem alvos\n");
            break;

        case 3:
            space();
            zerar_tabuleiro();
            printf("Tabuleiro zerado com sucesso.\n");
            break;

        case 4:
            menu_ext = 1;
            break;

        default:
            space();
            printf("Opção inválida. Por favor, tente novamente.\n");
            break;
        }

    } while (menu_ext != 1);

    return 0;
}
