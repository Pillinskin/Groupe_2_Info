#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 9
typedef struct Pile
{
    int pile[N];
    int Len;
}Pile;

Pile depiler(Pile unePile)
{
    unePile.Len-=1;
    return unePile;
}
Pile empiler(Pile unePile, int elt)
{
    unePile.pile[unePile.Len++]=elt;
    return unePile;
}
Pile operation(Pile unePile,char *expr[N])
{
     int i,tmp1,tmp2;
     for(i=0;i<N;i++)
     {
        if(expr[i]=="+" || expr[i]=="*" ||expr[i]=="-" )
        {
            if (unePile.Len<2)
            {
                printf("pas assez d'operandes pour effectuer l'operation %s\n",expr[i]);
                exit(0);
            }
            unePile=depiler(unePile);
            tmp1=tete(unePile);
            unePile=depiler(unePile);
            tmp2=tete(unePile);
            if (expr[i]=="+")
                unePile=empiler(unePile,tmp1+tmp2);
            else if (expr[i]=="*")
                unePile=empiler(unePile,tmp1*tmp2);
            else if (expr[i]=="-")
                unePile=empiler(unePile,tmp1-tmp2);
        }
        else
            unePile=empiler(unePile,atoi(expr[i]));
        printPile(unePile);
     }
    unePile.Len-=1;
    return unePile;
}
int tete(Pile unePile)
{
    return unePile.pile[unePile.Len];
}

void printPile(Pile unePile)
{
    int i;
    printf("{ ");
    for (i=0;i<unePile.Len;i++) printf("%i ",unePile.pile[i]);
    printf("}\n");
}

void main()
{
    Pile unePile;
    unePile.Len=0;
    char *expr[N]={"1","4","5","+","*","3","2","*","+"};
    unePile=operation(unePile,expr);
    if (unePile.Len>0){
        printf("Pas assez d'operateurs dans l'expression");
        exit(0);
    }
    printf("Le resultat de cette expression est: %i\n",tete(unePile));
}
