/*** Realiza el control automático de la planta****/
void ctrolAutom(void)
{
  if (HUM_SUELO < SUELO_SECO) // si el suelo está más seco que el parámetro determinado
  {
    regarPlanta(); // encender el relé que controla la bomba de agua
  }
}

/* Iniciar los relojes para cada tarea del programa*/
void relojes(void)
{
  timer.setInterval(TIEMPO_LEER_BOTONES * 1000, leerBotones); /*Leer botones cada cierto tiempo 
  determinado por la variable TIEMPO_LEER_BOTONES (en segundos)*/

  timer.setInterval(TIEMPO_LEER_TEMP_SUELO * 1000, getTEMP_SUELO); /* Leer temperatura de suelo cada cierto tiempo 
  determinado por la variable TIEMPO_LEER_TEMP_SUELO (en segundos) */

  timer.setInterval(TIEMPO_LEER_TEMPHUM_AIRE * 1000, getDHT11); /*Leer temperatura de aire cada cierto tiempo 
  determinado por la variable TIEMPO_LEER_TEMPHUM_AIRE (en segundos)*/

  timer.setInterval(TIEMPO_LEER_HUM_SUELO * 1000, getHUM_SUELO); /* Leer humedad de suelo cada cierto tiempo
  determinado por la variable TIEMPO_LEER_HUM_SUELO (en segundos)*/

  timer.setInterval(TIEMPO_ENVIO_UBIDOTS * 1000, EnviarUbidots); /* Enviar datos a ubidots cada cierto tiempo 
  determinado por la variable TIEMPO_ENVIO_UBIDOTS (en segundos)*/

  timer.setInterval(TIEMPO_CONTROL_AUTOM * 1000, ctrolAutom); /* Realizar el control automático de la bomba de agua cada cierto tiempo 
  determinado por la variable TIEMPO_CONTROL_AUTOM (en segundos)*/

  //timer.setInterval(DISPLAY_DATA_TM*1000, displayData);
  /* Enviar datos al monitor cada cierto tiempo determinado por la variable TIEMPO_ENVIO_UBIDOTS (en segundos)*/
}
