int sensorPin = 4;
int iteration = 600;
int debut = 0000;
int fin = 10000;
void setup()
{                
  Serial.begin(9600);
  randomSeed(analogRead(sensorPin));
  unsigned long tab[iteration];
  for (int i = 0; i<iteration; i++)
  {
   tab[i]=random(debut,fin);
  }
  int compteur=0;
  unsigned long rayonCarre = pow(fin,2);
  unsigned long x;
  unsigned long y;
  for (int p = 0; p<(iteration/2); p++)
  {
    if (pow(tab[2*p],2)+pow(tab[2*p+1],2) <= rayonCarre)
    {
      compteur++;    
    }    
  }    
  float pia = 80000*compteur/iteration;
  Serial.println(pia);
}

void loop()
{
}
