#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "";   // nama ssid dari wi-fi, jangan lebih dari 32 karakter
const char *pass =  "";   // password dari wi-fi
 
//------------------------------ Konfigurasi Broker
const char *mqtt_server = "";
const int mqtt_port = ;
const char *mqtt_user = "";
const char *mqtt_pass = "";
//------------------------------ End Konfigurasi Broker


char buffer[10];
 
//deklarasi konfigurasi server
WiFiClient wclient;
PubSubClient client(wclient, mqtt_server, mqtt_port);

void setup() {
  Serial.begin(115200);
  delay(10);
}

 
void loop() {
  //----------------- cek apakah wi-fi sudah tersambung
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Menghubungkan ke ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);
 
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("Wi-Fi Terhubung");
    Serial.println(WiFi.macAddress());
  }
  //----------------- End cek apakah wi-fi sudah tersambung
 
  //---------------- cek apakah ESP sudah tersambung dengan server
  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      Serial.println("Menghubungkan dengan MQTT Server");
      Serial.println(WiFi.macAddress());
      if (client.connect(MQTT::Connect("webinar_rcsf_sensor").set_auth(mqtt_user, mqtt_pass))) {
        Serial.println("Terhubung dengan MQTT Server");       
      } else {
        Serial.println("Tidak dapa terhubung dengan MQTT Server");   
      }
    }
    //--------------- cek apakah ESP sudah tersambung dengan server  
    if (client.connected())
    {
      int val = analogRead(A0);  
      dtostrf(val,5, 0, buffer);      
      client.publish("/sensor/suhu", buffer);
      delay(1000);      
    }
     
    client.loop();      
  }
}
