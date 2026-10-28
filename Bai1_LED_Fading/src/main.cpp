
#include <Arduino.h>
#include <esp_arduino_version.h>

#define BUTTON_PIN 4
#define LED_PIN 2

#define PWM_CHANNEL 0
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8

void setBrightness(int brightness) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWrite(LED_PIN, brightness);
#else
    ledcWrite(PWM_CHANNEL, brightness);
#endif
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
#else
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(LED_PIN, PWM_CHANNEL);
#endif
}

void loop() {
    // LED sáng dần
    for (int b = 0; b <= 255; b++) {
        setBrightness(b);

        if (digitalRead(BUTTON_PIN) == LOW) {
            Serial.println("button pressed");
        }

        delay(10);
    }

    // LED tối dần
    for (int b = 255; b >= 0; b--) {
        setBrightness(b);

        if (digitalRead(BUTTON_PIN) == LOW) {
            Serial.println("button pressed");
        }

        delay(10);
    }
}
