//PIEZAS CREACION, RANDOMIZACION,OBTENCION


#include <time.h>
#include <stdlib.h>
#include "juego.h"


void inicializar_Control_Bolsa(ControlBolsa *control)
{
    //Iniciamos La ultima pieza fuera de rango (piezasa entre 0 y 6)
    control->ultimaPiezaEntregada=-1;
    control->bolsaVacia=0;
    //Mezclamos la bolsa
    Mezclar_Bolsa(control);
}

void Mezclar_Bolsa(ControlBolsa *control)
{
    int piezas[7]= {0,1,2,3,4,5,6};
    int auxpieza,i,j;

    if(control->bolsaVacia==0)//control por si entramos aca sin terminar las piezas
    {

        //Mezclamos las piezas (7)
        for(i=0; i<7; i++)
        {
            j=rand()%(i+1);
            auxpieza= piezas[i];
            piezas[i]=piezas[j];
            piezas[j]=auxpieza;
        }
        //Evitamos que la primera pieza de la nueva bolsa sea igual a la ultima de la vieja bolsa
        if(piezas[0]==control->ultimaPiezaEntregada)
        {
            auxpieza=piezas[0];
            piezas[0]=piezas[6];
            piezas[6]=auxpieza;
        }
        //Copiamos vector en el vector de la estructura
        for(i=0; i<7; i++)
        {
            control->vectorBolsa[i]=piezas[i];
        }
        //Control de cantidad de piezas en el vector
        control->bolsaVacia=7;
    }
}

int obtener_Proxima_Pieza(ControlBolsa *control)
{
    int indice,piezaAEntregar;
    //Si no quedan piezas (contador en 0), mezclamos una nueva bolsa
    if (control->bolsaVacia==0)
    {
        Mezclar_Bolsa(control);
    }
    //Calculamos el Indice de pieza a entregar
    //Si bolsaVacia es 7, entregamos la posicion 0
    //Si bolsaVacia es 6, entregamos la posicion 1
    indice=7-control->bolsaVacia;
    piezaAEntregar=control->vectorBolsa[indice];

    //Actualizamos el estado para la proxima vez
    control->ultimaPiezaEntregada=piezaAEntregar;
    control->bolsaVacia--;//Restamos 1 al contador de piezas de la bolsa

    return piezaAEntregar;
}
