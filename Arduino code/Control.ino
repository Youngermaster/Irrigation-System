
/******Leer los comandos locales(botones de la bomba de agua (normalmente HIGH) y sensores) ******/
void leerBotones()
{
  boolean digiValue = rebote(BOTON_BOMBA_AGUA); // Detectar rebotes en el botón BOTON_BOMBA_AGUA
  if (!digiValue)                               // si no hubo rebote
  {
    BOMBA_ESTADO = !BOMBA_ESTADO; // como no hubo rebote se realiza el cambio de estado
    aplicarBoton();               // aplicar el comando
  }

  digiValue = rebote(BOTON_LEER_SENSORES); // Detectar rebotes en el botón BOTON_LEER_SENSORES
  if (!digiValue)                          // si no hubo rebote
  {
    VER_DATA = !VER_DATA; // como no hubo rebote se realiza el cambio de estado
    if (!VER_DATA)
    {                  // Si la variable que indica si se debe parar de mostrar los datos está en falso
      getDHT11();      // obtener datos del sensor de temperatura y humedad de aire
      getHUM_SUELO();  // obtener datos del sensor  humedad de suelo
      getTEMP_SUELO(); // obtener datos del sensor temperatura de suelo
      displayData();   // Mostrar los datos en el monitor serial
    }
  }
}

/* Detecta si hubo un rebote en el botón del pin dado en el parámetro, 
retorna true si hubo un rebote , false de lo contrario*/
boolean rebote(int pin)
{
  boolean estado;             // variable local que guarda el estado actual del botón
  boolean estadoPasado;       // variable local que guarda el estado pasado del botón
  const int reboteDelay = 30; // Variable quee guarda el número de veces que se debe ejecutar el manejo de los rebotes

  // Leer el estado del botón y guardarlo en una variabled local
  estadoPasado = digitalRead(pin);
  for (int counter = 0; counter < reboteDelay; counter++) // Realizar el manejo de rebotes el número de veces deterinado por reboteDelay
  {
    delay(1);                   // esperar 1ms
    estado = digitalRead(pin);  // leer el siguiente estado del botón
    if (estado != estadoPasado) // Si el botón cambió, por ruido o por que fue presionado
    {
      counter = 0;           // resetear el contador de manejo de rebotes
      estadoPasado = estado; // asignar el estado actual al estado presente del botón
    }
  }
  return estado; //retornar el estado del botón
}

/* Esperar a que se presione le botón un tiempo determinado de tiempo*/
void esperarInicioBoton(int waitTime)
{

  long startTiming = millis();        // empezar el timer  del programa en ms
  while (rebote(BOTON_LEER_SENSORES)) //Mientras se detecta el presionado del botón y se manejan los rebotes
  {
    if ((millis() - startTiming) > (waitTime * 1000))
      break; // Si el tiempo que ha pasado es mayor al tiempo de espera determinado , salir de la subrutina
  }
}

/*********** aplicar los cambios hechos en los botones a los actuadores*******/
void aplicarBoton()
{
  if (BOMBA_ESTADO == 1) // aplicar el cambio a la bomba de agua si el nuevo estado del botón es HIGH
  {
    digitalWrite(BOMBA_AGUA_PIN, LOW); // Encender el relé de la bomba de agua(lógica invertida)
    if (!VER_DATA)
      displayData(); /* Si la variable que indica si se debe parar de
        mostrar los datos está en falso, actualizar el monitor con los datos de los sensores*/
  }
  else // aplicar el cambio a la bomba de agua si el nuevo estado del botón es LOW
  {
    digitalWrite(BOMBA_AGUA_PIN, HIGH); // Apagar el relé de la bomba de agua (lógica invertida)
    if (!VER_DATA)
      displayData(); /* Si la variable que indica si se debe parar de
        mostrar los datos está en falso, actualizar el monitor con los datos de los sensores*/
  }
}

/******** Encender el relé que controla la bomba de agua por un tiempo determinado**************************/
void regarPlanta()
{
  BOMBA_ESTADO = 1;                     // el estado de la bomba de agua es HIGH o 1
  aplicarBoton();                       //Aplicar el comando( enciende el relé de la bomba de agua)
  delay(TIEMPO_ENCENDIDO_BOMBA * 1000); // Esperar un tiempo determinado por TIEMPO_PRENDIDO_BOMBA
  BOMBA_ESTADO = 0;                     // el estado de la bomba de agua es LOW o 0
  aplicarBoton();                       //Aplicar el comando(apaga el relé de la bomba de agua)
}
