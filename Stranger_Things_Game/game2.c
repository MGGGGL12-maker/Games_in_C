#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct 
{
    int vida;
    int taxa_raiva;
    int portal_ability; // 0 - Desativada 1 - Ativada
    int world; // 1 - Normal 2 - Invertido
}Player;



void matriz_com_espacos(int tam, char matriz[tam][tam+1])
{
    for (int l = 0; l < tam; l++)
    {
        for (int c = 0; c < tam; c++)
        {
            matriz[l][c] = ' ';
        }
    }
}


void imprimir_matriz(int tam, char matriz[tam][tam+1])
{
    for (int l = 0; l < tam; l++)
    {
        for (int c = 0; c < tam; c++)
        {
            printf("[%c] ", matriz[l][c]);
        }

        printf("\n");
    }
}


void implementar_elementos(int tam, char matriz[tam][tam+1], int qtd, char element)
{
    srand(time(NULL));

    int number_elements = 0;
    int pos_l;
    int pos_c;
    do
    {
        pos_l = rand()%3;
        pos_c = rand()%3;

        if (matriz[pos_l][pos_c] == ' ')
        {
            matriz[pos_l][pos_c] = element;
            number_elements++;
        }
    } while (number_elements < qtd);
}


void movement(int tam, char matriz[tam][tam+1], char move, int *taxa_r, Player *player)
{
    int pos_l, pos_c;

    for (int l = 0; l < tam; l++)
    {
        for (int c = 0; c < tam; c++)
        {
            if (matriz[l][c] == 'E')
            {
                pos_l = l;
                pos_c = c;
            }
        }
    }


    if (move == 'w')
    {
        if (matriz[pos_l-1][pos_c] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l--;
            matriz[pos_l][pos_c] = 'E';
        }
        else if (matriz[pos_l-1][pos_c] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l--;
            matriz[pos_l][pos_c] = 'E';
            player->world = 2;
        }
    }
    else if (move == 's')
    {
        if (matriz[pos_l+1][pos_c] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l++;
            matriz[pos_l][pos_c] = 'E';
        }
        else if (matriz[pos_l+1][pos_c] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l++;
            matriz[pos_l][pos_c] = 'E';
            player->world = 2;
        }
    }
    else if (move == 'a')
    {
        if (matriz[pos_l][pos_c-1] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c--;
            matriz[pos_l][pos_c] = 'E';
        }
        else if (matriz[pos_l][pos_c-1] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c--;
            matriz[pos_l][pos_c] = 'E';
            player->world = 2;
        }
    }
    else if (move == 'd')
    {
        if (matriz[pos_l][pos_c+1] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c++;
            matriz[pos_l][pos_c] = 'E';
        }
        else if (matriz[pos_l][pos_c+1] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c++;
            matriz[pos_l][pos_c] = 'E';
            player->world = 2;
        }
    }

    if (*taxa_r < 100)
    {
        (*taxa_r) += 10;
    }
}


int main()
{
    srand(time(NULL));


    int room_tam = 3;
    int mundo_invertido_tam = 10;


    char room[room_tam][room_tam+1];
    char invertido[mundo_invertido_tam][mundo_invertido_tam+1];


    // Criando a personagem 'Eleven'
    Player player;
    player.vida = 100;
    player.taxa_raiva = 0;
    player.portal_ability = 0;
    player.world = 1;


    matriz_com_espacos(room_tam, room);
    matriz_com_espacos(mundo_invertido_tam, invertido);


    implementar_elementos(room_tam, room, 1, 'E');
    
    
    imprimir_matriz(room_tam, room);


    char move;
    do
    {
        printf("\nVida: %i\n", player.vida);
        printf("Taxa de Raiva: %i%%\n", player.taxa_raiva);
        printf("\n\n(w, a, s, d) >> ");
        scanf("%c", &move);
        getchar();

        system("clear");

        
        
        
        
        if (player.world == 1)
        {
            if (move == 'w')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 's')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 'a')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 'd')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }


            if (player.portal_ability == 0)
            {
                if (player.taxa_raiva >= 60)
                {
                    int portal_chance = rand()%7;
        
                    if (portal_chance == 1)
                    {
                        implementar_elementos(room_tam, room, 1, 'I');
                        player.portal_ability = 1;
                    }
                    else
                    {
                        player.taxa_raiva = 0;
                        player.vida -= 20;
                    }
                }
            }
        }
        else
        {
            if (move == 'w')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 's')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 'a')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
    
            else if (move == 'd')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player);
            }
        }


        if (player.world == 1)
        {
            imprimir_matriz(room_tam, room);
        }
        else
        {
            implementar_elementos(mundo_invertido_tam, invertido, 1, 'E');
            imprimir_matriz(mundo_invertido_tam, invertido);
        }
    } while (player.vida != 0);
    
}