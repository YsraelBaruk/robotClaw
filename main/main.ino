#include <Arduino.h>

// Pinos ligados ao driver ULN2003
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Sequência de passo completo (duas bobinas ligadas)
int steps[4][4] = {
 {1, 1, 0, 0},  // A + B
 {0, 1, 1, 0},  // B + C
 {0, 0, 1, 1},  // C + D
 {1, 0, 0, 1}   // D + A
};

int currentStep = 0;
int direcao = 0; // 1 = horário, -1 = anti-horário, 0 = parado
unsigned long lastStepTime = 0;
int stepDelay = 5; // ms -> controla a velocidade (quanto menor, mais rápido)

String comando = "";



// Função para ativar bobinas
void energizarBobinas(int a, int b, int c, int d) {
 digitalWrite(IN1, a);
 digitalWrite(IN2, b);
 digitalWrite(IN3, c);
 digitalWrite(IN4, d);
}



void setup() {
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);

 Serial.begin(9600);
 Serial.println("Digite os comandos:");
 Serial.println("H - Girar horario");
 Serial.println("A - Girar anti-horario");
 Serial.println("P - Parar");
}


void loop() {
 // Lê comando via Serial
 if (Serial.available()) {
   comando = Serial.readStringUntil('\n');
   comando.trim();

   if (comando.equalsIgnoreCase("H")) {
     direcao = 1;
     Serial.println("Girando sentido horario...");
   }
   else if (comando.equalsIgnoreCase("A")) {
     direcao = -1;
     Serial.println("Girando sentido anti-horario...");
   }
   else if (comando.equalsIgnoreCase("P")) {
     direcao = 0;
     energizarBobinas(0,0,0,0); // desligar tudo
     Serial.println("Motor parado.");
   }
   else {
     Serial.println("Comando invalido. Use H, A ou P.");
   }
 }

 // Controle do motor
 if (direcao != 0) {
   if (millis() - lastStepTime >= stepDelay) {
     lastStepTime = millis();

     currentStep += direcao;
     if (currentStep > 3) currentStep = 0;
     if (currentStep < 0) currentStep = 3;

     energizarBobinas(
       steps[currentStep][0],
       steps[currentStep][1],
       steps[currentStep][2],
       steps[currentStep][3]
     );
   }
 }
}