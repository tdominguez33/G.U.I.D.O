#include <Arduino.h>
#include <ArduinoJson.h>
#include <httpGETRequest.h>

//Precio de los diferentes dolares (Gracias Alber por todos los dolares diferentes)
const char* precioDolarOficial_Compra;
const char* precioDolarOficial_Venta;
const char* precioDolarBlue_Compra;
const char* precioDolarBlue_Venta;
const char* precioDolarContadoConLiqui_Compra;
const char* precioDolarContadoConLiqui_Venta;
const char* precioDolarBolsa_Compra;
const char* precioDolarBolsa_Venta;

String dolarJSON;

String getDolar_JSON() {
  dolarJSON = httpsGETRequest ("https://www.dolarsi.com/api/api.php?type=valoresprincipales");
  return dolarJSON;
}

void getDolar_JSON_Parse (){

  const size_t capacity = JSON_ARRAY_SIZE(9) + 2*JSON_OBJECT_SIZE(0) + 9*JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(5) + 6*JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(10) + 580;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, dolarJSON);

  JsonObject dolarOficial = doc[0]["casa"];
  precioDolarOficial_Compra           = dolarOficial ["compra"];
  precioDolarOficial_Venta            = dolarOficial ["venta"];

  JsonObject dolarBlue = doc[1]["casa"];
  precioDolarBlue_Compra              = dolarBlue ["compra"];
  precioDolarBlue_Venta               = dolarBlue ["venta"];

  JsonObject dolarContadoConLiqui = doc[3]["casa"];
  precioDolarContadoConLiqui_Compra   = dolarContadoConLiqui ["compra"];
  precioDolarContadoConLiqui_Venta    = dolarContadoConLiqui ["venta"];
  
  JsonObject dolarBolsa = doc[4]["casa"];
  precioDolarBolsa_Compra             = dolarBolsa ["compra"];
  precioDolarBolsa_Venta              = dolarBolsa ["venta"];

}

const char* getDolarOficial_Compra (){
  return precioDolarOficial_Compra;
}

const char* getDolarOficial_Venta (){
  return precioDolarOficial_Venta;
}

const char* getDolarBlue_Compra (){
  return precioDolarBlue_Compra;
}

const char* getDolarBlue_Venta (){
  return precioDolarBlue_Venta;
}

const char* getDolarBolsa_Compra (){
  return precioDolarBolsa_Compra;
}

const char* getDolarBolsa_Venta (){
  return precioDolarBolsa_Venta;
}

const char* getDolarContadoConLiqui_Compra (){
  return precioDolarContadoConLiqui_Compra;
}

const char* getDolarContadoConLiqui_Venta (){
  return precioDolarContadoConLiqui_Venta;
}
