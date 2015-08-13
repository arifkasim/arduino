/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
 #include <SPI.h>
 //#include "RemoteLogger.h"
//#include <WiFi.h>
#include <string.h>

#include <Print.h>

class RemoteLogger {
  //WiFi connectedWifi;
  const char* ip;
  int port;
  WiFiClient client;
  public:
  RemoteLogger( char* ip, int port )
  {
    //this.connectedWifi = *connectedWifi;
    this->ip = ip;
    this->port = port;
  }
  void concat(char* mainStr, char* auxString)
  {
    
  }
  char* removeSpaces(char *data)
  {
    for (int i=0;i<strlen(data);i++)
    {
      if (data[i]==' ')
        data[i]='_';
    }
    return data;
  }
  
  void secretLog(int last=0)
  {
      WiFiClient client;
    client.connect(this->ip,this->port);
    if (last == 0)
       client.println("GET /secrethello HTTP/1.0");
      else
        client.println("GET /LAST HTTP/1.0");
    client.println();
  }
  void log(char* data)
  {
    
    char cleanedLogData [400]; // = new char[strlen(data)];
    strcpy(cleanedLogData,data);
    removeSpaces(cleanedLogData);
    char payload[450]; // = new char[24+strlen(cleanedLogData)];
    strcpy(payload,"GET /");
    strcat(payload ,cleanedLogData);
    strcat(payload ," HTTP/1.0");

    WiFiClient client;
    client.connect(this->ip,this->port);
    client.println(payload);
    client.println();
  
  }
};




char* ssid     = "XT1095-ahmed"; //"ATT392";
const char* password = "ahmed1234"; //"8088544055";
 
const char* host = "www.adafruit.com";
 WiFiServer server(80);
// RemoteLogger* logger;
 char* uintToCharPtr(uint32_t x, char* buf)
 {
    snprintf(buf, sizeof buf, "%lu", (unsigned long)x);
    return buf;
 }
void setup() {
  delay(10);
 
  // We start by connecting to a WiFi network
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }
 
    server.begin();
  //  logger = new RemoteLogger("192.168.1.76",1337);
   // logger->log("hello");
    ////Serial.print("Connected to wifi. My address:");
    IPAddress ipAddr = WiFi.localIP();
  
    //Serial.println(myAddress);
    WiFiClient client;
    char firstOctate[4];
    char secondOctate[4];
    char thirdOctate[4];
    char fourthOctate[4];
    char ip[16];
  //  snprintf(ip, sizeof ip, "%lu.%lu.%lu.%lu", (unsigned long)ipAddr[0],(unsigned long)ipAddr[1],(unsigned long)ipAddr[2],(unsigned long)ipAddr[3]);
  /*  uintToCharPtr(ipAddr[0],firstOctate);
    uintToCharPtr(ipAddr[1],secondOctate);
    uintToCharPtr(ipAddr[2],thirdOctate);
    uintToCharPtr(ipAddr[3],fourthOctate);

    char logData[400];
    
    strcpy(logData,"ESP8266 is online at ");
   strcat(logData,firstOctate);
   strcat(logData,".");
   strcat(logData,secondOctate);
   strcat(logData,".");
   strcat(logData,thirdOctate);
   strcat(logData,".");
   strcat(logData,fourthOctate);

     logger->log(logData);*/
}
 
int value = 0;
void loop() {
  delay(5000);
  ++value;
  WiFiClient client = server.available();
  if (client) {
    //Serial.println("New client connected");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
           client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<body>Hello from esp8266</body></html>");
          break;
        }
        if (c=='\n') {
          currentLineIsBlank= true;
        }
        else if (c!='\r') {
          currentLineIsBlank=false;
        }
      }
    }
    delay(1);
    client.stop();
  }
  
}

