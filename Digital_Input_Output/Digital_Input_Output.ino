#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int lampu = 4;

const char *ssid =  "";   // nama ssid dari wi-fi, jangan lebih dari 32 karakter
const char *pass =  "";   // password dari wi-fi
 
//------------------------------ Konfigurasi Broker
const char *mqtt_server = "";
const int mqtt_port = ;
const char *mqtt_user = "";
const char *mqtt_pass = "";
//------------------------------ End Konfigurasi Broker
 
 
//deklarasi konfigurasi server
WiFiClient wclient;
PubSubClient client(wclient, mqtt_server, mqtt_port);

//---------------- fungsi untuk menerima nilai balik (subcribe)
void callback(const MQTT::Publish& pub) {
  Serial.println(pub.payload_string()); 
  String value = pub.payload_string();
  if(value == "1")
  {
    LAMPU_ON();
    client.publish("/rumah/lampukamar/status", "ON");
  }
  else if(value == "0")
  {
    LAMPU_OFF();
    client.publish("/rumah/lampukamar/status", "OFF");
  }
}
//---------------- End fungsi untuk menerima nilai balik (subcribe)

char buffer[10];
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(lampu, OUTPUT);
  digitalWrite(lampu, HIGH);
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
      if (client.connect(MQTT::Connect("webinar_rcsf_lampu").set_auth(mqtt_user, mqtt_pass))) {
        Serial.println("Terhubung dengan MQTT Server");
        client.subscribe("/rumah/lampukamar");
        client.set_callback(callback);
      } else {
        Serial.println("Tidak dapa terhubung dengan MQTT Server");   
      }
    }
    //--------------- cek apakah ESP sudah tersambung dengan server   
    client.loop();      
  }
}
