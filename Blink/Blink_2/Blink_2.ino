void loop() 
{
 for ( int i=1; i<=1000; i++)
 {
   digitalWrite(led, HIGH);
   delay(1000/i);
   digitalWrite(led, LOW);
   delay(1000/i);
 }
}
