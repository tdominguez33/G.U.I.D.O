#include <Arduino.h>

#define INTERVALO_CONFIGURACION 500

unsigned long lastMillis = 0;
bool estadoLED = false;

void statusLED_Configuracion (int led_pin){
    unsigned long currentMillis = millis();

    if (currentMillis - lastMillis >= INTERVALO_CONFIGURACION){
        lastMillis = currentMillis;
        if (estadoLED == false){
            estadoLED = true;
        }else{
            estadoLED = false;
        }
    }
    digitalWrite (led_pin, estadoLED);
}
