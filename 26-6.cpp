#include <stdio.h>
#include<windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <cstdlib>
#include <iostream>
#include <vector>

//alto codigo
struct Carta{
	int valor;
	char *palo;
	int posicion;
	bool repartida;
};

void canta_truco(int puntos_ronda, std::vector<std::string> &opciones){
	//if(ia_acepta())
	if((rand()%1) == 0){
		//if()
		printf("QUIERO!!!");
		opciones.erase(opciones.begin() + opciones.size() - 2);
		puntos_ronda++;
		return;
	}
	printf("NO QUIERO");
	exit(0);
}

void win(int ganador){
	if(ganador) printf("Gano el jugador\n");
	else printf("Gano la IA\n");
	exit(0);
}

void carta_ganada(int carta_ganada_jug, int carta_ganada_ia, bool hizo_primera, int turno){
	if (carta_ganada_ia == 2 && carta_ganada_jug == 2) {
		if(turno == 1) {
			carta_ganada_ia--;
			carta_ganada_jug--;
			return;
		}
		if (!hizo_primera) win(0);
		else win(1);
	} else{
		if(carta_ganada_ia == 2) win(0);
		else if(carta_ganada_jug == 2) win(1);
	}
	printf("\n\n%d - %d \n\n", carta_ganada_ia, carta_ganada_jug);
	Sleep(2000);
}

void tira_carta_ia(Carta carta_tirada_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_ia, int turno){
  int r2 = rand()% (3-turno);
  cartas_tiradas_ia.push_back(mano_ia[r2]);
	mano_ia.erase(mano_ia.begin() + r2);
  printf("\n\n%d de %s\n\n", cartas_tiradas_ia[turno].valor, cartas_tiradas_ia[turno].palo);
}

void tira_carta(int opcion, std::vector<Carta> &cartas_tiradas_jug, Carta carta_tirada, std::vector<Carta> &mano_jugador, std::vector<std::string> &opciones, int turno){ //2.3.1
  cartas_tiradas_jug.push_back(carta_tirada);
	opciones.erase(opciones.begin() + opcion);
	mano_jugador.erase(mano_jugador.begin() + opcion);
  printf("\n\n%d de %s\n\n", cartas_tiradas_jug[turno].valor, cartas_tiradas_jug[turno].palo);
  Sleep(1500);
}

void imprimir_cartas(std::vector<Carta> &mano_jugador){
  system("cls");
  printf("\t");
  for (int i = 0; i < mano_jugador.size(); i++) {
		printf("%d. %d de %s\t", i+1, mano_jugador[i].valor, mano_jugador[i].palo);
	}
  printf("\n\n");
}

