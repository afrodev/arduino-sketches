#include <SoftwareSerial.h> 

// Esse é o Modulo de RFID
SoftwareSerial mySerial(2, 3);
char txrxbuffer[255];
int leitura[12];

// Pega o id leitor
char get_readID[] = { 0xAA , 0x00, 0x03, 0x25, 0x26, 0x00, 0x00, 0xBB };

void setup()
{
  // Taxa de leitura do terminal
  Serial.begin(57600);
  Serial.println("Hit Enter to read the RFID number"); // Mensagem de inicio
  mySerial.begin(9600); // Taxa de leitura do 
  
}

void loop() 
{ 
  delay(500);
  
  // Contador
  int counter = 0;
  int j = 0;
  int IDbyte = 0;
  
  while(mySerial.available()) {
    leitura[j]= mySerial.read();

    j++;
    //Serial.print(mySerial.read(), HEX);
  }


  for (j=5 ; j<9 ; j++) { // Retira apenas os Bytes com o ID dos tag
    Serial.print(leitura[j], HEX);
    //if (leitura[j] == tagValida[j-5])
      //IDbyte++;
  
  }

  for (j = 0 ; j < 8 ; j++) //Envia comando para leitura do tag
    mySerial.write(get_readID[j]);
    
  for (j = 0 ; j < 12 ; j++) //Limpa o Buffer de leitura dos tags
    leitura[j] = 0;
    
  Serial.println("");

}