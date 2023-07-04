#include "trufa.hpp"

void turno_jugador(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_jugador, std::vector<Carta> &mano_ia, int &puntos_ronda, int &puntos_envido, int turno, bool &ia_puede_cantar_truco){//2.3
	int opcion;
  	while (!mano_jugador.empty()) { //este while sirve para que, si canto truco, me siga pidiendo que tire una carta
  	//cuando tiro una carta, rompe; sino (canto truco o envido), repite y me pide una carta.
  		if(ia_se_retira || jug_se_retira) return;
		while(1){ //verificador
			imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
			char key = _getch();
			opcion = key - '0'; //para convertir en int mi char
			if(opcion >= 1 && opcion <= opciones.size()) break;
		} //esta secuencia de ifs es para cubrir los distintos casos que pueden darse con las opciones
		//por ejemplo, en el turno 1 puedo tener 6, 5, o 4 opciones, segun si cante envido o truco. Para cada uno de esos casos hay un if
		if(turno == 0){
			if(opciones.size() == 6){
				//si es el turno 1 y es la PRIMERA opcion que elijo, ya no puedo cantar envido
				opciones.erase(opciones.begin() + 4);
				if(opcion >= 1 && opcion <= 3){
					tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
					imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
					break;
				}
				if(opcion == 4) canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
				else if(opcion == 5) {
					puntos_envido = jug_canta_envido(mano_jugador, mano_ia, 1);
					Sleep(2000);
				}
				else if(opcion == 6){
					jug_se_retira = true;
					return;
				}
			}
			else { //si es el turno 1 y es la segunda opcion que elijo (porque en la primera cante truco o envido)
				if(opcion >= 1 && opcion <= 3){
					tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
					//pasamos opcion-1 asi funciona como subindice (0, 1, 2)
					imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
					break;
				} 
				if(opciones.size() == 5 && opcion == 4) canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
				//opciones.size = 5 cuando tengo la opcion de truco
				//cuando opciones.size = 4, no tengo truco, y la opcion nro 4 es RETIRARSE
				else {
					jug_se_retira = true;
					return;
				}
			}		
		}
		else if(turno == 1){
			if(opcion == 1 || opcion == 2){ //variaciones del codigo para adaptarse a cada ronda
				tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
				imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
				break;
			}
			if(opciones.size() == 4 && opcion == 3) canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
			else {
				jug_se_retira = true;
				return;
			}
		}
  		else{
			if(opcion == 1) {
				tira_carta(opcion-1, cartas_tiradas_jug, mano_jugador[opcion-1], mano_jugador, opciones, turno);
				imprimir(opciones, cartas_tiradas_jug, cartas_tiradas_ia, mano_jugador);
				break;
			}
			if(opciones.size() == 3 && opcion == 2) canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
			else {
				jug_se_retira = true;
				return;
			}
		}
  }
}

void tira_carta(int opcion, std::vector<Carta> &cartas_tiradas_jug, Carta carta_tirada, std::vector<Carta> &mano_jugador, std::vector<std::string> &opciones, int turno){ //2.3.1
  	cartas_tiradas_jug.push_back(carta_tirada); //agrego la carta tirada a este array
	opciones.erase(opciones.begin() + opcion); //y la borro de mi mano y de las opciones
	mano_jugador.erase(mano_jugador.begin() + opcion);
}

void turno_ia(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_ia, int &puntos_ronda, int turno, bool &ia_puede_cantar_truco){
	if(rand()%3 == 0) ia_canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
	Sleep(1000);
	tira_carta_ia(cartas_tiradas_ia, mano_ia, turno);
}

void tira_carta_ia(std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_ia, int turno){
  	int r2 = rand()% (3-turno); //tira una carta random
  	cartas_tiradas_ia.push_back(mano_ia[r2]);
	mano_ia.erase(mano_ia.begin() + r2);
}

void carta_ganada(int carta_ganada_jug, int carta_ganada_ia, bool hizo_primera, int turno, int &ganador){
	if (carta_ganada_ia == 2 && carta_ganada_jug == 2) { //si hubo empate de dos
		if(turno == 1) { //si hubo empate en las dos primeras rondas le restamos 1 a cada jugador, y asi quien gane la 3era tendra 2
			carta_ganada_ia--;
			carta_ganada_jug--;
			return;
		}
		if (!hizo_primera) ganador = 0; //si es la tercera ronda, gana quien hizo primera
		else ganador = 1;
	} else{ //gana quien llegue a 2 puntos
		if(carta_ganada_ia == 2) ganador = 0;
		else if(carta_ganada_jug == 2) ganador = 1;
	}
}

