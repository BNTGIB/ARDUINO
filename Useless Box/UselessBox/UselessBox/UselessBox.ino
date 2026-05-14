#include <Servo.h>
#include <Arduino.h>


#define FINGER 9
#define COVER 10
#define sw_COM 2
#define RED 3
#define GREEN 5
#define BLUE 6

#define Touch 130
#define FullOpen 150

Servo Finger, Cover;

typedef void (*ActionFunction)();
ActionFunction action[]={
    Normal0,
    Normal1,
    Normal2,
    Normal3,

    Angry0,
    Angry1,
    Angry2,
    Angry3,

    Shy,
};
const int Total_action = sizeof(action) / sizeof(action[0]);

void setup(){
    pinMode(sw_COM, INPUT_PULLUP);
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);

    setRGB(255, 255, 255);

    delay(1000);

    Finger.attach(FINGER);
    Cover.attach(COVER);

    sleep(); //HardWare.ino
}


void loop() {
    if (digitalRead(sw_COM) == HIGH) {

        int randNumber = random(Total_action); 
        
        action[randNumber]();
        sleep(); 
    }
}