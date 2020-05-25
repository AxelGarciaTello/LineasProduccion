#include <stdlib.h>
#include <stdio.h>

void LeerArchivo(int **a, int **t, int **e, int **x, int *n){
  char caracter;
  int i=0,
      j=0,
      k=0;
  FILE *fp;
  fp = fopen("LineasProduccion.txt","r");
  if(fp==NULL){
    fprintf(stderr, "File error");
    exit(-1);
  }
  caracter=fgetc(fp);
  *n=caracter-'0';
  *a = (int *) malloc((*n)*2*sizeof(int));
  *t = (int *) malloc((*(n)-1)*2*sizeof(int));
  *e = (int *) malloc(2*sizeof(int));
  *x = (int *) malloc(2*sizeof(int));
  caracter=fgetc(fp);
  for(k=0; k<2; k++){
    while((caracter=fgetc(fp))!='\n'){
      if(caracter!=' '){
        *(*a+i)=caracter-'0';
        i++;
      }
    }
  }
  i=0;
  for(k=0; k<2; k++){
    while((caracter=fgetc(fp))!='\n'){
      if(caracter!=' '){
        *(*t+i)=caracter-'0';
        i++;
      }
    }
  }
  i=0;
  while((caracter=fgetc(fp))!='\n'){
    if(caracter!=' '){
      *(*e+i)=caracter-'0';
      i++;
    }
  }
  i=0;
  while((caracter=fgetc(fp))!=EOF){
    if(caracter!=' '){
      *(*x+i)=caracter-'0';
      i++;
    }
  }
}

void LineasProduccion(int **a, int **t, int **e, int **x, int n,
  int **f, int **I, int *fr, int *Ir){
    int j=0;

    **f = **e + **a;
    *(*f+n) = *(*e+1) + *(*a+n);

    for(j=1; j<n; j++){
      if( *(*f+j-1) + *(*a+j) <= *(*f+n+j-1) + *(*t+n+j-2) + *(*a+j) ){
        *(*f+j) = *(*f+j-1) + *(*a+j);
        *(*I+j-1) = 1;
      }
      else{
        *(*f+j) = *(*f+n+j-1) + *(*t+n+j-2) + *(*a+j);
        *(*I+j-1) = 2;
      }
      if( *(*f+n+j-1) + *(*a+n+j) <= *(*f+j-1) + *(*t+j-1) + *(*a+n+j) ){
        *(*f+n+j) = *(*f+n+j-1) + *(*a+n+j);
        *(*I+n+j-2) = 2;
      }
      else{
        *(*f+n+j) = *(*f+j-1) + *(*t+j-1) + *(*a+n+j);
        *(*I+n+j-2) = 1;
      }
    }
    if( *(*f+n-1) + **x <= *(*f+n+n-1) + *(*x+1) ){
      *fr = *(*f+n-1) + **x;
      *Ir = 1;
    }
    else{
      *fr = *(*f+n+n-1) + *(*x+1);
      *Ir = 2;
    }
    //printf("\n");
}

void imprimir(int **A, int n){
  int i=0;
  for(i=0; i<n*2; i++){
    if(i==n){
      printf("\n");
    }
    printf("%d\t", *(*A+i));
  }
  printf("\n");
}

int main(void){
  int n=0,
      *a=0,
      *t=0,
      *e=0,
      *x=0,
      *f=0,
      *I=0,
      fr=0,
      Ir=0;
  LeerArchivo(&a,&t,&e,&x,&n);
  printf("Tabla a\n");
  imprimir(&a, n);
  printf("\n");
  printf("Tabla t\n");
  imprimir(&t, n-1);
  printf("\n");
  printf("Entradas:\n");
  imprimir(&e, 1);
  printf("\n");
  printf("Salidas:\n");
  imprimir(&x, 1);
  printf("\n");
  printf("\n");
  printf("\n");
  f = (int *) malloc(n*2*sizeof(int));
  I = (int *) malloc((n-1)*2*sizeof(int));
  LineasProduccion(&a,&t,&e,&x,n,&f,&I,&fr,&Ir);
  printf("Tabla f\n");
  imprimir(&f,n);
  printf("\n");
  printf("Tabla I\n");
  imprimir(&I,n-1);
  printf("\n");
  printf("f* : %d\tI* : %d", fr, Ir);
  printf("\n");
}
