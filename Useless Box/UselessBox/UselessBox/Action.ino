void Watch_Out_For_Me(){
  delay(500);
  cover(120);
  delay(2000);
  cover(0,2);
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
  finger(Touch);
  delay(250);
}   

void  Angry0(){ //delay (1s) -> Red  -> Angry Cover -> Open ->  delay 0.2s -> finger
  delay(1000);
  AngryCover();
  setRGB(255, 0, 0);
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(250);
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
void  Angry3(){ // Angry Cover -> Open -> delay 0.2s -> finger -> delay 0.2s ->slepp -> delay 0.7s -> Open -> Fninger -> delay 1s -> Angry Finger
  setRGB(255, 0, 0);
  AngryCover();
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(250);
  sleep();
  delay(1000);
  setRGB(255, 0, 0);
  cover(FullOpen);
  delay(200);
  finger(Touch);
  delay(700);
  AngryFinger();
}  
