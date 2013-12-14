//Signal Carré
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
    PORTD = 255;
    delayMicroseconds(50); //Pause de 50 microsecondes
    PORTD = 0;
    delayMicroseconds(50); //Pause de 50 microsecondes
}
