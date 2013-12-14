//Signal Triangulaire
//Par Pierre Pelé (pele.pierre@gmail.com)
//http://upsilonaudio.com/arduino-dac-r-2r-ladder/
//Septembre 2013

void setup()
{
  for (int i=0;i<8;i++) //Définir les broches 0 à 7 en tant que sorties 
  {
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  for (int a=0;a<256;a++)
  {
    PORTD = a;
    delayMicroseconds(50); //Pause de 50 microsecondes
  }
}
