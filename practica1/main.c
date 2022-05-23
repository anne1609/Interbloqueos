//1ero suponer q funciona siempre con el mismo nro de procesos y mismo nro de recursos, osea q es matriz cuadrada, mismo nro de filas q columnas

//paso de parametros por referencia en C : https://www.youtube.com/watch?v=vahXpd7HlEw

//BOOL EN C : https://learntutorials.net/es/c/topic/3336/booleano

#define bool int
#define true 1
#define false 0

#define TAM_MATRIZ 20

void solicitar(int matrizPesos[TAM_MATRIZ][TAM_MATRIZ],int filas, int columnas,int proceso,int recurso){
 int columnaArevisar=recurso-1;
 bool columnaCeros;

 if(columnaArevisar<columnas){
   columnaCeros=verificarColumnaCeros(matrizPesos,filas, columnaArevisar);
   if(columnaCeros==true){
     matrizPesos[proceso-1][recurso-1]=1;
   }else{
     matrizPesos[proceso-1][recurso-1]=2;
   }



 }else{
   printf("No es una columna valida, la ejecucion del programa finalizo");
 }



}

void liberar(int matrizPesos[TAM_MATRIZ][TAM_MATRIZ],int filas, int columnas,int proceso,int recurso){
int procesoEspera=0;
int recursoEspera=recurso-1;
bool hayEspera=false;
 if(matrizPesos[proceso-1][recurso-1]==1){
   matrizPesos[proceso-1][recurso-1]=0;
   enColumnaHayDos(matrizPesos,&procesoEspera,recursoEspera,&hayEspera,filas);
   if(hayEspera==true){
     matrizPesos[procesoEspera][recursoEspera]=1;
   }
 }else{
   printf("No se puede liberar, debido a que el proceso no esta usando un recurso");
 }

}
void  enColumnaHayDos(int matriz[TAM_MATRIZ][TAM_MATRIZ], int *fila,int columna,bool *hayEspera, int filas){

     while(*hayEspera==false && *fila<filas){
      if(matriz[*fila][columna]==2){
       *hayEspera=true;
      }
       //cuando ponia *fila++, no funcionaba, cuando es con puntero "*", no funciona ++ o --
       *fila=*fila+1;
     }
     *fila=*fila-1;
}




void inicializarMatrizConCeros(int matriz[TAM_MATRIZ][TAM_MATRIZ], int filas, int columnas){
  int i,j;
   for(i=0;i<filas;i++){
     for(j=0;j<columnas;j++){
        matriz[i][j]=0;
     }
   }

}

bool verificarColumnaCeros(int matriz[TAM_MATRIZ][TAM_MATRIZ],int filas,int columnaArevisar){
bool respuesta=true;
  int fila=0;

     while(respuesta==true && fila<filas){
      if(matriz[fila][columnaArevisar]!=0){
       respuesta=false;
      }

       fila++;
     }

 return respuesta;
}


void imprimirMatriz(int matriz[TAM_MATRIZ][TAM_MATRIZ], int filas, int columnas){
  int i,j=0;
    for(i=0;i<filas;i++){
     for(j=0;j<columnas;j++){
        printf("%i",matriz[i][j]);
     }
     printf("\n");
   }
   printf("\n");
}





int main(){
 int matriz[3][3];
 inicializarMatrizConCeros(matriz,3,3);
 imprimirMatriz(matriz,3,3);
 //solicitar(int matriz,int filas,int columnas,int proceso,int recurso
 printf("\n p1  s   r1\n");
 solicitar(matriz,3,3,1,1);
 imprimirMatriz(matriz,3,3);
 printf("\n p2  s   r1\n");
 solicitar(matriz,3,3,2,1);
 imprimirMatriz(matriz,3,3);
 printf("\n p1  d   r1\n");
 liberar(matriz,3,3,1,1);
 imprimirMatriz(matriz,3,3);



 return 0;

}


