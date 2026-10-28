
#include <Arduino.h>
#include <esp_arduino_version.h>

#define BUTTON_PIN   4    // Chân nút nhấn (ngắt ngoài)
#define LED_PIN      2    // Chân LED (điều khiển bằng PWM qua LEDC)
#define LED_CHANNEL  0    // Kênh LEDC (chỉ dùng cho core Arduino-ESP32 v2.x)
#define LED_FREQ     5000
#define LED_RES_BITS 8    // 8-bit -> giá trị PWM 0-255

#define DEBOUNCE_MS  200  // Bỏ qua các lần nhấn cách nhau quá gần (dội phím)

// Cờ báo hiệu đã có sự kiện nhấn nút, dùng chung giữa ISR và loop()
volatile bool buttonPressed = false;

// ----------------- TRÌNH PHỤC VỤ NGẮT (ISR) -----------------
void IRAM_ATTR handleInterrupt() {
    buttonPressed = true;   // ISR ngắn gọn, chỉ đặt cờ
}

void setLED(int brightness) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWrite(LED_PIN, brightness);
#else
    ledcWrite(LED_CHANNEL, brightness);
#endif
}

// Chớp LED một cái để báo đã nhận ngắt
void flashLED() {
    setLED(255);
    delay(100);
    setLED(0);
    delay(100);
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("\n=== BAI 1: Ngat ngoai + PWM LED (ESP32 / PlatformIO) ===");

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Thiết lập PWM (LEDC) cho LED: tần số 5000Hz, độ phân giải 8-bit (0-255)
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcAttach(LED_PIN, LED_FREQ, LED_RES_BITS);
#else
    ledcSetup(LED_CHANNEL, LED_FREQ, LED_RES_BITS);
    ledcAttachPin(LED_PIN, LED_CHANNEL);
#endif

    // Gắn ngắt ngoài: khi tín hiệu tại BUTTON_PIN chuyển từ HIGH -> LOW (FALLING)
    // thì gọi hàm handleInterrupt()
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);

    Serial.println("San sang. Nhan nut de xem LED nhay nhanh bao hieu ngat.");
}

void loop() {
    static int brightness = 0;
    static int step = 1;
    static unsigned long lastPress = 0;

    // Kiểm tra cờ ngắt ở mỗi bước fading -> phản hồi gần như tức thì
    if (buttonPressed) {
        buttonPressed = false;

        if (millis() - lastPress > DEBOUNCE_MS) {
            lastPress = millis();
            Serial.println("Ngat! Nut duoc nhan.");
            flashLED();
        }
    }

    // Fading: tăng/giảm độ sáng từng bước
    brightness += step;
    if (brightness <= 0 || brightness >= 255) {
        step = -step;
    }

    setLED(brightness);
    delay(10);
}
