#include "trufa.hpp" //donde se declaran todas las funciones, structs y variables globales
#include "envido.cpp" //funciones del envido
#include "truco.cpp" //funciones del truco
#include "imprimir.cpp" //funciones de imprimir opciones y cartas
#include "reglas.cpp" //funciones de imprimir reglas
#include "turnos.cpp" //funciones de los turnos de los jugadores
//en todos los archivos las funciones estan ordenadas segun su orden de aparicion

//alto codigo
void llenar_baraja(Carta baraja[], int valores[], char *palos[]){ 
	int i = 0; //recorre el array
    for (int j = 0; j < 4; j++) { //recorre los palos
        for (int k = 0; k < 10; k++) { //recorre los valores
            baraja[i].valor = valores[k];
        	baraja[i].palo = palos[j];
        	baraja[i].repartida = false;
			baraja[i].valor_envido = valores[k];
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
        	if(baraja[i].valor == 12){
				baraja[i].posicion = 8;
				baraja[i].valor_envido = 0;
			}
        	if(baraja[i].valor == 11){
				baraja[i].posicion = 9;
				baraja[i].valor_envido = 0;
			}
        	if(baraja[i].valor == 10){
				baraja[i].posicion = 10;
				baraja[i].valor_envido = 0;
			}
        	if(baraja[i].valor == 6) baraja[i].posicion = 12;
        	if(baraja[i].valor == 5) baraja[i].posicion = 13;
        	if(baraja[i].valor == 4) baraja[i].posicion = 14;
            i++;
        }
    }
}

