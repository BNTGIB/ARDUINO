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
    Normal0, // Open -> delay 0.2s -> finger
    Normal1, // Open -> delay 1s -> finger
    Normal2, // Open (speed=2) -> -> finger (speed=1) (same time)
    Normal3, // Open -> delay 2s -> finger (125 - just touch , no switch) -> delay 1s -> finger

    Angry0, // Red -> Angry Cover -> Open ->  delay 0.2s -> finger
    Angry1, // Red -> Open -> delay 0.2s -> finger -> Angry Finger
    Angry2, // Grean  Open (speed=2) -> delay 1s -> Red -> finger
    Angry3, // Angry Cover -> Open -> delay 0.2s -> finger -> delay 0.2s -> close -> open -> delay 0.2s -> Angry Finger

};
const int Total_action = sizeof(action) / sizeof(action[0]);

void setRGB(int red, int green, int blue);
void finger(int val, int speed=0);
void cover(int val, int speed=0);
void sleep();


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

int stressLevel = 0;         
unsigned long lastClickTime = 0;

void updateStress() {
  unsigned long now = millis();

    if( now - lastClickTime < 5000 ){ // increase stress if it be annoyed again in 5s
        stressLevel += (now-lastClickTime < 3000) ? random(1, 3) : 1; 
    } 
        
    else{
        // Giảm stress dựa trên thời gian chờ 
        int coolDown = (now - lastClickTime) / 2000; 
        stressLevel = max(0, stressLevel - coolDown);
    }

    stressLevel = min(stressLevel, 10); //limit the maximum  stress;
    lastClickTime = now;
}


void loop() {
  if (digitalRead(sw_COM) == HIGH) { // BOX_ON 
    updateStress();
    
    if(random(10)==0 && stressLevel >= 9){ // 10% Supprise!
        action[random(0, (int)Total_action*0.4)]();
    }
    else{
        int minIdx = stressLevel / 2;
        int maxIdx = (int)(Total_action * (1.0 - (0.4 - (stressLevel / 10.0) * 0.4)));
        action[random(minIdx, maxIdx)]();
    }
    sleep();

    if(random(3)==0 and stressLevel >= 5) 
        Watch_Out_For_Me();
  }
}