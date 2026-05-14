void Watch_Out_For_Me(){
  delay(500);
  cover(120);
  delay(2000);
  cover(0,1);
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