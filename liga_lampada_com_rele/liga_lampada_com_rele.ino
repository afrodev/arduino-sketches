int sinal_rele = 7;

void setup()
{
          pinMode(sinal_rele, OUTPUT);
}

void loop()
{
          digitalWrite(sinal_rele, HIGH);
          delay(5000);
          digitalWrite(sinal_rele, LOW);
          delay(5000);
  
}
