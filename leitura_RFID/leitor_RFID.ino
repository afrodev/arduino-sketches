#include <SoftwareSerial.h> 

// Esse é o Modulo de RFID nos pinos 2 e 3
SoftwareSerial mySerial(2, 3);
//Array que armazenará cada byte em HEX lido pelo RFID
int leitura[12];

// Pega o id leitor
char comando_LeituraTag[] = { 0xAA , 0x00, 0x03, 0x25, 0x26, 0x00, 0x00, 0xBB };
int tagValida1[4] = {135, 80, 114, 203};


void setup()
{
  // Taxa de leitura do terminal
  Serial.begin(57600);
  Serial.println("Iniciando leitor de RFID"); // Mensagem de inicio
  mySerial.begin(9600); // Taxa de leitura do modulo RFID
  
}

void loop() 
{ 
  delay(500);
  
  // Contador
  int j = 0;

  // Enquanto ele conseguir ler dados do modulo de RFID
  while(mySerial.available()) {
    // Ele lê e coloca no vetor de leitura
    leitura[j] = mySerial.read();
    j++;
  }

  if (verificaTagValida() == true) {
    // Retira apenas os Bytes com o ID dos tag
    for (j = 5; j < 9; j++) { 
      Serial.print(leitura[j], HEX);
      //Serial.print(" - ");
      //Serial.println(leitura[j]);
    }
    Serial.println();
  }
    

  // Envia comando para leitura do tag
  for (j = 0; j < 8; j++) 
    mySerial.write(comando_LeituraTag[j]);

  //Limpa o Buffer de leitura dos tags
  for (j = 0; j < 12; j++)
    leitura[j] = 0;
    
  //Serial.println("");
}

// Verifica se a tag é valida   
bool verificaTagValida() {
  // Compara se existe alguma tag que estamos procurando
  for (int j = 5; j < 9; j++) {
    int i = j - 5;
    
    if (leitura[j] != tagValida1[i]) {
      return false;
    }
  }

  return true;
}

