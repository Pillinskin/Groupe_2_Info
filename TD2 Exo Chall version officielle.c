#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Ensemble
{
    int *E;
    int nbelement;
    int taille;

}Ensemble;

void affichage(Ensemble E)
{
    int i;
    printf("{");
    for(i=0;i<E.nbelement-1;i++)
        printf("%d, ",E.E[i]);
    printf("%d}\n",E.E[i]);
}

int recherchedicho(Ensemble E,int x)
{
    int deb=0;
    int milieu;
    int *Tab=E.E;
    int fin=E.nbelement-1;
    do
    {
        milieu = (deb+fin)/2;
        if (Tab[milieu]==x)
            return milieu;
        else
        {
            if(x>Tab[milieu])
                deb=milieu+1;
            else
                fin=milieu-1;
        }
    }
    while (fin>=deb);
    return -1;

}

void appartient_gr_02(int x,int *T1,int s1,int n1)
{
    Ensemble UnEnsemble;
    UnEnsemble.E=T1,UnEnsemble.taille=s1,UnEnsemble.nbelement=n1;
    int result = recherchedicho(UnEnsemble,x);
    if (result==-1)
        printf("%d n'appartient pas a l'ensemble\n",x);
    else
        printf("%d appartient a l'ensemble\n",x);

}

void inclus_gr_02(int *T1,int s1,int n1,int *T2,int s2,int n2)
{
    Ensemble E1,E2;
    E1.E=T1,E1.taille=s1,E1.nbelement=n1;
    E2.E=T2,E2.taille=s2,E2.nbelement=n2;
    int i=0;
    int result = 0;
    while(result!=-1 && i<E1.nbelement)
        result=recherchedicho(E2,E1.E[i++]);
    if(result==-1)
        printf("Le premier ensemble n'est pas inclus dans le deuxieme\n");
    else
        printf("Le premier ensemble est inclus dans le deuxieme\n");

}

void union_gr_02(int *T1,int s1,int n1,int *T2,int s2,int n2, int *T3,int s3,int *n3)
{
    Ensemble E1,E2,E3;
    E1.E=T1,E1.taille=s1,E1.nbelement=n1;
    E2.E=T2,E2.taille=s2,E2.nbelement=n2;
    E2.E=T3,E2.taille=s3,E3.nbelement=n3;
    int i=0,j=0,k=0;
    while(i<E1.nbelement || j<E2.nbelement)
	{
		if(i==E1.nbelement)
			E3.E[k]=E2.E[j++];
		else if(j==E2.nbelement)
			E3.E[k]=E1.E[i++];
		else
			if (E1.E[i]<E2.E[j])
				E3.E[k]=E1.E[i++];
			 else if (E1.E[i] > E2.E[j])
                E3.E[k]=E2.E[j++];
            else
            {
                E3.E[k] = (E1.nbelement < E2.nbelement) ? E1.E[i++] : E2.E[j++];
                (E1.nbelement < E2.nbelement) ? j++ : i++;
                E3.nbelement -= 1;
            }
		k++;
	}
	affichage(E3);
}

void inter_gr_02(int *T1,int s1,int n1,int *T2,int s2,int n2, int *T3,int s3,int *n3)
{
    Ensemble E1,E2,E3;
    E1.E=T1,E1.taille=s1,E1.nbelement=n1;
    E2.E=T2,E2.taille=s2,E2.nbelement=n2;
    E3.E=T3,E2.taille=s3,E3.nbelement=n3;
    int i,k=0,result;
   if(E1.nbelement > E2.nbelement)
       for(i=0;i<E2.nbelement;i++)
       {
            result=recherchedicho(E1,E2.E[i]);
            if (result!=-1)
                E3.E[k++]=E2.E[i];
       }
   else
       for(i=0;i<E1.nbelement;i++)
       {
            result=recherchedicho(E2,E1.E[i]);
            if (result!=-1)
                E3.E[k++]=E1.E[i];
       }
    E3.nbelement=(sizeof(E3)/sizeof(int))-1;
    E3.taille=sizeof(E3);
    affichage(E3);

}

void main()
{
    int T[3]={2,3,32};
    int T2[6]={2,3,4,8,9,32};
    Ensemble UnEnsemble,UnEnsemble2, UnEnsemble3;
    UnEnsemble.E = T, UnEnsemble2.E = T2, UnEnsemble3.E = malloc(sizeof(UnEnsemble.nbelement + UnEnsemble2.nbelement));
    UnEnsemble.nbelement = (sizeof(T)/sizeof(int)),UnEnsemble2.nbelement=(sizeof(T2)/sizeof(int)), UnEnsemble3.nbelement=(sizeof(UnEnsemble3.E)/sizeof(int));
    UnEnsemble.taille=sizeof(T),UnEnsemble2.taille=sizeof(T2), UnEnsemble3.taille=sizeof(UnEnsemble3.E);
    affichage(UnEnsemble);
    affichage(UnEnsemble2);
    appartient_gr_02(32,UnEnsemble.E,UnEnsemble.taille,UnEnsemble.nbelement);
    inclus_gr_02(UnEnsemble.E,UnEnsemble.taille,UnEnsemble.nbelement,UnEnsemble2.E,UnEnsemble2.taille,UnEnsemble2.nbelement);
    inter_gr_02(UnEnsemble.E,UnEnsemble.taille,UnEnsemble.nbelement,UnEnsemble2.E,UnEnsemble2.taille,UnEnsemble2.nbelement,UnEnsemble3.E,UnEnsemble3.taille,UnEnsemble3.nbelement);
    union_gr_02(UnEnsemble.E,UnEnsemble.taille,UnEnsemble.nbelement,UnEnsemble2.E,UnEnsemble2.taille,UnEnsemble2.nbelement,UnEnsemble3.E,UnEnsemble3.taille,UnEnsemble3.nbelement);
}
