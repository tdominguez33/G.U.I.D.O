#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include <UniversalTelegramBot.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>


//-------------Bibliotecas Privadas-------------//

#include <getDolar.h>
#include <getBitcoin.h>
#include <httpGETRequest.h>
#include <morseBlinker.h>
#include <openWeatherClima.h>
#include <statusLED.h>
#include <wifiConfig.h>
#include <worldTimeAPI.h>
#include <zonasHorarias.h>



//---------------------WIFI---------------------//

// Datos de la red WiFi
String ssid_recibido;
String password_recibido;

WiFiClientSecure client;

bool modoConfiguracionWiFi = true;


//-------------------TELEGRAM-------------------//

// Token del Bot
#define BOTtoken "[Insertar Token del Bot de Telegram]"

// ID del chat individual
String chatID_Recibido;

//Inicializamos el BOT
UniversalTelegramBot bot(BOTtoken, client);

// Chequeamos por nuevos mensajes cada 1 segundo
int botRequestDelay = 1000;
unsigned long telegramUltimaVez;

bool usuarioNoAutorizado;


//--------------------BME280--------------------//
/*
  Conexiones:
    Vcc -> 3.3V
    GND -> GND
    SDA -> SDA (GPIO4)
    SCL -> SCL (GPIO5)
    CSB -> Desconectado
    SDO -> Desconectado
*/

Adafruit_BME280 bme;

#define PRESIONNIVELMAR_HPA (1013.25)

// Temperatura a la cual el asistente nos avisa
#define THRESHOLD_TEMPERATURA 40.00

// Variables en las que se guardan los datos del bme
double bme_temperatura = 0;
double bme_presion = 0;
double bme_altitud = 0;
double bme_humedad = 0;

// Momento en el que se chequeo por ultima vez la temperatura
unsigned long bme_temperaturaUltimaVez;

// Chequeamos 1 segundo luego de iniciar la primera vez
int bme_temperaturaTiempoChequeo = 1000;


//---------------------MQ2---------------------//
/*
  Conexiones:
    Vcc -> 3.3V
    GND -> GND
    A0  -> A0
    D0  -> SD2 (GPIO9)
*/

// Pin analogico al que conectamos el Sensor
#define MQ2_PIN_A A0

// Pin digital a utilizar para la interrupción
#define MQ2_PIN_D 9

// Variable en la que se guarda el ultimo valor leido
int mq2_valorActual = 0;

// Variable en la que se guarda si se detecta gas
bool mq2_gasDetectado = false;

// Función que se ejecuta si se detecta gas
ICACHE_RAM_ATTR void gasDetectado() {
  Serial.println("GAS DETECTADO!!!");
  mq2_gasDetectado = true;
}


//------------------Sensor PIR------------------//
/*
  Conexiones:
    Referenciar a esta pagina: https://community.wia.io/d/56-how-to-connect-a-pir-sensor-to-an-esp8266
*/

// Pin al que se conecta la salida del sensor (14 = D5)
#define PIR_PIN 14

// Variable que define si el chequeo de movimiento está activado
bool pir_chequeoActivado = false;

//Variable en la que se guarda si se detecta movimiento
bool pir_movimientoDetectado = false;

// Mensaje de alerta a enviar si se detecta movimiento
String pir_movimientoDetectadoMsg = "ALERTA, SE HA DETECTADO MOVIMIENTO";

//Funcion que se ejecuta si se detecta movimiento
ICACHE_RAM_ATTR void movimientoDetectado() {
  if (pir_chequeoActivado == true){
  Serial.println("MOVIMIENTO DETECTADO!!!");
  pir_movimientoDetectado = true;
  }
}


//---------------------DOLAR--------------------//

// Precio de los diferentes dolares (Gracias Alber por todos los dolares diferentes)
String main_precioDolarOficial_Compra;
String main_precioDolarOficial_Venta;
String main_precioDolarBlue_Compra;
String main_precioDolarBlue_Venta;
String main_precioDolarContadoConLiqui_Compra;
String main_precioDolarContadoConLiqui_Venta;
String main_precioDolarBolsa_Compra;
String main_precioDolarBolsa_Venta;


