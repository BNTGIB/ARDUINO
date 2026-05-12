#include <Servo.h>

#define FINGER 9
#define COVER 10
#define sw_com 2
#define RED 3
#define GREEN 5
#define BLUE 6

Servo finger, cover;

void setRGB(int red, int green, int blue) {  //Funcion for module led RGB
    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
}

void setup() {
    pinMode(sw_com, INPUT_PULLUP);
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);

   
    setRGB(255, 255, 255);      // WHITE color indicates initialization
    
    delay(2000);          //delay 2 second

    finger.attach(FINGER);
    cover.attach(COVER);

    // Return finger and cover to the "Sleeping" state
    finger.write(180);    
    cover.write(10);
}
void coverAngry(){
    cover.write(150);
    delay(200);
    cover.write(10);
    delay(200);
    cover.write(150);
    delay(200);
    cover.write(10);
    delay(200);
    cover.write(150);
    delay(200);
    cover.write(10);
    delay(200);
}
void coverAngry1() {
    // Rung bần bật nắp hộp 5 lần
    for(int i = 0; i < 5; i++) {
        cover.write(40);  // Chỉ hé nhẹ lên 30 độ
        delay(60);        // Đợi một khoảng cực ngắn
        cover.write(10);  // Đập sập xuống
        delay(60); 
    }
    
    // Mở to ra doạ nạt 1 cú chót
    cover.write(150);
    // Không thèm đóng, nhường lại cho hàm loop() xử lý vung tay
}

void coverAngry_Style2() {
    // 1. Hé nắp lên từ từ (Creepy mode)
    for(int pos = 10; pos <= 130; pos += 1) { 
        cover.write(pos);
        delay(15); // Mở chầm chậm
    }
    
    // 2. Dừng lại "nhìn" chằm chằm
    delay(800);
    
    // 3. Lúc này trong loop() tay vung ra gạt chớp nhoáng là đẹp!
}
void loop() {
    int switch_state = digitalRead(sw_com);

    if (switch_state == LOW) {
        setRGB(255, 0, 0);              // RED color
        coverAngry_Style2();                  // HIGH-> ON
        finger.write(180-130);
        delay(250);
        finger.write(180-0);
        delay(200);
        cover.write(10);
        setRGB(0, 255, 0);     // GREEN color
        delay(1000);
        
    } 
    // Mạch kín (LOW) -> Trạng thái NGỦ
    else {                        // LOW-> OFF
        setRGB(0, 255, 0);     // GREEN color
        finger.write(180-0);
        delay(200);
        cover.write(10);
    }
    delay(50);
}