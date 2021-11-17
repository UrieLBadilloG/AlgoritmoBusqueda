#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define Arista struct arista
#define Lista struct pila
typedef struct _Nodo{
	char dato;
	int visitado,terminado;
	int monto;
	char anterior;
    struct _Nodo* siguiente;
	Arista* adyacencia;
}Nodo;

Arista{
	int peso;
	Nodo*vrt;
	Arista*siguiente;
};

Lista{
	Nodo* dato;
	Lista*siguiente;
};
Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL;

void insertarNodo(char vertice);
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
void insertarArista(char ini, char fin, int peso);
void insertarPila(Nodo* aux);
Nodo*desencolar();
void dijkstra();
Nodo *asignarMemoria(char d){
	Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
	nuevo -> dato = d;
	nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->monto=-1;
    nuevo->anterior=0;
    return nuevo;
}
void insertarNodo(char vertice){
    Nodo *nuevo;
    Nodo* aux;
    nuevo = asignarMemoria(vertice);
    if(inicio==NULL){
        inicio=nuevo;
    }else{
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
      }
}

void insertarArista(char ini, char fin, int peso){
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
	Nodo* aux2;
    if(inicio==NULL){
         printf("Error: El grafo está vacio\n");
         return;
    }
    nuevo ->peso = peso;
    aux=inicio;
    aux2=inicio;
    while(aux2!=NULL){
        if(aux2->dato==fin){
            break;
        }
        aux2=aux2->siguiente;
    }
    if(aux2==NULL){
    	printf("Error:Vertice no encontrado\n");
    	return;
	}
    while(aux!=NULL){
        if(aux->dato==ini){
            agregarArista(aux,aux2,nuevo);
            return;
        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
    	printf("Error:Vertice no encontrado\n");
}

void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    if(aux->adyacencia==NULL){
	    aux->adyacencia=nuevo;
        nuevo->vrt=aux2;
    }else{
	    a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}
void visualizarPeso(char *re){
    int j = 0;
    int tam =  strlen(re);
    printf("%c", re[0]);
    for(int z = 0; z<tam-1; z++){
        char  i = re[z];
        char  f = re[z+1];
        Nodo*aux=inicio;
        Arista* ar;
        while(aux->dato!=i){
            aux=aux->siguiente;
        }
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar->vrt->dato!=f){
               ar=ar->siguiente;
            }
                printf("-%d-", ar->peso);
                printf("%c",ar->vrt->dato);

        }
    }
}



void insertarPila(Nodo* aux){
	Lista*nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->dato=aux;
	nuevo->siguiente=NULL;
	if(ini==NULL){
		ini=nuevo;
		final=nuevo;
	}else{
	   nuevo->siguiente=ini;
	   ini=nuevo;
	}
}
Nodo*desencolar(){
	Lista*aux;
	if(ini==NULL){
		return NULL;
	}else{
		aux=ini;
		ini=ini->siguiente;
		aux->siguiente=NULL;
		if(ini==NULL)
		final=NULL;
	}
	Nodo*resultado=aux->dato;
	return resultado;
}
void dijkstra(){
	Nodo*aux=inicio;
	char a,b;
	char r[100]="";
	int c=0;
	fflush(stdin);
	printf("Ingresar Nodo Inicial y Final(en minusculas):");
	scanf("%c %c",&a,&b);
	while(aux!=NULL){
		if(aux->dato==a){
			aux->terminado=1;
			aux->monto=0;
			break;
		}
		aux=aux->siguiente;
	}
	if(aux==NULL){
		printf("Vertice no encontrado\n");
		return;
	}
	while(aux!=NULL){
		Arista*a=aux->adyacencia;
	    while(a!=NULL){
		    if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
		    	a->vrt->monto=aux->monto+a->peso;
		        a->vrt->anterior=aux->dato;
			}
		    a=a->siguiente;
	    }
	    aux=inicio;
	    Nodo*min=inicio;
	    while(min->anterior==0 || min->terminado ==1)
	    min=min->siguiente;
	    while(aux!=NULL){
	    	if(aux->monto<min->monto && aux->terminado==0 && aux->anterior!=0)
	    	min=aux;
	    	aux=aux->siguiente;
		}
		aux=min;
		aux->terminado=1;
		if(aux->dato==b)
		break;
	}
	while(aux->anterior!=0){
		insertarPila(aux);
		char temp=aux->anterior;
		aux=inicio;
		while(aux->dato!=temp){
		   aux=aux->siguiente;
		}
	}
	insertarPila(aux);
	Arista *ar;
	while(ini!=NULL){
		//printf("%c ",desencolar()->dato);
		r[c]=desencolar()->dato;
		c++;

        //printf("%c ",ini->dato);
		//printf("%c ", a->vrt->dato);
	}
	visualizarPeso(r);
		printf("\n");
}
void LeerMatriz(){
    int leidos = 0;
    int pesos = 0;
    int filas = 97;
    int columnas = 97;

    FILE *bin;
    bin =  fopen ("grafo.bin", "rb");
    if(bin==NULL){
        printf("No se pudo encontrar el archivo binario");
    }
    else{
        fread (&leidos, sizeof(int), 1, bin);
        printf("%d\n", leidos);
        for(int i = 1; i<(leidos*leidos)+1; i++){
            fread (&pesos, sizeof(int), 1, bin);
            printf(" %d", pesos);
            if(i%leidos==0){
                printf("\n");

            }
        }
        fclose(bin);
    }
}
void LeerGrafo(){
    int leidos = 0;
    int pesos = 0;
    int filas = 97;
    int columnas = 97;

    FILE *bin;
    bin =  fopen ("grafo.bin", "rb");
    if(bin==NULL){
        printf("No se pudo encontrar el archivo binario");
    }
    else{
        fread (&leidos, sizeof(int), 1, bin);
        printf("%d\n", leidos);
        int cont = 97;
        for(int j = 0; j<leidos; j++){
            char c = cont;
            insertarNodo(c);
            cont++;
        }
        for(int i = 1; i<(leidos*leidos)+1; i++){
            fread (&pesos, sizeof(int), 1, bin);
           // printf(" %d", pesos);
            char i = filas;
            char f = columnas;
            if(pesos != 0){
                insertarArista(i, f, pesos);
            }
            filas++;
            if(i%leidos==0){
                filas=97;
                columnas++;
              //  printf("\n");

            }
        }
        fclose(bin);
    }
}
