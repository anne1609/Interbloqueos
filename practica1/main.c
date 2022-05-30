
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#define bool int
#define true 1
#define false 0
#define TAM_MATRIZ 10
#define TAM_FILA 9
int tamanios[40];

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
    printf("\n");
    int k=columnas;
    while(k<(filas+columnas)){
       printf("   r%d ",k+1);
       k++;
    }
    printf("\n");
    for(i=0;i<filas;i++){
     printf("p%d ",i+1);
     for(j=0;j<columnas;j++){
        printf("%i     ",matriz[i][j]);
     }
     printf("\n");
   }
   printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////

struct ListaAdyaNodo
{
	int id;
	// Vertices id
	struct ListaAdyaNodo *sgte;
};
struct Vertices
{
	int dato;
	struct ListaAdyaNodo *sgte;
	struct ListaAdyaNodo *ultimo;
};
struct Graph
{
	int tam;
	struct Vertices *nodo;
};
//set dato del nodo
void setDato(struct Graph *g)
{
	if (g->nodo != NULL)
	{
		int i = 0;
		for (i = 0; i < g->tam; i++)
		{
			// Establecer datos de nodos verticales
			g->nodo[i].dato = i;
			// Establecer valor NULL
			g->nodo[i].sgte = NULL;
			g->nodo[i].sgte = NULL;
		}
	}
	else
	{
		printf("El nodo vertice esta vacio");
	}
}
// Devuelve un nuevo grafo
struct Graph *newGraph(int tam)
{
	if (tam < 1)
	{
		printf("\nTamanio invalido del grafo ");
		exit(0);
	}
	struct Graph *g = (struct Graph *)
	malloc(sizeof(struct Graph));
	g->tam = tam;
	g->nodo = (struct Vertices *)
	malloc(sizeof(struct Vertices) *tam);
	setDato(g);
	return g;
}

//Conecta 2 nodos
void conectar(struct Graph *g, int inicio, int ultimo)
{
	// Primero crea el nodo de Adyacencia
	struct ListaAdyaNodo *arista = (struct ListaAdyaNodo *)
	malloc(sizeof(struct ListaAdyaNodo));
	if (arista != NULL)
	{
		arista->id = ultimo;
		arista->sgte = NULL;
		if (g->nodo[inicio].sgte == NULL)
		{
			g->nodo[inicio].sgte = arista;
		}
		else
		{
			// Agrega arista al final
			g->nodo[inicio].ultimo->sgte = arista;
		}
		// Obtener la ultima arista
		g->nodo[inicio].ultimo = arista;
	}
	else
	{
		printf("\n Overflow de memoria para crear arista");
	}
}

//Agrega arista entre 2 nodos dados
void agregarArista(struct Graph *g, int inicio, int ultimo)
{
	if (inicio < g->tam && ultimo < g->tam)
	{
		conectar(g, inicio, ultimo);
	}
	else
	{

		printf(" Vertices de nodo no validos %d  %d", inicio, ultimo);
	}
}

void imprimirListaAdyacencia(struct Graph *g)
{
	if (g != NULL)
	{
		struct ListaAdyaNodo *temp = NULL;
		for (int i = 0; i < g->tam; i++)
		{
		    if(i<(g->tam/2)){
			printf("\n Lista de adyacencia del vertice p%d: ", i+1);
		    }else{
		        printf("\n Lista de adyacencia del vertice r%d: ", i+1);
		    }

			temp = g->nodo[i].sgte;
			while (temp != NULL)
			{
			    int k=0;
			//temp->id son los vértices del nodo del grafo
            //en este caso temp->id es igual que
            //nodo[temp->id].datos
                if((g->nodo[temp->id].dato)<(g->tam/2)){
				  printf("p%d", g->nodo[temp->id].dato+1);
                }else{
                   printf("r%d", g->nodo[temp->id].dato+1);
                }
				temp = temp->sgte;
				k=k+1;
			}
		}
	}
	else
	{
		printf("Grafo vacio");
	}
}


