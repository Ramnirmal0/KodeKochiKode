#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
void setup() {
  pinMode(14,OUTPUT);
  digitalWrite(14,HIGH);
  pinMode(16,OUTPUT);
  digitalWrite(16,LOW);
  Serial.begin(9600);
  lcd.begin(16,2);
  

}

void loop() {
 int x=analogRead(A1);
 float y=(x*5.0*100)/1024;
 Serial.print("Kochi Temp =");
 Serial.println(y);
 lcd.setCursor(0,0);
 lcd.print("Kochi Temp=");
 lcd.setCursor(0,1);
 lcd.print(y);
 delay(3000);
 Serial.print("updating....");
 Serial.println(y);
 lcd.setCursor(0,0);
 lcd.print("Updating...");
 lcd.setCursor(0,1);
 lcd.print("      ");
 delay(2000);
 


}
