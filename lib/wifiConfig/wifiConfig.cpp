#include <Arduino.h>
#include <ESP8266WebServer.h>

// Iniciamos un servidor en el puerto 80
ESP8266WebServer server(80);

// Variables donde se almacenan el SSID y contraseña ingresados por el usuario
String ssidRecibido;
String passwordRecibido;
String chatIDRecibido;

// Variable que informa si la configuración está lista
bool ConfigReady = false;

// Página Principal
String paginaHTML_Root(){
    String HTML = "<!DOCTYPE html>\n";
    HTML +="<html lang=\"es\" style=\"height: 100%; font-family: Courier; background-color: rgb(30, 30, 30); display: table; margin: auto;\">\n";
    HTML +="<head>\n";
    HTML +="<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    HTML +="<title>G.U.I.D.O Configuración</title>\n";
    HTML +="</head>\n";
    HTML +="<body style=\"margin: auto; max-width: 1920px; height: 100%; display: table-cell; vertical-align: middle;\">\n";
    HTML +="<h1 style=\"color: rgb(230, 230, 230); margin-top: 0px; margin-left: 30px; margin-right: 30px;\">Bienvenido a la Configuración de G.U.I.D.O!</h1>\n";
    HTML +="<h3 style=\"color: rgb(230, 230, 230); margin-left: 30px; margin-right: 30px;\">Por favor ingrese el nombre y la contraseña de su red WiFi para que G.U.I.D.O pueda conectarse, además de su ChatID de Telegram para poder enviarle las alertas relacionadas a los sensores.</h3>\n";
    HTML +="<br>\n";
    HTML +="<br>\n";
    HTML +="<div style= \"display:block; text-align: center; max-width:1920px;\">\n";
    HTML +="<form action=\"/login\" method=\"POST\">\n";
    HTML +="<h4 style=\"color: rgb(230, 230, 230); margin-bottom: 5px;\">Nombre de la Red WiFi</h4>\n";
    HTML +="<input style=\"font-size: 16pt; background-color: rgb(230, 230, 230); border: none;\" type=\"text\" name=\"ssid\">\n";
    HTML +="<br>\n";
    HTML +="<h4 style=\"color: rgb(230, 230, 230); margin-bottom: 5px;\">Contraseña</h4>\n";
    HTML +="<input style=\"font-size: 16pt; background-color: rgb(230, 230, 230); border: none;\" type=\"password\" name=\"password\">\n";
    HTML +="<br>\n";
    HTML +="<h4 style=\"color: rgb(230, 230, 230); margin-bottom: 5px;\">ChatID de Telegram</h4>\n";
    HTML +="<input style=\"font-size: 16pt; background-color: rgb(230, 230, 230); border: none;\"type=\"text\" name=\"chatid\">\n";
    HTML +="<br>\n";
    HTML +="<input Style=\"font-size: 14pt; margin-top: 10px; background-color: rgb(72, 99, 156); border: none; color: white; padding: 7px 15px; text-decoration: none; border-radius: 5px;\" type=\"submit\" value=\"Ingresar\">\n";
    HTML +="</form>\n";
    HTML +="</div>\n";
    HTML +="</body>\n";
    HTML +="</html>";

    return HTML;
}

// Página a mostrar si se ingresa un SSID y Contraseña válidos
String paginaHTML_Success(){
  String HTML = "<!DOCTYPE html>\n";
    HTML +="<html lang=\"es\" style=\"height: 100%; font-family: Courier; background-color: rgb(30, 30, 30); display: table; margin: auto;\">\n";
    HTML +="<head>\n";
    HTML +="<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    HTML +="<title>G.U.I.D.O Configuración</title>\n";
    HTML +="</head>\n";
    HTML +="<body style=\"margin: auto; max-width: 1920px; height: 100%; display: table-cell; vertical-align: middle;\">\n";
    HTML +="<h1 style=\"color: rgb(230, 230, 230); margin-top: 0px; margin-left: 30px; margin-right: 30px;\">Datos Configurados Correctamente!</h1>\n";
    HTML +="<h3 style=\"color: rgb(230, 230, 230); margin-left: 30px; margin-right: 30px;\">G.U.I.D.O se iniciara con estos datos de ahora en adelante.</h3>\n";
    HTML +="</body>\n";
    HTML +="</html>";

    return HTML;
}

