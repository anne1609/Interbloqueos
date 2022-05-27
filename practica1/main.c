//1ero suponer q funciona siempre con el mismo nro de procesos y mismo nro de recursos, osea q es matriz cuadrada, mismo nro de filas q columnas

//paso de parametros por referencia en C : https://www.youtube.com/watch?v=vahXpd7HlEw

//BOOL EN C : https://learntutorials.net/es/c/topic/3336/booleano

#define bool int
#define true 1
#define false 0

#define TAM_MATRIZ 20
#include <stdio.h>
#include <stdlib.h>

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
			// Set vertic node data
			g->nodo[i].dato = i;
			// Set NULL Value
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
			printf("\n Lista de adyacencia del vertice %d  :", i);
			temp = g->nodo[i].sgte;
			while (temp != NULL)
			{
			//temp->id son los v�rtices del nodo del grafo
            //en este caso temp->id es igual que
            //nodo[temp->id].datos
				printf("  %d", g->nodo[temp->id].dato);
				temp = temp->sgte;
			}
		}
	}
	else
	{
		printf("Grafo vacio");
	}
}

//Aca cambie el nombre point por aux
int detectarCicloConDFS(struct Graph *g,
                int inicio, int aux, int visit[])
{
	if (visit[inicio] == 1 && aux == inicio)
	{
		// Cuando las visitas a un nodo son mas de una
        // Aqu� el inicio y el final son iguales
        // Contiene ciclo
		return 1;
	}
	else if (visit[aux] == 1)
	{
		// Cuando los nodos inicial y final no son iguales, entonces
        // Permitir visitar el mismo nodo m�s de una vez
		return 0;
	}
	// Establecer estado visitado 1
	visit[aux] = 1;
	// Obtener la direcci�n de la primera arista del nodo actual
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
// M�todo que gestiona el ciclo de b�squeda y detecci�n.
// operaci�n
void verificarCiclo(struct Graph *g)
{
	if (g->tam <= 0)
	{
		printf("Grafo vacio\n");
		return;
	}
	// Imprimir elemento gr�fo
	imprimirListaAdyacencia(g);
	// Esto est� almacenando la informaci�n sobre
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
		// Cambiar la ubicaci�n del nodo
		ubicacion++;
	}
	// Mostrar posible resultado
	if (resultado == 1)
	{
		printf("\n Resultado : Ciclo detectado\n");
	}
	else
	{
		printf("\n Resultado : No hay ciclo\n");
	}
}



///////////////////////////////////////



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

 void convertirMatrizAlistaAdya(struct Graph *g,int matriz[TAM_MATRIZ][TAM_MATRIZ], int filas, int columnas){
   int nroVertices=filas*columnas;
   int arrayAux1[filas];
   int arrayAux2[columnas];
   int vert1=0;int vert2=0;
   int fila=0; int columna=0;

   llenarArrayAuxs(arrayAux1,arrayAux2,filas,columnas);
   printf("El 1er array de vertices es:\n");
   imprimirArray(arrayAux1,filas);
   printf("\nEl 2do array de vertices es:\n");
   imprimirArray(arrayAux2,columnas);

  //struct Graph *g = newGraph(nroVertices);
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

int main(){
 /*
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
 imprimirMatriz(matriz,3,3);*/

//Generando un escenario ciclico
int matriz[2][2];
 inicializarMatrizConCeros(matriz,2,2);
 imprimirMatriz(matriz,2,2);
 //solicitar(int matriz,int filas,int columnas,int proceso,int recurso
 printf("\n p1  s   r1\n");
 solicitar(matriz,2,2,1,1);
 imprimirMatriz(matriz,2,2);
 printf("\n p2  s   r1\n");
 solicitar(matriz,2,2,2,1);
 imprimirMatriz(matriz,2,2);
 printf("\n p2  s   r2\n");
 solicitar(matriz,2,2,2,2);
 imprimirMatriz(matriz,2,2);
 printf("\n p1  s   r2\n");
 solicitar(matriz,2,2,1,2);
 imprimirMatriz(matriz,2,2);
 struct Graph *g1 = newGraph(4);
 convertirMatrizAlistaAdya(g1,matriz,2,2);
 verificarCiclo(g1);

 /* addEge, checkCycle,detectarCicloConDFS cambio de nombre
 // 6 implies the number of nodes in graph
	struct Graph *g = newGraph(6);
	// Connect node with an edge
	addEdge(g, 0, 1);
	addEdge(g, 0, 3);
	addEdge(g, 1, 2);
	addEdge(g, 2, 5);
	addEdge(g, 3, 4);
	addEdge(g, 4, 2);
	// Test A
	checkCycle(g);
	// Add other edge
	addEdge(g, 5, 1);
	// Test B
	checkCycle(g);
	///////
	struct Graph *j = newGraph(4);
	// Connect node with an edge
	addEdge(j, 0, 2);
	addEdge(j, 1, 3);
	addEdge(j, 2, 1);
	addEdge(j, 3, 0);

	// Test A
	checkCycle(j);*/


 return 0;

}


