#include <Arduino.h>
#include <ArduinoJSON.h>
#include <httpGETRequest.h>

// String donde se guarda el JSON en bruto
String bitcoinJSON;

//Precio en diferentes divisas
const char* precioBitcoinUSD;
const char* precioBitcoinEUR;
const char* precioBitcoinGBP;

void getBitcoin_JSON (){
  bitcoinJSON = httpGETRequest("http://api.coindesk.com/v1/bpi/currentprice.json");
  const size_t capacity = 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(5) + 530;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, bitcoinJSON);

  JsonObject bpi   = doc["bpi"];

  precioBitcoinUSD = bpi["USD"]["rate"];
  precioBitcoinEUR = bpi["EUR"]["rate"];
  precioBitcoinGBP = bpi["GBP"]["rate"];
}

const char* getBitcoinUSD (){
    return precioBitcoinUSD;
}

const char* getBitcoinEUR (){
    return precioBitcoinEUR;
}

const char* getBitcoinGBP (){
    return precioBitcoinGBP;
}
