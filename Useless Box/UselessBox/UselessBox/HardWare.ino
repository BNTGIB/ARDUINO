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
    for(int i = current; i <= val +2 ; i+= speed ){
      Finger.write(180-min(i,Touch+2));
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
  cover(1);
  delay(200);
  setRGB(0, 255, 0);
}

void AngryCover(){
  int time = random (3,7);
  for(int i=0;i<time;i++){
    cover(100);
    setRGB(200,0,0);
    delay(80);
    cover(0);
    setRGB(255,0,0);
    delay(80);
  }
  setRGB(255,0,0);
}

void AngryFinger(){
  int time = random (3,6);
  for(int i=0;i<time;i++){
    finger(110);
    setRGB(255,0,0);
    delay(150);
    finger(Touch-2);
    setRGB(220,0,0);
    delay(150);
  }
  setRGB(255,0,0);
}