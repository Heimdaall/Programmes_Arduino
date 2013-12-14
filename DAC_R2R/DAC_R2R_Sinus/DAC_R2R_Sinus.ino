//Signal Sinusoidal
//Par Pierre Pelé (pele.pierre@gmail.com)
//http://upsilonaudio.com/arduino-dac-r-2r-ladder/
//Septembre 2013

int N = 256;

void setup()
{
  for (int i=0;i<8;i++) //Définir les broches 0 à 7 en tant que sorties
  {
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  for (int t=0;t<256;t++)
  {
    PORTD = 127+127*sin(2*3.14159*(t/256));
    delayMicroseconds(50); //Pause de 50 microsecondes
  }
}
