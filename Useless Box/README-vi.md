# 📦 The Emotional Useless Box
Một chiếc hộp vô dụng (Useless Box) nhưng có "tính cách" đa dạng, được điều khiển bằng mảng con trỏ hàm.

##  Giới thiệu
Dự án DIY Useless Box được thiết kế với cơ cấu thanh truyền (Push-Pull Linkage) cho phép nắp hộp đóng sập chủ động, kết hợp với các kịch bản phản hồi Ngaa để tạo ra nhiều trạng thái cảm xúc khác nhau.

##  Tính năng (Features)
- Cơ chế nắp chủ động bằng Servo độc lập.
- Led RGB hiển thị trạng thái cảm xúc
- Hệ thống trạng thái cảm xúc ngẫu nhiên (Bình thường, Tức giận, Rụt rè,...).

##  Linh kiện Phần cứng (Hardware Requirements)
- 1x Vi điều khiển (Arduino NANO).
- 2x Micro Servo SG90.
- 1x Công tắc gạt MTS 2 chế độ.
- 1x Pin 18650 + Mạch sạc TP4056.
- 1x Mạch tăng áp mini (cho Arduino).
- Vật liệu vỏ: Formex 3mm.

##  Bản vẽ Thiết kế Cơ khí
![Case Blueprint](Formex_layout.png)

##  Hướng dẫn Cài đặt (Installation)
1. Clone repository này về máy.
2. Mở file `.ino` bằng Arduino IDE.
3. Đảm bảo đã cài đặt thư viện `Servo.h` (có sẵn trong IDE).
4. Nạp code vào mạch.

##  Lộ trình (TODO)
- [x] Thiết kế kích thước vỏ hộp Formex.
- [x] Đo và cắt Formex, tạo vỏ hôp.
- [x] Xử lý phần cứng: hàn và nối linh kiện.
- [x] Đưa linh kiện vào vỏ hộp và test các chức năng cơ bản.
- [ ] Viết Sourcode cơ bản và test.
- [ ] Hoàn thiện mảng các hàm (Function Pointers) cho kịch bản.

##  Hardware Setup & Troubleshooting

Trong quá trình thi công thực tế (cắt Formex, hàn mạch, đi dây), dự án đã gặp một số vấn đề vật lý và được xử lý bằng các kỹ thuật "hotfix" sau:

### 1. Vật liệu và thẩm mỹ: Độ bền vật liệu không đảm bảo
* **Vấn đề:** Khi cắt các miếng Formex theo bản thiết kế bản đầu, với miếng Formex 3mm thì phần đế 120x100mm trở nên quá mỏng manh, yếu ớt. Điều này cũng tương tự khi quan sát phần nắp gắn công tắc và 2 mặt bên trước-sau, nơi sẽ được lắp đặt các linh kiện.
* **Giải pháp:** Dán đè thêm 1 tấm Formex lên các vị trí yếu, nâng độ dày thành 6mm. Đồng thời thay đổi thiết kế hộp rộng hơn, cho các mặt bên phủ che đi vết cắt phần đế để tăng tính thẩm mỹ.

### 2. Cơ khí: Chống xoay công tắc MTS trên nền Formex
* **Vấn đề:** Bề mặt Formex xốp mềm, nếu chỉ vặn đai ốc, lực gạt công tắc liên tục sẽ làm củ công tắc bị xoay tròn. 
* **Giải pháp:** Áp dụng thứ tự lắp ráp ngược: `Vòng đệm răng cưa`  -> `Vòng đệm có ngàm phẳng` (mấu nhọn chĩa lên trên). Khi siết đai ốc, ngàm nhọn đâm và lún sâu vào Formex, tạo thành ngàm chống xoay hoàn hảo.

### 3 Cứu hộ Phần cứng (Hardware Bypass): Hỏng pad mạch sạc TP4056
* **Vấn đề:** Do thao tác hàn còn sơ sài, pad đồng `OUT -` trên mạch TP4056 bị tróc hoàn toàn.
* **Giải pháp:** Quan sát phần đường mạch đồng nối với `OUT -`, rồi dùng vật sắc nhọn cạo nhẹ phần sơn phủ màu xanh ở vị trí bất kỳ trên đường mạch đó, lộ ra phần đồng sáng bóng, phần đó sẽ thay thế `OUT -` -> Hàn dây vào vị trí vừa cạo. Sau đó sử dụng keo UHU đổ phủ kín mối hàn (kỹ thuật Strain Relief) để khóa chặt dây vào bo mạch, tránh lực kéo vật lý làm rụng chân IC.

### 4. Nạp code: Lỗi `not in sync: resp=0x00`
* **Vấn đề:** Arduino IDE không thể giao tiếp với chip khi upload.
* **Giải pháp:** Mạch Nano sử dụng bootloader phiên bản cũ. Khắc phục bằng cách chọn `Tools > Processor > ATmega328P (Old Bootloader)`.

### 5. Phần mềm gánh Phần cứng: Hàn nhầm chân Switch
* **Vấn đề:** Hàn nhầm dây vào chân phía trên thay vì chân dưới của công tắc gạt, dẫn đến logic vật lý bị ngược (gạt LÊN thì mạch hở, gạt XUỐNG thì mạch kín).
* **Giải pháp:** Sử dụng điện trở nội kéo lên `INPUT_PULLUP` và đảo ngược logic trong code. Mạch hở = `HIGH` (Bật hộp), Mạch kín = `LOW` (Tắt hộp). Tránh việc phải rã hàn vật lý.
---

## [Hardware Test Code](Hardware_Test/Hardware_Test.ino)

