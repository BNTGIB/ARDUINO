#include <Servo.h>
#include <Arduino.h>


#define FINGER 9
#define COVER 10
#define sw_COM 2
#define RED 3
#define GREEN 5
#define BLUE 6

#define Touch 128
#define FullOpen 160

Servo Finger, Cover;

void Watch_Out_For_Me();
void Normal0();
void Normal1();
void Normal2();
void Normal3();  

void  Angry0();
void  Angry1();
void  Angry2();
void  Angry3();


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



//////////////////////////////////////////////////////////////
void loop() {
  if (digitalRead(sw_COM) == HIGH) { // BOX_ON 
    // updateStress();
    
    Normal3();
    
    sleep();

    // if(random(3)==0 and stressLevel >= 5) 
    //     Watch_Out_For_Me();
  }
  else {
    sleep();
  }
}
/////////////////////////////////////////////////////////////
void setRGB(int red, int green, int blue){
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

void finger(int val, int speed=0){
  if(!speed) {
    Finger.write(180-val);
    return;
  }

  int current= 180 - Finger.read();
  if(val>current){
    for(int i = current; i <= val; i+= speed ){
      Finger.write(180-min(i,Touch));
        delay(10);
    }
  }
  else{
    for(int i = current; i >= val; i-= speed ){
      Finger.write(180-max(0,i));
        delay(10);
    }
  }
}

void cover(int val, int speed=0){
  if(!speed) {
    Cover.write(val);
    return;
  }

  int current= Cover.read();
  if(val>current){
    for(int i = current; i <= val; i+= speed ){
        Cover.write(min(i,FullOpen));
        delay(10);
    }
  }
  else{
    for(int i = current; i >= val; i-= speed ){
      Cover.write(max(0,i));
          delay(10);
    }
  }
}

void sleep(){
  finger(0);
  delay(200);
  cover(0);
  delay(200);
  setRGB(0, 255, 0);
}

void AngryCover(){
  int time = random (3,7);
  for(int i=0;i<time;i++){
    cover(100);
    setRGB(200,0,0);
    delay(100);
    cover(0);
    setRGB(255,0,0);
    delay(100);
  }
  setRGB(255,0,0);
}

void AngryFinger(){
  int time = random (3,6);
  for(int i=0;i<time;i++){
    finger(110);
    setRGB(255,0,0);
    delay(100);
    finger(Touch);
    setRGB(220,0,0);
    delay(100);
  }
  setRGB(255,0,0);
}
/////////////////////////////////////////////////////////////////////
void Watch_Out_For_Me(){
  delay(500);
  cover(120);
  delay(2000);
  cover(0,1);
}

void Normal0(){ // Open -> delay 0.2s -> finger
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(250);
}
void Normal1(){ // Open -> delay 1s -> finger
  cover(FullOpen);
  delay(1000);
  finger(Touch);
  delay(250);
}
void Normal2(){ // Open (speed=2) -> -> finger (speed=1) (same time)
  setRGB(255, 255, 0);
  cover(FullOpen,2);
  delay(200);
  finger(Touch,1);
  delay(250);
} 
void Normal3(){ // Open -> delay 2s -> finger (125 - just touch , no switch) -> delay 1s -> finger
  setRGB(255, 255, 0);
  cover(FullOpen);
  delay(2000);
  finger(120);
  delay(1000);
  finger(Touch+2);
  delay(250);
}   

void  Angry0(){ // Red -> Angry Cover -> Open ->  delay 0.2s -> finger
  setRGB(255, 0, 0);
  AngryCover();
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(200);
}
void  Angry1(){ // Red -> Open -> delay 0.2s -> finger -> delay 0.5s -> Angry Finger
  setRGB(255, 0, 0);
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(1000);
  AngryFinger();
} 
void  Angry2(){ // Yellow  Open (speed=2) -> delay 1s -> Red -> finger
  setRGB(255, 255, 0);
  cover(FullOpen,2);
  delay(1000);
  setRGB(255, 0, 0);
  finger(Touch);
  delay(250);
} 
void  Angry3(){ // Angry Cover -> Open -> delay 0.2s -> finger -> delay 0.2s ->slepp -> delay 1s -> Open -> Fninger -> delay 1s -> Angry Finger
  setRGB(255, 0, 0);
  AngryCover();
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(250);
  sleep();
  delay(1000);
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(1000);
  AngryFinger();
}  

