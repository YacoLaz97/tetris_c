#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED


#include "piezas.h"
#include "../GBT/gbt_temporizador.h"

//Dimensiones del tablero de Tetris
#define FILAS 24 //20 altura + 4 para la creacion de los tetrominos
#define COLUMNAS 10

//VALORES PARA LA DIFICUALTAD DE CAIDA , FIJACION Y VELOCIDAD DE LA PIEZA
#define VELOCIDAD_INICIAL 0.8f //SEGUNDOS POR FILA
#define DELAY_BASE 1.0f //SEGUNDO INICIAL DE FIJACION
#define INCREMENTO_DIFICULTAD 0.97f //REDUCCION DEL 3% (100% - 3% = 97%)

typedef struct{
    int x;//POSICION X
    int y;//POSICION Y
    int piezaID;//ID PIEZA ACTUAL DE 0 A 6
    float velocidadActual;//TIEMPO EN SEGUNDOS
    int contadorPiezas;//CONTADOR DE PIEZAS PARA AUMENTO DE VELOCIDAD (CADA 10 AUMENTO DE VELOCIDAD)
    float DelayActual;//TIEMPO PARA LA FIJACION DE LA PIEZA AL TOCAR EL SUELO
    //PUNTEROS A LOS TEMPORIZADORES (PUNTEROS PARA CADA TEMPORIZADOR)
    tGBT_Temporizador *tempCaida;
    tGBT_Temporizador *tempFijacion;
}EstadoJuego;

//Declaracion del tablero como matriz y de la pieza como matriz
typedef int Tablero[FILAS][COLUMNAS];

// --- PROTOTIPOS ---

void iniciar_Partida(EstadoJuego *juego, ControlBolsa *bolsa);//Inicializa el estado, la posicion y crea los temporizadores
void actualizar_Juego(EstadoJuego *juego, ControlBolsa *bolsa, Tablero tablero);//Se encarga de mover la pieza hacia abajo y gestionar la fijacion
void finalizar_Juego(EstadoJuego *juego);//Destruye los temporizadores al cerrar el programa
void penalizar_Fijacion(EstadoJuego *juego);// Reduce el DelayActual al 50% cuando el jugador mueve la pieza en el suelo


#endif //JUEGO_H_INCLUDED
