import netP5.*;
import oscP5.*;

import processing.serial.*;

OscP5 oscP5;

Serial port;  // Create object from Serial class
int end = 10;
String serial;
NetAddress puredata;
String portName = Serial.list()[1];

void setup()  
{
  
  
  port = new Serial(this, portName, 9600);
  port.clear();
   
  //serial = port.readStringUntil(end);
  serial = null;
  
  // Leitura 
  oscP5 = new OscP5(this, 3700);
  
  // Envio
  puredata = new NetAddress("192.168.4.255", 57500);

 size(200, 200);
 frameRate(10);
 // Open the port that the board is connected to and use the same speed (9600 bps)
 //port.bufferUntil('\n');
}

void draw()
{  
 
  delay(100);
    while(port.available() > 0) {
      serial = port.readStringUntil(end);
    }
    
    if (serial != null) {
      oscP5.send(new OscMessage("apertouBotao"), puredata);
      
      print(serial);
      serial = null;
    }
  
} 

//void oscEvent(OscMessage theOscMessage) { 

////if(theOscMessage.checkAddrPattern("/wiimote1")==true) {

//  println(" Axe X = " + theOscMessage);
//  return;
////}

//}