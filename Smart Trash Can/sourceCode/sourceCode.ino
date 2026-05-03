#include <Servo.h>

// --- CẤU HÌNH CHÂN ---
#define TRIG 4 
#define ECHO 2  
#define SERVO_PIN 9 
#define PIN_BATTERY A0 
const int RED = 3;
const int GREEN = 6;
const int BLUE = 11;

Servo ser;

// --- BIẾN TOÀN CỤC ---
int timee = 0;
float servoPos = 22;     
float colorPos = 0;    
float r = 0, g = 0, b = 0; 
float he = 0.5;
bool isLowBattery = false;

void setRGB(int red, int green, int blue){
    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
}
void setup() {
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);

    setRGB(255,0,0);
    delay(400);
    setRGB(255,100,0);
    delay(400);
    setRGB(0,255,0);
    delay(400);
    setRGB(0,0,0);
    delay(100);

    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(PIN_BATTERY, INPUT); 

    delay(200);
    ser.attach(SERVO_PIN);
    ser.write(16);
    
}

void calculateRainbow(int pos) {
    if (pos < 85) {
        r = 255 - pos * 3; g = pos * 3; b = 0;
    } else if (pos < 170) {
        pos -= 85; r = 0; g = 255 - pos * 3; b = pos * 3;
    } else {
        pos -= 170; r = pos * 3; g = 0; b = 255 - pos * 3;
    }
}

void checkBattery() {
    // Đọc trung bình 10 lần để tránh giá trị bị nhảy do nhiễu motor
    long sum = 0;
    for(int i=0; i<10; i++) sum += analogRead(PIN_BATTERY);
    float vBat = ( (sum / 10.0) * 5.0 / 1024.0) * 2.0;
    
    // 3.4V là ngưỡng bắt đầu báo đỏ
    isLowBattery = (vBat < 3.4 && vBat > 1.0); 
}

void serr(bool cl){
    if(cl){ 
        if(servoPos < 125){ // Giữ ở mức 100 để an toàn cho pin và dây
            servoPos += 3; 
            ser.write(servoPos);
        }
    }
    else{ 
        if(servoPos > 16){
            servoPos -= 1; 
            ser.write(servoPos);
        }
    }
}

void loop() {
    checkBattery();

    // 1. TÍNH TOÁN MÀU CẦU VỒNG
    colorPos += he;
    if (colorPos > 255) colorPos = 0;
    calculateRainbow((int)colorPos);

    // 2. SIÊU ÂM
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long du = pulseIn(ECHO, HIGH, 25000); 
    int dis = (du == 0) ? 999 : du * 0.034 / 2;

    // 3. LOGIC ĐIỀU KHIỂN
    if (isLowBattery) {
        serr(false);
        // Nháy đỏ mờ mờ để không quá tốn pin
        if (millis() % 1000 < 500) setRGB(100, 0, 0);
        else setRGB(0, 0, 0);
    }
    else if(dis > 0 && dis < 4){ 
        serr(true);
        setRGB(r, g, b); // Sáng 100% khi có người
        timee = 1;
        he = 0.5; 
    }
    else if(timee < 240 && timee > 0){ 
        serr(true);
        setRGB(r, g, b);
        timee += 1;
    }
    else{
        serr(false);
        // TĂNG ĐỘ SÁNG CHỜ LÊN 1/2 để hy vọng rút đủ dòng duy trì mạch sạc
        setRGB(r/4, g/4, b/4); 
        he = 0.1;
        timee = 0;
    }

    delay(5); 
}