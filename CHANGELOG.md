
# ChangeLog
Todos los cambios importantes del proyecto van a ser detallados en este archivo.

## [0.9.1] - 06.12.2020

### Cambiado

- Completada la libreria de morseBlinker, ahora soporta todas las letras y números.

## [0.9] - 30.11.2020

### Añadido

- Creada una función que titila "Guido" en código morse cada vez que se inicia el ESP (Why not?)

### Cambiado

- Eliminados comandos para controlar los LED's del ESP.

- Ahora el comando de debug /format chequea que el userID antes de ejecutarse.

### Arreglado

- Ahora el ESP no crashea si no se detecta el sensor BME.

## [0.8.3] - 24.11.2020

### Cambiado

- Ahora el ChatID se define en la configuración inicial.

- Ahora el Bot está abierto a cualquier persona, solamente los comandos de sensores están limitados al ChatID ingresado.

- Optimización en la recepción de mensajes.

## [0.8.2] - 19.11.2020

### Añadido

- Añadida página de 404 al setup WiFi.

## [0.8.1] - 14.11.2020

### Añadido

- Se añadieron las paginas de Root, Error y Success en una carpeta dentro de la libreria wifiConfig para poder previsualizarlas antes de subirlas al ESP.

- Añadidos varios comentarios en el código.

### Cambiado

- Overhaul de la pagina donde se ingresan los datos de la red por primera vez.

- Ahora el ESP crea una red aparte para conectarnos e ingresar los datos de la red.

### Arreglado

- Cambiadas algunas tabulaciones para mejor lectura.


## [0.8] - 14.11.2020

### Añadido

- Cuando el ESP detecta que se inicia por primera vez crea un servidor local en el que se pueden ingresar los datos de la red a conectarse.

### Pendiente

- Mejorar la pagina web donde se ingresan los datos.
- Iniciar el ESP como un punto de acceso y abrir el servidor en ese modo.


## [0.7.1] - 12.11.2020

### Añadido

- Añadido el comando /conversion y su explicación de uso en el menu.

### Cambiado

- Cambios menores al terminal.

## [0.7] - 11.11.2020

### Añadido

- Añadida la capacidad de obtener la fecha y hora desde el internet. No está pensado para ser utilizado como función es la base para habilitar futuras caracteristicas planeadas, por el momento se puede consultar con el comando /hora pero es para cuestiones de demostración y de debug.

- Se incluyó la libreria timelib.h, usada para convertir el tiempo que traemos de internet.

- Añadida la capacidad de hacer conversiones desde determinadas una zonas horarias hasta otras (Útil para los lanzamientos de SpaceX). Se Utiliza con el comando /conversion.

### Arreglado

- Eliminadas algunas librerias no utilizadas en la libreria de getDolar.

### Pendiente

- Añadir el comando /conversion en el menu y especificar como se usa.


## [0.6.6] - 09.11.2020

### Cambiado

- Ahora el SSID y la contraseña del WiFi la primera vez que se inicia el ESP. Estos se almacenan permanentemente en la memoria flash.

### Arreglado

- El terminal serial ahora está mucho más limpio


## [0.6.5] - 09.11.2020

### Cambiado

- Expandida la libreria de httpGETRequest para hacer solicitudes https.

- Ahora solamente se usa la libreria ArduinoJson, se elimino completamente a Arduino_Json.

- El sensor MQ2 ahora avisa de un aumento en el nivel de gas mediante una interrupción en vez de chequear cada 5 minutos el valor analogico.

## [0.6] - 05.11.2020

### Arreglado

Arreglado soporte del precio del dolar.
- Ya se puede solicitar el precio del dolar mediante el comando /dolar.

### Cambiado

- La función del clima y del precio del bitcoin son su propia libreria.

- Añadidas letras en negrita a varios mensajes para mejorar la lectura.

## [0.5.5] - 02.11.2020

### Añadido

Añadido soporte para el sensor PIR
- Se puede activar o desactivar el sensado de movimiento.
- Si se detecta movimiento el asistente te enviara un mensaje.

## [0.4.5] - 01.11.2020
 
### Añadido

Añadido soporte del sensor MQ2
- Se puede solicitar el valor del sensor MQ2.
- Se toman 20 muestras del aire al momento del inicio y con esos valores se define el threshold.
- Al superar el threshold el asistente envia un mensaje.

## [0.3.5] - 30.10.2020
 
### Añadido

Añadido soporte del sensor BMP
- Se pueden solicitar los valores de Temperatura, Presion y Altitud del sensor.
- Si se supera un valor de temperatura preestablecido, el asistente envia un mensaje.


## [0.2.5] - 29.10.2020
 
### Añadido

Añadida solicitud de Bitcoin
- Se puede solicitar el precio del Bitcoin, el asistente lo devuelve en U$D, Euros y Libras.

Añadida base de solicitud de precio de Dolar. [No Funciona]

## [0.1] - 26.10.2020
 
### Añadido

Añadido soporte para el clima
- Se puede solicitar el clima de cualquier ciudad
 