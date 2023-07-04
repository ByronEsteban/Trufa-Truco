#include "trufa.hpp"
//estas dos funciones estan entrelazadas, y se llaman mutuamente. Esto hace que, ni bien me cantan truco, pueda subir la apuesta
//en el momento, o bien subirla mas adelante, o no subirla nunca.

void ia_canta_truco(int &puntos_ronda, std::vector<std::string> &opciones, bool &ia_puede_cantar_truco){
	Sleep(1000);
	printf("\n"); //cuando se canta truco, retruco, etc se hace puntos_ronda++;
	//puntos_ronda = 1 significa que se esta cantando truco; puntos_ronda = 2, que se canta retruco, y asi
	if (puntos_ronda == 1){ //IA canta truco
		ia_puede_cantar_truco = false; //este verificador sirve para evitar que la ia cante truco si no puede
		printf("IA: \"Truco!!!\"\n");
		printf("ENTER para si, ESC para no, 1 para Retruco\n");
		while(1){ //verificador
			char key = _getch();
    		if (key == 13){
				puntos_ronda++; //quiero
				opciones.erase(opciones.begin() + opciones.size() - 1);
				opciones.erase(opciones.begin() + opciones.size() - 1);
				opciones.push_back("Retruco");
				opciones.push_back("Retirarse"); //cambiamos el TRUCO por RETRUCO
				return;
			}
			else if (key == 27) { //no quiero
				jug_se_retira = true;
				return;
			} 
			else if (key == '1') { //la subo
				puntos_ronda++;
				canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
				return;
			}
		}
	} 
	else if (ia_puede_cantar_truco && puntos_ronda == 2){ //IA canta retruco (cuando el jugador canto truco primero)
		ia_puede_cantar_truco = false;
		printf("IA: \"Retruco!!!\"\n");
		printf("ENTER para si, ESC para no, 1 para Vale 4\n");
		while(1){ //verificador
			char key = _getch();
    		if (key == 13){
				puntos_ronda++; //quiero
				opciones.erase(opciones.begin() + opciones.size() - 1);
				opciones.push_back("Vale 4");
				opciones.push_back("Retirarse");
				return;
			}
			else if (key == 27) { //no quiero
				jug_se_retira = true;
				return;
			} 
			else if (key == '1'){ //la subo
				puntos_ronda++;
				canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco);
				return;
			} 
		}
	} 
	else if (ia_puede_cantar_truco && puntos_ronda == 3){ //IA canta vale 4 (cuando la IA canto truco primero)
		printf("IA: \"Vale 4!!!\"\n");
		printf("ENTER para si, ESC para no\n");
		while(1){ //verificador
			char key = _getch();
    		if (key == 13){ //quiero
				puntos_ronda++; 
				return;
			}
			else if (key == 27) { //no quiero
				jug_se_retira = true;
				return;
			} 
		}
	}
}

void canta_truco(int &puntos_ronda, std::vector<std::string> &opciones, bool &ia_puede_cantar_truco){
	printf("\n"); 
	if (puntos_ronda == 1){ //JUG canta truco
		printf("Jug: \"Truco!!!\"\n");
		Sleep(800);
		if(rand()%10 >= 3){ //IA quiere
			opciones.erase(opciones.begin() + opciones.size() - 2); //borramos la opcion de truco
			puntos_ronda++;
			if (rand()%2) ia_canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco); //IA la sube
			else{ //IA quiere y no la sube
				printf("\nIA: \"Quiero!!!\"\n");
				Sleep(800);
			}
			return;
		} //IA no quiere
		printf("\nIA: \"No quiero...\"\n");
		Sleep(800);
		ia_se_retira = true;
		return;
	} 
	else if (puntos_ronda == 2){ //JUG canta retruco (cuando IA canto truco primero)
		ia_puede_cantar_truco = true;
		printf("Jug: \"Retruco!!!\"\n");
		opciones.erase(opciones.begin() + opciones.size() - 2);
		Sleep(800);
		if(rand()%10 >= 3){ //IA quiere
			puntos_ronda++;
			if (rand()%2) ia_canta_truco(puntos_ronda, opciones, ia_puede_cantar_truco); //IA la sube
			else{ //IA quiere y no la sube
				printf("\nIA: \"Quiero!!!\"\n");
				Sleep(800);
			}
			return;
		} //IA no quiere
		printf("\nIA: \"No quiero...\"\n");
		Sleep(800);
		ia_se_retira = true;
		return;
	} 
	else if (puntos_ronda == 3){ //JUG canta vale 4 (cuando el jug canto truco primero)
		printf("Jug: \"Vale 4!!!\"\n");
		Sleep(800);
		if(rand()%10 >= 3){ //IA quiere
			puntos_ronda++;
			printf("\nIA: \"Quiero!!!\"\n");
			Sleep(800);
			return;
		} //IA no quiere
		printf("\nIA: \"No quiero...\"\n");
		Sleep(800);
		ia_se_retira = true;
		return;
	}
}

