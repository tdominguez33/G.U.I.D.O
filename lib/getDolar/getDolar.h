#include <Arduino.h>

// Funciones necesarias para el funcionamiento de la libreria
String getDolar_JSON ();
void getDolar_JSON_Parse ();

// Funciones que devuelven los valores deseados
const char* getDolarOficial_Compra ();
const char* getDolarOficial_Venta ();
const char* getDolarBlue_Compra ();
const char* getDolarBlue_Venta ();
const char* getDolarBolsa_Compra ();
const char* getDolarBolsa_Venta ();
const char* getDolarContadoConLiqui_Compra ();
const char* getDolarContadoConLiqui_Venta ();
