#include <SoftwareSerial.h>
char gsmdata; // Will hold the incoming character from the GSM shield
SoftwareSerial GS(9, 10); // 9 RECIEVE 10 TRANS
int c = 0;
void setup()
{
  pinMode(7,OUTPUT);
  pinMode(11, OUTPUT); //motor pin
  Serial.begin(9600);
  GS.begin(9600);
  Serial.println("system startup............ ");
  delay(20000);  // give time to log on to network.
  GS.print("AT+CLIP=1\r"); // turn on caller ID notification
  delay(100);

}


void loop()
{
  if (GS.available() > 1) // To send the SMS to the called number
  {

    gsmdata = GS.read();

    Serial.println(gsmdata);
    if (gsmdata == '+')
    {
      delay(10);
      gsmdata = GS.read();
      if (gsmdata == '9')
      {
        delay(10);
        gsmdata = GS.read();
        if (gsmdata == '1')
        {
          delay(10);
          gsmdata = GS.read();
          if (gsmdata == '7')
          {
            delay(10);
            gsmdata = GS.read();
            if (gsmdata == '0')
            {
              delay(10);
              gsmdata = GS.read();
              if (gsmdata == '1')
              {
                delay(10);
                gsmdata = GS.read();
                if (gsmdata == '2')
                {
                  delay(10);
                  gsmdata = GS.read();
                  if (gsmdata == '7')
                  {
                    delay(10);
                    gsmdata = GS.read();
                    if (gsmdata == '6')
                    {
                      delay(10);
                      gsmdata = GS.read();
                      if (gsmdata == '7')
                      {
                        delay(10);
                        gsmdata = GS.read();
                        if (gsmdata == '0')
                        {
                          delay(10);
                          gsmdata = GS.read();
                          if (gsmdata == '3')
                          {
                            delay(10);
                            gsmdata = GS.read();
                            if (gsmdata == '1')
                            {
                              Serial.print("Number Identified");
                              digitalWrite(7,HIGH);
                              delay(5000);
                              digitalWrite(7,LOW);
                              
                              
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
