#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    char titulo[101];
    char codigo_filme[20];
    int qtd_disponivel;
    int n_alugueis;
    int n_devolucoes;
    float price;
    int status;  // 1 = ativo 0 = removido
}Filme;


void incializar_status_zero(Filme filmes[], int tam)
{
    for (int c = 0; c < tam; c++)
    {
        filmes[c].status = 0;
    }
}


void imprimir_Filmes(Filme filmes[], int tam)
{
    for (int f = 0; f < tam; f++)
    {
        if (filmes[f].status == 1)
        {
            printf("\nÍndice do Filme: %i\nTítulo: %s | Preço: R$%.2f | Código: %s | Qtd: %i\n\n", f, filmes[f].titulo, filmes[f].price, filmes[f].codigo_filme, filmes[f].qtd_disponivel);
        }
    }
}


int buscar_Filme(Filme filmes[], int numero_filmes, char codigo[])
{
    for (int i = 0; i < numero_filmes; i++)
    {
        if (strcmp(codigo, filmes[i].codigo_filme) == 0)
        {
            return i;
        }
    }

    return -1;
}


Filme criar_Filme(Filme filmes[], int numero_filmes)
{
    Filme filme;

    printf("\nTítulo do Filme: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = '\0';

    printf("\nPreço do Filme: R$");
    scanf("%f", &filme.price);
    getchar();

    filme.qtd_disponivel = 0;
    filme.n_alugueis = 0;
    filme.n_devolucoes = 0;


    char codigo[20];
    int indice_encontrado;
    do
    {
        printf("\nCódigo do Filme: ");
        scanf("%s", codigo);
        getchar();

        if (numero_filmes == 0)
        {
            strcpy(filme.codigo_filme, codigo);
            break;
        }
        else
        {
            indice_encontrado = buscar_Filme(filmes, numero_filmes, codigo);

            if (indice_encontrado != -1)
            {
                printf("\nJá existe um filme na lista com esse código, tente digitar outro!\n");
                continue;
            }
            else
            {
                strcpy(filme.codigo_filme, codigo);
                break;
            }
        }
    } while (1);
    
    filme.status = 0;

    return filme;
}


int estocar_Filme(Filme filmes[], int tam, char codigo[])
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(codigo, filmes[i].codigo_filme) == 0 && filmes[i].status == 1)
        {
            printf("Digite o quanto você quer estocar: ");
            scanf("%i", &filmes[i].qtd_disponivel);
            return 1;
        }   
    }

    return 0;
}


int inserir_Filme(Filme filmes[], int tam, int pos, Filme novo, int *numero_filmes)
{
    if (pos < 0 || pos >= tam)
    {
        printf("\nPosição inválida!!!\n");
        return 0;
    }
    else
    {
        if (filmes[pos].status == 1)
        {
            printf("\nEsta posição já está ocupada!\n");
            return 0;
        }
        else
        {
            filmes[pos] = novo;
            (*numero_filmes)++;
            filmes[pos].status = 1;
            return 1;
        }
    } 
}


int remover_Filme(Filme filmes[], int tam, char codigo[], int *numero_filmes)
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(codigo, filmes[i].codigo_filme) == 0 && filmes[i].status == 1)
        {
            filmes[i].status = 0;
            filmes[i].n_alugueis = 0;
            filmes[i].n_devolucoes = 0;
            filmes[i].qtd_disponivel = 0;
            (*numero_filmes)--;
            return 1;
        }
    }

    return 0;
}


