#include <LedControl.h>

#define din_matrix  3    // Din= pin donde entran datos
#define cs_matrix   2     // control del esclavo
#define clk_matrix  4
#define canal0_pot A6 // pine concectado al potencimoetro 

unsigned int valor_adc_pot;
unsigned char velocidad_Pacman ;

// Constructor

LedControl PacmanMatrix =  LedControl(din_matrix,clk_matrix,cs_matrix , 1); // controlador de el pacman matrix un arreglo de una matriz led 

// variables 

byte Pacman_abierto[8]={
  B00111100,
  B01010100,
  B10001000,
  B10010010,
  B10001000,
  B01000100,
  B00111100,
  B00000000
};

byte Pacman_cerrado[8]={
  B00111100,
  B01010010,
  B10000001,
  B10001111,
  B10000001,
  B01000010,
  B00111100,
  B00000000
};

//funciones
void setup() {
  Serial.begin(9600); 
  PacmanMatrix.shutdown(0,false); //Act // encendiendola matriz
  PacmanMatrix.setIntensity (0, 15);  // cnfiguracion del brillo de la matriz de 0-30
 PacmanMatrix.clearDisplay (0);
 Serial.println("Uso de la matriz led");
  pinMode(canal0_pot, INPUT);

}
// ciclo infinito
void loop() 
{
  valor_adc_pot = analogRead(canal0_pot);   //Leo el voltaje en el pin A0 del arduino

  for (int i=0; i<8; i++)
  {
   PacmanMatrix.setRow(0, i, Pacman_abierto[i]);
  }
  delay(valor_adc_pot);

  for (int i=0; i<8; i++)
  {
    PacmanMatrix.setRow(0, i, Pacman_cerrado[i]);
  }
    delay(valor_adc_pot);
}