//Librerias
#include <SPI.h>
#include <WiFi101.h>
#include <UbidotsArduino.h>

//Etiquetado de pines I/O
#define RIGHT_LED 6
#define LEFT_LED 7

//Constantes
////Ubidots
#define RIGHT_LED_ID "5ce6d3ad1d84723f2f0ce380" // Put here your Ubidots variable ID
#define LEFT_LED_ID "5ce6c5961d8472223e17b0f8"
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
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(LEFT_LED, OUTPUT);

  //Limpieza de salidas
  digitalWrite(RIGHT_LED, LOW);
  digitalWrite(LEFT_LED, LOW);

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
  float *responseArrayRight;
  float valueRight;
  responseArrayRight = client.getValue(RIGHT_LED_ID);

  float *responseArrayLeft;
  float valueLeft;
  responseArrayLeft = client.getValue(LEFT_LED_ID);

  if (responseArrayRight[0] == 1)
  {
    valueRight = responseArrayRight[1];
  }
  if (responseArrayLeft[0] == 1)
  {
    valueLeft = responseArrayLeft[1];
  }
  if (valueRight == 1)
  {
    digitalWrite(RIGHT_LED, HIGH);
  }
  else
  {
    digitalWrite(RIGHT_LED, LOW);
  }
  if (valueLeft == 1)
  {
    digitalWrite(LEFT_LED, HIGH);
  }
  else
  {
    digitalWrite(LEFT_LED, LOW);
  }

  delay(1000);
}