int detectarCicloConDFS(struct Graph *g,
                int inicio, int aux, int visit[])
{
	if (visit[inicio] == 1 && aux == inicio)
	{
		// Cuando las visitas a un nodo son mas de una
        // Aquí el inicio y el final son iguales
        // Contiene ciclo
		return 1;
	}
	else if (visit[aux] == 1)
	{
		// Cuando los nodos inicial y final no son iguales, entonces
        // Permitir visitar el mismo nodo más de una vez
		return 0;
	}
	// Establecer estado visitado 1
	visit[aux] = 1;
	// Obtener la dirección de la primera arista del nodo actual
	struct ListaAdyaNodo *temp = g->nodo[aux].sgte;
	int estado = 0;
	while (temp != NULL && !estado)
	{
		estado = detectarCicloConDFS(g, inicio, temp->id, visit);
		// Visita el borde siguiente
		temp = temp->sgte;
	}
	return estado;
}
// Método que gestiona el ciclo de búsqueda y detección.
// operación
void verificarCiclo(struct Graph *g)
{
	if (g->tam <= 0)
	{
		printf("Grafo vacio\n");
		return;
	}
	// Imprimir elemento del gráfo
	imprimirListaAdyacencia(g);
	// Esto está almacenando la información sobre
   // Estado del nodo visitante
	int visit[g->tam];
	int resultado = 0;
	int ubicacion = 0;
	while (ubicacion < g->tam && resultado == 0)
	{
		// Establecer todos los nodos de visita como 0
		for (int i = 0; i < g->tam; i++)
		{
			visit[i] = 0;
		}
		// Comprobar si la ruta del nodo contiene ciclo o no
		resultado = detectarCicloConDFS(g, ubicacion, ubicacion, visit);
		// Cambiar la ubicación del nodo
		ubicacion++;
	}
	// Mostrar posible resultado
	if (resultado == 1)
	{
		printf("\n Resultado : Hay ciclo \n");
	}
	else
	{
		printf("\n Resultado : No hay ciclo\n");
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////


 void convertirMatrizAlistaAdya(struct Graph *g,int matriz[TAM_MATRIZ][TAM_MATRIZ], int filas, int columnas){
   int nroVertices=filas*columnas;
   int arrayAux1[filas];
   int arrayAux2[columnas];
   int vert1=0;int vert2=0;
   int fila=0; int columna=0;

   llenarArrayAuxs(arrayAux1,arrayAux2,filas,columnas);

   for(fila=0;fila<filas;fila++){
     for(columna=0;columna<columnas;columna++){

       buscarVertice(matriz,filas,columnas,fila,columna,&vert1,&vert2,arrayAux1,arrayAux2);
       if(matriz[fila][columna]==2) {
          agregarArista(g, vert1, vert2);
       }else if(matriz[fila][columna]==1){
          agregarArista(g, vert2, vert1);
       }
     }

   }

 }
void llenarArrayAuxs(int arrayAux1[],int arrayAux2[],int filas,int columnas){
    int i=0;int j=0;int aux=columnas;
    int nroVertices=filas*columnas;
    for(i=0;i<filas;i++){
        arrayAux1[i]=i;
    }
    for(j=0;j<columnas;j++){
        arrayAux2[j]=aux;
        aux++;
    }

}
void imprimirArray(int array[],int tam){
    int i=0;
    for(i=0;i<tam;i++){
        printf("%i\t",array[i]);

    }
    printf("\n");
}
void buscarVertice(int matriz [TAM_MATRIZ][TAM_MATRIZ],int filas,int columnas,int fila,int columna,int *vert1,int *vert2,int arrayAux1[],int arrayAux2[]){
int i=0; int j=0;
    for(i=0;i<filas;i++){
      if(i==fila){
        *vert1=arrayAux1[i];
      }
    }
    for(j=0;j<columnas;j++){
      if(j==columna){
        *vert2=arrayAux2[j];
      }
    }
}
int readfile(const char *archivo,int indice,int mayor) {
  char texto[TAM_FILA]; // cadena que lee la primera fila del file.txt
  char *proc, *ope, *rec; // punteros que capturan el proceso, operacion y recurso separados por espacios
  char proceso[4];	// cadena que guarda el proceso
  char operacion;	// caracter que guarda la operacion
  char recurso[4];	// cadena que guarda el recurso
  int pr, re;
  //FILE *in = fopen(archivo, "r"); /* Abrimos el archivo para leer. */
  FILE *in = fopen("escenarioCircular.txt", "r"); /* Abrimos el archivo para leer. */
  if (!in)
      printf("No se pudo abrir el archivo.\n"), NULL;
  int i;
  int contador=0;
  char *token;
   llenarArrayConCeros(tamanios);
  //fgets(char arreglo[], int n, stdinTeclado)'\0' '\n';

  while(fgets(texto,TAM_FILA,in)){
 	strtok(texto,"\n");
	//printf("Instruccion: '%s'\n", texto);

	token = strtok(texto," ");

        while(token){

		contador= contador +1;
		if(contador == 1){
			proc = token;
			//printf("proc: '%s'\n", proc);
			int tam = strlen(proc);;
			int i;
			for(i =1; i< tam; i++){
				proceso[i-1] = proc[i];

			}

		}else if(contador ==2){
			ope = token;
			operacion = ope[0];


		}else if(contador ==3){
			rec = token;
			int tam = strlen(proc);
			int i;
			for(i =1; i< tam; i++){
				recurso[i-1] = rec[i];

			}

		}
		//printf("token: '%s'\n", token);


		token = strtok(NULL," ");

	}
	pr = atoi(proceso);
	re = atoi(recurso);
	contador =0;

	if(operacion == 's'){

		llenarConTamanios(pr,re,tamanios,&indice);

	}else if(operacion =='d'){

		llenarConTamanios(pr,re,tamanios,&indice);

	}

  }
  mayorTam(tamanios,&mayor);

  fclose(in);
  return mayor;

}
void readfile2(const char *archivo,int tamanio,int matriz[TAM_MATRIZ][TAM_MATRIZ]) {
  char texto[TAM_FILA]; // cadena que lee la primera fila del file.txt
  char *proc, *ope, *rec; // punteros que capturan el proceso, operacion y recurso separados por espacios
  char proceso[4];	// cadena que guarda el proceso
  char operacion;	// caracter que guarda la operacion
  char recurso[4];	// cadena que guarda el recurso
  int pr, re;
  //FILE *in = fopen(archivo, "r"); /* Abrimos el archivo para leer. */
  FILE *in = fopen("escenarioCircular.txt", "r"); /* Abrimos el archivo para leer. */
  if (!in)
      printf("No se pudo abrir el archivo.\n"), NULL;
  int i;
  int contador=0;
  char *token;
   llenarArrayConCeros(tamanios);
  //fgets(char arreglo[], int n, stdinTeclado)'\0' '\n';

  while(fgets(texto,TAM_FILA,in)){
 	strtok(texto,"\n");
	printf("Instruccion: '%s'\n", texto);

	token = strtok(texto," ");

        while(token){

		contador= contador +1;
		if(contador == 1){
			proc = token;
			//printf("proc: '%s'\n", proc);
			int tam = strlen(proc);;
			int i;
			for(i =1; i< tam; i++){
				proceso[i-1] = proc[i];

			}

		}else if(contador ==2){
			ope = token;
			operacion = ope[0];


		}else if(contador ==3){
			rec = token;
			int tam = strlen(proc);
			int i;
			for(i =1; i< tam; i++){
				recurso[i-1] = rec[i];

			}

		}
		//printf("token: '%s'\n", token);


		token = strtok(NULL," ");

	}
	pr = atoi(proceso);
	re = atoi(recurso);
	contador =0;

	if(operacion == 's'){

		//printf("LLAMANDO A SOLICITUD: '%c'\n", operacion);
		solicitar(matriz,tamanio,tamanio,pr,re);
		imprimirMatriz(matriz,tamanio,tamanio);


	}else if(operacion =='d'){
		//printf("LLAMANDO A LIBERA: '%c'\n", operacion);
		liberar(matriz,tamanio,tamanio,pr,re);
		imprimirMatriz(matriz,tamanio,tamanio);

	}

  }

  crearGrafoApartirMatriz(matriz,tamanio,tamanio);

  fclose(in);


}
void llenarArrayConCeros(int tamanios[]){
    int i=0;
    for(i=0;i<40;i++){
        tamanios[i]==0;
    }
}
void llenarConTamanios(int tamPr,int tamRe,int tamanios[],int *i){

      tamanios[*i]=tamPr;
      *i=*i+1;
      tamanios[*i]=tamRe;
      *i=*i+1;


}
void mayorTam(int tamanios[],int *mayor){
    for(int i=0;i<40;i++){
     if(tamanios[i]>*mayor){
        *mayor=tamanios[i];
     }
    }
}
//solo convierte la matriz a lista de adyacencia q seria el grafo y verifica si existe ciclo del grafo ya creado
void crearGrafoApartirMatriz(int matriz [TAM_MATRIZ][TAM_MATRIZ],int filas,int columnas){
     int tam=filas+columnas;
     struct Graph *g1 = newGraph(tam);
     convertirMatrizAlistaAdya(g1,matriz,filas,columnas);
     verificarCiclo(g1);
}

int main(int argc, char *const argv[]){
     int tamanio=0;
     int matriz[TAM_MATRIZ][TAM_MATRIZ];
     tamanio=readfile(argv[1],0,0);
     inicializarMatrizConCeros(matriz,tamanio,tamanio);
     imprimirMatriz(matriz,tamanio,tamanio);
     readfile2(argv[1],tamanio, matriz);
 return 0;

}
