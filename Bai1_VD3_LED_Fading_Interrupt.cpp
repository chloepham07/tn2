#include <Arduino.h>

const int LED1 = 4;
const int LED2 = 2;
const int BTN = 18;

void IRAM_ATTR onNut() {
    digitalWrite(LED2, !digitalRead(LED2));
}

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(BTN, INPUT_PULLUP);

    ledcAttach(LED1, 5000, 8);

    attachInterrupt(digitalPinToInterrupt(BTN), onNut, FALLING);
}

void loop() {
    for (int d = 0; d < 256; d++) {
        ledcWrite(LED1, d);
        delay(4);
    }

    for (int d = 255; d >= 0; d--) {
        ledcWrite(LED1, d);
        delay(4);
    }
}
