
#include <Arduino.h>

#define ADC 34    // ADC1_CH6 (input-only) - chan giua cua bien tro
#define LED 18    // LED dieu khien bang LEDC
#define N 8       // So mau cua bo loc trung binh truot

#define USE_FILTER 1  // 1: LED theo gia tri da loc, 0: LED theo gia tri tho (de so sanh)

int buf[N]; int idx = 0;

void setup() {
    Serial.begin(115200);
    ledcAttach(LED, 5000, 8);

    // Nap san bo dem bang gia tri dau tien de khong bi "leo doc" tu 0 luc khoi dong
    int first = analogRead(ADC);
    for (int i = 0; i < N; i++) buf[i] = first;
}

// Loc trung binh truot: giu N mau gan nhat, tra ve trung binh cong
int loc(int m) {
    buf[idx] = m; idx = (idx + 1) % N;
    long t = 0; for (int i = 0; i < N; i++) t += buf[i];
    return t / N;
}

void loop() {
    int tho = analogRead(ADC);
    int l = loc(tho);

#if USE_FILTER
    ledcWrite(LED, map(l, 0, 4095, 0, 255));
#else
    ledcWrite(LED, map(tho, 0, 4095, 0, 255));
#endif

    // Dinh dang ">ten:gia_tri" de ve do thi bang Teleplot / Serial Plotter
    Serial.print(">tho:"); Serial.println(tho);
    Serial.print(">loc:"); Serial.println(l);
    delay(20);
}
