#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


// Struct para definir os Players
typedef struct
{
    int id_player;
    char name[30];
    float defense;
    float attack;
    float life;
    int died;

} player;


// Função para inicializar os times
void initialize_team(player* player, int ids_init, int ids_end, char team[], int color)
{
    srand(time(NULL));

    if (color == 0){
        printf("\033[1;33m========================\033[m\n");
        printf("\033[1;31m        %s          \033[m\n", team);
        printf("\033[1;33m========================\033[m\n\n");
    }
    else if (color == 1)
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

        player[i].died = 0;
        printf("========================\n");
    }
}


// Função para definir qual time irá começar
int set_the_time_team()
{
    srand(time(NULL));

    // 0 - Red Team; 1 - Blue Team

    return rand()%2;
}


// Função para atacar outros jogadores
void attack_func(player* attack_team, player* defense_team, int attack_ch_id, int defense_ch_id)
{
    srand(time(NULL));

    // Precisão do jogador que está atacando
    float accuracy = (1 - ((attack_team[attack_ch_id].life * attack_team[attack_ch_id].attack)/1000))*100;
    
    float num = (rand()%101);

    if (num < accuracy){
        printf("\n\n\033[1;33m============================================================\033[m\n");
        printf("\033[1;35mO lutador(a) %s errou o ataque no lutador %s!!!\033[m\n", attack_team[attack_ch_id].name, defense_team[defense_ch_id].name);
        printf("\033[1;33m============================================================\033[m\n\n");
    }
    else
    {
        float damage = attack_team[attack_ch_id].attack/(defense_team[defense_ch_id].defense/10);
        defense_team[defense_ch_id].life -= damage;
        printf("\n\n\033[1;33m============================================================\033[m\n");
        printf("\033[1;35mO lutador(a) %s acertou o ataque no lutador %s!!!\033[m\n", attack_team[attack_ch_id].name, defense_team[defense_ch_id].name);
        printf("\033[1;35mLutador(a) %s arrancou %.2f de vida do lutador %s\033[m\n", attack_team[attack_ch_id].name, damage, defense_team[defense_ch_id].name);
        printf("\033[1;33m============================================================\033[m\n");
    }
}


// Função que define a morte de um jogador
void death_func(player* player, int id_pla, int* deaths, int team)
{
    if (team == 0)
    {
        if (player[id_pla].life <= 0){
            player[id_pla].life = 0;
            printf("\n\n========================================\n");
            printf("%s do RED TEAM acabou de morrer!!!\n", player[id_pla].name);
            printf("========================================\n\n");
            *deaths += 1;
            player[id_pla].died = 1;
        }
    }
    else if (team == 1)
    {
        if (player[id_pla].life <= 0){
            player[id_pla].life = 0;
            printf("\n\n========================================\n");
            printf("%s do BLUE TEAM acabou de morrer!!!\n", player[id_pla].name);
            printf("========================================\n\n");
            *deaths += 1;
            player[id_pla].died = 1;
        }
    }
}


