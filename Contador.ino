/*
 * Autores: Gervasio Gesse Junior
 *          Iris menezes Barbosa
 * Titulo: Projeto Integrador 10 bimestre Univesp Polo Jandira
 * Data: 08 de Novembro de 2020 
 * Resumo: Contador de passagem para transporte publico.
 */


#include <Arduino.h>
#include <TM1637Display.h>

//Pinos de controle do modulo display
#define CLK 4
#define DIO 5

//Pinos do sensor de obstaculos
#define entrada1 6
#define entrada2 3
#define entrada3 7

//Define o contador
int cont = 0;
bool flipflop1 = false;
bool flipflop2 = false;
bool flipflop3 = false;

//Inicializa o display
TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  pinMode(entrada3, INPUT);
  //Define o brilho do display
  display.setBrightness(0x0f);
}

void loop() {
  // put your main code here, to run repeatedly:

if(digitalRead(entrada1) == LOW && digitalRead(entrada2) == LOW){
  digitalWrite(13, HIGH);
} else {
  digitalWrite(13, LOW);
}
//  if(digitalRead(entrada2)==HIGH) {
//    digitalWrite(13, LOW);
//  } else {
//    digitalWrite(13, HIGH);
//  }
//  if(digitalRead(entrada1)==HIGH) {
//    digitalWrite(13, LOW);
//  } else {
//    digitalWrite(13, HIGH);
//  }
  if(flipflop1 == false && flipflop2 == false){
    if(digitalRead(entrada1) == LOW) flipflop1 = true;
    if(digitalRead(entrada2) == LOW) flipflop2 = true;
  }
  
  if(flipflop1 == true){
    if(digitalRead(entrada2) == LOW) flipflop2 = true;
    if(flipflop2 == true){
      if(digitalRead(entrada1) == HIGH && digitalRead(entrada2) == HIGH){
        cont++;
        flipflop1 = false;
        flipflop2 = false;
      }
    }
  }

  if(flipflop2 == true){
    if(digitalRead(entrada1) == LOW) flipflop1 = true;
    if(flipflop1 == true){
      if(digitalRead(entrada1) == LOW && digitalRead(entrada2) == HIGH){
        if( cont > 0 ){
          cont--;
          digitalWrite(13,HIGH);
        }
        flipflop1 = false;
        flipflop2 = false;
      }
    }
  }

  if(flipflop1 == true && flipflop2 == true && digitalRead(entrada1) == HIGH && digitalRead(entrada2) == HIGH){
    digitalWrite(13,HIGH);
    flipflop1 = false;
    flipflop2 = false;
  }

  if(flipflop3 == false){
    if(digitalRead(entrada3) == LOW) flipflop3 = true;
    digitalWrite(13,HIGH);
  } else {
    if(digitalRead(entrada3) == HIGH){
      flipflop3 = false;
      digitalWrite(13,LOW);
      if(cont > 0) cont--;
    }
  }
  
  //Mostra o valor no display
  display.showNumberDec(cont, false);
       
  delay(100);    

}
