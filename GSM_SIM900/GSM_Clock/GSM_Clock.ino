int8_t answer;
int x ;
int onModulePin= 2; // Il s'agit du port DTR (ou PWR) du module SIM900.
char REPONSE[200];

void setup(){

    pinMode(onModulePin, OUTPUT);
    Serial2.begin(115200);
    Serial.begin(115200);
    Serial.println("Initialisation ...");
    power_on();
    delay(3000);
    answer = sendATcommand("AT+CCLK?", "+CCLK:", 5000);
    //Serial.println("Repere 1");
    if (answer == 1)
    {
        //Serial.println("Repere 2");
        answer = 0;
        while(Serial2.available() == 0);
        do{
            if(Serial2.available() > 0){    
                REPONSE[x] = Serial2.read();
                x++;
                //Serial.println("Repere 3");
                if (strstr(REPONSE, "OK") != NULL)    
                {
                    answer = 1;
                    //Serial.println("Repere 4");
                }
            }
        }while(answer == 0);
        REPONSE[x] = '\0';        
        Serial.println("Voici la reponse du SIM900");
        Serial.println(REPONSE);            
    }
    else
    {
        Serial.print("Erreur ");
        Serial.println(answer, DEC);
    }
}


void loop() // Il n'y a aucune commandes dans la fonction loop.
{
}

// Définition des différentes fonctions.

void power_on(){

    uint8_t answer=0;
    
    // Cette commande vérifie si le module GSM est en marche.
    answer = sendATcommand("AT", "OK", 2000);
    if (answer == 0)
    {
        // Mise en marche du module GSM
        digitalWrite(onModulePin,HIGH);
        delay(3000);
        digitalWrite(onModulePin,LOW);
    
        // Envoie d'une commande AT toutes les deux secondes et attente d'une réponse.
        while(answer == 0){
            answer = sendATcommand("AT", "OK", 2000);    
        }
    }
    
}

// Cette fonction permet d'envoyer des commandes AT au module GSM.
int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    // Initialisation de la chaine de caractère (string).
    memset(response, '\0', 100);
    
    delay(100);
    
    // Initialisation du tampon d'entrée (input buffer).
    while( Serial2.available() > 0) Serial2.read();
    
    // Envoi des commandes AT
    Serial2.println(ATcommand);


    x = 0;
    previous = millis();

    // Cette boucle attend la réponse du module GSM.
    
    do{
// Cette commande vérifie s'il y a des données disponibles dans le tampon.
//Ces données sont comparées avec la réponse attendue.
        if(Serial2.available() != 0){    
            response[x] = Serial2.read();
            x++;
            // Comparaison des données
            if (strstr(response, expected_answer) != NULL)    
            {
                answer = 1;
            }
        }
    // Attente d'une réponse.
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}
