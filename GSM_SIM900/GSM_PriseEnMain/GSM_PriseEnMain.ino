#include <SoftwareSerial.h>
#define RX  7
#define TX  8
#define PWR 6 // Il s'agit du port DTR (ou PWR) du module SIM900.

// On créé un port série de manière logicielle.
SoftwareSerial softSerial(RX, TX);

void setup () 
{
   Serial.begin(19200);
   softSerial.begin(19200);
   softSerial.println("INIT");
   softSerial.println("GPRS on/off");
   GPRS_software_on_off();

}

void loop()
{
    if (softSerial.available())
            Serial.write(softSerial.read());
                if (Serial.available())
                    softSerial.write(Serial.read());
}

void GPRS_software_on_off(){
  digitalWrite(PWR,HIGH);
  delay(2500);
  digitalWrite(PWR,LOW);
}
