#include <Arduino.h>
int stringCaracteres = 0;

/*
    Código Morse Internacional:

    -La longitud de un punto es una unidad.
    -La longitud de una raya es de tres unidades.
    -El espacio entre partes de una misma letra es de una unidad.
    -El espacio entre letras es de tres unidades.
    -El espacio entre palabras es de siete unidades.
*/

// Función que representa una raya en el LED, ya incluye el delay necesario entre partes de una misma letra
void morse_Raya(int status_led){
    digitalWrite (status_led, HIGH);
    delay(750);
    digitalWrite (status_led, LOW);
    delay(250);
}

// Función que representa un punto en el LED, ya incluye el delay necesario entre partes de una misma letra
void morse_Punto(int status_led){
    digitalWrite (status_led, HIGH);
    delay(250);
    digitalWrite (status_led, LOW);
    delay(250);
}

// Funcion que separa las letras (Sumamos 500ms a los 250ms que quedan de la última letra para hacer la separación)
void morse_EspacioLetra(){
    delay (500);
}

//Función que separa las palabras (Sumamos 1500ms a los 250ms que quedan de la última letra para hacer la separación)
void morse_EspacioPalabra(){
    delay (1500);
}

void morseBlinker (int status_led, String texto){
    stringCaracteres = texto.length();
    for (int i = 0; i <= stringCaracteres; i++){
        String caracter;
        caracter = texto.substring(i, i+1);
        
        if (caracter == "A"){           // .-
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "B"){     // -...
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "C"){     // -.-.
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "D"){     // -..
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "E"){     // .
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "F"){     // ..-.
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "G"){     // --.
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "H"){     // ....
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "I"){     // ..
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "J"){     // .---
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "K"){     // -.-
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "L"){     // .-..
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "M"){     // --
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "N"){     // -.
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "O"){     // ---
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "P"){     // .--.
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "Q"){     // --.-
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "R"){     // .-.
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "S"){     // ...
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "T"){     // -
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "U"){     // ..-
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "V"){     // ...-
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "W"){     // .--
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "X"){     // -..-
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "Y"){     // -.--
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "Z"){     // --..
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "1"){     // .----
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "2"){     // ..---
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "3"){     // ...--
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "4"){     // ....-
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == "5"){     // .....
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "6"){     // -....
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "7"){     // --...
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "8"){     // ---..
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "9"){     // ----.
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Punto(status_led);
            morse_EspacioLetra();
        }else if (caracter == "0"){     // -----
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_Raya(status_led);
            morse_EspacioLetra();
        }else if (caracter == " "){     // (7 Espacios)
            morse_EspacioPalabra();
        }
    }
}
