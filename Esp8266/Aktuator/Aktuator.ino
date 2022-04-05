#include <ESP8266WiFi.h>
#include <RBDdimmer.h>
#include <Fuzzy.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

//Deklarasi WiFi
const char* ssid = "IOT";
const char* password = "12345678";
WiFiClient client;

//Deklarasi MQTT
const char* mqttBroker = "test.mosquitto.org";
PubSubClient mqtt(client);

//Deklarasi JSON Document
DynamicJsonDocument doc(100);
DynamicJsonDocument doc1(100);

//Deklarasi id aktuator
#define KoyaId 1

//inisiasi LED
#define LEDPWR D3
#define LEDSEND D7


//---------Inisiasi Dimmer ----------
#define outputPin 12
#define zerocross 5
dimmerLamp dimmer(outputPin, zerocross);
int oLampu;

//-------- Inisiasi Relay--------
const int relay1 = 14;
const int relay2 = 4;

float oKipas, oFogger;



//-----inisiasi variabel parameter kondisi lingkungan 
float temperature, humidity;
float nh3;

//------------ inisiasi Fuzzy dan Set nilai tiap Variabel ------------
Fuzzy *fuzzy = new Fuzzy();

//fuzzy input
FuzzySet *dingin        = new FuzzySet(0, 0, 25, 32);
FuzzySet *normal        = new FuzzySet(25, 32, 33, 40);
FuzzySet *panas         = new FuzzySet(23, 40, 50, 500);

//Fuzzy Input
FuzzySet *rendah        = new FuzzySet(0, 0, 20, 30);
FuzzySet *lembab        = new FuzzySet(20, 30, 50, 60);
FuzzySet *tinggi        = new FuzzySet(50, 60, 70, 70);

//Fuzzy Input
FuzzySet *aman          = new FuzzySet(0, 0, 5, 11);
FuzzySet *bahaya        = new FuzzySet(5, 11, 20, 20);

//Fuzzy Output
FuzzySet *redup         = new FuzzySet(1, 1, 1, 40);
FuzzySet *sedang        = new FuzzySet(1, 40, 60,99);
FuzzySet *terang        = new FuzzySet(60 ,99, 99, 99);

//Fuzzy output
FuzzySet *kipasA        = new FuzzySet(1, 1, 1, 1);
FuzzySet *kipasP        = new FuzzySet(0, 0, 0, 0);

//Fuzzy Output
FuzzySet *foggerA        = new FuzzySet(1, 1, 1, 1);
FuzzySet *foggerP        = new FuzzySet(0, 0, 0, 0);


//memanggil tab lain
#include "2_fuzzy_set.h"
#include "3_fuzzy_rule.h"
void wifiConnect();
void connect_mqtt();
void callback(char* topic, byte* payload, unsigned int length);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dimmer.begin(NORMAL_MODE, ON);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(LEDPWR, OUTPUT);
  pinMode(LEDSEND, OUTPUT);
  digitalWrite(LEDPWR, HIGH);
  mqtt.setServer(mqttBroker, 1883);
  mqtt.setCallback(callback);
  
  wifiConnect();
  connect_mqtt();
  
  fuzzySet();
  fuzzyRule();
}

void loop() {
  mqtt.loop();
  // put your main code here, to run repeatedly:
//  temperature = random(0, 60);
//  humidity = random(0, 100);
//  nh3 = random(0, 40);

  //---------------------
//  Serial.print("Temperature ");
//  Serial.print(temperature);  Serial.println(" *C");
//  Serial.print("Humidity    ");
//  Serial.print(humidity);     Serial.println(" %");
//  Serial.print("Amonia      ");
//  Serial.print(nh3);            Serial.println(" ppm");
//  Serial.println("");
//
//  
  
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Menghubungkan");

  while (WiFi.status() !=WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Wifi Connected Succes!");
  Serial.print("Node MCU IP ADDRESS : ");
  Serial.println(WiFi.localIP());
}

void connect_mqtt() {
  while(!mqtt.connected()) {
    Serial.println("Connecting MQTT ...");
    if(mqtt.connect("anderson")) {
      mqtt.subscribe("KoYaApp_1"); 
    }
  }
  Serial.println();
  Serial.println("mqtt Connected");
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Data diterima [");
  Serial.print(topic);
  Serial.print("]");
  for (int i=0; i<length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  deserializeJson(doc, payload);
  temperature = doc["temperature"];
  humidity = doc["humidity"];
  nh3 = doc["amonia"];

  digitalWrite(LEDSEND, HIGH);
  delay(1000);
  digitalWrite(LEDSEND, LOW);

  Serial.print("Temperature ");
  Serial.print(temperature);  Serial.println(" *C");
  Serial.print("Humidity    ");
  Serial.print(humidity);     Serial.println(" %");
  Serial.print("Amonia      ");
  Serial.print(nh3);            Serial.println(" ppm");
  Serial.println("");

  fuzzy->setInput(1, temperature);
  fuzzy->setInput(2, humidity);
  fuzzy->setInput(3, nh3);
  
  fuzzy->fuzzify();

  oLampu = fuzzy->defuzzify(1);
  oKipas = fuzzy->defuzzify(2);
  oFogger = fuzzy->defuzzify(3);

  doc1["lamp"] = oLampu;
  doc1["fan"] = oKipas;
  doc1["fogger"] = oFogger;
  doc1["id"] = KoyaId;
  

  char buffer[100];

  serializeJson(doc1, buffer);
  mqtt.publish("KoYaAppAktuator", buffer);
  
  dimmer.setPower(oLampu);
  if (oKipas == 1) {
    digitalWrite(relay1, LOW);
  } else {
    digitalWrite(relay1, HIGH);
  }

  if(oFogger == 1) {
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay2, HIGH);
  }
  
  
  // Set output vlaue: LAMPU
  //    int maplampu = map (lampu, 0, 2000, 1, 99);
  //    dimmer.setPower(maplampu);                        //(1%-99%)
  Serial.println("Result: ");
  Serial.print("       Lampu: ");
  Serial.println(oLampu);
  Serial.print("       kipas: ");
  Serial.println(oKipas);
  Serial.print("       fogger: ");
  Serial.println(oFogger);
  if (oKipas == 1) {
    Serial.println("Kipas : Aktif");
  } else {
    Serial.println("Kipas : Padam");
  }
  if (oFogger == 1) {
    Serial.print("Fogger : Aktif");
  } else {
    Serial.print("Fogger : Padam");
  }
  //    Serial.print("       maplampu: ");
  //    Serial.println(maplampu);
  Serial.println("");
  Serial.println("");
}
