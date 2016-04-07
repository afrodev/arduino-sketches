import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import netP5.*; 
import oscP5.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class kitkat_osc_processing extends PApplet {






OscP5 oscP5;

Serial port;  // Create object from Serial class
int end = 10;
String serial;
NetAddress puredata;
String portName = Serial.list()[1];

public void setup()  
{
  
  
  port = new Serial(this, portName, 9600);
  port.clear();
   
  //serial = port.readStringUntil(end);
  serial = null;
  
  // Leitura 
  oscP5 = new OscP5(this, 3700);
  
  // Envio
  puredata = new NetAddress("192.168.4.255", 57500);

 
 frameRate(10);
 // Open the port that the board is connected to and use the same speed (9600 bps)
 //port.bufferUntil('\n');
}

public void draw()
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
  public void settings() {  size(200, 200); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "kitkat_osc_processing" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
