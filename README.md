# Trufa-Truco - 3/7/2023
### Integrantes: Ignacio Lesta, Santiago Morito y Byron Urriza.
El programa principal es el "Trufa.cpp". 
En la carpeta Funciones se encuentra "trufa.hpp", donde están declaradas las funciones y variables globales. 
En los demás .cpp estan las funciones completas, estos .cpp son importados en "Trufa.cpp"

Acá está el link al documento del proyecto: https://docs.google.com/document/d/1AlUI5J0dY3bqmGBcczAyxzD5gWqkHnba76Fs-8cEQjg/edit?usp=drive_link.
Que incluye Seguimiento y Manual de usuario.

El programa es un juego de truco totalmente funcional, tanto jugador como IA pueden cantar en cualquier momento y jugar cualquier carta, hasta llegar a 30 puntos y ganar.

El programa tiene algunos bugs y fallas, que no se pudieron corregir por falta de tiempo. Sin embargo, son mínimas (salvo la última, son muy improbables o afectan a aspectos muy concretos), no perjudican la experiencia, y en los demás aspectos el programa funciona a la perfección y es muy intuitivo.

Los bugs/errores identificados son:
+ Si empieza la IA y la primer carta se emparda, en vez de tocarle tirar a la IA le toca al jugador.

  Este bug se debe a una que el código de las rondas no fue totalmente bien adaptado a ambos casos (que empiece el jug o que empiece la IA), no es complicado de solucionar, pero lleva bastante tiempo, y es una falla demasiado insignificante y poco probable como para que afecte.
+ Si se canta truco en la primera ronda, no se puede cantar "El envido va primero".

  Este error es más grave, no lo pudimos solucionar por falta de tiempo.
+ Si se tienen tres cartas del mismo palo hay riesgo de que calcule mal el envido

  Nuevamente, por falta de tiempo no se pudo corregir, pero de nuevo, es tan poco probable que suceda que pierde toda su gravedad.
+ Cuando alguno llega a 30 puntos, no se termina inmediatamente el partido, sino que termina cuando finaliza la ronda

  No es difícil de solucionar (hubo falta de tiempo) y tampoco afecta tanto.
+ La "inteligencia" de la IA son randoms ._.

### Cosas que el programa hace/se pueden hacer:
+ Cantar truco
+ Cantar envido
+ (ambos en cualquier momento)
+ La IA puede cantar truco (en cualquier momento) y envido
+ Retirarse
+ Suma los puntos (cuando alguno llega a 30 termina)
+ Tiene los estilos completos
+ Salir del programa en cualquier momento
+ Imprimir reglas
### No vamos a:
+ Hacer la trufa
+ Hacer la flor
