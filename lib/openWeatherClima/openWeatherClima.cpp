#include <Arduino.h>
#include <httpGETRequest.h>
#include <ArduinoJson.h>

// API key de OpenWeather para obtener el clima
#define  OPENWEATHER_APIKEY "[Insertar OpenWeather API Key]"

// String donde se guarda el JSON en bruto
String openWeatherJSON;

// Variables en las que se guardan los datos de OpenWeather
double temperatura = 0;
double temperatura_st = 0;
double viento = 0;
double nubes = 0;
int humedad = 0;
const char* ciudad;
const char* pais;

void openWeather_JSON (String openWeather_ciudadUsuario){
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + openWeather_ciudadUsuario + "&units=metric&lang=es&APPID=" + OPENWEATHER_APIKEY;
    openWeatherJSON = httpGETRequest(serverPath.c_str());

    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 280;
    DynamicJsonDocument JSON_Clima(capacity);

    deserializeJson(JSON_Clima, openWeatherJSON);

    temperatura     =  JSON_Clima["main"]["temp"];
    temperatura_st  =  JSON_Clima["main"]["feels_like"];
    viento          =  JSON_Clima["wind"]["speed"];
    nubes           =  JSON_Clima["clouds"]["all"];
    humedad         =  JSON_Clima["main"]["humidity"];
    ciudad          =  JSON_Clima["name"];
    pais            =  JSON_Clima["sys"]["country"];

}

double openWeather_getTemperatura (){
    return temperatura;
}

double openWeather_getTemperaturaST (){
    return temperatura_st;
}

double openWeather_getViento (){
    return viento;
}

double openWeather_getNubes (){
    return nubes;
}

double openWeather_getHumedad (){
    return humedad;
}

String openWeather_getCiudad (){
    return ciudad;
}

String openWeather_getPais (){
    return pais;
}
