int led=13;

void setup()
{
 Serial.begin(9600);
 pinMode(8, INPUT);
 pinMode(led, OUTPUT);
}

void loop()
{
  for(int i=30000; i<50000;i+=10) // Les constantes choisies sont le fruit de quelques minutes de tâtonnement
  {
    digitalWrite(led, HIGH);
    delay(1000/sqrt(i));
    digitalWrite(led,LOW);
    delay(1000/sqrt(i));
    if (analogRead(3)*5./1023>=4) // Si l'utilisateur appuie sur le bouton car il ne distingue plus le clignotement
    {
      Serial.println(1000/(1000/sqrt(i))); // Alors Arduino renvoie à l’écran le nombre de clignotements par seconde à cet instant
    }
  }
}
