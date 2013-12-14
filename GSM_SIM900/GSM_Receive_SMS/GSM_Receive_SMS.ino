int8_t answer;
int x;
int onModulePin= 2; // Il s'agit du port DTR (ou PWR) du module SIM900.
char SMS[200];

void setup(){

    pinMode(onModulePin, OUTPUT);
    Serial.begin(115200);
    Serial2.begin(115200);  

    Serial.println("------------------------------------------------------");
    Serial.println("----Upsilon Audio - Envoyer un SMS avec le SIM900-----");
    Serial.println("------------------------------------------------------");
    Serial.println("");
    Serial.println("Initialisation en cours ...");
    power_on();
    
    delay(3000);
    
    // Cette commande active la carte SIM.
    //Supprimez cette ligne si vous n'avez pas de code PIN.
    sendATcommand("AT+CPIN=****", "OK", 2000);
    
    delay(3000);
    
    Serial.println("Mode SMS en cours d'activation ...");
    // Activation du mode texte pour les SMS.
    sendATcommand("AT+CMGF=1", "OK", 1000);
    // Sélection de la mémoire.
    sendATcommand("AT+CPMS=\"SM\",\"SM\",\"SM\"", "OK", 1000);
    // Lecture du premier SMS disponible.
    answer = sendATcommand("AT+CMGR=1", "+CMGR:", 2000);
    if (answer == 1)
    {
        answer = 0;
        while(Serial2.available() == 0);
        // Cette boucle récupère les données du SMS
        do{
// Si des données sont disponibles dans le tampon de la liaison série
// Le programme récupère ces données et les compares au code retour de la compmande AT
            if(Serial2.available() > 0){    
                SMS[x] = Serial2.read();
                x++;
                // Le module GSM a t'il envoyé le code de retour "OK" ?
                if (strstr(SMS, "OK") != NULL)    
                {
                    answer = 1;
                }
            }
        }while(answer == 0); // Attente du code de retour.
        
        SMS[x] = '\0';
        
        Serial.println("Voici le SMS:");
        Serial.println("");
        Serial.print(SMS);
        Serial.println("");    
        
    }
    else
    {
        Serial.print("Erreur: ");
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

    //Serial.println(response); //Cette ligne permet de debuguer le programme en cas de problème !
    return answer;
}
