int sensorPin = 0;
unsigned long iteration = 100000;
unsigned long debut = 00000;
unsigned long fin = 10000;
void setup()
{                
  Serial.begin(9600);
  randomSeed(analogRead(sensorPin));
  unsigned long compteur=0;
  unsigned long rayonCarre = pow(fin,2);
  for (unsigned long i = 0; i<iteration; i++)
  {
    if (pow(random(debut,fin),2)+pow(random(debut,fin),2) <= rayonCarre)
    {
      compteur++;    
    }    
  }  
  float pia = 40000*compteur/iteration;
  Serial.println(pia);
}

void loop()
{
}
