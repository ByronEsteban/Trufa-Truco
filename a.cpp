#include <stdio.h>
#include<windows.h> //Sleep(4000);
#include <string.h>
#include <time.h>
#include <stdbool.h>
//alto codigo
struct Carta{
	int valor;
	char *palo;
	int posicion;
	bool repartida;
};

void tira_carta(Carta cartas_tiradas_jug[], Carta mano_jugador, int turno){ //2.3.1
  cartas_tiradas_jug[turno] = mano_jugador;
  printf("\n\n%d de %s\n\n", cartas_tiradas_jug[turno].valor, cartas_tiradas_jug[turno].palo);
}

void imprimir_cartas(Carta mano_jugador[]){
  system("cls");
  printf("\t1. %d de %s\t", mano_jugador[0].valor, mano_jugador[0].palo);
  printf("2. %d de %s\t", mano_jugador[1].valor, mano_jugador[1].palo);
  printf("3. %d de %s\t", mano_jugador[2].valor, mano_jugador[2].palo);
  printf("\n\n");
}

void turno_jugador(Carta cartas_tiradas_jug[], Carta cartas_tiradas_ia[], Carta mano_jugador[], int puntos_ronda_jug, int puntos_ronda_ia, int turno){//2.3
  int opcion;
  while (1) {
    imprimir_cartas(mano_jugador);
    printf("1- Carta 1\n2- Carta 2\n3- Carta 3\n4- Truco\n5- Envido\n6- Flor\n7- Retirarse\n");
    scanf("%d", &opcion);
    switch (opcion) {
      case 1:
        tira_carta(cartas_tiradas_jug, mano_jugador[0], turno);
        Sleep(4000);
        break; //borrar
      case 2:
		tira_carta(cartas_tiradas_jug, mano_jugador[1], turno);
        Sleep(4000);
        break;
      case 3:
        tira_carta(cartas_tiradas_jug, mano_jugador[2], turno);
        Sleep(4000);
        break;
     /* case 4:
        canta_truco();
      case 5:
        canta_envido();
      case 6:
        canta_flor()
      case 7:
        retirarse();
      default:
        printf("responde trola\n", );*/
    }
    break;
  }
}

void repartir_baraja(Carta baraja[], Carta mano_jugador[], Carta mano_ia[]){ //2.2
	int i = 0, j = 0, k = 0;
	while (i < 6){
		int r = rand()%40;
		if(!baraja[r].repartida){
			baraja[r].repartida = true;
			if(i%2 == 0) mano_jugador[j++] = baraja[r];
			else mano_ia[k++] = baraja[r];
			i++;
		}
	}
	/*for(int i = 0; i < 3; i++){
		printf("Carta %d Jug: %d de %s\n", i+1, mano_jugador[i].valor, mano_jugador[i].palo);
		printf("Carta %d IA: %d de %s\n", i+1, mano_ia[i].valor, mano_ia[i].palo);
	}*/
}

void desordenar_baraja(Carta baraja[]){ //2.1
	for(int i = 0; i < 1000; i++){
		int r = rand()%40;
		int s = rand()%40;
		Carta temp = baraja[r];
		baraja[r] = baraja[s];
		baraja[s] = temp;
	}
}

void truco(Carta baraja[]){ //2
	desordenar_baraja(baraja);
	Carta mano_jugador[3], mano_ia[3];
	int ronda = 0;
  int puntos_jug = 0, puntos_ia = 0;
  bool jugador_es_mano = true;
	while (puntos_jug < 30 || puntos_ia < 30){
    Carta cartas_tiradas_jug[3];
    Carta cartas_tiradas_ia[3];
		repartir_baraja(baraja, mano_jugador, mano_ia);
    //printf("\n\n%d de %s\n\n", mano_jugador[0].valor, mano_jugador[0].palo);
    int puntos_ronda_jug = 0, puntos_ronda_ia = 0;
    if(jugador_es_mano){
			turno_jugador(cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda_jug, puntos_ronda_ia, 0);
			//turno_ia();
			turno_jugador(cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda_jug, puntos_ronda_ia, 1);
			//turno_ia();
			turno_jugador(cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda_jug, puntos_ronda_ia, 2);
			/*turno_ia();
		} else{
			turno_ia();
			turno_jugador();
			turno_ia();
			turno_jugador();
			turno_ia();
			turno_jugador();
		*/}
	}
}