void truco(Carta baraja[]){ 
	desordenar_baraja(baraja);
  	puntos_jug = 0;
	puntos_ia = 0;
  	bool jugador_es_mano = rand()%2;
	while (puntos_jug < 30 && puntos_ia < 30){
    	std::vector<Carta> cartas_tiradas_jug, cartas_tiradas_ia;
    	std::vector<Carta> mano_jugador, mano_ia;
		int i = 0;
		while (i < 6){
			int r = rand()%40;
			if(!baraja[r].repartida){ //si la carta no fue repartida, se asigna a la mano
				baraja[r].repartida = true;
				if(i%2 == 0) mano_jugador.push_back(baraja[r]); //3 van para el jug
				else mano_ia.push_back(baraja[r]); //y 3 para la ia
				i++;
			}
		}
		for(int i = 0; i < 40; i++) baraja[i].repartida = false; //volvemos a poner todas las cartas como no repartidas para la prox ronda
    	int ganador = -1; //si la ronda la ia valdra 0; si gana el jug 1; mientras no gane ninguno, vale -1
    	//en los booleanos, 0 designa a la IA y 1 al jug.
    	bool ia_puede_cantar_truco = true;
    	jug_se_retira = false;
		ia_se_retira = false;		
    	int puntos_ronda = 1, puntos_envido = 0;
    	int carta_ganada_jug = 0, carta_ganada_ia = 0; //la cantidad de cartas que gano cada jugador en la ronda
    	std::vector<std::string> opciones;
    	opciones.push_back("Carta 1");
		opciones.push_back("Carta 2");
		opciones.push_back("Carta 3");
		opciones.push_back("Truco");
		opciones.push_back("Envido");
		opciones.push_back("Retirarse");
		bool hizo_primera; //valdra 0 o 1 segun quien hizo primera
		while(1){ //este while es para poder salir de los if, mediante un break, si alguno de los jugs se retira
		if(jugador_es_mano){ 
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 0, ia_puede_cantar_truco);
			if(ia_se_retira){ //estos verificadores estan tras cada turno para que si alguno se retira acabar la ronda inmediatamente
				ganador = true; //gana el jug
				break;
			} 
			else if(jug_se_retira){
				ganador = false; //gana la ia
				break;
			}
			if(puntos_envido == 0 && rand()%3 != 0) puntos_envido = ia_canta_envido(mano_jugador, mano_ia, jugador_es_mano);
			//si el jugador no canto envido (envido == 0) la ia puede cantar
			//la IA funciona principalmente mediante randoms porque no dio el tiempo para diseñarle una inteligencia
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 0, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		}
		else{
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(rand()%3 != 0){
				puntos_envido = ia_canta_envido(mano_jugador, mano_ia, jugador_es_mano);
				opciones.erase(opciones.begin() + 4); //borramos la opcion de envido
			} 
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 0, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 0, ia_puede_cantar_truco);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		}
		
		if(cartas_tiradas_jug[0].posicion > cartas_tiradas_ia[0].posicion){ //si la primer carta la gano la ia
			hizo_primera = false;
			carta_ganada_ia++;
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 1, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 1, ia_puede_cantar_truco);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		} 
		else {
			if(cartas_tiradas_jug[0].posicion == cartas_tiradas_ia[0].posicion) carta_ganada_ia++; //si es empate se suma a ambos
			hizo_primera = true;
			carta_ganada_jug++;
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 1, ia_puede_cantar_truco);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 1, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		}
		if(cartas_tiradas_jug[1].posicion > cartas_tiradas_ia[1].posicion){ //idem para la segunda ronda
			carta_ganada_ia++;
			carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 1, ganador); //esta funcion verifica si alguien gano
			if(ganador == 0 || ganador == 1) break; //si alguno gano rompe, sino continua
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 2, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 2, ia_puede_cantar_truco);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		} 
		else {
			if(cartas_tiradas_jug[1].posicion == cartas_tiradas_ia[1].posicion) carta_ganada_ia++;
			carta_ganada_jug++;
			carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 1, ganador);
			if(ganador == 0 || ganador == 1) break;
			turno_jugador(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador, mano_ia, puntos_ronda, puntos_envido, 2, ia_puede_cantar_truco);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
			turno_ia(opciones, cartas_tiradas_ia, mano_ia, puntos_ronda, 2, ia_puede_cantar_truco);
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			if(ia_se_retira){
				ganador = true;
				break;
			} 
			else if(jug_se_retira){
				ganador = false;
				break;
			}
		}
		if(cartas_tiradas_jug[2].posicion > cartas_tiradas_ia[2].posicion) carta_ganada_ia++;
		else {
			if(cartas_tiradas_jug[2].posicion == cartas_tiradas_ia[2].posicion) carta_ganada_ia++;
			else carta_ganada_jug++;
		}
		carta_ganada(carta_ganada_jug, carta_ganada_ia, hizo_primera, 2, ganador);
		if(ganador == 0 || ganador == 1) break;
		}
		
    	if(!ganador){ //gana ia xq == 0
    		if(puntos_envido < 0) { //si gano el tanto se le suma
    			puntos_ia += puntos_ronda + puntos_envido*-1;
			} 
			else { //sino se le suma al jug
				puntos_jug += puntos_envido;
				puntos_ia += puntos_ronda;
			}
		} 
		else { //gana jug xq == 1
			if(puntos_envido > 0) { //viceversa
    			puntos_jug += puntos_ronda + puntos_envido;
			} 
			else {
				puntos_ia += puntos_envido*-1;
				puntos_jug += puntos_ronda;
			}
		}
		printf("Puntos jug = %d\n", puntos_jug);
		printf("Puntos IA = %d\n", puntos_ia);
		Sleep(2000);
		jugador_es_mano = !jugador_es_mano; //la siguiente ronda comenzara el otro jug
	}
	printf("GANASTE\n");
}

void desordenar_baraja(Carta baraja[]){ 
	for(int i = 0; i < 1000; i++){
		int r = rand()%40;
		int s = rand()%40;
		Carta temp = baraja[r];
		baraja[r] = baraja[s];
		baraja[s] = temp;
	}
}

int main() { //0
	srand(time(NULL));
    Carta baraja[40];
    int valores[10] = {1,2,3,4,5,6,7,10,11,12};
    char *palos[4] = {"Espada", "Basto", "Oro", "Copa"};
    llenar_baraja(baraja, valores, palos);
    while(1){ //este while funciona como verificador de que ingreso una opcion valida
    	printf("Opciones:\n1. Truco\n2. Trufa - NO DISPONIBLE\n3. Reglas\n4. Apreta ESC para salir\n");
    	printf("ELegi algo: ");
    	char key = _getch();  // lee el primer caracter que se ingrese
    	if(key == '1') truco(baraja);
    	//else if (key == '2') NO HUBO TIEMPO :(
    	else if (key == '3'){
    		imprimir_reglas(palos);
    		while(1){
    			char key = _getch();
    			if(key == 27) break;
			}
			system("cls");
		}
    	else if (key == 27 || key == '4') break;
    	else system("cls");
	} 
    return 0;
}
