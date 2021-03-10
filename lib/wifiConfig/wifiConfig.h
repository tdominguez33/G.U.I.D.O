#include <Arduino.h>
// Configuración Necesaria para la inicializacion del servidor
void configWifi();

// Devuelve TRUE si se recibió un SSID y Contraseña válidos de la página
bool configuracionWIFILista();

// Espera respuesta del servidor
void handleClient();

// Funciones que se ejecutan dependiendo de en que página nos encontremos
void handleRoot();
void handleSuccess();
void handleNotFound();

// Funciones que devuelven la página web a mostrar
String paginaHTML_Root();
String paginaHTML_Success();
String paginaHTML_Error();
String paginaHTML_404();

// Funciones que devuelven el SSID, la contraseña y el ChatID ingresados.
String getSSID();
String getPassword();
String getChatID();
