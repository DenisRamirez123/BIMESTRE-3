/* FUNDACION KINAL 
   DENIS ESTUARDO DE JESÚS RAMÍREZ PADILLA 
   TALLER DE ELECTRONICA DIGITAL 
   EB5AM 
   2020288
   ALEJANDRO NAVAS
   PROYECTO FINAL BIM II
*/

//Libreria Neopixel 

#include <Adafruit_NeoPixel.h>

#define trigger 10
#define echo 11
#define Cantidad_Leds 1
#define pin_Led 9

Adafruit_NeoPixel pixels(Cantidad_Leds, pin_Led, NEO_GRB + NEO_KHZ800);

int conteo = 0;
int maximo = 9;

const int segmentos[] = {2, 3, 4, 5, 6, 7, 8};

const int digitos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}  // 9
 
};

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);

   for (int i = 0; i < 7; i++) {
    pinMode(segmentos[i], OUTPUT);
  }
   
   pixels.begin();
   pixels.show();
   displayDigitos(conteo);
  }

void loop()
{
  float Distancia = readDistancia();
  Serial.print("Persona detectada a : ");      //envio el mensaje por el monitor serial
  Serial.print(" cm  ");
  Serial.println(readDistancia());                                 //imprimo la distancia leida por el sensor
  delay(100);
 
if (Distancia >= 6.00 && Distancia <=  10.00) {
    if (conteo < maximo) {
      conteo++;
      displayDigitos(conteo);
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    } else {
      displayLleno();
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    }
    pixels.show();
    delay(1000);
  }
}

float readDistancia(void)
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);      
  digitalWrite(trigger, LOW);
 
  long echo_Sensor = pulseIn(echo, HIGH);  
  long distancia = echo_Sensor/59;              
 
  return distancia;                              
}

void displayDigitos(int digito) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], digitos[digito][i]);
  }
}

void displayLleno() {
  for (int i = 0; i < 7; i++) {
    if (i == 6) {
      digitalWrite(segmentos[i], HIGH);
    } else {
      digitalWrite(segmentos[i], LOW);
    }
  }
}
