#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char name[101];
    int prod_cod;
    int qtd;
    int n_sells;
    int n_buys;
    float price;
    int status; // 0 -> Whithout the System 1 -> Whithin the System
}Product;


void print_Products(Product* shelf, int tam)
{
    for (int prod = 0; prod<tam; prod++)
    {
        printf("\nNome: %s | Preço: %.2f | Código: %i\n", shelf[prod].name, shelf[prod].price, shelf[prod].prod_cod);
    }
}


int main()
{
    // Variáveis auxiliares
    int tam = 10;

    // Vetores auxiliares
    Product shelf[tam];




    print_Products(shelf, tam);
    return 0;
}
