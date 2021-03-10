#include <Arduino.h>

/*
    Biblioteca super simple que ilumina el LED indicado con el código morse correspondiente.
    Para indicar que palabra mostrar ingresarla en la función en mayúsculas. 
    La biblioteca soporta todas las letras (Excepto la Ñ, esta no existe en morse) y los números del 0 al 9.
    
    Ejemplo de uso:
    morseBlinker(PIN_LED, "GUIDO")
*/

void morse_Raya(int);
void morse_Punto(int);
void morse_EspacioLetra();
void morse_EspacioPalabra();
void morseBlinker (int, String);
