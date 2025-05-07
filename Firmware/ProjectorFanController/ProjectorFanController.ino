/*Projector fan controller*/
int icr, frecuency, duty_cycle;

void setup() {

  Serial.begin(115200);    
  while (!Serial);

  //Setup fan and LED
  digitalWrite(13, HIGH);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
}

void loop() {
  //calculate fan speed
  float temp1 = getTemp(A1, /*D*/8, A0);
  float temp2 = getTemp(A2, /*D*/7, A0);
  float temp3 = getTemp(A3, /*D*/6, A0);

  float duty1 = map(temp1, 30, 80, 25, 100);//LCD
  float duty2 = map(temp2, 40, 90, 25, 100);//LED
  float duty3 = map(temp3, 30, 80, 25, 100);//cpu
  duty_cycle = max(max(duty1,duty2),duty3);  //0...100

  //apply fan speed
  analogWrite(11, map((float)duty_cycle, 0, 100, 0, 255));


  //debug to serial
  Serial.print("temp1: "); 
  Serial.println(temp1);
  Serial.print("temp2: "); 
  Serial.println(temp2);
  Serial.print("temp3: "); 
  Serial.println(temp3);
  Serial.print("duty_cycle: "); 
  Serial.println(duty_cycle);
  Serial.println("=============");

  //debug to LED
  digitalWrite(13, HIGH);
  delay(duty_cycle);
  digitalWrite(13, LOW);
  delay(100-duty_cycle);
}



float map(float x, float in_min, float in_max, float out_min, float out_max) {
  if(x<in_min)
    return out_min;
  if(x>in_max)
    return out_max;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
