#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Struct para definir os Players
typedef struct
{
    int id_player;
    char name[30];
    float defense;
    float attack;
    float life;

} player;



// Função para inicializar os times
void initialize_team(player* player, int ids_init, int ids_end, char team[], int color)
{
    srand(time(NULL));

    if (color == 2){
        printf("\033[1;33m========================\033[m\n");
        printf("\033[1;31m        %s          \033[m\n", team);
        printf("\033[1;33m========================\033[m\n\n");
    }
    else if (color == 3)
    {
        printf("\033[1;33m========================\033[m\n");
        printf("\033[1;34m        %s          \033[m\n", team);
        printf("\033[1;33m========================\033[m\n\n");
    }

    printf("========================\n");
    for (int i = ids_init; i < ids_end; i++){
        player[i].id_player = i;
        printf("ID: %i\n", player[i].id_player);

        printf("WARRIOR NAME: ");
        scanf("%s", player[i].name);
        getchar();

        player[i].defense = rand()%11;

        player[i].attack = rand()%11;

        while (player[i].attack == 0 || player[i].defense == 0){
            player[i].defense = rand()%11;

            player[i].attack = rand()%11;
        }
        
        player[i].life = 100;
        printf("========================\n");
    }
}


int main(void)
{
    // Quantidade de jogadores
    int qtd = 4;

    // Time Red
    player red_team[qtd];

    // Time Blue
    player blue_team[qtd];


    // Inicializando Times
    initialize_team(red_team, 0, 4, "RED TEAM", 2);
    initialize_team(blue_team, 0, 4, "BLUE TEAM", 3);

    
    return 0;
}