#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include "WIFI_config.h";
Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800); //Configure LED Strip Variable

const char *prefix = "http://"; //Comes before URL
const char *postfix ="/api/job"; //Comes after URL
String octoip_files = prefix +octoip+ postfix; //set URL together
WiFiServer server(80);//Port 80 for http stuff
String header;

WiFiClient client;

float progress_completion = 0;//Completion
float led_calc = 0;//
int wifi_wait= 0;//Time to Connect to Wifi

//Start Value of LEDs 
int LED_R = 0;
int LED_G = 0;
int LED_B = 0;
          
void setup() {
      Serial.begin(115200);
        strip.begin();
        strip.clear();
        strip.show();

      WiFi.mode(WIFI_STA);//Set WiFi mode
      WiFi.disconnect();
      delay(100);  
      Serial.print("Connecting to: ");
      Serial.println(ssid);
        WiFi.begin(ssid, password);
      
        while (WiFi.status() != WL_CONNECTED)
        {//Until Wifi is not Connected Draw Dots in Serial Monitor % on LED Strip
          Serial.print(".");
            wifi_wait++;
            strip.fill(strip.Color(50,50,50), 0, wifi_wait);
            strip.show();
            delay(500);
        }
            strip.clear();
            strip.show();
            
        Serial.println("");
        Serial.println("WLAN Verbunden");
        Serial.println("Ip addresse: ");
          IPAddress ip = WiFi.localIP();//Ip Adresse einer Variable zuweisen
        Serial.println(ip);//Ip Adresse ausgeben
      server.begin();
}
void loop() {

          API_JOB_CHECK(); 
          
WiFiClient client = server.available();   // Auf Clients (Server-Aufrufe) warten
  if (client) {                             // Bei einem Aufruf des Servers
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
            // Die Webseite anzeigen
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"1\">");
            client.println("<link rel=\"icon\" href=\"data:,\"></head>");
 
              client.print("Progress: "); 
                client.println(progress_completion);
            client.println("<br>");
              client.print("Leds: ");
                client.println(NUM_LEDS);
            client.println("<br>");
              client.print("Leds Clac: ");
                client.println(led_calc);    
          client.stop();
  }


      
}
