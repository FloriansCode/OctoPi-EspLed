#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
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
      WiFi.hostname("OctoPi-EspLed");
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

      ArduinoOTA.setHostname("OctoPi-EspLed");
      ArduinoOTA.begin();
}
void loop() {

          API_JOB_CHECK(); 
          WEBSITE();
          ArduinoOTA.handle();
 
}

//User Website
void WEBSITE(){
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

//http request to get Job Information
void API_JOB_CHECK (){
    HTTPClient http;                        //Preparing the HTTP request.
      http.begin(octoip_files);             //HTTP link
      http.addHeader("X-Api-Key", APIKEY);  //add API KEY
        int httpCode = http.GET();          //Send the request
        String payload = http.getString();  //Get the request response payload
      http.end();   //Close connection

        // Just used: https://arduinojson.org/v6/assistant/ and striped that down
        StaticJsonDocument<768> doc;
        deserializeJson(doc, payload);      
          JsonObject job = doc["job"];
          JsonObject progress = doc["progress"];    
            progress_completion = progress["completion"]; //Progressbar in %
            String state = doc["state"]; // State of the Printer
            String pre_state = "waiting";
          //Serial Print status.
          Serial.print("Status: ");
          Serial.println(state);
                    Serial.print("URL: ");
          Serial.println(octoip_files);

            if((state == "Operational") or (state == "Paused"))
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Operational();
              pre_state= state;
              }
            else if(state == "Printing")
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Printing();
              pre_state= state;
              }
              else if(state == "Finishing")
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Finishing();
              pre_state= state;
              }
            else if(state == "Cancelling")
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Cancelling();
              pre_state= state;
              }
            else
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Offline();
              pre_state= state;
              }
  }

//different Printer states 
void Operational()
{
          //Fade Out
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
        for(LED_R, LED_G, LED_B; LED_R>=1,LED_G>=1, LED_B>=1 ; LED_R--,LED_G--,LED_B-- ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          //Reset Color //to be safe
          LED_R = 0;
          LED_G = 0;
          LED_B = 0;

         //Fade in
         for(LED_R, LED_G, LED_B; LED_R<=50,LED_G<=50, LED_B<=50 ; LED_R++,LED_G++,LED_B++ ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          
}
void Printing()
{
        strip.show();
        led_calc = ((end_LED -start_LED)*  progress_completion) /100;
        //Debug Progress
        //Serial.print("Progress: "); 
        //  Serial.println(progress_completion);
        //Serial.print("Leds: ");
        //  Serial.println(NUM_LEDS);
        //Serial.print("Leds Clac: ");
        //  Serial.println(led_calc);
        
        if(led_calc >=1){
        strip.fill(strip.Color(50,50,50), start_LED, led_calc);
        strip.show();
        }
        else{       //Light up first LED
          strip.clear();
          strip.fill(strip.Color(50,50,50), start_LED, 1);
          strip.show();
          }
        delay(1000);
}
void Finishing()
{
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          
        for(LED_G; LED_G >=0; LED_G--){
          strip.fill(strip.Color(0,LED_G,0), 0, 0);
          strip.show();
          Serial.println(LED_G);
          delay(50);
          }
          LED_G = 0;
          
        for(LED_G; LED_G<=50; LED_G++){
          strip.fill(strip.Color(0,LED_G,0), 0, 0);
          strip.show();
          Serial.println(LED_G);
          delay(50);
          }
          LED_G = 50;         
}

void Cancelling(){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          
        for(LED_R; LED_R >=0; LED_R--){
          strip.fill(strip.Color(LED_R,0,0), 0, 0);
          strip.show();
          Serial.println(LED_R);
          delay(50);
          }
          LED_R = 0;
          
        for(LED_R; LED_R<=50; LED_R++){
          strip.fill(strip.Color(LED_R,0,0), 0, 0);
          strip.show();
          Serial.println(LED_R);
          delay(50);
          }
          LED_R = 50;
}
void Offline(){
          strip.clear();
          strip.show();
}
void FadeOut(){
        for(LED_R, LED_G, LED_B; LED_R>=1,LED_G>=1, LED_B>=1 ; LED_R--,LED_G--,LED_B-- ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          //Reset Color
          LED_R = 0;
          LED_G = 0;
          LED_B = 0;
}
