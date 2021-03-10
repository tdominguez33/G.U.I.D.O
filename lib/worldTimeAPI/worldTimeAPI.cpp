#include <Arduino.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <httpGETRequest.h>

String horaIP_JSON;

long horaIP_unixtime;
int horaIP_offsetUTC_int;

String getHoraIP_Init() {
  horaIP_JSON = httpGETRequest ("http://worldtimeapi.org/api/ip");
  return horaIP_JSON;
}

void getHoraIP_Parse (){
    const size_t capacity = JSON_OBJECT_SIZE(15) + 310;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, horaIP_JSON);

    const char* horaIP_offsetUTC = doc["utc_offset"];
    horaIP_offsetUTC_int = atoi (horaIP_offsetUTC);

    horaIP_unixtime = doc["unixtime"];

}

String getMinutosIP (){
    String horaIP_minuto (minute(horaIP_unixtime));
    return horaIP_minuto;
}

String getHoraIP (){
    int hora = hour(horaIP_unixtime) + horaIP_offsetUTC_int;
    if (hora > 24){
        hora = hora - 24;
    }
    else if (hora < 0){
        hora = hora + 24;
    }
    String horaIP_hora (hora);
    return horaIP_hora;
}

String getDiaIP (){
    String horaIP_dia (day(horaIP_unixtime));
    return horaIP_dia;
}

String getMesIP (){
    String horaIP_mes (month(horaIP_unixtime));
    return horaIP_mes;
}

String getYearIP (){
    String horaIP_year (year(horaIP_unixtime));
    return horaIP_year;
}

int getOffsetIP (){
    return horaIP_offsetUTC_int;
}

String getHoraUTC (){
    String horaUTC (hour(horaIP_unixtime));
    return horaUTC;
}

String getHoraEST (){
    int hora = hour(horaIP_unixtime) - 5;
    if (hora > 24){
        hora = hora - 24;
    }
    else if (hora < 0){
        hora = hora + 24;
    }
    String horaEST (hora);
    return horaEST;
}

String getHoraPST (){
    int hora = hour(horaIP_unixtime) - 8;
    if (hora > 24){
        hora = hora - 24;
    }
    else if (hora < 0){
        hora = hora + 24;
    }
    String horaPST (hora);
    return horaPST;
}