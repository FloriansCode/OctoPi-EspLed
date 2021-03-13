//CONFIG FILE//
//Wifi Config
const char* ssid = "YOUR_WIFI_NAME_HERE";                //WiFi Name
const char*  password = "YOUR_WIFI_PASSWORD_HERE"; //Wifi Password

//Octoprint Config
String octoip = "octopi.local";                         //Octoprint Ip-Adress
const char* APIKEY = "YOUR_APIKEY_HERE";  //Octoprint API or Application Key.

//LED Config
#define DATA_PIN    D6    //Connected DATA PIN
#define NUM_LEDS    20    //Nummers of LEDs

#define start_LED 0 //Start of LEDs to Show Progress (First LED ist 0)

#define end_LED 20   //End of LEDs to Show Progress
