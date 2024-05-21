
#include <ESP8266WiFi.h>

////////////// Library NETPIE 2020  ///////////////////
#include <PubSubClient.h>
#include <Wire.h>


///////////// ssid password NETPIE2020  //////////////
const char* ssid = "*****" ;
const char* password = "******" ;

////////////////////  variable int to string ////////////
int num1 = 0, pushgreen1 = 0, pushred1 = 0 ;
int allanglerg2 = 0, pgreen1 = 0 , keepallrg2 = 0  ;
/////////////////////// part of NETPIE 2020   ////////////////

////////// Client Token Secret for  Device GY521node1 ////////////
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883 ;
const char* mqtt_Client = "*****";
const char* mqtt_username = "*****";
const char* mqtt_password = "*****";


char msg[100];  ///////  can increase msg[120]
long lastMsg = 0;

WiFiClient espClient;
PubSubClient client(espClient);

///////////// Void of NETPIE2020  ////////////////////
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting NETPIE2020 connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("NETPIE2020 connected");
      client.subscribe("@msg/HMC5883");

    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

// function callback()

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  ////////// Loop Subscribe angle HMC5883L , pushgreen , pushred /////////////
   Serial.println(message);       
       if(String(topic) == "@msg/HMC5883") {
       allanglerg2  =  message.toInt() ; // variable.toInt() string to int
  //    Serial.print(" allanglerg2  is ");
   //   Serial.print(allanglerg2 );
  //    Serial.print("\n");
  }


  ////////// End void callback  /////////////////
}

void setup()
{

  Serial.begin(115200);
  //////////// LED in ESP8266 //////////////
  pinMode(D4, OUTPUT);
  delay(500);


//////////////////////  SETUP LOOP For NETPIE 2020  //////////////////
  Serial.println("Starting...");
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); 


}       /////////////// END  Void SETUP ////////////////////////////


void loop()
{
 //////////////// NETPIE2020 in Void LOOP /////////////////
     if (!client.connected()) {
    reconnect();
  }
  client.loop();  

 ///// if pushgreen or same value send  angle to motor ////
    Serial.print("Send angle HMC to Uno  "); 
    Serial.print(allanglerg2) ;
    Serial.print("\n") ;
    delay(100) ;
    Serial.flush();  
    delay(200) ;  // 100    
    /////////// END checksw1 , send data 1000 to ESP8266 ///////////
 // allanglerg2 = 0 ;

} ///////////////// END Void loop ()  /////////////////////







