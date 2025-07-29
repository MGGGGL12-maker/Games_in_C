#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct 
{
    int vida;
    int taxa_raiva;
    int portal_ability; // 0 - Desativada 1 - Ativada
    int world; // 1 - Normal 2 - Invertido
    int Will; // 0 - Sem Will 1 - Com Will
    int vitoria; // 0 - Não ganhou 1 - Ganhou
}Player;


typedef struct 
{
    int pos_l;
    int pos_c;
    int ativo; // 0 - Derrotado 1 - Ativo
}Demodog;


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
    int number_elements = 0;
    int pos_l;
    int pos_c;
    do
    {
        pos_l = rand()%tam;
        pos_c = rand()%tam;

        if (matriz[pos_l][pos_c] == ' ')
        {
            matriz[pos_l][pos_c] = element;
            number_elements++;
        }
    } while (number_elements < qtd);
}


void will_movement(int tam, char matriz[tam][tam+1], Player *player)
{
    int pos_l_w = -1, pos_c_w = -1;

    for (int l = 0; l < tam; l++)
    {
        for (int c = 0; c < tam; c++)
        {
            if (matriz[l][c] == 'W')
            {
                pos_l_w = l;
                pos_c_w = c;
                break;
            }
        }
        if (pos_l_w != -1)
            break;
    }
    
    if (pos_l_w == -1)
        return;

    int new_l = pos_l_w;
    int new_c = pos_c_w;

    for (int attempts = 0; attempts < 10; attempts++)
    {
        int move_w = rand() % 4;

        new_l = pos_l_w;
        new_c = pos_c_w;

        if (matriz[new_l-1][new_c] == 'E')
        {
            printf("\n\nEvelen encontrou Will!!!\n\n");
            matriz[new_l][new_c] = ' ';
            player->Will = 1;
            break;
        }
        else if (matriz[new_l+1][new_c] == 'E')
        {
            printf("\n\nEvelen encontrou Will!!!\n\n");
            matriz[new_l][new_c] = ' ';
            player->Will = 1;
            break;
        }
        else if (matriz[new_l][new_c-1] == 'E')
        {
            printf("\n\nEvelen encontrou Will!!!\n\n");
            matriz[new_l][new_c] = ' ';
            player->Will = 1;
            break;
        }
        else if (matriz[new_l][new_c+1] == 'E')
        {
            printf("\n\nEvelen encontrou Will!!!\n\n");
            matriz[new_l][new_c] = ' ';
            player->Will = 1;
            break;
        }

        if (move_w == 0)
            new_l--; // Cima
        else if (move_w == 1)
            new_l++; // Baixo
        else if (move_w == 2)
            new_c--; // Esquerda
        else if (move_w == 3)
            new_c++; // Direita

        if (new_l >= 0 && new_l < tam && new_c >= 0 && new_c < tam && matriz[new_l][new_c] == ' ')
        {
            matriz[pos_l_w][pos_c_w] = ' ';
            matriz[new_l][new_c] = 'W';
            break;
        }
    }
}


