/*
Instituto Politecnico Nacional
Escuela Superior de Cómputo
Analisis de algoritmos
Grupo: 3CV2
Alumnos: Garcia Tello Axel
		 Rodríguez Acosta Alan
Profesor: Benjamin Luna Benoso
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Optimización de las líneas de producción

Fecha: 22 de mayo de 2020
*/
#include <stdlib.h>
#include <stdio.h>

//Función para leer un archivo de texto con las líneas de producción
void LeerArchivo(int **a, int **t, int **e, int **x, int *n){
  char caracter;
  int i=0,
      j=0,
      k=0;
  FILE *fp;
  //Abrimos el archivo
  fp = fopen("LineasProduccion.txt","r");
  if(fp==NULL){
    fprintf(stderr, "File error");
    exit(-1);
  }
  /*Obtenemos el tamaño de nuestras líneas de producción para asignar
   espacio de memoria*/
  caracter=fgetc(fp);
  *n=caracter-'0';
  *a = (int *) malloc((*n)*2*sizeof(int));
  *t = (int *) malloc((*(n)-1)*2*sizeof(int));
  *e = (int *) malloc(2*sizeof(int));
  *x = (int *) malloc(2*sizeof(int));
  //Leemos cada caracter y lo guardamos en su variable correspondiente
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
  fclose(fp);
}

//Función para determinar la linea de producción más óptima
void LineasProduccion(int **a, int **t, int **e, int **x, int n,
  int **f, int **I, int *fr, int *Ir){
    int j=0;

    //Inicialización de la tabla f
    **f = **e + **a;
    *(*f+n) = *(*e+1) + *(*a+n);

    //Evaluamos las n areas de trabajo
    for(j=1; j<n; j++){
      /*Analizamos cual de los 2 posibles caminos de cada area de
      trabajo es el menor, guardamos los datos del seleccionado*/
      if( *(*f+j-1) + *(*a+j) <= *(*f+n+j-1) + *(*t+n+j-2) + *(*a+j) ){
        *(*f+j) = *(*f+j-1) + *(*a+j);
        *(*I+j-1) = 1;
      }
      else{
        *(*f+j) = *(*f+n+j-1) + *(*t+n+j-2) + *(*a+j);
        *(*I+j-1) = 2;
      }
      //Realizamos el mismo analisis ahora con la línea 2
      if( *(*f+n+j-1) + *(*a+n+j) <= *(*f+j-1) + *(*t+j-1) + *(*a+n+j) ){
        *(*f+n+j) = *(*f+n+j-1) + *(*a+n+j);
        *(*I+n+j-2) = 2;
      }
      else{
        *(*f+n+j) = *(*f+j-1) + *(*t+j-1) + *(*a+n+j);
        *(*I+n+j-2) = 1;
      }
    }
    //Analizamos el caso final de salida
    if( *(*f+n-1) + **x <= *(*f+n+n-1) + *(*x+1) ){
      *fr = *(*f+n-1) + **x;
      *Ir = 1;
    }
    else{
      *fr = *(*f+n+n-1) + *(*x+1);
      *Ir = 2;
    }
}

//Función para imprimir tablas en general
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

//Función para imprimir la linea de producción en orden descendente
void imprimirLineaProduccion(int n, int **I, int Ir){
  int i=Ir,
      j=0;
  printf("línea %d, estación %d\n", i, n);
  for(j=n-2;j>=0; j--){
    i=*(*I+((i-1)*(n-1))+j);
    printf("línea %d, estación %d\n", i, j+1);
  }
}

//Inicio del programa
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
  LeerArchivo(&a,&t,&e,&x,&n); //Lectura del archivo
  //Asignamos memoria correspondiente a las tablas de resultados
  f = (int *) malloc(n*2*sizeof(int));
  I = (int *) malloc((n-1)*2*sizeof(int));
  //Calculamos la línea de producción más óptima
  LineasProduccion(&a,&t,&e,&x,n,&f,&I,&fr,&Ir);
  //Imprimimos las tablas
  printf("Tabla f\n");
  imprimir(&f,n);
  printf("\n");
  printf("Tabla I\n");
  imprimir(&I,n-1);
  printf("\n");
  printf("f* : %d\tI* : %d\n", fr, Ir);
  printf("\n");
  printf("Línea de producción más óptima\n");
  imprimirLineaProduccion(n, &I, Ir); //Imprimimos la línea de producción
  //Liberamos el espacio en memoria
  free(a);
  free(t);
  free(e);
  free(x);
  free(f);
  free(I);
}
