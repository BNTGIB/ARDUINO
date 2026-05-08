# 📦 The Emotional Useless Box
Một chiếc hộp vô dụng (Useless Box) nhưng có "tính cách" đa dạng, được điều khiển bằng mảng con trỏ hàm.

## 💡 Giới thiệu
Dự án DIY Useless Box được thiết kế với cơ cấu thanh truyền (Push-Pull Linkage) cho phép nắp hộp đóng sập chủ động, kết hợp với các kịch bản phản hồi Ngaa để tạo ra nhiều trạng thái cảm xúc khác nhau.

## ✨ Tính năng (Features)
- Cơ chế nắp chủ động bằng Servo độc lập.
- Led RGB hiển thị trạng thái cảm xúc
- Hệ thống trạng thái cảm xúc ngẫu nhiên (Bình thường, Tức giận, Rụt rè,...).

## 🛠️ Linh kiện Phần cứng (Hardware Requirements)
- 1x Vi điều khiển (Arduino NANO).
- 2x Micro Servo SG90.
- 1x Công tắc gạt MTS 2 chế độ.
- 1x Pin 18650 + Mạch sạc TP4056.
- 1x Mạch tăng áp mini (cho Arduino).
- Vật liệu vỏ: Formex 3mm.

## 📐 Bản vẽ Thiết kế Cơ khí
![Case Blueprint](Case_size.png)

## 🚀 Hướng dẫn Cài đặt (Installation)
1. Clone repository này về máy.
2. Mở file `.ino` bằng Arduino IDE.
3. Đảm bảo đã cài đặt thư viện `Servo.h` (có sẵn trong IDE).
4. Nạp code vào mạch.

## 🗺️ Lộ trình (TODO)
- [x] Thiết kế kích thước vỏ hộp Formex (120x90x50mm).
- [ ] Lắp ráp cơ cấu thanh truyền cho nắp.
- [ ] Cài đặt hệ thống LED RGB hiển thị cảm xúc.
- [ ] Hoàn thiện mảng các hàm (Function Pointers) cho kịch bản.