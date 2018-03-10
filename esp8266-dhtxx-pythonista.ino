#include <ESP8266WiFi.h>
#include <WiFiUDP.h>


#include "DHT.h"
#define DHTPIN D4       // PIN SENSOR 

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22 
//#define DHTTYPE DHT21 // DHT 21

DHT dht(DHTPIN, DHTTYPE);

WiFiUDP UDP;                              //
char buff[16];                            //
const char ssid[]="WEMOS";              // wifi ssid
const char pass[]="12345678";             // wifi password
const char iPhoneIP[]   = "192.168.4.2";  // iPhone/Ipad iP
const int  iPhoneTxPort = 7000;           // UDP Tx port
const int  iPhoneRxPort = 9000;           // UDP Rx port
long t = 2000;                            //time

void setup() {
   Serial.begin(9600);
   dht.begin();

   WiFi.softAP(ssid, pass);               // WiFi connect
   UDP.begin(iPhoneTxPort);               // iPhoneTxPort
   
}

void loop() {
    ESP.wdtDisable();                              //
    int rx = UDP.parsePacket();                    // packet size
    if (rx){                                       // recive
      int len = UDP.read(buff, rx);                // rx lengs
      if (len > 0){                                // rx action
        buff[len] = '\0';                          // Termination char
        int c = buff[0];                           // header
        String r = "0";                            // No
        if ( c == '1' ){ r = "1"; t = 2*1000;}     // 1,  3 sec
        if ( c == '2' ){ r = "2"; t = 5*1000;}  // 2,  30 sec
        if ( c == '3' ){ r = "3"; t = 7*1000;} // 3,  1 min
        String data = "t/" + r +"/ / ";
        UDP.beginPacket(iPhoneIP, iPhoneRxPort);   // UDP port
        UDP.print(data);                           // Tx  data
        UDP.endPacket();                           // end packet
        //-----------------------------------------// UDP Transmitt   
        c = '9';                                   //
     }
    }
    delay(t);
    report();
}

void report(){
    ESP.wdtDisable();
    String t = String(dht.readTemperature());    //Humidity
    String h = String(dht.readHumidity()); //Temperature
    String c = String(int(millis()/1000));    //count
    String data = "d/" + t + "/" + h ;        // id+tempe+humid
    Serial.println(data);
    //-------------------------------------//UDP transmitt
    UDP.beginPacket(iPhoneIP, iPhoneRxPort);// UDP port
    UDP.print(data);                       // Tx  data
    UDP.endPacket();                       // end packet
  }

