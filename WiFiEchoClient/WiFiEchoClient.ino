#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h"   //please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;     // your network SSID (name)
char pass[] = SECRET_PASS;     // your network password

int status = WL_IDLE_STATUS;
IPAddress server(192,168,1,43);  //Rpi server
int port = 4500;

WiFiClient client;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
  }

  if (WiFi.status() == WL_NO_SHIELD) {   // check for the presence of the shield
    Serial.println("WiFi shield not present");
    while (true);                 // don't continue
  }

  while ( status != WL_CONNECTED) {   // attempt to connect to WiFi network
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);      // Connect to WPA/WPA2 network
    delay(5000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();
}


void loop() {
  connectToServer();
  delay(5000);
}


void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void connectToServer(){
  Serial.println("Attempting connection...");
  if (client.connect(server , port)){
    Serial.println("Connection to echoserver successful");
    client.print("hello Rpi");
    int timeOut = millis() + 1000;     //Added timeout client.available() is not reliable
    while (millis()<timeOut){
      if (client.available()){
        char c = client.read();
        Serial.print(c);
      }
    }
    Serial.print("\n");
    client.stop();
    }
}
