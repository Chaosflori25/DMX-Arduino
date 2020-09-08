#include <DMXSerial.h>
#define RELAY1  8                        
#define RELAY2  9
#define DE 3
#define RE 2
#define DEV_VERSION true // test without dmx
#define N                                              //char rxChar= 0;
#define DMX_ADRESS 13
#define Mosfet 16
bool running = false;
int red1, green1, blue1;
void setup()//--------------------------------------setup
{    
Serial.begin(9600);  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(Mosfet, OUTPUT);

 //DMX Setup
 DMXSerial.init(DMXProbe);
 DMXSerial.maxChannel(6);
}
void getdmx(){//------------------------------------getdmx
  if(DEV_VERSION){
    red1 = 0;
    green1 = 0;
    blue1 = 0;
  }
      red1 = DMXSerial.read(DMX_ADRESS+1);
      green1 = DMXSerial.read(DMX_ADRESS+2);
      blue1 = DMXSerial.read(DMX_ADRESS+3);
}
void loop(){//----------------------------------------loop
 if (DMXSerial.receive() || DEV_VERSION) {
  
  if (running == false){  // Bei reconnect
      running = true;
      DMXSerial.receive();
     
//----------------------------------------------------On
      
      if (DMXSerial.read(red1) > 0) {
          digitalWrite(RELAY1,LOW);      
          Serial.println("RELAY 1 turned On");
      } else Serial.println("RELAY 1 already On!");
        
       if (DMXSerial.read(blue1) > 0){ 
          digitalWrite(RELAY1,LOW);      
          Serial.println("RELAY 2 turned On");
       }else Serial.println("RELAY 2 already On!");

//-----------------------------------------------------Off
       
      if  (DMXSerial.read(red1) == 0){ 
           digitalWrite(RELAY1,HIGH);      
           Serial.println("RELAY 1 turned Off");
      } else Serial.println("RELAY 1 already Off!");
        
      if  (DMXSerial.read(blue1) == 0){ 
           digitalWrite(RELAY2,HIGH);      
           Serial.println("RELAY 2 turned Off");
      } else Serial.println("RELAY 2 already Off!");
        
//------------------------------------------------------Mosfet(R1)

    if (digitalRead(RELAY1) == HIGH){
        digitalWrite(Mosfet, LOW); }
    if (digitalRead(RELAY1) == LOW){
        digitalWrite(Mosfet, HIGH);}

//-----------------------------------------------------Mosfet(R2)   
    
    if (digitalRead(RELAY2) == HIGH){
        digitalWrite(Mosfet, LOW); }
    if (digitalRead(RELAY2) == LOW){
        digitalWrite(Mosfet, HIGH);}
        
//-----------------------------------------------------else          
      }else{
    // Wenn kein DMX Signal

      if (DMXSerial.noDataSince()>3000){
        if(running==true){ // Connection Lost
          running = false;// benötigt um reconnect zu erkennen
        }
          delay(5000); //DMX Check alle Sekunde
      }
     }
   }
 }
