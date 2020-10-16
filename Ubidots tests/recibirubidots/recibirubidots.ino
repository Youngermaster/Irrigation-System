//Librerias
#include <SPI.h>
#include <WiFi101.h>
#include <UbidotsArduino.h>

//Etiquetado de pines I/O
#define LED 6

//Constantes
////Ubidots
#define IDLED "5ce6d3ad1d84723f2f0ce380"            // Put here your Ubidots variable ID
#define TOKEN "BBFF-Ts6ARRUPEL4x6wspLNJk8UerEYcMef" // Put here your Ubidots TOKEN

//Variables
char ssid[] = "YOUNG-PC 5564"; //  your network SSIDTEMP (name)
char pass[] = "(V757b97";      // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;              // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
////Ubidots
Ubidots client(TOKEN);

void setup()
{
  //Configuracion de pines I/O
  pinMode(LED, OUTPUT);

  //Limpieza de salidas
  digitalWrite(LED, LOW);

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
  float *responseArray;
  float value;
  responseArray = client.getValue(IDLED);

  Serial.print("---------------> mmm... Loading\n");
  // The library return a verify float in the first position, 0 when
  // it doesn't get the value and 1 when it get the value
  // in the second position is the value
  if (responseArray[0] == 1)
  {
    value = responseArray[1];
  }
  if (value == 1)
  {
    digitalWrite(LED, HIGH);
    Serial.print("----------------------> It works! <----------------------");
  }
  else
  {
    digitalWrite(LED, LOW);
    Serial.print("It works! LOW\t");
  }
  delay(1000);
}