// Momento en el que se chequeo por ultima vez el precio
unsigned long monedasUltimaVez;

// Chequeamos 1 segundo luego de iniciar la primera vez
int monedasTiempoChequeo = 1000;

//-------------------LED ESP-------------------//

#define PINLED 2
bool ledState = HIGH;

#define STATUSLED 12


//------------------MENSAJES------------------//

void handleNewMessages(int numNewMessages) {

  for (int i=0; i<numNewMessages; i++) {
    // Obtenemos Chat ID del remitente
    String chat_id = String(bot.messages[i].chat_id);
    
    // Texto recibido de Telegram
    String text = bot.messages[i].text;
    Serial.println(text);

    // Nombre del usuario que envio el mensaje
    String from_name = bot.messages[i].from_name;

    if (text == "/start" || text == "/menu") {
      String bienvenida = "Bienvenido a G.U.I.D.O " + from_name + ".\n";
      bienvenida += "Para utilizar el asistente, utiliza los siguientes comandos:\n\n";
      bienvenida += "/bitcoin - Obtener el precio del Bitcoin en USD \n";
      bienvenida += "/bme - Obtener valores del sensor BME280 \n";
      bienvenida += "/clima [Ciudad] - Obtener el clima de la ciudad ingresada \n";
      bienvenida += "/conversion [Desde] [A] [Hora] - Convertir desde una zona horaria a otra (Zonas soportadas: UTC/GMT/EST/EDT/PST/ARG)\n";
      bienvenida += "/dolar - Obtener el precio del Dolar en Pesos Argentinos \n";
      bienvenida += "/hora - Obtener la fecha y hora desde el internet \n";
      bienvenida += "/mq2 - Obtener valores del sensor MQ2 \n";
      bienvenida += "/pir [on/off] - Encender o apagar el chequeo de movimiento \n";
      bienvenida += "/menu - Mostrar esta lista de comando de nuevo \n";
      bot.sendMessage(chat_id, bienvenida, "");
    }
    
    if (text.startsWith("/clima")) {
      String ciudad_usuario = text.substring(7);
      openWeather_JSON(ciudad_usuario);
      String clima = "𝗖𝗹𝗶𝗺𝗮 𝗲𝗻 " + openWeather_getCiudad() + ", " + openWeather_getPais() + ".\n\n"
      + "𝗧𝗲𝗺𝗽𝗲𝗿𝗮𝘁𝘂𝗿𝗮: " + openWeather_getTemperatura() + "°C\n"
      + "𝗦𝗲𝗻𝘀𝗮𝗰𝗶𝗼𝗻 𝗧𝗲𝗿𝗺𝗶𝗰𝗮: " + openWeather_getTemperaturaST() + "°C \n"
      + "𝗩𝗶𝗲𝗻𝘁𝗼: " + openWeather_getViento() + "m/s \n" 
      + "𝗖𝗼𝗯𝗲𝗿𝘁𝘂𝗿𝗮 𝗱𝗲 𝗡𝘂𝗯𝗲𝘀: " + openWeather_getNubes() + "% \n" 
      + "𝗛𝘂𝗺𝗲𝗱𝗮𝗱: " + openWeather_getHumedad() + "% \n";
      bot.sendMessage(chat_id, clima, "");
    } 
    
    else if (text == "/bitcoin") {
      getBitcoin_JSON();
      String bitcoin = String ("𝗣𝗿𝗲𝗰𝗶𝗼 𝗱𝗲𝗹 𝗕𝗶𝘁𝗰𝗼𝗶𝗻: \n\n") + "U$D " + getBitcoinUSD() + "\n" + "€ " + getBitcoinEUR() + "\n" + "£ " + getBitcoinGBP();
      bot.sendMessage(chat_id, bitcoin, "");
    }

    else if (text == "/dolar") {
      String dolar = String ("𝗣𝗿𝗲𝗰𝗶𝗼 𝗱𝗲𝗹 𝗗𝗼𝗹𝗮𝗿: \n\n")
      + "𝗗𝗼𝗹𝗮𝗿 𝗢𝗳𝗶𝗰𝗶𝗮𝗹:\n" + "   Compra: $" + main_precioDolarOficial_Compra + "\n" + "   Venta: $" + main_precioDolarOficial_Venta + "\n"
      + "𝗗𝗼𝗹𝗮𝗿 𝗕𝗹𝘂𝗲:\n" + "   Compra: $" + main_precioDolarBlue_Compra + "\n" + "   Venta: $" + main_precioDolarBlue_Venta + "\n"
      + "𝗗𝗼𝗹𝗮𝗿 𝗕𝗼𝗹𝘀𝗮:\n" + "   Compra: $" + main_precioDolarBolsa_Compra + "\n" + "   Venta: $" + main_precioDolarBolsa_Venta + "\n"
      + "𝗗𝗼𝗹𝗮𝗿 𝗖𝗼𝗻𝘁𝗮𝗱𝗼 𝗰𝗼𝗻 𝗟𝗶𝗾𝘂𝗶:\n" + "   Compra: $" + main_precioDolarContadoConLiqui_Compra + "\n" + "   Venta: $" + main_precioDolarContadoConLiqui_Venta;
      bot.sendMessage(chat_id, dolar, "");
    }
    
    else if (text == "/bme") {
      if (chat_id == chatID_Recibido){
        bme_temperatura = bme.readTemperature();
        bme_presion = bme.readPressure() / 100.0F;
        bme_altitud = bme.readAltitude(PRESIONNIVELMAR_HPA);
        bme_humedad = bme.readHumidity();
        String bme = String ("𝗩𝗮𝗹𝗼𝗿𝗲𝘀 𝗱𝗲 𝗹𝗮 𝗰𝗮𝘀𝗮: \n\n") 
        + "𝗧𝗲𝗺𝗽𝗲𝗿𝗮𝘁𝘂𝗿𝗮: " +  bme_temperatura + "°C\n" 
        + "𝗛𝘂𝗺𝗲𝗱𝗮𝗱: " + bme_humedad + " %\n" 
        + "𝗣𝗿𝗲𝘀𝗶𝗼𝗻: " + bme_presion + " hPa\n" 
        + "𝗔𝗹𝘁𝗶𝘁𝘂𝗱: " + bme_altitud + " m";
        bot.sendMessage(chat_id, bme, "");
      }
      else{
        usuarioNoAutorizado = true;
      }
      
    }
    else if (text == "/mq2") {
      if (chat_id == chatID_Recibido){
        mq2_valorActual = analogRead (MQ2_PIN_A);
        String mq2 = String ("Valor en el sensor MQ2: ") + mq2_valorActual + "\n" + "El threshold es de aproximadamente 280" + "\n" + "Recuerde que al superar el threshold el asistente le avisará automaticamente";
        bot.sendMessage(chat_id, mq2, "");
      }else{
        usuarioNoAutorizado = true;
      }
      
    }
    else if (text.startsWith("/pir")) {
      if (chat_id == chatID_Recibido){
        String pir;
        if(text.substring(5) == "on"){
          pir_chequeoActivado = true;
          pir = "Chequeo de Movimiento Activado";
        }
        else if (text.substring(5) == "off"){
          pir_chequeoActivado = false;
          pir = "Chequeo de Movimiento Desactivado";
        }
        else{
          pir = "Por favor ingrese solamente 'on' o 'off'";
        }
        bot.sendMessage(chat_id, pir, "");
      }else{
          usuarioNoAutorizado = true;
        }
    }
    
    else if (text == "/hora") {
      getHoraIP_Init ();
      getHoraIP_Parse ();
      String hora = String ("Hora: ") + getHoraIP() + ":" + getMinutosIP() + "\nDia: " + getDiaIP() + "/" + getMesIP() + "/" + getYearIP() + "\nZonas Horarias:" 
      + "\n   UTC/GMT: "  + getHoraUTC() + ":" + getMinutosIP() 
      + "\n   EST/EDT: "  + getHoraEST() + ":" + getMinutosIP() 
      + "\n   PST: "      + getHoraPST() + ":" + getMinutosIP();
      bot.sendMessage(chat_id, hora, "");
    }
    
    else if (text.startsWith("/conversion")) {
      String conversionDesde  = text.substring(12, 15);
      String conversionA      = text.substring(16, 19);
      String conversionHora   = text.substring(20, 25);
      String conversion = conversionHora + " " + conversionDesde + " Equivale a " + conversionZonaHoraria (conversionDesde, conversionA, conversionHora) + " " + conversionA;
      bot.sendMessage(chat_id, conversion, "");
    }
    // Comando para Debug
    else if (text == "/format") {
      if (chat_id == chatID_Recibido){
        LittleFS.format();
        String format = "Memoria Formateada, reinicie el ESP para ver los cambios";
        bot.sendMessage(chat_id, format, "");
      }else{
        usuarioNoAutorizado = true;
      } 
    }

    if (usuarioNoAutorizado == true){
      bot.sendMessage(chat_id, "Usuario No Autorizado", "");
    }
  }
}


