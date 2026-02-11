/************************************************************************************************************
 🔹 CONTROL DE LED CON INTERRUPCIÓN Y ANTIRREBOTE (Bounce2) 🔹
  - Detecta cambios de estado de un botón conectado al pin 2 usando interrupciones y la librería Bounce2.
  - El botón se configura con INPUT_PULLUP interno para evitar fluctuaciones de voltaje.
  - Intervalo de antirrebote configurado en 25 ms para lecturas estables.
  - Cuando se presiona el botón:
      • Se alterna el estado de un LED conectado al pin 12.
      • Se imprime "Botón presionado" en el monitor serie.
  - Cuando se suelta el botón:
      • Se imprime "Botón soltado" en el monitor serie.
  - El estado del botón también se mantiene en la variable `estadoBoton`, actualizada dentro de la ISR.
  - Compatible con flancos descendentes (fell) y ascendentes (rose) de Bounce2.
  K. Michalsky – 11.2025
*************************************************************************************************************/

#include <Bounce2.h>

// DEFINICION DE PINS
#define BOTON 2
#define LED_PIN 12

// DEFINICION DE VARIABLES
int ledState = LOW;
volatile bool estadoBoton = LOW;

//  INICIAR OBJETO BOUNCE
Bounce debouncer = Bounce();

void setup()
{
  Serial.begin(9600);
  // DEFINER LED COMO OUTPUT
  pinMode(LED_PIN, OUTPUT);

  // CONFIGURACION DE LA INTERRUPCION
  attachInterrupt(digitalPinToInterrupt(BOTON), cambiarEstadoBoton, CHANGE);

  // CONFIGURACION DEL ANTIREBOTE
  // Conecta el antirrebote a un pin con modo INPUT_PULLUP
  // Intervalo de antirebote de 25mm (10-30mm es suficiente
  // Tamien se puede escribir de la siguiente manera:
  // pinMode(BOTON, INPUT_PULLUP);
  // debouncer.attach(BOTON);
  debouncer.attach(BOTON, INPUT_PULLUP);
  debouncer.interval(25);
}

void loop()
{
  // Actualizar la instancia de Bounce. Debe llamarse solo una vez por bucle()
  debouncer.update();
  LED();
}

// ISR (INTERRUPT SERIAL ROUTINE)
// Esta funcion se llama en la interrupcion
// digitalRead(BOTON) lee el pin y devuelve HIGH o LOW.
// Se compara con LOW usando ==.
// Si el pin está en LOW, la comparación da true (1).
// Si está en HIGH, da false (0).
// Luego el resultado (true o false) se asigna a estadoBoton con =
void cambiarEstadoBoton()
{
  estadoBoton = digitalRead(BOTON) == LOW;
}

// FUNCION PARA IMPRIMIR Y ENCENDER O APAGAR EL LED
void LED()
{
  // COMPROBAR SI EL BOTON HA CAMBIADO DE ESTADO
  if (debouncer.fell())
  {
    // El botón ha sido presionado
    Serial.println("Botón presionado");
    // Cambia el estado del LED y pone el nuevo estado al Pin correspondiente
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  if (debouncer.rose())
  {
    // El botón ha sido soltado
    Serial.println("Botón soltado");
  }
}