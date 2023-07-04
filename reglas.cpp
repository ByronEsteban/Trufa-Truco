#include "trufa.hpp"

void imprimir_orden_cartas(Carta orden_de_cartas[]){
	printf("   * %d de %s\n", orden_de_cartas[0].valor, orden_de_cartas[0].palo);
	printf("   * %d de %s\n", orden_de_cartas[1].valor, orden_de_cartas[1].palo);
	printf("   * %d de %s\n", orden_de_cartas[2].valor, orden_de_cartas[2].palo);
	printf("   * %d de %s\n   * ", orden_de_cartas[3].valor, orden_de_cartas[3].palo);
	for(int i = 4; i < 40; i++){
		if(i == 8 || i == 12 || i == 14 || i == 18 || i == 22 || i == 26 || i == 28 || i == 32 || i == 36) printf("\n   * ");
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
	for(int i = 0; i < 4; i++){ //uso varios for para que i sirva tambien de subindice de palos
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

void imprimir_reglas(char *palos[]){
	system("cls");
	printf(" Como jugar\n\n");
	printf(" * Objetivo del juego: Que uno de los jugadores lleguen a los 30 puntos; estos puntos se dividen en dos, 15 y 15.\n   Los puntos se consiguen ganando rondas.\n");
	printf("\n * Inicio del juego: Se reprten las cartas y comienza uno de los dos jugadores, llamado \"mano\".\n   En su turno, cada jugador debe tirar una carta, y ademas puede cantar truco, envido (si esta habilitado) y retirarse.\n   Una vez tirada la carta, el rival tirara la suya.\n   Quien tenga la carta mas alta (ver orden de cartas) gana y vuelve a tirar. Quien gane dos cartas gana la ronda\n");
	printf("\n * El orden de cartas es:\n");
	Carta orden_de_cartas[40];
    llenar_orden_cartas(orden_de_cartas, palos);
	imprimir_orden_cartas(orden_de_cartas); //borrar despues
	printf("\n * Cantos: Los jugadores pueden, en su turno, cantar TRUCO, para que la ronda se juegue por mas puntos.\n   Tambien, en su primer turno pueden cantar ENVIDO. A ambos cantos el rival puede subirlos y jugar asi por mas puntos\n\n");
	printf(" Apreta ESC para salir: ");
}
