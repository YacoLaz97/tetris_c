#ifndef PIEZAS_H_INCLUDED
#define PIEZAS_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include "../GBT/gbt_temporizador.h"

//Dimensiones del tablero de Tetris
#define FILAS 24 //20 altura + 4 para la creacion de los tetrominos
#define COLUMNAS 10

#define TAM_PIEZA 4

typedef int Pieza[TAM_PIEZA][TAM_PIEZA];

// Estructura para manejar la logica de la bolsa de piezas
typedef struct{
    int vectorBolsa[7];//BOLSA DE VECTOR
    int ultimaPiezaEntregada;
    int bolsaVacia;//0 SI , 1 NO
}ControlBolsa;

//Prototipos Randomizador de bolsa de piezas
void inicializar_Control_Bolsa(ControlBolsa *control);
int obtener_Proxima_Pieza(ControlBolsa *control);
void Mezclar_Bolsa(ControlBolsa *control);


#endif // PIEZAS_H_INCLUDED