void turno_jugador(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_jugador, int puntos_ronda, int turno){//2.3
  int opcion;
  while (!mano_jugador.empty()) {
	while(1){
		imprimir_cartas(mano_jugador);
		printf("Seleccione una opcion:\n");
		for (int i = 0; i < opciones.size(); i++) {
			printf("%d. %s\n", i+1, opciones[i].c_str());
		}
		scanf("%d", &opcion);
		if(opcion >= 1 && opcion <= opciones.size()) break;
	}
	opciones.erase(opciones.begin() + 3);
	opciones.erase(opciones.begin() + 3);
	if(turno == 0){
		if(opcion >= 1 || opcion <= 3) tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
		else if(opcion == 4) canta_truco(puntos_ronda, opciones);
		//else if(opcion == 5) //canta_envido(puntos_ronda, opciones);
		//else if(opcion == 6) //canta_flor(puntos_ronda, opciones);
		else if(opcion == 7) exit(0);
	}
	else if(turno == 1){
		if(opcion == 1 || opcion == 2) tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
		else if(opcion == 3) canta_truco(puntos_ronda, opciones);
		else if(opcion == 4) exit(0);
	}
  else{
		if(opcion == 1) tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
		else if(opcion == 2) canta_truco(puntos_ronda, opciones);
		else exit(0);
	}
    if(opcion != 4) break; //dejarlo para los casos de tirar carta, NO para truco, flor, envido, retirarse
  }
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
	std::vector<Carta> mano_jugador, mano_ia;
	int ronda = 0;
  	int puntos_jug = 0, puntos_ia = 0;
  	bool jugador_es_mano = true;
	while (puntos_jug < 30 || puntos_ia < 30){
    std::vector<Carta> cartas_tiradas_jug, cartas_tiradas_ia;
	//repartir_baraja(baraja, mano_jugador, mano_ia);
	int i = 0;
	while (i < 6){
		int r = rand()%40;
		if(!baraja[r].repartida){
			baraja[r].repartida = true;
			if(i%2 == 0) mano_jugador.push_back(baraja[r]);
			else mano_ia.push_back(baraja[r]);
			i++;
		}
	}
    if(mano_ia.empty()) printf("\n\nasdasd\n\n");
    //Sleep(30000);
    int puntos_ronda_jug = 0, puntos_ronda_ia = 0;
    int puntos_ronda = 1;
    int carta_ganada_jug = 0, carta_ganada_ia = 0;
    if(jugador_es_mano){
		bool hizo_primera;
    	std::vector<std::string> opciones;
    	opciones.push_back("Carta 1");
		opciones.push_back("Carta 2");
		opciones.push_back("Carta 3");
		opciones.push_back("Truco");
		opciones.push_back("Envido");
		opciones.push_back("Flor");
		opciones.push_back("Retirarse");
		turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 0);
		//ia_canta_envido
		//ia_canta_truco
		tira_carta_ia(cartas_tiradas_jug[0], cartas_tiradas_ia, mano_ia, 0);
      	Sleep(1500);
      	/*if(puntos_ronda <= 1){
      		opciones.erase(opciones.begin() + 3);
			opciones.erase(opciones.begin() + 3);
		}*/
		if(cartas_tiradas_jug[0].posicion > cartas_tiradas_ia[0].posicion){
			hizo_primera = false;
			carta_ganada_ia++;
			tira_carta_ia(cartas_tiradas_jug[0], cartas_tiradas_ia, mano_ia, 1);
	      	Sleep(1500);
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 1);
		} else {
			if(cartas_tiradas_jug[0].posicion == cartas_tiradas_ia[0].posicion) carta_ganada_ia++;
			hizo_primera = true;
			carta_ganada_jug++;
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 1);
			tira_carta_ia(cartas_tiradas_jug[1], cartas_tiradas_ia, mano_ia, 1);
	      	Sleep(1500);
		}
		if(cartas_tiradas_jug[1].posicion > cartas_tiradas_ia[1].posicion){
			carta_ganada_ia++;
			carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 1);
			tira_carta_ia(cartas_tiradas_jug[1], cartas_tiradas_ia, mano_ia, 2);
	      	Sleep(1500);
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 2);
		} else {
			if(cartas_tiradas_jug[1].posicion == cartas_tiradas_ia[1].posicion) carta_ganada_ia++;
			carta_ganada_jug++;
			carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 1);
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 2);
			tira_carta_ia(cartas_tiradas_jug[2], cartas_tiradas_ia, mano_ia, 2);
	      	Sleep(1500);
		}
		turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, puntos_ronda, 1);
		if(cartas_tiradas_jug[2].posicion > cartas_tiradas_ia[2].posicion) carta_ganada_ia++;
		else {
			if(cartas_tiradas_jug[2].posicion == cartas_tiradas_ia[2].posicion) carta_ganada_ia++;
			else carta_ganada_jug++;
		}
		carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 2);
		Sleep(5000);
			/*turno_ia();
		} else{
			turno_ia();
			turno_jugador();
			turno_ia();
			turno_jugador();
			turno_ia();
			turno_jugador();
		*/}
		jugador_es_mano = !jugador_es_mano;
	}
}

/*void imprimir_orden_cartas(Carta orden_de_cartas[]){
	printf("%d de %s\n", orden_de_cartas[0].valor, orden_de_cartas[0].palo);
	printf("%d de %s\n", orden_de_cartas[1].valor, orden_de_cartas[1].palo);
	printf("%d de %s\n", orden_de_cartas[2].valor, orden_de_cartas[2].palo);
	printf("%d de %s\n", orden_de_cartas[3].valor, orden_de_cartas[3].palo);
	for(int i = 4; i < 40; i++){
		if(i == 8 || i == 12 || i == 14 || i == 18 || i == 22 || i == 26 || i == 28 || i == 32 || i == 36) printf("\n");
		printf("%d de %s - ", orden_de_cartas[i].valor, orden_de_cartas[i].palo);
	}
	printf("\n");
}*/

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
