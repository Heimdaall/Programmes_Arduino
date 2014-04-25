//SIM900 - DTMF
//Par Pierre Pelé
//http://upsilonaudio.com/
//Avril 2014

// Arduino UNO : Taille binaire : 10 428 octets (d'un max de 32 256 octets)
// Arduino MEGA : Taille binaire : 12 160 octets (d'un max de 258 048 octets)

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"

CallGSM call;

char number[20];
byte stat=0;
int value=0;
int pin=1;
char value_str[5];
char DTMF_char='_';
int count=0;
boolean started=false;

void setup() 
{
  pinMode(pin,INPUT);
  // Port Série
  Serial.begin(9600);
  Serial.println("Etablissement de la connexion avec le SIM900");
  if (gsm.begin(9600))
  {
    Serial.println("\nStatus : PRET");
    started=true;
  }
  else
  {
    Serial.println("\nStatus : VEILLE");
  }
  
  //Détection des signaux DTMF
  call.SetDTMF(1);
}

void loop() 
{
  if(started)
  {
    // Status des appels
    stat=call.CallStatus();
    if(stat==CALL_INCOM_VOICE)
    {
      Serial.println("Debut de la communication !");
      delay(50);
      call.PickUp();
    }
    while(stat==CALL_ACTIVE_VOICE)
    {
      for (int k=0; k<100; k++)
      {
        DTMF_char=call.DetDTMF();
        if(DTMF_char!='-')
        {
          Serial.println(DTMF_char);
        }
      }
      stat=call.CallStatus();
    }
    delay(1000);
    Serial.println("Fin de la communication !");
  }
}