void movement(int tam, char matriz[tam][tam+1], char move, int *taxa_r, Player *player, int tam_invertido, char invertido[tam_invertido][tam_invertido+1], int qtd_demodogs, Demodog demodogs[])
{
    int pos_l, pos_c;
    int l, c;

    for (l = 0; l < tam; l++)
    {
        for (c = 0; c < tam; c++)
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

            if (player->world == 2)
            {
                for (int i = 0; i < qtd_demodogs; i++)
                {
                    if (demodogs[i].pos_l == pos_l-1 && demodogs[i].pos_c == pos_c && demodogs[i].ativo == 1)
                    {
                        player->vida -= 10;
                        printf("\n\nVocê esbarrou em um DEMODOG e gastou 10 de vida para derrotá-lo!!!\n\n");
                        demodogs[i].ativo = 0;
                    }
                    
                }
            }

        }
        else if (matriz[pos_l-1][pos_c] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            implementar_elementos(tam_invertido, invertido, 1, 'E');
            player->world = 2;
        }
        else if (matriz[pos_l-1][pos_c] == 'P')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l--;
            matriz[pos_l][pos_c] = 'E';
            if (player->vida < 100)
            {
                player->vida+=5;
                printf("\n\nVocê coletou uma panqueca! +5 de Vida\n\n");
            }
        }
        else if (matriz[pos_l-1][pos_c] == 'R' && player->Will == 1)
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l--;
            matriz[pos_l][pos_c] = 'E';
            player->vitoria = 1;
        }
    }

    else if (move == 's')
    {
        if (matriz[pos_l+1][pos_c] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l++;
            matriz[pos_l][pos_c] = 'E';

            if (player->world == 2)
            {
                for (int i = 0; i < qtd_demodogs; i++)
                {
                    if (demodogs[i].pos_l == pos_l+1 && demodogs[i].pos_c == pos_c && demodogs[i].ativo == 1)
                    {
                        player->vida -= 10;
                        printf("\n\nVocê esbarrou em um DEMODOG e gastou 10 de vida para derrotá-lo!!!\n\n");
                        demodogs[i].ativo = 0;
                    }
                }
            }
            

        }
        else if (matriz[pos_l+1][pos_c] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            implementar_elementos(tam_invertido, invertido, 1, 'E');
            player->world = 2;
        }
        else if (matriz[pos_l+1][pos_c] == 'P')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l++;
            matriz[pos_l][pos_c] = 'E';
            if (player->vida < 100)
            {
                player->vida+=5;
                printf("\n\nVocê coletou uma panqueca! +5 de Vida\n\n");
            }
        }
        else if (matriz[pos_l+1][pos_c] == 'R' && player->Will == 1)
        {
            matriz[pos_l][pos_c] = ' ';
            pos_l++;
            matriz[pos_l][pos_c] = 'E';
            player->vitoria = 1;
        }
    }

    else if (move == 'a')
    {
        if (matriz[pos_l][pos_c-1] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c--;
            matriz[pos_l][pos_c] = 'E';

            if (player->world == 2)
            {
                for (int i = 0; i < qtd_demodogs; i++)
                {
                    if (demodogs[i].pos_l == pos_l && demodogs[i].pos_c == pos_c-1 && demodogs[i].ativo == 1)
                    {
                        player->vida -= 10;
                        printf("\n\nVocê esbarrou em um DEMODOG e gastou 10 de vida para derrotá-lo!!!\n\n");
                        demodogs[i].ativo = 0;
                    }
                }
            }
            
        }
        else if (matriz[pos_l][pos_c-1] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            implementar_elementos(tam_invertido, invertido, 1, 'E');
            player->world = 2;
        }
        else if (matriz[pos_l][pos_c-1] == 'P')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c--;
            matriz[pos_l][pos_c] = 'E';
            if (player->vida < 100)
            {
                player->vida+=5;
                printf("\n\nVocê coletou uma panqueca! +5 de Vida\n\n");
            }
        }
        else if (matriz[pos_l][pos_c-1] == 'R' && player->Will == 1)
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c--;
            matriz[pos_l][pos_c] = 'E';
            player->vitoria = 1;
        }
    }

    else if (move == 'd')
    {
        if (matriz[pos_l][pos_c+1] == ' ')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c++;
            matriz[pos_l][pos_c] = 'E';

            if (player->world == 2)
            {
                for (int i = 0; i < qtd_demodogs; i++)
                {
                    if (demodogs[i].pos_l == pos_l && demodogs[i].pos_c == pos_c+1 && demodogs[i].ativo == 1)
                    {
                        player->vida -= 10;
                        printf("\n\nVocê esbarrou em um DEMODOG e gastou 10 de vida para derrotá-lo!!!\n\n");
                        demodogs[i].ativo = 0;
                    }
                }
            }
            
        }
        else if (matriz[pos_l][pos_c+1] == 'I')
        {
            matriz[pos_l][pos_c] = ' ';
            implementar_elementos(tam_invertido, invertido, 1, 'E');
            player->world = 2;
        }
        else if (matriz[pos_l][pos_c+1] == 'P')
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c++;
            matriz[pos_l][pos_c] = 'E';
            if (player->vida < 100)
            {
                player->vida+=5;
                printf("\n\nVocê coletou uma panqueca! +5 de Vida\n\n");
            }
        }
        else if (matriz[pos_l][pos_c+1] == 'R' && player->Will == 1)
        {
            matriz[pos_l][pos_c] = ' ';
            pos_c++;
            matriz[pos_l][pos_c] = 'E';
            player->vitoria = 1;
        }
    }

    if (*taxa_r < 100)
    {
        (*taxa_r) += 10;
    }
}


