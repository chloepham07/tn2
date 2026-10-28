# Thực hành ESP32

Các bài thực hành ESP32 viết bằng PlatformIO (board esp32dev, framework Arduino).

## Bài 1 - Ví dụ 1: LED Fading (`Bai1_LED_Fading`)

LED ở GPIO 2 sáng dần rồi tối dần bằng PWM. Nút nhấn ở GPIO 4 được kiểm tra trong vòng lặp nên khi nhấn sẽ bị trễ.

## Bài 1 - Ví dụ 2: LED Fading có ngắt (`Bai1_VD2_LED_Interrupt`)

Giống ví dụ 1 nhưng nút nhấn dùng ngắt ngoài. Khi nhấn nút LED chớp một cái và Serial in ra "Ngat! Nut duoc nhan.".

## Bài 1 - Ví dụ 3: Fading + ngắt đảo LED (`Bai1_VD3_LED_Fading_Interrupt`)

LED ở GPIO 4 sáng tắt dần liên tục. Nhấn nút ở GPIO 18 thì LED ở GPIO 2 đổi trạng thái (bật/tắt) qua ngắt.

## Bài 2: Chống dội phím (`Bai2_Debounce`)

Nút ở GPIO 4 dùng ngắt, chống dội bằng `millis()` với thời gian 50 ms. Mỗi lần nhấn hợp lệ thì LED GPIO 2 đổi trạng thái. Serial in số lần nhấn hợp lệ, số sườn thô và số lần bị lọc.

## Bài 3: Đọc biến trở, lọc và điều khiển LED (`Bai3_ADC_Loc_LEDC`)

Đọc biến trở ở GPIO 34, lọc trung bình 8 mẫu rồi dùng giá trị đó chỉnh độ sáng LED ở GPIO 18. Serial in giá trị thô và giá trị đã lọc để vẽ đồ thị.