// Função que realiza o sistema de combat
void combat_system(int* time_team, int qtd, player* red_team, player* blue_team, int choice, int* blue_deaths, int* red_deaths)
{   
    if (*time_team == 0)
    {
        for (int c = 0; c < qtd; c++)
        {
            if (red_team[c].died == 0)
            {
                printf("======================\n");
                printf("\033[1;36m   TIME TEAM: RED   \033[m\n");

                printf("======================\n\n");
                printf("TEAM: \033[1;31mRED\033[m\n");
                printf("ID: %i\n", red_team[c].id_player);
                printf("WARRIOR NAME: %s\n", red_team[c].name);
                printf("LIFE: %.2f\n", red_team[c].life);
                printf("ATTACK: %.2f\n", red_team[c].attack);
                printf("DEFENSE: %.2f\n", red_team[c].defense);
                printf("======================\n\n\n\n");
    
                printf("\033[1;33m==============================\033[m\n");
                for (int i = 0; i < qtd; i++)
                {
                    printf("TEAM: \033[1;34mBLUE\033[m\n");
                    printf("ID: %i\n", blue_team[i].id_player);
                    printf("WARRIOR NAME: %s\n", blue_team[i].name);
                    printf("LIFE: %.2f\n\n", blue_team[i].life);
                }
                printf("\033[1;33m==============================\033[m\n\n\n");
    
                printf("\033[1;33m==============================\033[m\n");
                printf("\033[1;36mRed Deaths: %i\n", *red_deaths);
                printf("\033[1;36mBlue Deaths: %i\n", *blue_deaths);
                printf("\033[1;33m==============================\033[m\n\n\n");
    
                printf("Escolha o ID do jogador que você deseja atacar: ");
                scanf("%i", &choice);
                getchar();
    
                while (choice < 0 || choice > 3){
                    printf("\nDADO INVÁLIDO!!! Digite um ID válido: ");
                    scanf("%i", &choice);
                }
    
                while (blue_team[choice].died == 1)
                {
                    printf("\nO lutador(a) %s já está morto(a)!!! Digite outro ID: ", blue_team[choice].name);
                    scanf("%i", &choice);
                }
    
                sleep(1);
    
                attack_func(red_team, blue_team, c, choice);
                death_func(blue_team, choice, blue_deaths, 1);
    
                if (*blue_deaths == 4)
                {
                    break;
                    sleep(4);
                    system("clear");
                }
    
                sleep(4);
                system("clear");
            }
        }

        *time_team = 1;
    }
    else if (*time_team == 1)
    {
        for (int c = 0; c < qtd; c++)
        {
            if (blue_team[c].died == 0)
            {
                printf("======================\n");
                printf("\033[1;36m   TIME TEAM: BLUE   \033[m\n");

                printf("======================\n\n");
                printf("TEAM: \033[1;34mBLUE\033[m\n");
                printf("ID: %i\n", blue_team[c].id_player);
                printf("WARRIOR NAME: %s\n", blue_team[c].name);
                printf("LIFE: %.2f\n", blue_team[c].life);
                printf("ATTACK: %.2f\n", blue_team[c].attack);
                printf("DEFENSE: %.2f\n", blue_team[c].defense);
                printf("======================\n\n\n\n");
    
                printf("\033[1;33m==============================\033[m\n");
                for (int i = 0; i < qtd; i++)
                {
                    printf("TEAM: \033[1;31mRED\033[m\n");
                    printf("ID: %i\n", red_team[i].id_player);
                    printf("WARRIOR NAME: %s\n", red_team[i].name);
                    printf("LIFE: %.2f\n\n", red_team[i].life);
                }
                printf("\033[1;33m==============================\033[m\n\n");
    
                printf("\033[1;33m==============================\033[m\n");
                printf("\033[1;36mRed Deaths: %i\n", *red_deaths);
                printf("\033[1;36mBlue Deaths: %i\n", *blue_deaths);
                printf("\033[1;33m==============================\033[m\n\n\n");
    
                printf("Escolha o ID do jogador que você deseja atacar: ");
                scanf("%i", &choice);
                getchar();
    
                while (choice < 0 || choice > 3){
                    printf("\nDADO INVÁLIDO!!! Digite um ID válido: ");
                    scanf("%i", &choice);
                }
    
                while (red_team[choice].died == 1)
                {
                    printf("\nO lutador(a) %s já está morto(a)!!! Digite outro ID: ", red_team[choice].name);
                    scanf("%i", &choice);
                }
    
                sleep(1);
    
                attack_func(blue_team, red_team, c, choice);
                death_func(red_team, choice, red_deaths, 0);
    
                if (*red_deaths == 4)
                {
                    break;
                    sleep(4);
                    system("clear");
                }
    
                sleep(4);
                system("clear");

            }
        }

        *time_team = 0;
    }
}


int main(void)
{
    // Variáveis auxiliares
    int qtd = 4;
    int red_deaths = 0;
    int blue_deaths = 0;
    int time_team = set_the_time_team();
    int choice;


    // Time Red
    player red_team[qtd];

    // Time Blue
    player blue_team[qtd];


    // Inicializando Times
    initialize_team(red_team, 0, 4, "RED TEAM", 0);
    system("clear");
    initialize_team(blue_team, 0, 4, "BLUE TEAM", 1);
    system("clear");

    // Main loop
    do
    {
        combat_system(&time_team, qtd, red_team, blue_team, choice, &blue_deaths, &red_deaths);


    } while (red_deaths < 4 && blue_deaths < 4);

    system("clear");

    printf("\033[1;33m==============================\033[m\n");
    printf("\033[1;35m          GAME OVER          \033[m\n");
    printf("\033[1;33m==============================\033[m\n\n\n");

    printf("\033[1;33m==============================\033[m\n");
    printf("\033[1;36mRed Deaths: %i\n", red_deaths);
    printf("\033[1;36mBlue Deaths: %i\n", blue_deaths);
    if (red_deaths == 4)
    {
        printf("\n\033[1;35mBLUE TEAM GANHOU A PARTIDA!!!!\033[m\n");
    }
    else if (blue_deaths == 4)
    {
        printf("\n\033[1;35mRED TEAM GANHOU A PARTIDA!!!!\033[m\n");
    }
    printf("\033[1;33m==============================\033[m\n");
    
    return 0;
}