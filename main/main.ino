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

#define IN1_M4 A0
#define IN2_M4 A1
#define IN3_M4 A2
#define IN4_M4 A3

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

void energizarBobinas(int motor, int a, int b, int c, int d) {
  switch (motor) {
    case 1:
      digitalWrite(IN1_M1, a);
      digitalWrite(IN2_M1, b);
      digitalWrite(IN3_M1, c);
      digitalWrite(IN4_M1, d);
      break;

    case 2:
      digitalWrite(IN1_M2, a);
      digitalWrite(IN2_M2, b);
      digitalWrite(IN3_M2, c);
      digitalWrite(IN4_M2, d);
      break;

    case 3:
      digitalWrite(IN1_M3, a);
      digitalWrite(IN2_M3, b);
      digitalWrite(IN3_M3, c);
      digitalWrite(IN4_M3, d);
      break;

    case 4:
      digitalWrite(IN1_M4, a);
      digitalWrite(IN2_M4, b);
      digitalWrite(IN3_M4, c);
      digitalWrite(IN4_M4, d);
      break;

    default:
      // Caso o motor seja inválido
      Serial.println("Motor inválido!");
      break;
  }
}

// Definições dos pinos de cada motor
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

#define IN1_M4 A0
#define IN2_M4 A1
#define IN3_M4 A2
#define IN4_M4 A3

// Matriz de passos (bobinas)
int steps[4][4] = {
  {1, 0, 0, 1},
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0}
};

// Controle
int direcao = 0;
int motorSelecionado = 1;
int currentStep = 0;
unsigned long lastStepTime = 0;
int stepDelay = 5; // ajuste a velocidade do passo (ms)

String comando;

// ---------------------------
// Função para energizar bobinas
// ---------------------------
void energizarBobinas(int motor, int a, int b, int c, int d) {
  switch (motor) {
    case 1:
      digitalWrite(IN1_M1, a); digitalWrite(IN2_M1, b);
      digitalWrite(IN3_M1, c); digitalWrite(IN4_M1, d);
      break;
    case 2:
      digitalWrite(IN1_M2, a); digitalWrite(IN2_M2, b);
      digitalWrite(IN3_M2, c); digitalWrite(IN4_M2, d);
      break;
    case 3:
      digitalWrite(IN1_M3, a); digitalWrite(IN2_M3, b);
      digitalWrite(IN3_M3, c); digitalWrite(IN4_M3, d);
      break;
    case 4:
      digitalWrite(IN1_M4, a); digitalWrite(IN2_M4, b);
      digitalWrite(IN3_M4, c); digitalWrite(IN4_M4, d);
      break;
  }
}

// ---------------------------
// Configuração
// ---------------------------
void setup() {
  pinMode(IN1_M1, OUTPUT); pinMode(IN2_M1, OUTPUT);
  pinMode(IN3_M1, OUTPUT); pinMode(IN4_M1, OUTPUT);

  pinMode(IN1_M2, OUTPUT); pinMode(IN2_M2, OUTPUT);
  pinMode(IN3_M2, OUTPUT); pinMode(IN4_M2, OUTPUT);

  pinMode(IN1_M3, OUTPUT); pinMode(IN2_M3, OUTPUT);
  pinMode(IN3_M3, OUTPUT); pinMode(IN4_M3, OUTPUT);

  pinMode(IN1_M4, OUTPUT); pinMode(IN2_M4, OUTPUT);
  pinMode(IN3_M4, OUTPUT); pinMode(IN4_M4, OUTPUT);

  Serial.begin(9600);

  Serial.println("===== Controle de Motores =====");
  Serial.println("A - Motor 1");
  Serial.println("B - Motor 2");
  Serial.println("C - Motor 3");
  Serial.println("D - Motor 4");
  Serial.println("H - Girar horario");
  Serial.println("N - Girar anti-horario");
  Serial.println("P - Parar motor");
  Serial.println("===============================");
}

// ---------------------------
// Loop principal
// ---------------------------
void loop() {
  if (Serial.available()) {
    comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toUpperCase();

    // Seleção de motor
    if (comando == "A") { motorSelecionado = 1; Serial.println("Motor 1 selecionado."); }
    else if (comando == "B") { motorSelecionado = 2; Serial.println("Motor 2 selecionado."); }
    else if (comando == "C") { motorSelecionado = 3; Serial.println("Motor 3 selecionado."); }
    else if (comando == "D") { motorSelecionado = 4; Serial.println("Motor 4 selecionado."); }

    // Direção do motor selecionado
    else if (comando == "H") { direcao = 1; Serial.println("Girando sentido horario..."); }
    else if (comando == "N") { direcao = -1; Serial.println("Girando sentido anti-horario..."); }
    else if (comando == "P") { 
      direcao = 0; 
      energizarBobinas(motorSelecionado, 0,0,0,0);
      Serial.println("Motor parado."); 
    }
    else {
      Serial.println("Comando invalido. Use A-D para motor, H/N/P para controle.");
    }
  }

  // Movimento do motor selecionado
  if (direcao != 0) {
    if (millis() - lastStepTime >= stepDelay) {
      lastStepTime = millis();
      currentStep += direcao;
      if (currentStep > 3) currentStep = 0;
      if (currentStep < 0) currentStep = 3;

      energizarBobinas(
        motorSelecionado,
        steps[currentStep][0],
        steps[currentStep][1],
        steps[currentStep][2],
        steps[currentStep][3]
      );
    }
  }
}
