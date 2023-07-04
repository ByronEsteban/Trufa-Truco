#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include "trufa.hpp"

int calcular_tanto_jug(std::vector<Carta> &mano_jugador){
	int envido = 0;
	/*if (mano_jugador[0].palo == mano_jugador[1].palo && mano_jugador[2].palo == mano_jugador[1].palo) {
		int min = 8;
		for (int i = 0; i < 3; i++) {
			if (mano_jugador[i].valor_envido < min) {
				min
			}
		}
	}*/
	/*else*/ if (!strcmp(mano_jugador[0].palo, mano_jugador[1].palo)) {
		envido = 20 + mano_jugador[0].valor_envido + mano_jugador[1].valor_envido;
	} else if (!strcmp(mano_jugador[2].palo, mano_jugador[1].palo)) {
		envido = 20 + mano_jugador[2].valor_envido + mano_jugador[1].valor_envido;
	} else if (!strcmp(mano_jugador[0].palo, mano_jugador[2].palo)) {
		envido = 20 + mano_jugador[0].valor_envido + mano_jugador[2].valor_envido;
	} else {
		for (int i = 0; i < 3; i++) {
			if (mano_jugador[i].valor_envido > envido) {
				envido = mano_jugador[i].valor_envido;
			}
		}
	}
	return envido;
}

int calcular_tanto_ia(std::vector<Carta> &mano_ia){
	int envido = 0;
	/*else*/ if (!strcmp(mano_ia[0].palo, mano_ia[1].palo)) {
		envido = 20 + mano_ia[0].valor_envido + mano_ia[1].valor_envido;
	} else if (!strcmp(mano_ia[2].palo, mano_ia[1].palo)) {
		envido = 20 + mano_ia[2].valor_envido + mano_ia[1].valor_envido;
	} else if (!strcmp(mano_ia[0].palo, mano_ia[2].palo)) {
		envido = 20 + mano_ia[0].valor_envido + mano_ia[2].valor_envido;
	} else {
		for (int i = 0; i < 3; i++) {
			if (mano_ia[i].valor_envido > envido) {
				envido = mano_ia[i].valor_envido;
			}
		}
	}
	return envido;
}

bool comparar_tanto(int tanto_jug, int tanto_ia, bool jugador_es_mano, bool quien_canta){
	Sleep(800);
	if(quien_canta){
		if (tanto_jug > tanto_ia || (tanto_jug == tanto_ia && jugador_es_mano)) {
			printf("Jug: \"%d\"\n", tanto_jug);
			printf("IA: \"Son buenas...\"\n");
			Sleep(1000);
			return true;
		}
		else {
			printf("Jug: \"%d\"\n", tanto_jug);
			printf("IA: \"%d son mejores!!\"\n", tanto_ia);
			Sleep(1000);
			return false;
		}
	}
	else {
		if (tanto_ia > tanto_jug || (tanto_ia == tanto_jug && !jugador_es_mano)) {
			printf("IA: \"%d\"\n", tanto_ia);
			printf("Jug: \"Son buenas...\"\n");
			Sleep(1000);
			return false;
		}
		else {
			printf("IA: \"%d\"\n", tanto_ia);
			printf("Jug: \"%d son mejores!!\"\n", tanto_jug);
			Sleep(1000);
			return true;
		}
	}
}

int jug_canta_envido(std::vector<Carta> &mano_jugador, std::vector<Carta> &mano_ia, bool jugador_es_mano){
	int tanto_jug = calcular_tanto_jug(mano_jugador);
	int tanto_ia = calcular_tanto_ia(mano_ia);
	printf("Jug: \"Envido!!!\"\n");
	if(rand()%2){ //ia quiere
		if(rand()%3 == 0){ //ia la sube
			int abc = rand()%10;
			if(abc == 10){ //falta envido
				printf("IA: \"Falta Envido!!!\"\n");
				printf("ENTER para s�, ESC para no");
				while(1){ //verificador
					char key = _getch();
    				if (key == 13) { //si quiero
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 30 - puntos_ia;
						else return -30 + puntos_jug;
    				} 
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -2;
    				} 
				}
			} 
			else if (abc >= 7){ //real envido
				printf("IA: \"Real Envido!!!\"\n");
				printf("ENTER para s�, ESC para no, 1 para Falta envido");
				while(1){ //verificador
					char key = _getch();
    				if (key == 13) { //si quiero
    					printf("\nJug: \"Quiero!!!\"\n");
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 5;
						else return -5;
    				}
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -2;
    				} 
    				else if (key == '1'){
    					printf("\nJug: \"Falta envido!!!\"\n");
    					Sleep(800);
    					if(rand()%5 == 0){ //ia quiere
    						printf("IA: \"Quiero!!!\"\n");
							if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 30 - puntos_ia;
							else return -30 + puntos_jug;
    					} else return 5;
    				} 
				}
			}
			else { //envido envido
				printf("IA: \"Envido!!!\"\n");
				printf("ENTER para s�, ESC para no, 1, para Real envido, 2 para Falta envido");
				while(1){ //verificador
					char key = _getch();
    				if (key == 13) { //si quiero
    					printf("\nJug: \"Quiero!!!\"\n");
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 4;
						else return -4;
    				}
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -2;
    				} 
    				else if (key == '1'){ //jug canta real envido
    					printf("\nJug: \"Real Envido!!!\"\n");
    					Sleep(800);
    					int bca = rand()%4;
    					if(bca == 0){ //ia canta falta
    						printf("IA: \"Falta Envido!!!\"\n");
							printf("ENTER para s�, ESC para no");
							while(1){ //verificador
								char key = _getch();
    							if (key == 13) { //si quiero
        						if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 30 - puntos_ia;
								else return -30 + puntos_jug;
    							} 
								else if (key == 27) { //no quiero
        							printf("\nJug: \"No quiero...\"\n");
        							return -7;
    							} 
							}
						} 
						else if(bca == 1){ //ia no quiere
							printf("IA: \"No quiero...\"\n");
							return 4;
						}
    					else { //ia quiere
    							printf("IA: \"Quiero!!!\"\n");
    							Sleep(800);
								if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 7;
								else return -7;
    					} 
    				} 
    				else if (key == '2'){ //jug canta falta envido
    					printf("\nJug: \"Falta envido!!!\"\n");
    					Sleep(800);
    					if(rand()%5 == 0){ //ia quiere
    						printf("IA: \"Quiero!!!\"\n");
							if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 30 - puntos_ia;
							else return -30 + puntos_jug;
    					} 
						else{
							printf("IA: \"No quiero...\"\n");
							return 4;
						} 
    				} 
				}
			}
		} 
		else { //ia no la sube == 2 puntos
			printf("\nIA: \"Quiero!!!\"\n");
        	if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 1)) return 2;
			else return -2;
		}
	} //ia no quiere
	printf("\nIA: \"No quiero...\"\n");
	return 1;
}