//---------------------SETUP---------------------//

void setup() {
  Serial.begin(115200);
  
  pinMode (STATUSLED, OUTPUT);

  morseBlinker(STATUSLED, "GUIDO");

  #ifdef ESP8266
    client.setInsecure();
  #endif

  // Configuración del Servidor Local
  configWifi();

  // LittleFS
  if (LittleFS.begin()){
    Serial.println(F("LittleFS Inicializado"));
  }else{
    Serial.println(F("Fallo la inicializacion de LittleFS"));
  }

  // Descomentar si se quiere formatear la memoria
  //LittleFS.format();

  if (LittleFS.exists("/ssid.txt") == true){
    modoConfiguracionWiFi = false;
  }else{
    modoConfiguracionWiFi = true;
    Serial.println ("Modo de Configuración WiFi");
  }


  // Modo Configuracion de WiFi
  // Inicializamos un Access Point
  if (modoConfiguracionWiFi == true){
    WiFi.mode(WIFI_AP);
    IPAddress ip(1,2,3,4);
    IPAddress gateway(1,2,3,1);
    IPAddress subnet(255,255,255,0);
    WiFi.softAPConfig(ip, gateway, subnet);
    WiFi.softAP("G.U.I.D.O", "pasantias2020");
    Serial.println ("Access Point G.U.I.D.O Iniciado");
  }

  // Esperamos a tener una respuesta de la página
  while (modoConfiguracionWiFi == true){

    statusLED_Configuracion(STATUSLED);

    handleClient();

    if (configuracionWIFILista() == true){
      
      // Escribimos en los archivos de SSID y Contraseña (w = write)
      File ssid_flash = LittleFS.open(F("/ssid.txt"), "w");

      if (ssid_flash){
        ssid_flash.print(getSSID());
        ssid_flash.close();
      }else{
        ssid_flash.println("Problema al crear archivo!");
      }

      File password_flash = LittleFS.open(F("/password.txt"), "w");

      if (password_flash){
        password_flash.print(getPassword());
        password_flash.close();
      }else{
        password_flash.println("Problema al crear archivo!");
      }

      File chatID_flash = LittleFS.open(F("/chatid.txt"), "w");

      if (chatID_flash){
        chatID_flash.print(getChatID());
        chatID_flash.close();
      }else{
        chatID_flash.println("Problema al crear archivo!");
      }

      // Salimos del modo de Configuración
      modoConfiguracionWiFi = false;
      Serial.println ("Configuración Exitosa");
    }
  }

  // Cambiamos el estado del LED para notificar de que se esta en la configuración
  digitalWrite (STATUSLED, LOW);
  

  // Leemos los archivos de SSID y Contraseña (r = read)
  File ssid_flash = LittleFS.open(F("/ssid.txt"), "r");
  if (ssid_flash){
    ssid_recibido = ssid_flash.readString();
    ssid_flash.close();
  }else{
    Serial.println("Problema al leer archivo!");
  }

  File password_flash = LittleFS.open(F("/password.txt"), "r");
  if (password_flash){
    password_recibido = password_flash.readString();
    password_flash.close();
  }else{
    Serial.println("Problema al leer archivo!");
  }

  File chatID_flash = LittleFS.open(F("/chatid.txt"), "r");
  if (chatID_flash){
    chatID_Recibido = chatID_flash.readString();
    chatID_flash.close();
  }else{
    Serial.println("Problema al leer archivo!");
  }
  


  // Conectamos al WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_recibido, password_recibido);

  Serial.print("Conectando a WiFi: ");
  Serial.print(ssid_recibido);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }



  // Imprimimos la direccion IP del ESP8266
  Serial.println(F("\n\rWiFi Conectado!"));
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Direccion MAC: ");
  Serial.println(WiFi.macAddress() + "\n");



  // Configuración sensor BME
  bool status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("No se pudo encontrar el Sensor BME");
  }



  // Configuración sensor MQ2
  pinMode(MQ2_PIN_A, INPUT);

  Serial.println ("Tomando muestras con el MQ2");
  delay (5000);
  mq2_valorActual = analogRead (MQ2_PIN_A);

  attachInterrupt(digitalPinToInterrupt(MQ2_PIN_D), gasDetectado, RISING);



  // Configuración sensor PIR
  pinMode(PIR_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), movimientoDetectado, RISING);

  // Cambiamos el estado del LED para confimar que la configuración está lista
  digitalWrite (STATUSLED, HIGH);
}