int alugar_Filme(Filme filmes[], int tam, char codigo[], float* total)
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(codigo, filmes[i].codigo_filme) == 0 && filmes[i].status == 1)
        {
            if (filmes[i].qtd_disponivel > 0)
            {
                filmes[i].qtd_disponivel--;
                filmes[i].n_alugueis++;
                (*total) += filmes[i].price;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}


int devolver_Filme(Filme filmes[], int tam, char codigo[])
{
    for (int i = 0; i < tam; i++)
    {
        if (strcmp(codigo, filmes[i].codigo_filme) == 0 && filmes[i].status == 1)
        {
            filmes[i].qtd_disponivel++;
            filmes[i].n_devolucoes++;
            return 1;
        }
    }

    return 0;
}


void relatorios_Vendas(Filme filmes[], int tam, int id_rel, float total)
{
    int i, j;
    Filme temp;

    if (id_rel == 1)
    {

        for (i = 0; i < tam - 1; i++) {
            for (j = 0; j < tam - 1 - i; j++) {
                if (filmes[j].n_alugueis < filmes[j+1].n_alugueis) {
                    temp = filmes[j];
                    filmes[j] = filmes[j+1];
                    filmes[j+1] = temp;
                }
            }
        }

        printf("=====================================\n");
        printf("FILMES MAIS ALUGADOS:\n");
        for (int f = 0; f < tam; f++)
        {
            if (filmes[f].status == 1)
            {
                printf("[TÍTULO: %s | PREÇO: R$%.2f | N_ALUGUÉIS: %i]\n\n", filmes[f].titulo, filmes[f].price, filmes[f].n_alugueis);
            }
        }
        printf("=====================================\n\n\n");
    }

    else if (id_rel == 2)
    {
        for (i = 0; i < tam - 1; i++) {
            for (j = 0; j < tam - 1 - i; j++) {
                if (filmes[j].n_devolucoes < filmes[j+1].n_devolucoes) {
                    temp = filmes[j];
                    filmes[j] = filmes[j+1];
                    filmes[j+1] = temp;
                }
            }
        }

        printf("=====================================\n");
        printf("FILMES MAIS ALUGADOS:\n");
        for (int f = 0; f < tam; f++)
        {
            if (filmes[f].status == 1)
            {
                printf("[TÍTULO: %s | N_ALUGUÉIS: %i]\n\n", filmes[f].titulo, filmes[f].n_devolucoes);
            }
        }
        printf("=====================================\n\n\n");
    }

    else if (id_rel == 3)
    {
        printf("=====================================\n");
        printf("Total acumulado: R$%.2f\n", total);
        printf("=====================================\n");
    }

    else if (id_rel == 4)
    {
        printf("=====================================\n");
        printf("FILMES EM ESTOQUE:\n");
        for (int p = 0; p < tam; p++)
        {
            if (filmes[p].qtd_disponivel > 0 && filmes[i].status == 1)
            {
                printf("[TÍTULO: %s | ESTOQUE: %i]", filmes[p].titulo, filmes[p].qtd_disponivel);
            }
        }
    }
}


int main()
{   
    int tam = 10;
    int posicao_filme;
    int numero_filmes = 0;
    char codigo[20];
    float total;

    Filme lista_filmes[tam];

    incializar_status_zero(lista_filmes, tam);



    int choice;
    int choice_bool;
    int pos_bool;
    do
    {
        printf("===================== SEJA BEM-VINDO A LOCADORA 2000 ===================\n");
        printf("\nLembre-se que para usar o sistema você deve inserir pelo menos um filme!\n\n");
        printf("\nNúmero de Filmes: %i\n\n", numero_filmes);
        printf("MENU: \n[1] INSERIR FILME \n[2] ESTOCAR FILME \n[3] MOSTRAR FILMES \n[4] REMOVER FILMES \n[5] ALUGAR FILME \n[6] DEVOLVER FILME \n[7] SAIR DO SISTEMA\n\n>> ");
        choice_bool = scanf("%i", &choice);
        getchar();


        while (choice < 0 || choice > 7 || choice_bool == 0)
        {
            printf("\nDado inválido!!! Digite novamente!\n\n");
            printf(">> ");
            choice_bool = scanf("%i", &choice);
            getchar();
        }

        
        if (choice == 1)
        {
            printf("\nDigite o índice da posição que você deseja inserir o filme (A estante possui %i espaços com índices de 0 a %i): ", tam, tam-1);
            pos_bool = scanf("%i", &posicao_filme);
            getchar();

            while (pos_bool < 0 || pos_bool >= tam || pos_bool == 0)
            {
                printf("\nDado inválido!!! Digite novamente!\n\n");
                printf(">> ");
                pos_bool = scanf("%i", &posicao_filme);
                getchar();
            }            


            int insercao_bool = inserir_Filme(lista_filmes, tam, posicao_filme, criar_Filme(lista_filmes, numero_filmes), &numero_filmes);

            if (insercao_bool == 1)
            {
                printf("\nFilme inserido com sucesso!!!\n");
            }
            else
            {
                printf("\nERRO AO INSERIR FILME!\n");
                continue;
            }
        }

        else if (choice == 2 && numero_filmes > 0)
        {
            printf("\nDigite o código do filme que deseja estocar: ");
            scanf("%s", codigo);
            getchar();

           int estocar_bool = estocar_Filme(lista_filmes, tam, codigo);

           if (estocar_bool == 1)
           {
                printf("\nestoque adicionado com sucesso!\n");
           }
           else
           {
                printf("\nERRO! Você está tentando estocar um filme que não está no sistema!\n");
           }
        }

        else if (choice == 3 && numero_filmes > 0)
        {
            imprimir_Filmes(lista_filmes, tam);
        }

        else if (choice == 4 && numero_filmes > 0)
        {
            printf("\nDigite o código do filme que deseja remover: ");
            scanf("%s", codigo);
            getchar();

            int remocao_bool = remover_Filme(lista_filmes, tam, codigo, &numero_filmes);

            if (remocao_bool == 1)
            {
                printf("\nFilme removido com sucesso!\n");
            }
            else
            {
                printf("ERRO! Você está tentando remover um filme que não está no sistema");
            }
        }

        else if (choice == 5 && numero_filmes > 0)
        {
            printf("\nDigite o código do filme que deseja alugar: ");
            scanf("%s", codigo);
            getchar();


            int alugar_bool = alugar_Filme(lista_filmes, tam, codigo, &total);

            if (alugar_bool == 1)
            {
                printf("\nDivirta-se com o seu filme!\n");
            }
            else
            {
                printf("\nERRO: Você está tentando alugar um filme que não está no sistema OU está com falta de estoque!\n");
                continue;
            }
        }

        else if (choice == 6 && numero_filmes > 0)
        {
            printf("\nDigite o código do filme que você deseja devolver: ");
            scanf("%s", codigo);
            getchar();


            int devolucao_bool = devolver_Filme(lista_filmes, tam, codigo);

            if (devolucao_bool == 1)
            {
                printf("\nObrigado por devolver e volte sempre!\n");
            }
            else
            {
                printf("\nERRO: Você está tentando devolver um filme que não está no sistema!\n");
                continue;
            }
        }

        else if (choice == 7)
        {
            printf("\nObrigado por usar o sistema da Locadora 2000!\n");
            break;
        }
    } while (1);
    
    system("clear");

    relatorios_Vendas(lista_filmes, tam, 1, total);
    printf("\n\n");
    relatorios_Vendas(lista_filmes, tam, 2, total);
    printf("\n\n");
    relatorios_Vendas(lista_filmes, tam, 3, total);
    printf("\n\n");
    relatorios_Vendas(lista_filmes, tam, 4, total);
}