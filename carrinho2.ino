#include <HCSR04.h>
#include <SoftwareSerial.h>

SoftwareSerial blue(2, 3);//Portas usadas para a ligação do modulo bluetooth 
//motor A
int out1 = 5;
int out2 = 6;
int vA=9;
//motor B
int out3 = 7;
int out4 = 8;
int vB=10;

//Sensor ultrasonico
int TRIGGER = 11;
int ECHO = 12;

UltraSonicDistanceSensor dS(TRIGGER, ECHO);

char valorEnviado;// variavel que vai recerber o conteudo enviado pelo bluetooth

void setup() {
  Serial.begin(9600);
  blue.begin(9600);

  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);

  pinMode(vA, OUTPUT);
  pinMode(vB, OUTPUT);

  analogWrite(vA, 0);
  analogWrite(vB, 0);

  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
}
void front(int A, int B) { //função ir para frente
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH);

  analogWrite(vA, A);
  analogWrite(vB, B);
}

void back(int A, int B) { //função ir para trás
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);

  analogWrite(vB, A);
  analogWrite(vA, B);
}

void left_front(int A, int B){ // função ir para esquerda para frente
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
  
  analogWrite(vA, A);
  analogWrite(vB, B);
}


void right_front(int A, int B){ // função ir para direita para frente
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);

  analogWrite(vA, A);
  analogWrite(vB, B);
}

void left_back(int A, int B){ // função ir para esquerda para trás
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);

  analogWrite(vA, A);
  analogWrite(vB, B);
}

void right_back(int A, int B){ // função ir para direita para trás
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);

  analogWrite(vA, A);
  analogWrite(vB, B);
}

void stop(int A, int B) { // função de parar
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
  
  analogWrite(vA, A);
  analogWrite(vB, B);
}

int velocidadeA(char vr){
  if(vr == 'f' || vr == 'r' || vr == 'e' || vr == 'a')
    return 250;
  if(vr == 'F' || vr == 'R' || vr == 'E' || vr == 'A')
    return 200;
  if(vr == '1' || vr == '2' || vr == '4' || vr == '5')
    return 150;
  if(vr == 'p' || vr == 'd' || vr == 'D' || vr == '3' || vr == 'b' || vr == 'B' || vr == '6')
    return 0;
}
int velocidadeB(char vr){
  if(vr == 'f' || vr == 'r' || vr == 'd' || vr == 'b')
    return 250;
  if(vr == 'F' || vr == 'R' || vr == 'D' || vr == 'B')
    return 200;
  if(vr == '1' || vr == '2' || vr == '3' || vr == '6')
    return 150;
  if(vr == 'p' || vr == 'e' || vr == 'E' || vr == '4' || vr == 'a' || vr == 'A' || vr == '5')
    return 0;
}

void loop() {
  if (blue.available()) {
    valorEnviado = blue.read();
  }
  
  Serial.println(valorEnviado);

  int distancia = 0;

  distancia = dS.measureDistanceCm();

  if(distancia < 20){
    stop(0, 0);
  }
  
   delay(1000);
   
  if (valorEnviado == 'f' || valorEnviado == 'F' || valorEnviado == '1') {
    front(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }
  
  if (valorEnviado == 'r' || valorEnviado == 'R' || valorEnviado == '2') {
    back(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }
  
  if (valorEnviado == 'd' || valorEnviado == 'D' || valorEnviado == '3') {
    right_front(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }

  if (valorEnviado == 'e' || valorEnviado == 'E' || valorEnviado == '4') {
    left_front(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }

  if (valorEnviado == 'a' || valorEnviado == 'A' || valorEnviado == '5') {
    left_back(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }

  if (valorEnviado == 'b' || valorEnviado == 'B' || valorEnviado == '6') {
    right_back(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }

  if(valorEnviado == 'p'){
    stop(velocidadeA(valorEnviado), velocidadeB(valorEnviado));
  }
}
