#include <Servo.h>

#define VELOCIDADE_DO_SOM 0.034
#define POS_FECHADO 60
#define POS_ABERTO 180

Servo meuServo;

const int trigPin = 4;
const int echoPin = 5;
bool open = false;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  meuServo.attach(9);
  meuServo.write(POS_FECHADO);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * VELOCIDADE_DO_SOM / 2; // dividido por dois para não contar distância de ida + volta do som

  if (distance > 0 && distance <= 30) {
    if (!open) {
      Serial.println("PLAY_AUDIO");
      delay(600);
    }
    meuServo.write(POS_ABERTO);
    open = true;
    delay(2000);
  } else {
    meuServo.write(POS_FECHADO);
    open = false;
  }
}
