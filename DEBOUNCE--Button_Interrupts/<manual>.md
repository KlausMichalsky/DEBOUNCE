/************************************************************************************************************
 🔹 CONTROL DE LED CON INTERRUPCIÓN Y ANTIRREBOTE (Bounce2) – MINI MANUAL 🔹
 
 Descripción general:
  - Este sketch permite controlar un LED usando un botón con antirrebote y lectura mediante interrupción.
  - Se utiliza la librería Bounce2 para evitar lecturas falsas al presionar o soltar el botón.
  - Además, se implementa una interrupción para actualizar el estado del botón en tiempo real.

-------------------------------------------------------------
1️⃣ DEFINICIÓN DE PINES Y VARIABLES
  - BOTON (pin 2): botón de entrada con pull-up interno.
  - LED_PIN (pin 12): LED que se enciende/apaga según la acción del botón.
  - ledState: variable para almacenar el estado actual del LED (HIGH/LOW).
  - estadoBoton: variable volatile actualizada por la ISR para reflejar el estado real del botón.
  - debouncer: objeto de Bounce2 para manejar antirrebote.

-------------------------------------------------------------
2️⃣ SETUP
  - Inicializa el monitor serie a 9600 baudios.
  - Configura LED_PIN como salida.
  - Configura interrupción en BOTON para detectar cualquier cambio (CHANGE) y ejecutar la ISR `cambiarEstadoBoton`.
  - Configura el objeto Bounce2:
      • Asocia al pin del botón con INPUT_PULLUP.
      • Intervalo de antirrebote de 25 ms.

-------------------------------------------------------------
3️⃣ LOOP
  - Llama a `debouncer.update()` una vez por ciclo para actualizar el estado del botón.
  - Llama a la función `LED()` que maneja el encendido/apagado del LED y envía mensajes al monitor serie.

-------------------------------------------------------------
4️⃣ INTERRUPCIÓN (ISR)
  - Función: `cambiarEstadoBoton()`
  - Ejecutada automáticamente al detectar un cambio en el pin del botón.
  - Lee el pin del botón con `digitalRead(BOTON)` y asigna true/false a `estadoBoton` según si está presionado (LOW) o no (HIGH).
  - Permite conocer el estado real del botón incluso si el loop está ocupado haciendo otra tarea.

-------------------------------------------------------------
5️⃣ FUNCION LED()
  - Detecta flancos descendentes (falling edge) usando `debouncer.fell()`:
      • Imprime "Botón presionado".
      • Cambia el estado de `ledState` y actualiza el LED.
  - Detecta flancos ascendentes (rising edge) usando `debouncer.rose()`:
      • Imprime "Botón soltado".

-------------------------------------------------------------
💡 NOTAS
  - La combinación de interrupción y Bounce2 asegura lectura estable y rápida del botón.
  - El LED responde instantáneamente al presionar, evitando rebotes eléctricos.
  - La variable `estadoBoton` puede usarse para otros controles en paralelo.

 K. Michalsky – 11.2025
*************************************************************************************************************/
