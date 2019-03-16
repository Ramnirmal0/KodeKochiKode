/*
   Licenced by pineapplem3 Inc Team. for more details about our team visit : pineapplem3.com .
   know more about our policy at : https://pineapplem3.com/privacy-policy/
   Know more about our terms of use : https://pineapplem3.com/terms-of-use/
   visit our official website for more details : https://pineapplem3.com/
   Programmed and Compiled by : Nirmal Ram .
   Contributor : Prasoon Kottarathil
*/
// Accelerometer and gyrosensor initiatilsation
#include<Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
// Main code initialisation
long int age = 21, duration = 120000, duration2 = 120000;
//predefined value used for test purpose.
float height = 175.0, walking_speed = 2.8, excersise = 0.1, cal_burnt = 0.1, bmr = 1814;
char sex;
int buz_pin = 13, count = 0, count2 = 0, foot = 0;
// pulse sensor Initialisation
int sensor_pin = 0;
volatile int heart_rate;
volatile int analog_data;
volatile int time_between_beats = 600;
volatile boolean pulse_signal = false;
volatile int beat[10];         //heartbeat values will be sotred in this array
volatile int peak_value = 512;
volatile int trough_value = 512;
volatile int thresh = 525;
volatile int amplitude = 100;
volatile boolean first_heartpulse = true;
volatile boolean second_heartpulse = false;
volatile unsigned long samplecounter = 0;   //This counter will tell us the pulse timing
volatile unsigned long lastBeatTime = 0;
//force sensor intiatilisation
int fsrPin = 1;     // the FSR and 10K pulldown are connected to a1
int fsrReading;     // the analog reading from the FSR resistor divider



void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  pinMode(buz_pin, OUTPUT);
  interruptSetup();

}

void loop() {
  // accelerometer and gyroscope sensor loop
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 12, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  //hidden data at user interface (app)
  Serial.print("Accelerometer Readings from Eshirt: \n===================================\n"); Serial.print("\n\n");
  Serial.print("X axis = "); Serial.print(AcX); Serial.print("\n\n");
  Serial.print("Y axis= "); Serial.print(AcY); Serial.print("\n\n");
  Serial.print("Z axis= "); Serial.println(AcZ); Serial.print("\n\n");
  //hidden data at user interface (app)
  Serial.print("Gyroscope Reading from Eshirt: \n======================================\n"); Serial.print("\n\n");
  Serial.print("X axis= "); Serial.print(GyX); Serial.print("\n\n");
  Serial.print("Y axis= "); Serial.print(GyY); Serial.print("\n\n");
  Serial.print("Z axis= "); Serial.println(GyZ); Serial.print("\n\n");
  Serial.println(" ");
  //delay(1000);
  //pulse sensor loop
  Serial.print("BPM: ");
  Serial.println(heart_rate);
  //delay(2000); //  take a break
  //force sensor loop
  fsrReading = analogRead(fsrPin);
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading
  if (fsrReading == 0) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 10) {
    Serial.println(" - Light touch");
  } else if (fsrReading < 50) {
    Serial.println(" - Light squeeze");
  } else if (fsrReading < 150) {
    Serial.println(" - Medium squeeze");
  } else {
    Serial.println(" - Big squeeze");
  }
  //delay(1000);
  //temperature sensor loop
  int x = analogRead(A2);
  float mytemp = (x * 5.0 * 100) / 1024;
  Serial.print("Body Temperature =");
  Serial.println(mytemp);

  // applying checking conditions and optimatization algorithms
  //first condition to check cal_burnt using execersises
  if (AcX > 20000 or AcY > 20000 or AcZ > 20000 or AcX < -20000 or AcY < -20000 or AcZ < -20000)
  {
    if (count == duration)
    {
      excersise = 0.1 * walking_speed + excersise;
      cal_burnt = 7.0 + cal_burnt;
      count = 0;
    }
    count = count + 1;
    foot = foot + 1;
    if (count2 == duration2)
    {
      count2 = count2 + 1;
      bmr = 1814 + bmr;
    }
  }
  Serial.println("\n\nCalories Burnt = ");
  Serial.println(cal_burnt);
  Serial.println("\n\nSteps walked = ");
  Serial.println(foot);
  Serial.println("\n\nBMR = ");
  Serial.println(bmr);
}

void alert()
{

  while (1) {
    digitalWrite(buz_pin, HIGH);
    delay(100);
    digitalWrite(buz_pin, LOW);
    delay(100);
  }
}


void interruptSetup()
{

  TCCR2A = 0x02;  // This will disable the PWM on pin 3 and 11
  OCR2A = 0X7C;   // This will set the top of count to 124 for the 500Hz sample rate
  TCCR2B = 0x06;  // DON'T FORCE COMPARE, 256 PRESCALER
  TIMSK2 = 0x02;  // This will enable interrupt on match between OCR2A and Timer
  sei();          // This will make sure that the global interrupts are enable
}

ISR(TIMER2_COMPA_vect)
{
  cli();
  analog_data = analogRead(sensor_pin);
  samplecounter += 2;
  int N = samplecounter - lastBeatTime;
  if (analog_data < thresh && N > (time_between_beats / 5) * 3)
  {
    if (analog_data < trough_value)
    {
      trough_value = analog_data;
    }
  }
  if (analog_data > thresh && analog_data > peak_value)
  {
    peak_value = analog_data;
  }
  if (N > 250)
  {
    if ( (analog_data > thresh) && (pulse_signal == false) && (N > (time_between_beats / 5) * 3) )
    {
      pulse_signal = true;
      digitalWrite(buz_pin, HIGH);
      time_between_beats = samplecounter - lastBeatTime;
      lastBeatTime = samplecounter;
      if (second_heartpulse)
      {
        second_heartpulse = false;
        for (int i = 0; i <= 9; i++)
        {
          beat[i] = time_between_beats; //Filling the array with the heart beat values
        }
      }
      if (first_heartpulse)
      {
        first_heartpulse = false;
        second_heartpulse = true;
        sei();
        return;
      }
      word runningTotal = 0;
      for (int i = 0; i <= 8; i++)
      {
        beat[i] = beat[i + 1];
        runningTotal += beat[i];
      }
      beat[9] = time_between_beats;
      runningTotal += beat[9];
      runningTotal /= 10;
      heart_rate = 60000 / runningTotal;
    }
  }
  if (analog_data < thresh && pulse_signal == true)
  {
    digitalWrite(buz_pin, LOW);
    pulse_signal = false;
    amplitude = peak_value - trough_value;
    thresh = amplitude / 2 + trough_value;
    peak_value = thresh;
    trough_value = thresh;
  }
  if (N > 2500)
  {
    thresh = 512;
    peak_value = 512;
    trough_value = 512;
    lastBeatTime = samplecounter;
    first_heartpulse = true;
    second_heartpulse = false;
  }
  sei();
}
