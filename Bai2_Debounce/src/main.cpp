
#include <Arduino.h>

#define BUTTON_PIN   4    // Chan nut nhan (ngat ngoai)
#define LED_PIN      2    // Chan LED bao hieu
#define DEBOUNCE_MS  50   // Cua so chong doi: bo qua suon xuong trong 50ms sau suon dau

volatile uint32_t debouncedCount = 0;        // So lan nhan nut THUC SU (da chong doi)
volatile uint32_t rawEdgeCount = 0;          // So suon xuong THO (de doi chieu, chua chong doi)
volatile unsigned long lastInterruptTime = 0; // Moc thoi gian (ms) cua suon gan nhat (ca len lan xuong)

// ----------------- ISR: CO CHONG DOI BANG millis() -----------------
// Ngat CHANGE: bat ca suon xuong (nhan) lan suon len (nha).
// Chi dem 1 lan nhan khi chan dang LOW va chan da "yen lang" >= 50ms truoc do.
// Nho vay doi phim luc NHA nut (len-xuong-len...) cung bi loc.
void IRAM_ATTR handleInterrupt() {
    unsigned long now = millis();
    bool isLow = digitalRead(BUTTON_PIN) == LOW;

    if (isLow) {
        rawEdgeCount++;   // Ghi nhan moi suon xuong tho, chi de doi chieu/giai thich
    }

    if (isLow && now - lastInterruptTime >= DEBOUNCE_MS) {
        // Chan da on dinh >= 50ms roi moi xuong LOW -> day la lan nhan MOI
        debouncedCount++;
    }
    // Moi suon (ke ca suon bi bo qua) deu dat lai moc -> cua so chong doi keo dai
    // den khi tin hieu het nay
    lastInterruptTime = now;
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("\n=== BAI 2: Demo Debounce bang millis() trong ISR ===");

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, CHANGE);

    Serial.println("San sang. Nhan nut va so sanh so suon tho voi so lan nhan da chong doi.");
}

void loop() {
    static uint32_t lastShown = 0;

    // Chi in khi co lan nhan hop le moi
    uint32_t pressed = debouncedCount;
    if (pressed != lastShown) {
        lastShown = pressed;

        // Moi lan nhan hop le -> dao trang thai LED
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));

        uint32_t raw = rawEdgeCount;
        Serial.printf("Nhan hop le: %lu | Suon tho: %lu | Bi loc (doi phim): %lu\n",
                      (unsigned long)pressed, (unsigned long)raw,
                      (unsigned long)(raw - pressed));
    }

    delay(10);
}
