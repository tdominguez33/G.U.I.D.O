#include <Arduino.h>
#include <worldTimeAPI.h>

String conversionZonaHoraria (String conversionDesde, String conversionA, String conversionHora){
    String Hora = conversionHora.substring(0, 2);
    String Minutos = conversionHora.substring(3, 5);
    if (conversionDesde == "UTC" || conversionDesde == "GMT"){

        if (conversionA == "EST" || conversionA == "EDT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 5;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);

        }else if (conversionA == "PST"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 8;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);

        }else if (conversionA == "ARG"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 3;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
        }

    }else if (conversionDesde == "EST" || conversionDesde == "EDT"){

        if (conversionA == "UTC" || conversionA == "GMT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 5;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
            
        }else if (conversionA == "PST"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 3;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);

        }else if (conversionA == "ARG"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 2;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
        }
        
    }else if (conversionDesde == "PST"){
        
        if (conversionA == "UTC" || conversionA == "GMT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 8;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
            
        }else if (conversionA == "EST" || conversionA == "EDT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 3;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);

        }else if (conversionA == "ARG"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 5;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
        }

    }else if (conversionDesde == "ARG"){

        if (conversionA == "UTC" || conversionA == "GMT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int + 3;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
            
        }else if (conversionA == "EST" || conversionA == "EDT"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 2;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);

        }else if (conversionA == "PST"){
            int Hora_int = Hora.toInt();
            Hora_int = Hora_int - 5;
            if (Hora_int > 24){
                Hora_int = Hora_int - 24;
            }
            else if (Hora_int < 0){
                Hora_int = Hora_int + 24;
            }
            String Hora_Final (Hora_int);
            return String (Hora_Final + ":" + Minutos);
        }
    }
    return String ("Error");
}
