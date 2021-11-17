#include"2020640048_BGU.h"
int main(){
    int z;
    do{
        printf("Escoja una opcion:\n");
        printf("1............La matriz de adyacencia obtenida\n");
        printf("2............Dijkstra\n");
        printf("3............Salir\n");
        scanf("%d", &z);
        switch(z){
        case 1:
            LeerMatriz();
            break;
        case 2:
            LeerGrafo();
            dijkstra();
            break;
        }
    system("PAUSE");
    system("CLS");
    }while(z!=3);
    return 0;
}
