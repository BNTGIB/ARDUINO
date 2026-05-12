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

void loop() {
    int switch_state = digitalRead(sw_com);

    if (switch_state == LOW) {
        setRGB(255, 0, 0);              // RED color
        coverAngry();                  // HIGH-> ON
        delay(500);
        cover.write(150);
        delay(200);
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