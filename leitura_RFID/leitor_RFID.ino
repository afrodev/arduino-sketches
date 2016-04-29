#include <SoftwareSerial.h> 

SoftwareSerial mySerial(2, 3);
const int ledPin = 7;
String atual;

//MF_READ - Código para leitura 
byte MF_GET_SNR[15] = {0XAA, 0X00, 0X0A, 0X20, 0X01, 0X01, 0X10, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0x3A, 0XBB};

// PARA ESCREVER 0FFFFF NA TAG
byte MF_WRITE_1[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X2B, 0XBB}; //MF_WRITE 16 F (A)

// PARA ESCREVER 0FFFF1 NA TAG 
byte MF_WRITE_2[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X11, 0X11, 0X2B, 0XBB}; //MF_WRITE 14F 11 11 (B)

// PARA ESCREVER 000000 NA TAG
byte MF_WRITE_3[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X2B, 0XBB}; //MF_WRITE 16 zeros (C)

// PARA ESCREVER 0000001 NA TAG
byte MF_WRITE_4[31] = {0XAA, 0X00, 0X1A, 0X21, 0X01, 0X01, 0X10, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X11, 0X11, 0X2B, 0XBB}; //MF_WRITE 14 zeros 11 11 (D)

// Texto que será escrito o rfid_leitura
String rfid_leitura;

// Grava a leitura anterior para comparar
String rfid_anterior;

void setup() {
  // Inicializa todos os seriais
  Serial.begin(57600);
  
  // Inicializa o modulo do rfid_leitura
  mySerial.begin(9600);

  // Debug 
  //Serial.println("SKETCH ABERTO");
  
  // Ativa o Botão 
  pinMode(ledPin, OUTPUT);

  atual = "-1";
  rfid_anterior = "-1";

}

void loop() {
  modoLeituraRFID();
  //modoEscritaRFID(MF_WRITE_4);
}

void modoLeituraRFID() {
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

  //Serial.println(rfid_leitura);

  
  // Valida os RFID's
  if (rfid_leitura == "0FFFFF"){         // 1
      atual = '1';
      validaRFID("01","0FFFFF", 1);
      
  } else if (rfid_leitura == "0FFFF1") { // 2
      atual = '2';
      validaRFID("01","0FFFF1", 2);
      
  } else if (rfid_leitura == "000000") { // 3
      atual = '3';
      validaRFID("01","000000", 3);
      
  } else if(rfid_leitura == "0000001"){  // 4
      atual = '4';
      
      validaRFID("01","0000001", 4);
      
  } else {
      if (rfid_anterior != "-1") {
            String tex = "indice/sicredi/0" + atual;
            tex += "OUT";

        Serial.println(tex); 

        rfid_anterior = "-1";
        //Serial.println("NÃO ESTÁ PRESSIONANDO"); 
        digitalWrite(ledPin, 0);
//        digitalWrite(ledPin + 1, 0);
//        digitalWrite(ledPin + 2, 0);
//        digitalWrite(ledPin + 3, 0);
//        digitalWrite(ledPin + 4, 0);
      }
  }
}


// Função que valida o RFID
void validaRFID(String id_mesa, String rfid_leitura, int num_id) {
  if (rfid_anterior != rfid_leitura) {
    rfid_anterior = rfid_leitura;
    String tex = "indice/sicredi/0" + atual;
    tex += "IN";
    
    //Serial.write("0" + num_id);
    Serial.println(tex); 
    //Serial.println(rfid_leitura);
    digitalWrite(ledPin, 1);
  }
}


// Escreve valor no RFID
void modoEscritaRFID(byte MF_WRITE[31]) {
    Serial.println("ESCREVENDO NO RFID");
    
    mySerial.write(MF_WRITE, 31);
    delay(200);
    Serial.println("TERMINOU DE ESCREVER NO RFID");

}
