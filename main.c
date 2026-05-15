/*
Apellido: Gallardo, Elias
DNI: 43574421
Entrega: Sí/No

Apellido: Lazarte, Yaco Neyen
DNI: 40731532
Entrega: Sí/No

Apellido: Taboada, Priscila
DNI: 39986743
Entrega: Sí/No

*/

//EL BUCLE DEL JUEGO

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../GBT/gbt.h"
#include "../GBT/gbt_graficos.h"
#include "juego.h"
#include "graficos.h"
#include "piezas.h"

#define ANCHO_VENTANA 128
#define ALTO_VENTANA 128
#define CANT_COLORES 16


tGBT_ColorRGB paletaCGA[CANT_COLORES] =
{

    /// 0-15: Colores CGA (16 colores)
    {0x00, 0x00, 0x00}, // 0:   Negro
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}  // 15:  Usado como transparente por GBT
};

int main()
{
    srand(time(NULL));//Se utiliza para el randomizador de pieza

    Tablero miTablero;//matriz tablero
    ControlBolsa miBolsa;//vectorbolsa, ultima pieza, bolsa vacia
    EstadoJuego miJuego;//posicion,velocidad,idpieza,temp


    //Inicializacion de la biblioteca grafica GBT
    gbt_iniciar();
    //Creacion de la ventana (Nombre Ventana, Ancho, Alto, Escala)
    gbt_crear_ventana("Tetris C",ANCHO_VENTANA,ALTO_VENTANA, 7);
    //Aplicacion de la paleta de colores por defecto (CGA/VGA)
    //0 para que la libreria cargue sus colores base
    gbt_aplicar_paleta(paletaCGA,CANT_COLORES,0);

    /**----INICIALIZACION DE LA PARTIDA----*/
    inicializar_Control_Bolsa(&miBolsa);//Crea la bolsa de piezas y la llena
    printf("La bolsa:\n");
    for(int i=0;i<7;i++){
        printf("%d\t",miBolsa.vectorBolsa[i]);//VEMOS BOLSA EN CONSOLA
    }
    inicializar_Tablero(miTablero);//Declaracion e inicializacion del tablero
    iniciar_Partida(&miJuego, &miBolsa);

    int corriendo=1;//iniciamos el juego con 1 termina en 0
    while (corriendo)
    {
        gbt_procesar_entrada();
        if (gbt_tecla_presionada(GBTK_ESCAPE))corriendo=0;

        //Temporizador
        //Si la pieza toca el fondo o colisiona
        //1 Fijamos al tablero
        //2 Volver a pedir Pieza
        //3 iniciar caida y posiciones de pieza en funcion
        actualizar_Juego(&miJuego, &miBolsa, miTablero);//Actualizacion para el movimiento de la pieza

        //RENDERIZADO
        gbt_borrar_backbuffer(0); // Limpiar pantalla (negro)

        //DIBUJAMOS EL TABLERO ESTATICO
        dibujar_Tablero(miTablero); // Dibujar el estado actual

        //DIBUJAMOS LA PIEZA CAYENDO
        dibujar_Pieza_Caida(&miJuego);//Dibuja la caida de la pieza

        gbt_volcar_backbuffer(); //Envia a pantalla lo dibujado
        gbt_esperar(16); // Aproximadamente 60 FPS
    }


    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