int ia_canta_envido(std::vector<Carta> &mano_jugador, std::vector<Carta> &mano_ia, bool jugador_es_mano){
	int tanto_jug = calcular_tanto_jug(mano_jugador);
	int tanto_ia = calcular_tanto_ia(mano_ia);
	printf("IA: \"Envido!!!\"\n");
	printf("ENTER para s�, ESC para no, 1 para Envido, 2 para Real envido, 3 para Falta envido");
	while(1){ //verificador
		char key = _getch();
    	if (key == 13) { //si quiero
    		printf("\nJug: \"Quiero!!!\"\n");
        	if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 2;
			else return -2;
    	} 
		else if (key == 27) { //no quiero
        	printf("\nJug: \"No quiero...\"\n");
        	return -1;
    	} 
    	else if(key == '1'){ //canto envido envido
    		printf("Jug: \"Envido!!!\"\n");
    		int bca = rand()%5;
    		if(bca == 0){ //ia canta falta
    			printf("IA: \"Falta Envido!!!\"\n");
				printf("ENTER para s�, ESC para no");
				while(1){ //verificador
					char key = _getch();
   					if (key == 13) { //si quiero
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 30 - puntos_ia;
						else return -30 + puntos_jug;
    				} 
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -4;
    				} 
				}
			} 
			else if(bca == 1){ //ia canta real
				printf("IA: \"Real Envido!!!\"\n");
				printf("ENTER para s�, ESC para no, 1 para Falta envido");
				while(1){ //verificador
					char key = _getch();
   					if (key == 13) { //si quiero
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 7;
						else return -7;
    				} 
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -4;
    				} 
    				else if (key == '1') { //canto falta envido
        				printf("Jug: \"Falta Envido!!!\"\n");
						if(rand()%5 > 2){ //IA quiere
							printf("IA: \"Quiero!!!\"\n");
							if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 30 - puntos_ia;
							else return -30 + puntos_jug;
						}
						else { //IA no quiere
        					printf("\nIA: \"No quiero...\"\n");
        					return 7;
    					} 
					}
    			} 
			}
			else if(bca == 2){ //ia no quiere
				printf("\nIA: \"No quiero...\"\n");
        		return 2;
			}
			else{ //ia quiere
				printf("\nJug: \"Quiero!!!\"\n");
        		if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 4;
				else return -4;
			}
		}
    	else if(key == '2'){ //canto real envido
    		printf("Jug: \"Real envido!!!\"\n");
    		int bca = rand()%3;
    		if(bca == 0){ //ia canta falta
    			printf("IA: \"Falta Envido!!!\"\n");
				printf("ENTER para s�, ESC para no");
				while(1){ //verificador
					char key = _getch();
   					if (key == 13) { //si quiero
        				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 30 - puntos_ia;
						else return -30 + puntos_jug;
    				} 
					else if (key == 27) { //no quiero
        				printf("\nJug: \"No quiero...\"\n");
        				return -5;
    				} 
				}
			}
			else if(bca == 1){ //ia no quiere
				printf("\nIA: \"No quiero...\"\n");
        		return 2;
			}
			else{ //ia quiere
				printf("\nIA: \"Quiero!!!\"\n");
        		if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 5;
				else return -5;
			}
    	} 
    	else if(key == '2'){ //canto falta envido
    		printf("Jug: \"Falta Envido!!!\"\n");
			if(rand()%4 == 0){ //IA quiere
				printf("IA: \"Quiero!!!\"\n");
				if (comparar_tanto(tanto_jug, tanto_ia, jugador_es_mano, 0)) return 30 - puntos_ia;
				else return -30 + puntos_jug;
			}
			else { //IA no quiere
        		printf("\nIA: \"No quiero...\"\n");
        		return 2;
    		} 
    	}
	}
}
  
