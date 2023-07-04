#ifndef TRUFA_HPP
#define TRUFA_HPP
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>

bool jug_se_retira, ia_se_retira;
int puntos_jug, puntos_ia;
struct Carta{
	int valor;
	char *palo;
	int posicion; //la fuerza de la carta (la mas fuerte es la 1, la mas debil la 14). 1 de espada = 1, 1 de basto = 2... todos los 3 = 5...
	bool repartida; //si la carta fue repartida al jug o a la IA, para evitar que se reparta la misma carta dos veces
	int valor_envido; //10, 11, 12 valen 0; el resto valen sus valores (1 = 1, 2 = 2...)
};

//funciones listadas por orden de aparicion:
//el primer numero es el orden de aparicion, el segundo el desglose de las funciones como una EDT, el tecero el archivo donde esta la funcion

//int main(); 0 - 0 - Trufa.cpp
void llenar_baraja(Carta baraja[], int valores[], char *palos[]); //1 - 0.1 - Trufa.cpp
void truco(Carta baraja[]); //2 - 1 - Trufa.cpp
void desordenar_baraja(Carta baraja[]); //3 - 1.1 - Trufa.cpp
void turno_jugador(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_jugador, std::vector<Carta> &mano_ia, int &puntos_ronda, int &puntos_envido, int turno, bool &ia_puede_cantar_truco); //4 - 1.2 - turnos.cpp 
int calcular_tanto_jug(std::vector<Carta> &mano_jugador); //5 - 1.2.1 - envido.cpp
int calcular_tanto_ia(std::vector<Carta> &mano_ia); //6 1.2.2 - envido.cpp
void imprimir(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_jugador); //7 - 1.2.3 - imprimir.cpp
void imprimir_cartas_tiradas(std::vector<Carta> &cartas_tiradas_jug, std::vector<Carta> &cartas_tiradas_ia); //8 -1.2.3.1 - imprimir.cpp
void imprimir_cartas(std::vector<Carta> &mano_jugador); //9 - 1.2.3.2 - imprimir.cpp
void tira_carta(int opcion, std::vector<Carta> &cartas_tiradas_jug, Carta carta_tirada, std::vector<Carta> &mano_jugador, std::vector<std::string> &opciones, int turno); //10 - 1.2.4 - turnos.cpp
void canta_truco(int &puntos_ronda, std::vector<std::string> &opciones, bool &ia_puede_cantar_truco); //11 - 1.2.5 y 1.4.1.1 - truco.cpp 
void ia_canta_truco(int &puntos_ronda, std::vector<std::string> &opciones, bool &ia_puede_cantar_truco); //12 - 1.2.5.1 y 1.4.1 - truco.cpp 
int jug_canta_envido(int tanto_jug, int tanto_ia, bool jugador_es_mano); //13 - 1.2.6 - envido.cpp
bool comparar_tanto(int tanto_jug, int tanto_ia, bool jugador_es_mano); //14 - 1.2.6.1 y 1.3.1 - envido.cpp
int ia_canta_envido(std::vector<Carta> &mano_jugador, std::vector<Carta> &mano_ia, bool jugador_es_mano); //15 - 1.3 - envido.cpp
void turno_ia(std::vector<std::string> &opciones, std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_ia, int &puntos_ronda, int turno, bool &ia_puede_cantar_truco); //16 - 1.4 - turnos.cpp
void tira_carta_ia(std::vector<Carta> &cartas_tiradas_ia, std::vector<Carta> &mano_ia, int turno); //17 - 1.5 - turnos.cpp
void carta_ganada(int carta_ganada_jug, int carta_ganada_ia, bool hizo_primera, int turno, int &ganador); //18 - 1.6 - turnos.cpp
void imprimir_reglas(char *palos[]); //19 - 2.1 - reglas.cpp
void llenar_orden_cartas(Carta orden_de_cartas[], char *palos[]); //20 - 2.1.1 - reglas.cpp
void imprimir_orden_cartas(Carta orden_de_cartas[]); //21 - 2.1.2 - reglas.cpp

#endif

