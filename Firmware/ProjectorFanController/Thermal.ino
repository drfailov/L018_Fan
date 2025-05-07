// Thermistor Example #3 from the Adafruit Learning System guide on Thermistors 
// https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit Industries
// MIT License - please keep attribution and consider buying parts from Adafruit

//PIN_THERMISTOR
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 3
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    

int samples[NUMSAMPLES];  //buffer







float getInternalTemp(){
  //float temperature=(ADCW – 324.31f)/1.22f;
  //return temperature;
  ADMUX = 0xC8; // turn on internal reference, right-shift ADC buffer, ADC channel = internal temp sensor
  delay(10);  // wait a sec for the analog reference to stabilize
  
  ADCSRA |= _BV(ADSC); // start the conversion
  while (bit_is_set(ADCSRA, ADSC)); // ADSC is cleared when the conversion finishes
  return (ADCL | (ADCH << 8)) - 342; // combine bytes & correct for temp offset (approximate)} 
}





float getTemp(int pinSensor, int pinPwr, int pinGnd){
  pinMode(pinPwr, OUTPUT);  //POWER for thermistor
  digitalWrite(pinPwr, HIGH);
  pinMode(pinGnd, OUTPUT);  //GND for thermistor
  digitalWrite(pinGnd, LOW);
  
  uint8_t i;
  float average;
  for (i=0; i< NUMSAMPLES; i++) { // take N samples in a row, with a slight delay
   samples[i] = analogRead(pinSensor);
   delay(5);
  }
  average = 0; // average all the samples out
  for (i=0; i< NUMSAMPLES; i++) 
     average += samples[i];
  average /= NUMSAMPLES;
  average = 1023 / average - 1; // convert the value to resistance
  average = SERIESRESISTOR / average; //Thermistor resistance 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart;
}
