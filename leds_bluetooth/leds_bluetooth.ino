#include "BluetoothSerial.h"

BluetoothSerial BT;

const int N = 4;
int leds[N] = {19, 18, 5, 17};  // LED1, LED2, LED3, LED4

void todos(bool v) {
  for (int i = 0; i < N; i++) digitalWrite(leds[i], v);
}

// 6 - todos piscam juntos
void piscaTodos(int vezes, int ms) {
  for (int i = 0; i < vezes; i++) {
    todos(HIGH); delay(ms);
    todos(LOW);  delay(ms);
  }
}

// 7 - sequencia ida e volta
void sequencia(int vezes) {
  for (int v = 0; v < vezes; v++) {
    for (int i = 0; i < N; i++) {
      digitalWrite(leds[i], HIGH); delay(150); digitalWrite(leds[i], LOW);
    }
    for (int i = N - 2; i > 0; i--) {
      digitalWrite(leds[i], HIGH); delay(150); digitalWrite(leds[i], LOW);
    }
  }
}

// 8 - alternado (1 e 3 / 2 e 4)
void alternado(int vezes) {
  for (int v = 0; v < vezes * 2; v++) {
    for (int i = 0; i < N; i++) digitalWrite(leds[i], (i % 2) == (v % 2));
    delay(250);
  }
  todos(LOW);
}

// 9 - contador binario de 0 a 15
void contadorBinario() {
  for (int n = 0; n < 16; n++) {
    for (int i = 0; i < N; i++) digitalWrite(leds[i], (n >> i) & 1);
    delay(400);
  }
  todos(LOW);
}

void setup() {
  BT.begin("ESP32_LEDs");
  for (int i = 0; i < N; i++) pinMode(leds[i], OUTPUT);
  piscaTodos(1, 300);  // teste: todos piscam 1 vez ao ligar
}

void loop() {
  if (!BT.available()) return;
  char c = BT.read();

  switch (c) {
    case '1': case '2': case '3': case '4': {
      int p = leds[c - '1'];
      digitalWrite(p, !digitalRead(p));  // liga/desliga o LED escolhido
      break;
    }
    case '5': todos(HIGH); break;        // acende todos
    case '6': piscaTodos(5, 300); break; // pisca todos juntos
    case '7': sequencia(3); break;
    case '8': alternado(5); break;
    case '9': contadorBinario(); break;
    case '0': todos(LOW); break;         // apaga tudo
  }
}
