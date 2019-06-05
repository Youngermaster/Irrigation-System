
/*****************************************Etiquetado de pines **************************/

#define BOTON_BOMBA_AGUA D4 //El botón que prende el relé de la bomba de agua está conectado al pin digital D4 (GPIO2)
#define DHTPIN D5 // el sensor de temperatura y humedad  está conectado al Pin digital D5 o GPIO14
#define ONE_WIRE_BUS 5 //el sensor de temperatura de suelo está conectado al Pin digital D1 O GPIO5
#define BOMBA_AGUA_PIN D2 //El relé de la boba de agua está conectado al Pin digital D1 O GPIO4
#define HUM_SUELO_PIN A0// el sensor de humedad de suelo está conectado al Pin digital A0
#define HUM_SUELO_PIN_VCC D8/*  el sensor de humedad de suelo se alimenta(suministrar 5v) por medio 
del pin digital D8 porque es un sensor de gran consumo*/
#define BOTON_LEER_SENSORES D6   //El botón que actualiza los valores de los sensores está conectado al pin digital D6 (GPIO2)

/******************************************* Definición de las Variables  ******************************************/

/************************** Variables para la conexión a internet *************************/
#define TOKEN  "BBFF-Ts6ARRUPEL4x6wspLNJk8UerEYcMef"  //TOKEN de ubidots
#define ID_1 "5ce98d391d847243b203c566" // variable ID para la bomba de agua

//contraseñas y Wi-Fi SSID
//#define WIFISSID "ManuelAndroid" // Wi-Fi SSID 1
//#define PASSWORD "manuel123" // Wi-Fi password 1
#define WIFISSID "iPhone de Camila" // Wi-Fi SSID 2
#define PASSWORD "camijeje" // Wi-Fi password 2

//#define WIFISSID "UNE_0595" // Wi-Fi SSID 1
//#define PASSWORD "00002442706007" // Wi-Fi password 2


/*********************************** Variables para el sensor de temperatura y humedad DHT11**********************/
#define DHTTYPE DHT11 // el tipo del sensor de temperatura y humedad  es DHT11
float TEMP_AIRE=0;// Variable que guarda la temperatura del aire en grados centígrados
float HUM_AIRE=0;// Variable que guarda la humedad del aire (porcentaje)

/*********************************** Variables para el sensor de humedad de suelo YL-69 **************************/
int HUM_SUELO = 0;// Variable que guarda la humedad del suelo (porcentaje)

/*********************************** Variables del sensor de temperatura de suelo DS18B20 **************************/
float TEMP_SUELO;// Variable que guarda la temperatura del suelo en grados centígrados

/*********************************** Variables para los relés **************************/
boolean BOMBA_ESTADO = 0;//variable booleana que guarda el estado de la bomba de agua (1 si está prendida , 0 si está apagada)


/************* Parámetros para el control automático de la bomba de agua*******************/
#define SUELO_SECO      66 // por debajo de  este valor se considera que el suelo está seco
#define TIEMPO_ENCENDIDO_BOMBA  5 // tiempo por el cual la bomba de agua estará prendida (en segundos)

/*****************************  Timers para la lectura de sensores, botones y control de  actuadores *******************/
#define TIEMPO_LEER_BOTONES   1L  // tiempo cada cuánto se leen los botones(en segundos)
#define TIEMPO_LEER_TEMP_SUELO 2L  // tiempo cada cuánto se lee el sensor de temperatura de suelo (en segundos)
#define TIEMPO_LEER_HUM_SUELO  10L // tiempo cada cuánto se lee el sensor de humedad de suelo (en segundos)
#define TIEMPO_LEER_TEMPHUM_AIRE  2L  // tiempo cada cuánto se lee el sensor de temperatura del aire (en segundos)
#define TIEMPO_ENVIO_UBIDOTS   10L // tiempo cada cuánto se envían datos a ubidots (en segundos)
#define TIEMPO_CONTROL_AUTOM     20L // tiempo cada cuánto se hace el control automático de la bomba de agua (en segundos)

/***************************** Variables para la muestra de datos *************************/
boolean VER_DATA = 1;// Booleano que determina si se muestran los datos en el serial
#define TIEMPO_VER_DATA   30 // tiempo  de espera para mostrar los datos
