/************************************************************************************************************
 🔹 CONTROL DE LED CON BOTÓN Y ANTIRREBOTE (Bounce2) 🔹
  - Detecta la pulsación de un botón conectado al pin 2 usando la librería Bounce2.
  - El botón se configura con INPUT_PULLUP interno.
  - Intervalo de antirrebote configurado en 25 ms para evitar lecturas erróneas.
  - Al presionar el botón, se alterna el estado de un LED conectado al pin 12.
  - Imprime en el monitor serie "on" o "off" según el estado del LED.
  - Funciona con flancos descendentes (falling edge) detectados por la librería Bounce2.
  K. Michalsky – 11.2025
*************************************************************************************************************/

#include <Bounce2.h>

//  DEFINICION DE PINS
#define BOTON 2
#define LED_PIN 12

int ledState = LOW;

//  INICIAR OBJETO BOUNCE
Bounce debouncer = Bounce();

void setup()
{

  Serial.begin(9600);

  //  CONFIGURACION DEL ANTIREBOTE
  //  Conecta el antirrebote a un pin con modo INPUT_PULLUP
  //  Intervalo de antirebote de 25mm (10-30mm es suficiente)
  debouncer.attach(BOTON, INPUT_PULLUP);
  debouncer.interval(25);

  //  MODO DEL PIN DEL LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop()
{
  //  Actualizar la instancia de Bounce. Debe llamarse solo una vez por bucle ()
  debouncer.update();
  boton();
}

//  FUNCION DE PRESIONADO DEL BOTON
void boton()
{
  // debouncer.fell() detecta flanco descendente de HIGH a LOW mientras que debouncer.rose() detecta flanco ascendente de LOW a HIGH
  if (debouncer.fell())
  {
    // Si el estado del pin no es HIGH (PULLUP interno invierte la logica) Imprime "on" sino "off"
    if (ledState != HIGH)
    {
      Serial.println("on");
    }
    else
      Serial.println("off");
    // Cambia el estado del LED y pone el nuevo estado al Pin correspondiente
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}