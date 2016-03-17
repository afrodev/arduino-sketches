#include <SoftwareSerial.h> 

SoftwareSerial mySerial(2, 3);
const int ledPin = 7;


//MF_READ - Código para leitura
byte MF_GET_SNR[15] = {0XAA, 0X00, 0X0A, 0X20, 0X01, 0X01, 0X10, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0x3A, 0XBB};

// PARA ESCREVER 0FFFFF NA TAG
//byte MF_GET_SNR[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X2B, 0XBB}; //MF_WRITE 16 F (A)

// PARA ESCREVER 0FFFF1 NA TAG 
//byte MF_GET_SNR[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X11, 0X11, 0X2B, 0XBB}; //MF_WRITE 14F 11 11 (B)

// PARA ESCREVER 000000 NA TAG
//byte MF_GET_SNR[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X2B, 0XBB}; //MF_WRITE 16 zeros (C)

// PARA ESCREVER 0000001 NA TAG
//byte MF_GET_SNR[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X11, 0X11, 0X2B, 0XBB}; //MF_WRITE 14 zeros 11 11 (D)


// Texto que será escrito o rfid_leitura
String rfid_leitura;

// Grava a leitura anterior para comparar
String rfid_anterior;


// Verifica se está debug
boolean debugging;


void setup() {
  // Inicializa todos os seriais
  Serial.begin(57600);
  
  // Inicializa o modulo do rfid_leitura
  mySerial.begin(9600);

  // Debug 
  debugging = true; 
  Serial.println("SKETCH ABERTO");
  
  // Ativa o Botão 
  pinMode(ledPin, OUTPUT);

  rfid_anterior = "-1";

}

void loop() {
  // Escreve no modulo rfid, o comando de leitura
  mySerial.write(MF_GET_SNR, sizeof(MF_GET_SNR));
  delay(150); // Delay 

  // Inicializa o texto de rfid
  rfid_leitura = "";

  // Enquanto o modulo estiver livre
  while(mySerial.available() > 0) {
      
      // Leitura dos dados rfid
      int x = mySerial.read();
    
      //Se é zero coloca na string 0
      if(x == 0){
        rfid_leitura += "0";
      }

      // Leitura do segundo byte
      x = mySerial.read();

      //Se o byte lido for FF (255 em decimal), coloca um F na string
      if(x == 255){
        rfid_leitura += "F";
      }

      // Leitura do proximo byte
      x = mySerial.read();
      
      // Se o byte for 0x11
      if(x == 17) {
        rfid_leitura += "1";
      }  
  }

  // 
  if (rfid_leitura == "0FFFFF"){         // 1
      if (rfid_anterior != "0FFFFF") {
        if(debugging)  {
          rfid_anterior = rfid_leitura;
          Serial.println("id01"); 
          Serial.println(rfid_leitura);
          digitalWrite(ledPin, 1);
        }
        else Serial.write(1);
      }
  } else if (rfid_leitura == "0FFFF1") { // 2
      if (rfid_anterior != "0FFFF1") {
        if(debugging){ 
          rfid_anterior = rfid_leitura;          
          Serial.println("id02"); 
          Serial.println(rfid_leitura);
          digitalWrite(ledPin, 1);
        }
        else Serial.write(2);
      }
  } else if (rfid_leitura == "000000") { // 3
      if (rfid_anterior != "000000") {
        if(debugging) {
          rfid_anterior = rfid_leitura;
          Serial.println("id03"); 
          Serial.println(rfid_leitura); 
          digitalWrite(ledPin, 1);
        }
        else Serial.write(3);
      }
  } else if(rfid_leitura == "0000001"){  // 4
      if (rfid_anterior != "0000001") {
        if(debugging){
          rfid_anterior = rfid_leitura;
          Serial.println("id04"); 
          Serial.println(rfid_leitura);    
          digitalWrite(ledPin, 1);
        }
        else Serial.write(4);
      }
  }else {
        rfid_anterior = "-1";
        digitalWrite(ledPin, 0);
  }

}
