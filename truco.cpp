#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int truco(void){

}

int trufa(void){

}

void reglas(void){

}


int main(void) {
  while (1) {
  int opcion;
  printf("Bienvenido al TRUFA-TRUCO!!!\n");
  printf("Ingresa la opcion que quieras:\n");
  printf("1) Ingresa la opcion que quieras:\n"); //TRUCO
  printf("Ingresa la opcion que quieras:\n"); //TRUFA
  printf("Ingresa la opcion que quieras:\n"); //REGLAS
  printf("Ingresa la opcion que quieras:\n"); //SALIR
  scanf("%d", &opcion);
  switch (opcion) {
    case 1:
      printf("Ha seleccionado la opción 1.\n");
      break;
    case 2:
      printf("Ha seleccionado la opción 2.\n");
      break;
    case 3:
      printf("Ha seleccionado la opción 3.\n");
      break;
    case 4:
      return 0;
    default:
      printf("Opción inválida.\n");
      break;
    }
 	printf("Ingresa 1 para truco y 2 para trufa: ");
  	scanf("%d", &a);
    if(a == 1 || a == 2) break;
	else{
		system("cls");
		printf("Ingrese un numero valido\n");
	}
  }

  return 0;
}
