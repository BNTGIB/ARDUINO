void setRGB(int red, int green, int blue){
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
}

void finger(int val, int speed=0){
  if(!speed) {
    Finger.write(val);
    return;
  }

  int current= Finger.read();
  if(val>current)
    for(int i = current; i <= val; i+= speed )
      Finger.write(min(i,Touch));
  else
    for(int i = current; i >= val; i-= speed )
      Finger.write(max(0,i));
}

void cover(int val, int speed=0){
  if(!speed) {
    Cover.write(val);
    return;
  }

  int current= Cover.read();
  if(val>current)
    for(int i = current; i <= val; i+= speed )
      Cover.write(min(i,Touch));
  else
    for(int i = current; i >= val; i-= speed )
      Cover.write(max(0,i));
}

void sleep(){
  finger(0);
  delay(200);
  cover(0);
}