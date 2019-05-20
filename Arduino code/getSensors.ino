void getSoilMoisterData(void)
{
  soilMoister = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;
  int sum =0;
  for(int i = 0; i < N; i++) // read sensor "N" times and get the average
  {
    int s = analogRead(soilMoisterPin);   
    soilMoister = soilMoister +s;
    sum = soilMoister +s;
    delay(150);
  }
  
  digitalWrite (soilMoisterVcc, LOW);
  soilMoister = soilMoister/N; 
  soilMoister = (soilMoister)/1024;
  soilMoister = 100 - (soilMoister*100);
}


void getDhtData(void){
  float tempIni = airTemp;
  float humIni = airHum;
  airTemp = dht.readTemperature();
  airHum = dht.readHumidity();
  if (isnan(airHum) || isnan(airTemp)){
    Serial.println("Failed to read from DHT sensor!");
    airTemp = tempIni;
    airHum = humIni;
    return;
  }
}

/***************************************************
 * Get SoilTemp sensor data
 **************************************************/
void getSoilTempData()
{
  DS18B20.requestTemperatures(); 
  soilTemp = DS18B20.getTempCByIndex(0);

  int newData = ((soilTemp + 0.05) * 10); //fix soilTemp value to 1 decimal place.
  soilTemp = (newData / 10.0);
}