void imprimir_orden_cartas(Carta orden_de_cartas[]){
	printf("%d de %s\n", orden_de_cartas[0].valor, orden_de_cartas[0].palo);
	printf("%d de %s\n", orden_de_cartas[1].valor, orden_de_cartas[1].palo);
	printf("%d de %s\n", orden_de_cartas[2].valor, orden_de_cartas[2].palo);
	printf("%d de %s\n", orden_de_cartas[3].valor, orden_de_cartas[3].palo);
	for(int i = 4; i < 40; i++){
		if(i == 8 || i == 12 || i == 14 || i == 18 || i == 22 || i == 26 || i == 28 || i == 32 || i == 36) printf("\n");
		printf("%d de %s - ", orden_de_cartas[i].valor, orden_de_cartas[i].palo);
	}
	printf("\n");
}

void llenar_orden_cartas(Carta orden_de_cartas[], char *palos[]){
	orden_de_cartas[0].valor = 1;
	orden_de_cartas[0].palo = palos[0];
	orden_de_cartas[1].valor = 1;
	orden_de_cartas[1].palo = palos[1];
	orden_de_cartas[2].valor = 7;
	orden_de_cartas[2].palo = palos[0];
	orden_de_cartas[3].valor = 7;
	orden_de_cartas[3].palo = palos[2];
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+4].valor = 3;
		orden_de_cartas[i+4].palo = palos[i];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+8].valor = 2;
		orden_de_cartas[i+8].palo = palos[i];
	}
	for(int i = 0; i < 2; i++){
		orden_de_cartas[i+12].valor = 1;
		orden_de_cartas[i+12].palo = palos[i+2];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+14].valor = 12;
		orden_de_cartas[i+14].palo = palos[i];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+18].valor = 11;
		orden_de_cartas[i+18].palo = palos[i];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+22].valor = 10;
		orden_de_cartas[i+22].palo = palos[i];
	}
	orden_de_cartas[26].valor = 7;
	orden_de_cartas[26].palo = palos[1];
	orden_de_cartas[27].valor = 7;
	orden_de_cartas[27].palo = palos[3];
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+28].valor = 6;
		orden_de_cartas[i+28].palo = palos[i];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+32].valor = 5;
		orden_de_cartas[i+32].palo = palos[i];
	}
	for(int i = 0; i < 4; i++){
		orden_de_cartas[i+36].valor = 4;
		orden_de_cartas[i+36].palo = palos[i];
	}
}

void llenar_baraja(Carta baraja[], int valores[], char *palos[]){ // 1
	int i = 0;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 10; k++) {
            baraja[i].valor = valores[k];
        	baraja[i].palo = palos[j];
        	baraja[i].repartida = false;
        	if(baraja[i].valor == 1){
        		if(baraja[i].palo == "Espada") baraja[i].posicion = 1;
        		else if(baraja[i].palo == "Basto") baraja[i].posicion = 2;
        		else baraja[i].posicion = 7;
			}
        	if(baraja[i].valor == 7){
        		if(baraja[i].palo == "Espada") baraja[i].posicion = 3;
        		else if(baraja[i].palo == "Oro") baraja[i].posicion = 4;
        		else baraja[i].posicion = 11;
			}
        	if(baraja[i].valor == 3) baraja[i].posicion = 5;
        	if(baraja[i].valor == 2) baraja[i].posicion = 6;
        	if(baraja[i].valor == 12) baraja[i].posicion = 8;
        	if(baraja[i].valor == 11) baraja[i].posicion = 9;
        	if(baraja[i].valor == 10) baraja[i].posicion = 10;
        	if(baraja[i].valor == 6) baraja[i].posicion = 12;
        	if(baraja[i].valor == 5) baraja[i].posicion = 13;
        	if(baraja[i].valor == 4) baraja[i].posicion = 14;
            i++;
        }
    }
}

int main() { //0
	srand(time(NULL));
    Carta baraja[40]; 
    int valores[10] = {1,2,3,4,5,6,7,10,11,12};
    char *palos[4] = {"Espada", "Basto", "Oro", "Copa"};
    llenar_baraja(baraja, valores, palos);
    printf("Opciones:\n1. Truco\n2. Trufa\n3. Reglas\n4. Salir\n");
    printf("ELegi algo: ");
    int opcion;
    while(1){
    	scanf("%d", &opcion);
    	switch(opcion) {
    	case 1:
    	    truco(baraja);
    	    break;
    	case 2:
    	    //trufa();
    	    break;
   		case 3:
   		    //reglas();
    	    break;
    	case 4:
    	    return 0;
    	default:
    	    printf("Elegi una opcion valida");
    	    break;
		}
	}
    //Carta orden_de_cartas[40];
    //llenar_orden_cartas(orden_de_cartas, palos);

	/*for (int i = 0; i < 40; i++) {
		printf("%d de %s -> %d\n", baraja[i].valor, baraja[i].palo, baraja[i].posicion);
    }*/

    //imprimir_orden_cartas(orden_de_cartas); //borrar despues

    return 0;
}
