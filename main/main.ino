#define IN1_M1 2
#define IN2_M1 3
#define IN3_M1 4
#define IN4_M1 5

#define IN1_M2 6
#define IN2_M2 7
#define IN3_M2 8
#define IN4_M2 9

#define IN1_M3 10
#define IN2_M3 11
#define IN3_M3 12
#define IN4_M3 13

#define IN1_M4 4
#define IN2_M4 5
#define IN3_M4 6
#define IN4_M4 7

const int steps[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

int currentStep = 0;
int direcao = 0; // 1 = horário, -1 = anti-horário, 0 = parado
unsigned long lastStepTime = 0;
int stepDelay = 5; // ms -> controla a velocidade (quanto menor, mais rápido)
String comando = "";

void energizarBobinas(int a, int b, int c, int d) {
 digitalWrite(IN1_M1, a);
 digitalWrite(IN2_M1, b);
 digitalWrite(IN3_M1, c);
 digitalWrite(IN4_M1, d);
}

void setup() {
 pinMode(IN1_M1, OUTPUT);
 pinMode(IN2_M1, OUTPUT);
 pinMode(IN3_M1, OUTPUT);
 pinMode(IN4_M1, OUTPUT);
 
 pinMode(IN1_M2, OUTPUT);
 pinMode(IN2_M2, OUTPUT);
 pinMode(IN3_M2, OUTPUT);
 pinMode(IN4_M2, OUTPUT);
 
 pinMode(IN1_M3, OUTPUT);
 pinMode(IN2_M3, OUTPUT);
 pinMode(IN3_M3, OUTPUT);
 pinMode(IN4_M3, OUTPUT);
 
 pinMode(IN1_M1, OUTPUT);
 pinMode(IN2_M1, OUTPUT);
 pinMode(IN3_M1, OUTPUT);
 pinMode(IN4_M1, OUTPUT);
 
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