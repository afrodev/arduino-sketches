#include <IRremote.h>
#include <IRremoteInt.h>

// Programa : Teste Controle Remoto IR  
// Autor : Arduino e Cia  
  
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
String armazenavalor = "";
int pinoledvermelho = 7;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
    {
      armazenavalor = String(results.value, HEX);  
      if (armazenavalor == "25802501") //Verifica se a tecla 1 foi acionada  
      {  
        Serial.println(1);
        digitalWrite(pinoledvermelho, HIGH);  //Acende o led vermelho  
      }


      
     //Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
    }
}
