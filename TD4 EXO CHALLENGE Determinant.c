#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct zmatrix {
  int n ; // nombre de lignes
  int m ; // nombre de colonnes
  float **M ; // la matrice nxm
} ;

typedef struct zmatrix mymatrix ;

mymatrix * creer (int n, int m)
{
  int i, j ;
  mymatrix * tmp = malloc(sizeof(mymatrix)) ;
  tmp->n = n ;
  tmp->m = m ;
  // allocation de la matrice
  tmp->M = malloc(n*sizeof(float*)) ;
  for (i=0; i<n; i++)
    (tmp->M)[i] = malloc(m*sizeof(float)) ;
  // initialisation à 0
  for (i=0; i<n; i++)
  {
    for (j=0; j<m; j++)
      (tmp->M)[i][j] = 0 ;
  }
  return tmp ;
}


mymatrix * concatener (mymatrix *A, mymatrix *B)
{
  mymatrix *C ;
  int i, j, k ;
  assert(A->n == B->n) ;
  C = creer(A->n, A->m+B->m) ;
  for (i=0; i < A->n; i++)
  {
    k = 0 ;
    for (j=0; j < A->m;  j++,k++)
      (C->M)[i][k] = (A->M)[i][j] ;
    for (j=0; j < B->m;  j++,k++)
      (C->M)[i][k] = (B->M)[i][j] ;
  }
  return C ;
}

void print_matrix(mymatrix *A)
{
  int i, j ;
  for (i=0; i<A->n; i++)
  {
    for (j=0; j<A->m; j++)
    {
      printf("%0.2f\t", (A->M)[i][j]);
    }
    printf("\n") ;
  }
  printf("\n");
}
int gauss(mymatrix *C,int n, int k) {

    for (int z=0;z<C->n-1;z++)
    {
        for (int i=z+1;i<C->n;i++)
        {
            for (int j=z+1;j<C->n;j++)
                C->M[i][j]-=C->M[z][j]*C->M[i][z]/C->M[z][z];
           C->M[i][n]-=C->M[i][z]*C->M[z][n]/C->M[z][z];
           if(C->M[n-1][n-1]==0)// Si le dernier element de la diagonale de A est nul la matrice est non inversible
                return 0;
            C->M[i][z]=0;
        }
    }
    return 1;
}
int remontee_gauss(mymatrix *C,int n,int k)
{
    int i,j,z;
    for(i=C->n-1;i>=0;i--)
    {
        for(j=C->n-1;j>i;j--)
        {
            for(z=C->n;z<C->m;z++)
                C->M[i][z]=C->M[i][z]-C->M[i][j]*C->M[j][z];
        C->M[i][j]=0;
        }
     for(z=C->n;z<C->m;z++)
        C->M[i][z]=C->M[i][z]/C->M[i][i];
     C->M[i][i]=1;
    }
 return 1;
}
float determinant(mymatrix *C)
{
    int i;
    float det=1;
    for(i=0;i<C->n;i++)
        det=det*C->M[i][i];
    return det;
}
int main()
{
  mymatrix *A = creer(3,3);
  mymatrix *B = creer(3,1);
  mymatrix *C ;
    A->M[0][0]=1;
    A->M[0][1]=1;
    A->M[0][2]=2;
    A->M[1][0]=1;
    A->M[1][1]=-1;
    A->M[1][2]=-1;
    A->M[2][0]=1;
    A->M[2][1]=0;
    A->M[2][2]=1;
  (B->M)[0][0] = 5;
  (B->M)[1][0] = 1;
  (B->M)[2][0] = 3;
  C = concatener(A,B);
printf("Matrice C : Obtenu par concatenation de A et B\n");
  print_matrix(C);
    gauss(C,B->n,B->m);
    printf("Question 1) : \n");
    printf("Matrice C : Descente de Gauss\n");
    print_matrix(C);
     printf("Question 2) : \n");
    printf("Matrice C : Remontee de Gauss\n");
    remontee_gauss(C,B->n,B->m);
    print_matrix(C);
    printf("Question 3) : \n");
    printf("Resoudre le systeme lineaire : La resolution du systeme ce fait grace a la question 1 et 2 par exemple la solution de ce systeme ce voit a la question 2\n");
    printf("Inverser des matrices : L'inverse d'une matrice triangulaire supérieur est une matrice triangulaire supérieur il suffit d'inverser les elements a la diagonal de la matrice comme la matrice est une matrice identite alors l'inverse de la matrice  C est note C^-1 = C\n");
    printf("Determinant : Le determinant de C est egale au determinant de la matrice triangulaire(multiplication de ses elements diagonaux).\n");
    printf("Le determinant de C est : %0.2f",determinant(C));
  return 0;
}
