#include <stdlib.h>
#include "juego.h"

//CAIDA DE PIEZAS, VELOCIDAD, COLISION, ETC

void iniciar_Partida(EstadoJuego *juego, ControlBolsa *bolsa){
    //Pedimos la primera pieza
    juego->piezaID=obtener_Proxima_Pieza(bolsa);
    juego->x=3;
    juego->y=0;

    //Definimos tiempos iniciales
    juego->velocidadActual=VELOCIDAD_INICIAL;
    juego->contadorPiezas=0;
    juego->DelayActual=DELAY_BASE;

    //Creamos temporizadores. Guardamos los punteros en la estructura
    juego->tempCaida=gbt_temporizador_crear((double)juego->velocidadActual);
    juego->tempFijacion=gbt_temporizador_crear((double)juego->DelayActual);
}

void actualizar_Juego(EstadoJuego *juego, ControlBolsa *bolsa, Tablero tablero){
    //---LOGICA DE CAIDA---
    //gbt_temporizador_consumir devuelve 1 si paso el tiempo y reinicia solo el temp
    //Si pasaron los 0.8 segundos, entra al if
    if(gbt_temporizador_consumir(juego->tempCaida)){
        if(juego->y<22){//Si y=24, la pieza ya ocupa hasta la fila 23 (el fondo real)
            juego->y++;
        }
    }

    //---LOGICA DE FIJACION---
    if(juego->y>=22){
        //Usamos el otro puntero para controlar el tiempo de fijacion
        if(gbt_temporizador_consumir(juego->tempFijacion)){

            juego->contadorPiezas++;//Sumamos una pieza mas c/10 aumentara la dificultad

            //Si pasaron 10 piezas, aumentamos dificultad
            if(juego->contadorPiezas==10){
                juego->velocidadActual*=INCREMENTO_DIFICULTAD;
                juego->contadorPiezas=0;

                //Actualizamos el temporizador de caida con la nueva velocidad
                gbt_temporizador_destruir(juego->tempCaida);
                juego->tempCaida=gbt_temporizador_crear((double)juego->velocidadActual);
            }

            //Reseteamos para la siguiente pieza
            juego->piezaID=obtener_Proxima_Pieza(bolsa);
            juego->x=3;
            juego->y=0;

            //Reseteamos para igualar el temp de fijacion con tempCaida, por el aumento de dificultad (+3% cada 10 piezas caidas)
            gbt_temporizador_destruir(juego->tempFijacion);
            juego->tempFijacion=gbt_temporizador_crear((double)juego->DelayActual);
        }
    }
    else{
        //Pausamos el temporizador de fijacion
        //Tenia pensado cheat para promocion que la pieza pueda subir, pausar para subir
        //Pausar para salir del juego
        gbt_temporizador_pausar(juego->tempFijacion);
    }
}

void penalizar_Fijacion(EstadoJuego *juego){
    //Si el jugador mueve la pieza estando en el suelo, el tiempo de pegado baja al 50%
    juego->DelayActual*=0.5f;

    //Recreamos el temp con el nuevo tiempo reducido
    gbt_temporizador_destruir(juego->tempFijacion);
    juego->tempFijacion=gbt_temporizador_crear((double)juego->DelayActual);
}

void finalizar_Juego(EstadoJuego *juego) {
    //Liberamos la memoria de los punteros antes de salir
    gbt_temporizador_destruir(juego->tempCaida);
    gbt_temporizador_destruir(juego->tempFijacion);
}

//FALTA COLISION DE BLOQUES Y MOVIMIENTOS
