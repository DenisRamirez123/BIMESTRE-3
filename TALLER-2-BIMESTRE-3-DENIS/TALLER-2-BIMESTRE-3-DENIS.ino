/* CENTRO EDUCATIVO TECNICO LABORAL KINAL
  Denis Estuardo de Jesús Ramírez Padilla
  Taller de Electronica en dispositivos digitales
  Tercer Bimestre
  Practica 2
  2020288

*/

//Librerias usadas para el proyecto 
#include <Wire.h>
#include <SparkFun_ADXL345.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

ADXL345 acelerometro_ADXL345; // Objeto para el acelerómetro ADXL345

const int numLeds = 10; // Número total de LEDs
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Pines de los LEDs
const int mercalli[] = {30, 47, 50, 55, 65, 70, 85, 90, 95, 100};  // Valores de magnitud para usar la escala Mercalli

// Configuración para el DFMiniplayer
SoftwareSerial mySoftwareSerial(13, 12); // RX, TX para el DFMiniplayer
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600); 
  Serial.println("Uso del acelerometro ADXL345");

  acelerometro_ADXL345.powerOn(); // Enciende el acelerómetro
  acelerometro_ADXL345.setRangeSetting(16); // Configura el rango de ±16g

  // Inicializa los pines de los LEDs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Apaga todos los LEDs al inicio
  }

  // Inicialización del DFMiniplayer
  mySoftwareSerial.begin(9600);
  if (!player.begin(mySoftwareSerial)) {
    Serial.println("Error al iniciar el DFMiniplayer");
  } else {
    Serial.println("DFMiniplayer iniciado correctamente");
  }
}

void loop() {
  // Lee las aceleraciones en los ejes X, Y, Z
  int x, y, z;
  acelerometro_ADXL345.readAccel(&x, &y, &z);

  // Formula para calcular la magnitud de la aceleración
  float magnitud = sqrt(x * x + y * y + z * z);

  // Determina la intensidad Mercalli basada en la magnitud
  int intensidad = 0;
  for (int i = 0; i < numLeds; i++) {
    if (magnitud < mercalli[i]) {
      intensidad = i;
      break;
    }
  }

  // Muestra la magnitud por el puerto serial para pruebas 
  Serial.print("Magnitud de aceleracion: ");
  Serial.println(magnitud);

  // Enciende los LEDs correspondientes hasta la intensidad detectada
  for (int i = 0; i <= intensidad; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  // Apaga los LEDs restantes
  for (int i = intensidad + 1; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // magnitud correspondiente al inicio del dfMini Player 
  if (magnitud >= 65) {
    Serial.println("Reproduciendo pista MP3...");
    player.volume(20);
    player.playMp3Folder(2); // Reproduce la pista MP3 con el número de índice 2 
    delay(1000); // Espera un segundo para evitar múltiples reproducciones instantáneas
  }

  delay(500); // Espera medio segundo antes de la próxima lectura
}

