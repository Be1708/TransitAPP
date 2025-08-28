#include <SoftwareSerial.h>

// Sensores
const int trig1 = 2, echo1 = 3;
const int trig2 = 4, echo2 = 5;
const int trig3 = 6, echo3 = 7;

// Bluetooth
SoftwareSerial BT(0, 1); // RX, TX

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long dur = pulseIn(echoPin, HIGH, 30000); // timeout 30 ms
  if (dur == 0) return -1;
  return dur * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);      // Para monitor serial
  BT.begin(9600);          // Para HC-05

  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT); pinMode(echo3, INPUT);

  Serial.println("Iniciando...");
}

void loop() {
  long d1 = readDistance(trig1, echo1);
  long d2 = readDistance(trig2, echo2);
  long d3 = readDistance(trig3, echo3);
  long nd1 = d1*-1;
  long nd2 = d2*-1;
  long nd3 = d3*-1;

  String linha = String(nd1) + "," + String(nd2) + "," + String(nd3); // Formata a linha

  Serial.println(linha);   // Envia para USB
  BT.println(linha);       // Envia para Bluetooth

  delay(300);              // intervalo de leitura
}

