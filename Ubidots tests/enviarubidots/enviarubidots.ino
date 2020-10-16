//Librerias
#include <SPI.h>
#include <WiFi101.h>
#include <UbidotsArduino.h>

//Etiquetado de pines I/O
#define POT1 A0
#define POT2 A1

//Constantes
////Ubidots
#define IDTEMP "5cdaed631d84724f4fc065f8"           // Put here your Ubidots variable ID
#define IDHUM "5cdaed711d84724fa2cc4286"            // Put here your Ubidots variable ID
#define TOKEN "BBFF-Ts6ARRUPEL4x6wspLNJk8UerEYcMef" // Put here your Ubidots TOKEN

//Variables
float t = 0;               //Variable temperatura
float h = 0;               //Variable humedad
char ssid[] = "IoT-B19";   //  your network SSIDTEMP (name)
char pass[] = "meca2017*"; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;          // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
////Ubidots
Ubidots client(TOKEN);

void setup()
{
  //Configuracion de pines I/O

  //Limpieza de salidas

  //Comunicaciones
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv <= "1.1.0")
  {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSIDTEMP: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
}
void loop()
{
  //float value = random(100);
  //float value2 = random(50);
  t = analogRead(POT1) * 100 / 1023.0; //Lectura analoga de la temperatura
  h = analogRead(POT2) * 100 / 1023.0; //Lectura analoga de la humedad
  client.add(IDTEMP, t);
  client.add(IDHUM, h);
  client.sendAll();
  Serial.println("Temperature ->");
  Serial.println(t);
  Serial.println("Hum ->");
  Serial.println(h);
  delay(1000);
}
