//SIM900 - Connexion au réseau
//Par Pierre Pelé
//http://upsilonaudio.com/
//Avril 2014

//#define DEBUG // Décommentez pour debugger !

void setup()
{
  if(connexion_Reseau(15000))
  {
    Serial.println("Connexion au reseau : OK !");
  }
  else
  {
    Serial.println("Connexion au reseau : ERREUR !");
  }
}

void loop()
{ 
}

// DÉFINITION DES FONCTIONS

// ÉTAT DE LA CONNEXION AU RÉSEAU
uint8_t connexion_Reseau(unsigned int timeout)
{
  uint8_t  answer=0;
  unsigned long previous;
  previous = millis();
  
  while((answer == 0) && ((millis() - previous) < timeout))
  {
    if((envoyer_Commande_AT("AT+CREG?", "+CREG: 0,1", 500) 
    || envoyer_Commande_AT("AT+CREG?", "+CREG: 0,5", 500)) == 1 )
    {
      answer=1;
    }
  }
  
  return answer;
}

// ENVOYER UNE COMMANDE AT
uint8_t envoyer_Commande_AT(char* commande_AT, char* reponse_Esperee, unsigned int timeout)
{

    uint8_t x=0,  answer=0;
    char reponse[100];
    unsigned long previous;

    // Initialisation de la chaine de caractère (string).
    memset(reponse, '\0', 100);
    
    delay(100);
    
    // Initialisation du tampon d'entrée (input buffer).
    while( Serial2.available() > 0)
    {
      Serial2.read();
    }
    
    // Envoi de la commande AT.
    Serial2.println(commande_AT);

    // Réponse du SIM900.
    // Cette boucle vérifie s'il y a des données disponibles dans le tampon.
    // Ces données sont comparées avec la réponse attendue.

    x = 0;
    previous = millis();
    
    do
    {
       if(Serial2.available() != 0)
         {    
         reponse[x] = Serial2.read();
         x++;
         // Comparaison des données
         if (strstr(reponse, reponse_Esperee) != NULL)    
         {
           answer = 1;
         }
    }
    }while((answer == 0) && ((millis() - previous) < timeout));
    
    #ifdef DEBUG
    Serial.println(reponse);
    #endif
    
    return answer;
}
