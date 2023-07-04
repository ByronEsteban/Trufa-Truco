#include "trufa.hpp"

void imprimir_cartas_tiradas(std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia){
  	printf("\t");
  	for (int i = 0; i < cartas_tiradas_ia.size(); i++) {
		printf("%d de %s\t", cartas_tiradas_ia[i].valor, cartas_tiradas_ia[i].palo);
	}
  	printf("\n\n\t");
	for (int i = 0; i < cartas_tiradas_jug.size(); i++) {
		printf("%d de %s\t", cartas_tiradas_jug[i].valor, cartas_tiradas_jug[i].palo);
	}
	printf("\n\n\t--------------\n\n");
}

void imprimir_cartas(std::vector<Carta> &mano_jugador){
  	printf("\t");
  	for (int i = 0; i < mano_jugador.size(); i++) {
		printf("%d. %d de %s\t", i+1, mano_jugador[i].valor, mano_jugador[i].palo);
	}
  	printf("\n\n");
}

void imprimir(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_jugador, bool turno_jug){
	system("cls");
	printf("Puntos jug: ");
	for (int i = 0; i < puntos_jug; i++) {
		if(i % 5 == 0) printf(" ");
		if(i == 15) printf("- ");
		printf("|");
	}
	printf("\n\n");
	printf("Puntos IA:  ");
	for (int i = 0; i < puntos_ia; i++) {
		if(i % 5 == 0) printf(" ");
		if(i == 15) printf("- ");
		printf("|");
	}
	printf("\n\n\n");
	imprimir_cartas_tiradas(cartas_tiradas_jug, cartas_tiradas_ia);
	imprimir_cartas(mano_jugador);
	if(!turno_jug){ 
		printf("\033[41m Turno IA \n\n\033[40m");
		printf("\033[90m");
	} else printf("\033[44m Turno Jugador \n\n\033[40m");
	printf("Seleccione una opcion:\n");
	for (int i = 0; i < opciones.size(); i++) {
		printf("%d. %s\n", i+1, opciones[i].c_str());
	}
	printf("\n\033[37m");
}

