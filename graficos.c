//TODA LA MECANICA DE LOS DIBUJOS EN PANTALLA

#include "graficos.h"

//Colores
#define N 15 // Transparente (Fondo)
#define A 14 // Amarillo (O)
#define C 3  // Cian/Celeste (I)
#define V 2  // Verde(S)
#define R 4  // Rojo (Z)
#define M 5  // Magenta/Purpura (T)
#define B 1  // Azul (J)
#define L 6  // Marron/Naranja (L)
#define G 7 // gris claro

//PIEZAS
// I
Pieza pieza_I =
{
    {N, N, N, N},
    {C, C, C, C},
    {N, N, N, N},
    {N, N, N, N}
};
// O
Pieza pieza_O =
{
    {A, A, N, N},
    {A, A, N, N},
    {N, N, N, N},
    {N, N, N, N}
};
// T
Pieza pieza_T =
{
    {N, M, N, N},
    {M, M, M, N},
    {N, N, N, N},
    {N, N, N, N}
};
// S
Pieza pieza_S =
{
    {N, V, V, N},
    {V, V, N, N},
    {N, N, N, N},
    {N, N, N, N}
};
// Z
Pieza pieza_Z =
{
    {R, R, N, N},
    {N, R, R, N},
    {N, N, N, N},
    {N, N, N, N}
};
// J
Pieza pieza_J =
{
    {B, N, N, N},
    {B, B, B, N},
    {N, N, N, N},
    {N, N, N, N}
};
// L
Pieza pieza_L =
{
    {N, N, L, N},
    {L, L, L, N},
    {N, N, N, N},
    {N, N, N, N}
};

//FUNCION LLENA DE COLOR EL FONDO DE LA MATRIZ / NO DIBUJA SOLO LLENA DE NUMEROS EL FONDO
void inicializar_Tablero(Tablero tablero)
{
    int f,c;
    for (f=0; f<FILAS; f++)
    {
        for (c=0; c<COLUMNAS; c++)
        {
            if(f==4)
                tablero[f][c]=4;//COLOREAMOS LA 4TA FILA DE ROJO=4 PARA VER EL LIMITE TABLERO VISIBLE
            else
                tablero[f][c]=7;//GRIS TODO EL TABLERO
        }
    }
}

//FUNCION QUE DIBUJA EN PANTALLA LOS PIXELES
void dibujar_Tablero(Tablero tablero)
{
    int f,c,xBase,yBase;

    //Recorremos desde la fila 4 (las primeras 4 son del margen y para crear la pieza en el tablero)
    //f=0 porque asi dibujo las celdas invisibles, f=4 para no dibujarlas
    for (f=0; f<FILAS; f++)
    {
        for (c=0; c<COLUMNAS; c++)
        {
            // Si la celda no es transparente (color 15)
            if(tablero[f][c]!=15)//OPTIMIZACION CONSIDERO PORQUE SINO ESTARIA DIBUJANDO TODO EL TIEMPO / NO HACE EFECTO POR FONDO GRIS PARA VISUALIZACION
            {

                //#define TAM_BLOQUE 5
                //#define MARGEN_X 39   // Centrado horizontal (128-50)/2 =39 desplazamos los 39 pixele para centrar el tablereo
                //#define MARGEN_Y 4

                //Calculamos la esquina superior izquierda del bloque
                //xBase: Margen izquierdo + (columna actual * tamaño del bloque = 5)
                //yBase: Margen superior + ((fila-4) * tamaño del bloque)
                //Restamos 4 a la fila para que la fila 4 de la matriz sea la 0 en pantalla CONSIDERAR PARA NO DIBUJAR LA PARTE DEL TABLERO INVISIBLE

                xBase=MARGEN_X+(c*TAM_BLOQUE);
                yBase=MARGEN_Y+(f*TAM_BLOQUE);

                //DIBUJO DEL BLOQUE
                //Pintamos pixel por pixel un cuadrado de 4x4. Como el TAM_BLOQUE es 5, queda 1 pixel de margen para que no sea una mancha lisa
                for (int i=0; i<4; i++)
                {
                    for (int j=0; j<4; j++)
                    {
                        //void gbt_dibujar_pixel(uint16_t x, uint16_t y, uint8_t colorIndice);
                        gbt_dibujar_pixel(xBase+i,yBase+j,tablero[f][c]);
                    }
                }
            }
        }
    }
}

//OBTENEMOS LA PIEZA Y LA DIBUJAMOS EN PANTALLA
void dibujar_Pieza_Caida(EstadoJuego *juego)
{
    int f, c, colorPieza, yBase, xBase;
    Pieza *piezaSeleccionada;

    //OBTENEMOS LA MATRIZ DE LA PIEZA
    switch(juego->piezaID)
    {
    case 0:
        piezaSeleccionada = &pieza_I;
        break;
    case 1:
        piezaSeleccionada = &pieza_O;
        break;
    case 2:
        piezaSeleccionada = &pieza_T;
        break;
    case 3:
        piezaSeleccionada = &pieza_S;
        break;
    case 4:
        piezaSeleccionada = &pieza_Z;
        break;
    case 5:
        piezaSeleccionada = &pieza_J;
        break;
    case 6:
        piezaSeleccionada = &pieza_L;
        break;
    }

    //OBTENEMOS EL COLOR POR EL PUNTERO A LA PIEZA
    for(f=0; f<4; f++)
    {
        for(c=0; c<4; c++)
        {

            colorPieza = (*piezaSeleccionada)[f][c];

            if (colorPieza != 15)
            {
                xBase=MARGEN_X+((juego->x+c)*TAM_BLOQUE);
                yBase=MARGEN_Y+((juego->y+f-0)*TAM_BLOQUE); // Ojo aquí con el -2 o -4 según tu tablero

                for(int i=0; i<4; i++)
                {
                    for (int j=0; j<4; j++)
                    {
                        gbt_dibujar_pixel(xBase+i,yBase+j,colorPieza);
                    }
                }
            }
        }
    }
}