void posicoes_Demodogs(Demodog demodogs[], int qtd, int invertido_tam, char matriz[invertido_tam][invertido_tam+1])
{   
    int pos_l;
    int pos_c;


    for (int i = 0; i < qtd; i++)
    {
        do
        {
            pos_l = rand()%invertido_tam;
            pos_c = rand()%invertido_tam;
    
            if (matriz[pos_l][pos_c] == ' ')
            {
                demodogs[i].pos_l = pos_l;
                demodogs[i].pos_c = pos_c;
                break;
            }
        } while (1);

        demodogs[i].ativo = 1;
    }
}


int main()
{
    srand(time(NULL));


    int room_tam = 3;
    int mundo_invertido_tam = 10;
    int qtd_demodogs = 4;

    
    char room[room_tam][room_tam+1];
    char invertido[mundo_invertido_tam][mundo_invertido_tam+1];

    
    Demodog demodogs[qtd_demodogs];
    
    
    
    
    // Criando a personagem 'Eleven'
    Player player;
    player.vida = 100;
    player.taxa_raiva = 0;
    player.portal_ability = 0;
    player.world = 1;
    player.Will = 0;
    player.vitoria = 0;
    
    
    matriz_com_espacos(room_tam, room);
    matriz_com_espacos(mundo_invertido_tam, invertido);
    

    implementar_elementos(room_tam, room, 1, 'E'); // E - "Eleven"
    
    implementar_elementos(mundo_invertido_tam, invertido, 10, 'A'); // A - "Árvores"
    implementar_elementos(mundo_invertido_tam, invertido, 5, 'C'); // C - "Carros"
    implementar_elementos(mundo_invertido_tam, invertido, 5, 'M'); // M - "Casas Abandonadas/Mansões abandonadas"
    implementar_elementos(mundo_invertido_tam, invertido, 10, 'P'); // P = "Panquecas"
    implementar_elementos(mundo_invertido_tam, invertido, 1, 'W'); // W = "Will"_
    implementar_elementos(mundo_invertido_tam, invertido, 1, 'R'); // R = "Portal para o mundo Real"
    posicoes_Demodogs(demodogs, qtd_demodogs, mundo_invertido_tam, invertido);
    

    imprimir_matriz(room_tam, room);
    
    char move;
    do
    {
        printf("\nVida: %i\n", player.vida);
        printf("Taxa de Raiva: %i%%\n", player.taxa_raiva);
        printf("\n\n(w, a, s, d) >> ");
        scanf("%c", &move);
        getchar();


        system("clear"); // Caso esteja usando Windows, troque por "clear" por "cls"
        
        
        if (player.world == 1)
        {
            if (move == 'w')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
            }
    
            else if (move == 's')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
            }
    
            else if (move == 'a')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
            }
    
            else if (move == 'd')
            {
                movement(room_tam, room, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
            }


            if (player.portal_ability == 0)
            {
                if (player.taxa_raiva >= 60)
                {
                    int portal_chance = rand()%6;
        
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
                movement(mundo_invertido_tam, invertido, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
                will_movement(mundo_invertido_tam, invertido, &player);
            }
    
            else if (move == 's')
            {
                movement(mundo_invertido_tam, invertido, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
                will_movement(mundo_invertido_tam, invertido, &player);
            }
    
            else if (move == 'a')
            {
                movement(mundo_invertido_tam, invertido, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
                will_movement(mundo_invertido_tam, invertido, &player);
            }
    
            else if (move == 'd')
            {
                movement(mundo_invertido_tam, invertido, move, &player.taxa_raiva, &player, mundo_invertido_tam, invertido, qtd_demodogs, demodogs);
                will_movement(mundo_invertido_tam, invertido, &player);
            }
        }


        if (player.world == 1)
        {
            imprimir_matriz(room_tam, room);
        }
        else
        {
            imprimir_matriz(mundo_invertido_tam, invertido);
        }

    } while (player.vida > 0 && player.vitoria != 1);


    system("clear"); // Caso esteja usando Windows, troque por "clear" por "cls"
    
    if (player.vida <= 0)
    {
        printf("\n============================================\n");
        printf("GAME OVER!!! VOCÊ MORREU!!!\n");
        printf("============================================\n");
    }
    else if (player.vitoria == 1)
    {
        printf("\n===============================================================================\n");
        printf("GAME OVER!!! VOCÊ SALVOU WILL DO MUNDO INVERTIDO E SOBREVIVEU COM %i DE VIDA!!!\n", player.vida);
        printf("=================================================================================\n");
    }
}