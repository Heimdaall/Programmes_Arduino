//SIM900 - Connexion au réseau
//Par Pierre Pelé
//http://upsilonaudio.com/
//Avril 2014

//#define DEBUG // Décommentez pour debugger !

#include <SIM900.h>
#include <SoftwareSerial.h>
 
void setup() 
{
  Serial.begin(9600);
  Serial.println("Mise en route");
  if (gsm.begin(9600))
  {
    Serial.println("\nStatus=PRET");
  }
  else
  {
    Serial.println("\nStatus=VEILLE");
  }
  int reg;
  reg=gsm.CheckRegistration();
  switch (reg)
  {
    case REG_NOT_REGISTERED:
      Serial.println("Le modem GSM est non enrengistre !");
      break;
    case REG_REGISTERED:
      Serial.println("Le modem GSM est enrengistre !");
      break;
    case REG_NO_RESPONSE:
      Serial.println("Le modem GSM ne repond pas !");
      break;
    case REG_COMM_LINE_BUSY:
      Serial.println("Liaison serie indisponible !");
      break;
  }
  delay(30000);
}
 
void loop()
{ 
}
