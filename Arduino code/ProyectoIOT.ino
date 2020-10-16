
#include "Definiciones.h" // Incluir definición de variables y etiquetado de pines

/************************************************** Librerias ************************************************/

/*****Librerias para la conexión a internet Y ubidots******/
#include <ESP8266WiFi.h>
#include "UbidotsMicroESP8266.h"

#include <SimpleTimer.h> // Libreria para los relojes de las diferentes tareas

/***** Librerias para el sensor de temperatura y humedad DHT11****/
#include <Adafruit_Sensor.h> //Libreria Adafruit_Sensor
#include <DHT.h>             //Libreria DHT
#include <SimpleDHT.h>       //Libreria SimpleDHT

/**** Librerias para el sensor de temperatura DS18B20 *******/
#include <DallasTemperature.h> //Libreria DallasTemperature
#include <OneWire.h>           //Libreria OneWire

/***** Configuración de comunicaciones/librerias ****/
SimpleTimer timer;                   //Configuración de relojes
DHT dht(DHTPIN, DHTTYPE);            //Configuración del sensor DHT11
OneWire oneWire(ONE_WIRE_BUS);       //Configuración de la libreria Onewire para DS18B20
DallasTemperature DS18B20(&oneWire); //Configuración de la libreria DallasTemperature para DS18B20

/**** Inicialización de comunicaciones IOT ****/
Ubidots client(TOKEN);

/********************************************Configuración************************************************/
void setup()
{

  //Comunicaciones
  Serial.begin(115200); //Inicio comunicaciones con el PC por el Serial0 a 115200bauds (debug)

  delay(10);                             //Espero TIEMPO milisecs
  Serial.println("ArduFarmBot 2");       //Mandar al monitor serial el inicio del programa
  Serial.println(".... Starting Setup"); //Mandar al monitor serial el inicio del programa
  Serial.println(" ");                   //Mandar al monitor serial el inicio del programa

  //Configuracion de pines
  pinMode(BOMBA_AGUA_PIN, OUTPUT);            //Pin de la bomba de agua como salida
  pinMode(HUM_SUELO_PIN_VCC, OUTPUT);         //Pin de la alimentación del sensor de humedad de suelo como salida
  pinMode(BOTON_BOMBA_AGUA, INPUT_PULLUP);    //inicializar el pin BOTON_BOMBA_AGUA como entrada con la resistencia pull up activada
  pinMode(BOTON_LEER_SENSORES, INPUT_PULLUP); //inicializar el pin BOTON_LEER_SENSORES como entrada con la resistencia pull up activada

  //Limpieza de salidas fisicas
  digitalWrite(BOMBA_AGUA_PIN, HIGH);   // Apagar el BOMBA_AGUA_PIN (relé de lógica invertida)
  digitalWrite(HUM_SUELO_PIN_VCC, LOW); // Apagar el pin de alimentación del  sensor de humedad de suelo

  //Comunicaciones IOT
  client.wifiConnection(WIFISSID, PASSWORD);      // inicializar conexión WIFI con la WIFISSID y la contraseña guardadas
  client.setDebug(true);                          // Descomentar para debugging
  client.setDataSourceName("Irrigation System");  // Cambiar el nombre del device de ubidots
  client.setDataSourceLabel("irrigation-system"); // Cambiar el label del device de ubidots

  dht.begin();     // inicializar el sensor DHT11
  DS18B20.begin(); // inicializar el sensor DS18B20

  esperarInicioBoton(TIEMPO_VER_DATA); // Esperar un tiempo en ms
  relojes();                           // Inicializar los relojes de las tareas
}

/****************************************Ejecución****************************************************/

void loop()
{
  timer.run(); // iniciar los timers
}