//---------------------LOOP---------------------//

void loop() {

  // Telegram
  if (millis() > telegramUltimaVez + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.print("Nuevo Mensaje: ");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    telegramUltimaVez = millis();
  }
  


  // Dolar
  if (millis() > monedasUltimaVez + monedasTiempoChequeo)  {
    getDolar_JSON();
    getDolar_JSON_Parse();
    main_precioDolarOficial_Compra = getDolarOficial_Compra();
    main_precioDolarOficial_Venta = getDolarOficial_Venta();
    main_precioDolarBlue_Compra = getDolarBlue_Compra();
    main_precioDolarBlue_Venta = getDolarBlue_Venta();
    main_precioDolarContadoConLiqui_Compra = getDolarContadoConLiqui_Compra();
    main_precioDolarContadoConLiqui_Venta = getDolarContadoConLiqui_Venta();
    main_precioDolarBolsa_Compra = getDolarBolsa_Compra();
    main_precioDolarBolsa_Venta = getDolarBolsa_Venta();

    monedasUltimaVez = millis();

    // Cambiamos el tiempo para que chequee cada 1 hora
    monedasTiempoChequeo = 3600000;
  }



  // Sensor BME
  if (millis() > bme_temperaturaUltimaVez + bme_temperaturaTiempoChequeo)  {
    // Obtenemos el valor del sensor
    bme_temperatura = bme.readTemperature();
    
    // Cambiamos la frecuencia de chequeo a una vez cada 5 min
    bme_temperaturaTiempoChequeo = 300000;

    // Si se supera el threshold enviamos un mensaje
    if (bme_temperatura > THRESHOLD_TEMPERATURA){
      String bme_temperatura_peligro = String("ALERTA, SE ALCANZÓ UNA TEMPERATURA DE ") + bme_temperatura + "°C";
      bot.sendMessage(chatID_Recibido, bme_temperatura_peligro, "");
      // Cambiamos la frecuencia de chequeo a una vez cada 30 seg (Sobreescribimos el tiempo de 5 min)
      bme_temperaturaTiempoChequeo = 30000;
    }
    bme_temperaturaUltimaVez = millis();
  }



  // Sensor MQ2
  if (mq2_gasDetectado == true){
    String mq2_gas_peligro = String("ALERTA, SE SUPERO EL THRESHOLD DEL MQ2\nEL VALOR ACTUAL ES DE: ") + mq2_valorActual;
    bot.sendMessage(chatID_Recibido, mq2_gas_peligro, "");
    mq2_gasDetectado = false;
  }



  // Sensor PIR
  if (pir_chequeoActivado == true && pir_movimientoDetectado == true){
    bot.sendMessage(chatID_Recibido, pir_movimientoDetectadoMsg, "");
    pir_movimientoDetectado = false;
  }
}