// Página de Error
String paginaHTML_Error(){
  String HTML = "<!DOCTYPE html>\n";
    HTML +="<html lang=\"es\" style=\"height: 100%; font-family: Courier; background-color: rgb(30, 30, 30); display: table; margin: auto;\">\n";
    HTML +="<head>\n";
    HTML +="<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    HTML +="<title>G.U.I.D.O Configuración</title>\n";
    HTML +="</head>\n";
    HTML +="<body style=\"margin: auto; max-width: 1920px; height: 100%; display: table-cell; vertical-align: middle;\">\n";
    HTML +="<form action=\"/\" method=\"GET\">\n";
    HTML +="<h1 style=\"color: rgb(230, 230, 230); margin-top: 0px; margin-left: 30px; margin-right: 30px;\">Ups... Algo Salió Mal!</h1>\n";
    HTML +="<h3 style=\"color: rgb(230, 230, 230); margin-left: 30px; margin-right: 30px;\">Asegurate de completar ambos campos antes de presionar el botón.</h3>\n";
    HTML +="<br>\n";
    HTML +="<input Style=\"font-size: 14pt; margin-left: 30px; margin-right: 20px; background-color: rgb(72, 99, 156); border: none; color: white; padding: 7px 15px; text-decoration: none; border-radius: 5px;\" type=\"submit\" value=\"Reintentar\">\n";
    HTML +="</form>\n";
    HTML +="</body>\n";
    HTML +="</html>";

    return HTML;
}

// Página de 404
String paginaHTML_404(){
  String HTML = "<!DOCTYPE html>\n";
    HTML +="<html lang=\"es\" style=\"height: 100%; font-family: Courier; background-color: rgb(30, 30, 30); display: table; margin: auto;\">\n";
    HTML +="<head>\n";
    HTML +="<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    HTML +="<title>G.U.I.D.O Configuración</title>\n";
    HTML +="</head>\n";
    HTML +="<body style=\"margin: auto; max-width: 1920px; height: 100%; display: table-cell; vertical-align: middle;\">\n";
    HTML +="<form action=\"/\" method=\"GET\">\n";
    HTML +="<h1 style=\"color: rgb(230, 230, 230); margin-top: 0px; margin-left: 30px; margin-right: 30px;\">Error 404!</h1>\n";
    HTML +="<h3 style=\"color: rgb(230, 230, 230); margin-left: 30px; margin-right: 30px;\">La página que estas buscando no existe.</h3>\n";
    HTML +="<br>\n";
    HTML +="<input Style=\"font-size: 14pt; margin-left: 30px; margin-right: 20px; background-color: rgb(72, 99, 156); border: none; color: white; padding: 7px 15px; text-decoration: none; border-radius: 5px;\" type=\"submit\" value=\"Volver al Inicio\">\n";
    HTML +="</form>\n";
    HTML +="</body>\n";
    HTML +="</html>";

    return HTML;
}

void handleClient(){
    server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", paginaHTML_Root());
}

void handleSuccess() {
  if( ! server.hasArg("ssid") || ! server.hasArg("password") || server.arg("ssid") == NULL || server.arg("password") == NULL) {
    server.send(200, "text/html", paginaHTML_Error());
    return;
  }else {                                                                             
    server.send(200, "text/html", paginaHTML_Success());
    ssidRecibido = server.arg("ssid");
    passwordRecibido = server.arg("password");
    chatIDRecibido = server.arg("chatid");
    // Delay para que el ESP llegue a enviar la página antes de desconectar el AP
    delay (500);
    ConfigReady = true;
  }
}

void handleNotFound(){
  server.send(404, "text/html", paginaHTML_404());
}

void configWifi(){
  // Funciones que se van a ejecutar dependiendo de en que pagina estemos
  server.on("/", HTTP_GET, handleRoot);
  server.on("/login", HTTP_POST, handleSuccess);
  server.onNotFound(handleNotFound);

  // Iniciamos el server en el ESP
  server.begin();

}

bool configuracionWIFILista(){
  return ConfigReady;
}

String getSSID(){
  return ssidRecibido;
}

String getPassword(){
  return passwordRecibido;
}

String getChatID(){
  return chatIDRecibido;
}
