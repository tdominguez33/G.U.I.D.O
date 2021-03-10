#include <Arduino.h>

// Funciones necesarias para el funcionamiento de la libreria
String getHoraIP_Init ();
void getHoraIP_Parse ();

// Funciones que devuelven datos según la ubicación del ESP (IP)
String getSegundosIP ();
String getMinutosIP ();
String getHoraIP ();
String getDiaIP ();
String getMesIP ();
String getYearIP ();
int getOffsetIP ();

// Funciones que devuelven las horas de las diferentes zonas horarias
String getHoraUTC ();   // Universal Time Coordinated   (Lo mismo que GMT)
String getHoraEST ();   // Eastern Standard Time        (Lo mismo que EDT)
String getHoraPST ();   // Pacific Standard Time
