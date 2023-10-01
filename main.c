#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para calcular o PV do personagem
int calcularVida(int classe, int vig) {
    switch (classe) {
        case 1:
            return 20 + vig;
        case 2:
            return 16 + vig;
        case 3:
            return 12 + vig;
        default:
            return -1; // Valor de classe inválido
    }
}

// Função para calcular o PE do personagem
int calcularPE(int classe, int pre) {
    switch (classe) {
        case 1:
            return 2 + pre;
        case 2:
            return 3 + pre;
        case 3:
            return 4 + pre;
        default:
            return -1; // Valor de classe inválido
    }
}

int escolherOrigem() {
    int opcao;
    printf("Escolha a origem do personagem:\n");
    printf("1. Acadêmico\n");
    printf("2. Agente de Saúde\n");
    printf("3. Amnésico\n");
    printf("4. Artista\n");
    printf("5. Atleta\n");
    printf("6. Chef\n");
    printf("7. Criminoso\n");
    printf("8. Cultista Arrependido\n");
    printf("9. Desgarrado\n");
    printf("10. Engenheiro\n");
    printf("11. Executivo\n");
    printf("12. Investigador\n");
    printf("13. Lutador\n");
    printf("14. Magnata\n");
    printf("15. Mercenário\n");
    printf("16. Militar\n");
    printf("17. Operário\n");
    printf("18. Policial\n");
    printf("19. Religioso\n");
    printf("20. Servidor Público\n");
    printf("21. Teórico da Conspiração\n");
    printf("22. T.I\n");
    printf("23. Trabalhador Rural\n");
    printf("24. Trambiqueiro\n");
    printf("25. Universitário\n");
    printf("26. Vítima\n");
    scanf("%d", &opcao);

    while (opcao < 1 || opcao > 26){
        printf("Opção inválida. Tente novamente.\n");
        scanf("%d", &opcao);
    }    

    return opcao;
}

int main() {
    int FOR = 1, AGI = 1, INT = 1, VIG = 1, PRE = 1, classe, origem;
    int PV, PE, SAN;
    int pontos = 4;
    int menu1;
    char nome[100];

    printf("\nInsira o nome do personagem :\n");
    scanf("%s", nome);

     if (strlen(nome) == 0) {
        printf("\nNome inválido. O nome do personagem não pode estar vazio.\n");
        return 1;
    }

    FILE *arquivo;
    arquivo = fopen("ficha.txt", "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    origem = escolherOrigem();
    
    while (pontos > 0) {
        printf("\nDeseja modificar qual atributo?\n");
        printf("1. FOR\n");
        printf("2. AGI\n");
        printf("3. INT\n");
        printf("4. VIG\n");
        printf("5. PRE\n");
        scanf("%d", &menu1);

        int* atributo; // Ponteiro para o atributo selecionado

        switch (menu1) {
            case 1:
                atributo = &FOR;
                break;
            case 2:
                atributo = &AGI;
                break;
            case 3:
                atributo = &INT;
                break;
            case 4:
                atributo = &VIG;
                break;
            case 5:
                atributo = &PRE;
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                continue; // Restart the loop if an invalid option is chosen
        }

        printf("\n%s = %d\n", (menu1 == 1 ? "FOR" : (menu1 == 2 ? "AGI" : (menu1 == 3 ? "INT" : (menu1 == 4 ? "VIG" : "PRE")))), *atributo);
        printf("Pontos restantes: %d\n", pontos);
        printf("Deseja colocar quantos pontos neste atributo? (MÁX 2)\n");

        int aux;
        scanf("%d", &aux);

        if (aux > pontos) {
            printf("\nVocê não tem essa quantidade de pontos disponíveis.\n");
        } else if (*atributo + aux > 3 || *atributo + aux < 0) {
            printf("\nO valor não pode ultrapassar 3 ou ser menor que 0.\n");
        } else {
            *atributo += aux;
            pontos -= aux;
            printf("\nValor de atributo atualizado.\n");
        }
    }

    menu1 = 0;

    while (menu1 != 1 && menu1 != 2 && menu1 != 3) {
        printf("\nQual a classe do personagem ?\n");
        printf("\n1 - Combatente");
        printf("\n2 - Especialista");
        printf("\n3 - Ocultista\n");
        scanf("%d",& menu1);

        switch (menu1) {
            case 1:
                printf("\nClasse combatente selecionada\n");
                classe = 1;
                break;

            case 2:
                printf("\nClasse especialista selecionada\n");
                classe = 2;
                break;

            case 3:
                printf("\nClasse ocultista selecionada\n");
                classe = 3;
                break;

            default:
                printf("\nOpção inválida");
        }
    }

    // Calcula PV e PE do personagem com base nos atributos de VIG e PRE
    PV = calcularVida(classe , VIG);
    PE = calcularPE(classe , PRE);

    switch (classe) {
        case 1:
            SAN = 12;
            break;

        case 2:
            SAN = 16;
            break;

        case 3:
            SAN = 20;
    }

    fprintf(arquivo, "\nFicha:\n");
    fprintf(arquivo, "Nome: %s\n", nome);
    fprintf(arquivo, "FOR: %d\n", FOR);
    fprintf(arquivo, "AGI: %d\n", AGI);
    fprintf(arquivo, "INT: %d\n", INT);
    fprintf(arquivo, "VIG: %d\n", VIG);
    fprintf(arquivo, "PRE: %d\n", PRE);
    fprintf(arquivo, "Vida: %d\n", PV);
    fprintf(arquivo, "Pontos de Esforço: %d\n", PE);
    fprintf(arquivo, "Sanidade : %d\n\n", SAN);
    fprintf(arquivo, "-----------------------\n");
    fprintf(arquivo, "Habilidades:\n");

    switch (classe) {
        case 1:
            fprintf(arquivo, "Ataque Especial\n");
            break;

        case 2:
            fprintf(arquivo, "Eclético\n");
            fprintf(arquivo, "Perito\n");
            break;

        case 3:
            fprintf(arquivo, "Escolhido pelo Outro Lado\n");
    }

    fclose(arquivo);

    printf("Ficha Finalizada e Salva\n");

    return 0;
}
