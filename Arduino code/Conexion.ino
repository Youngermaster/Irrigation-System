/****** Muestra los datos en el monitor serial ******/
void displayData()
{

  // Muestra la temperatura de aire
  Serial.print("Temperatura: "); // Muestra la humedad del suelo
  Serial.print(TEMP_AIRE);       // Muestra la humedad del suelo
  Serial.print("°C");            // Muestra las unidades en centígrados
  Serial.println(" ");           // Imprimir una línea

  // Muestra la humedad del suelo
  Serial.print("Soil moisture: "); // Muestra la humedad del suelo
  Serial.print(HUM_SUELO);         // Muestra la humedad del suelo
  Serial.print("%");               // Muestra %
  Serial.println(" ");             // Imprimir una línea

  // Muestra la Humedad de aire
  Serial.print("Humedad "); // Muestra la Humedad de aire
  Serial.print(HUM_AIRE);   // Muestra la Humedad de aire
  Serial.print("%");        // Muestra %
  Serial.println(" ");      // Imprimir una línea

  // Muestra la temperatura de suelo
  Serial.print("Temperature soil is: "); // Muestra la temperatura de suelo
  Serial.print(TEMP_SUELO);              // Muestra la temperatura de suelo
  Serial.println(" ");
  ; // Imprimir una línea

  // Muestra el estado de la bomba de agua
  String BOMBA_ESTADOStr; //variable local que guarda el estado de la bomba de agua
  if (BOMBA_ESTADO == 1)
    BOMBA_ESTADOStr = "on "; //si el estado de la bomba de agua es 1 está prendida
  if (BOMBA_ESTADO == 0)
    BOMBA_ESTADOStr = "off"; //si el estado de la bomba de agua es 0 está apagada

  Serial.print("PUMP ");           // Muestra el estado de la bomba de agua
  Serial.println(BOMBA_ESTADOStr); // Muestra el estado de la bomba de agua
}

/******** ENVIAR DATOS DE LOS SENSORES A UBIDOTS Y RECIBIR EL CONTROL DE LA BOMBA DE AGUA****/
void EnviarUbidots()
{
  client.add("Outside temperature", TEMP_AIRE); // Añade el dato de TEMP_AIRE a la variable Outside temperature del dispositivo en ubidots
  client.add("Outside humidity", HUM_AIRE);     // Añade el dato de HUM_AIRE a la variable Outside humidity del dispositivo en ubidots
  client.add("Soil humidity", HUM_SUELO);       // Añade el dato de HUM_SUELO a la variable Soil humidity del dispositivo en ubidots
  client.add("Soil temperature", TEMP_SUELO);   // Añade el dato de TEMP_SUELO a la variable Outside temperature del dispositivo en ubidots
  client.sendAll(true);                         // Envia los datos

  if (client.getValue(ID_1) == 1) // Si el control de la bomba de agua (botón en el dashboard de ubidots es 1
  {
    regarPlanta(); // Enciende el relé de la bomba de agua
  }
}
