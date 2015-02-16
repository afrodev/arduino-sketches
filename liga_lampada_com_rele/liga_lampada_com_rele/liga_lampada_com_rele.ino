// Ligar o pino GND do rele no PINO GND do Arduino
// Ligar o pino IN do rele no pino 7 do Arduino
// Ligar o pino VCC do rele no pino 5V do Arduino

int sinal_rele = 7;

void setup()
{
          pinMode(sinal_rele, OUTPUT);
}

void loop()
{
          digitalWrite(sinal_rele, HIGH);
          delay(1000);
          digitalWrite(sinal_rele, LOW);
          delay(10000);
  
}
