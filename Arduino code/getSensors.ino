/* Subrutinas para la lectura de los sensores*/


/* Lee el sensor de humedad de suelo (YL-69)y convierte el valor análogo a un porcentaje*/
void getHUM_SUELO  (void )
{
  
  digitalWrite (HUM_SUELO_PIN_VCC, HIGH);//Encender el pin digital que alimenta el sensor
  delay (500);//esperar 500 ms 
  HUM_SUELO = analogRead(HUM_SUELO_PIN); //Leer el sensor de humedad de suelo (análogo)
  
  int OldMax =1024;// el máximo que lee el sensor (suelo muy seco)
  int OldMin =471;// el mpinimo que lee el sensor (suelo muy húmedo) este 
  // mínimo es debido a que el sensor no llega a 0 por que es poco sensible y se corroe fácilmente
  int OldRange = (OldMax - OldMin);// rango en el que el sensor trabaja
  int NewMax = 100;// el máximo que se debe mostrar es 100%
  int NewMin = 0;// el mínimo que se debe mostrar es 0%
  int NewRange = (NewMax - NewMin);// nuevo rango que se debe mostrar
  HUM_SUELO = (((HUM_SUELO - OldMin) * NewRange) / OldRange) + NewMin;//convierte el valor obtenido al nuevo rango (0%-100%)

  if (HUM_SUELO<0)// si la conversión resulta en un valor negativo
  {
      HUM_SUELO =0;// el porcentaje de humedad es 0
  }

  if (HUM_SUELO>100)// si la conversión resulta en un porcentaje mayor a 100%
  {
      HUM_SUELO =100;// elporcentaje de humedad es 100%
  }

 HUM_SUELO = 100- HUM_SUELO ;// cambiar el porcentaje para que se muestre 0% en la mínima humedad y 100% en la máxima

  
  
}

/* Lee el sensor de sensor de temperatura y humedad del aire*/
void getDHT11(void)
{
  float tempAnterior = TEMP_AIRE;// Variable temporal que guarda la temperatura del aire en grados centígrados
  float humAnterior = HUM_AIRE;// Variable temporal que guarda la humedad del aire (porcentaje)
  TEMP_AIRE = dht.readTemperature();//Leer la temperatura del aire del sensor DHT11
  HUM_AIRE = dht.readHumidity();//Leer la humedad del aire del sensor DHT11
  if (isnan(HUM_AIRE) || isnan(TEMP_AIRE))// si el sensor lanza un resultado que no es un número, se ignora
  {
    TEMP_AIRE = tempAnterior;// la temperatura es el último valor válido
    HUM_AIRE = humAnterior;// la humedad es el último valor válido
    return;// fin de la subrutina
  }
}

/* Lee el sensor de sensor de temperatura de suelo*/
void getTEMP_SUELO()
{
  DS18B20.requestTemperatures(); // Hacer el pedido de datos por medio de la libreria del sensor DS18B20
  TEMP_SUELO = DS18B20.getTempCByIndex(0);//Leer la temperatura del suelo del sensor DS18B20
  int newData = ((TEMP_SUELO + 0.05) * 10); //Pasar la temperatura de suelo a un valor con una posición decimal 
  TEMP_SUELO = (newData / 10.0); //Pasar la temperatura de suelo a un valor con una posición decimal 
}
