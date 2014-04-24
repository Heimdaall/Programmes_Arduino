//SIM900 - ENVOYER - RECEVOIR UN SMS
//Par Pierre Pelé
//http://upsilonaudio.com/
//Avril 2014

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;

int numdata;
boolean started=false;
char* numero_Destinataire="+33600000000"; // Numéro de téléphone du destinataire
char smsbuffer[160];
char n[20];

void setup() 
{
  // Port Série
  Serial.begin(9600);
  Serial.println("Etablissement de la connexion avec le SIM900.");
  if (gsm.begin(9600))
  {
    Serial.println("\nStatus : PRET");
    started=true;  
  }
  else
  {
    Serial.println("\nStatus : VEILLE");
  }
  
  if(started)
  {
    // ENVOI DU SMS
    if (sms.SendSMS(numero_Destinataire, "Upsilon Audio !"))
    {
      Serial.println("\nSMS envoye !");
    }
    else
    {
      Serial.println("\nERREUR !");
    }
  }
}

void loop() 
{
  if(started)
  {
    // RECEVOIR UN SMS
    if(gsm.readSMS(smsbuffer, 160, n, 20))
    {
      Serial.println(n);
      Serial.println(smsbuffer);
    }
    delay(1000);
  }
}
