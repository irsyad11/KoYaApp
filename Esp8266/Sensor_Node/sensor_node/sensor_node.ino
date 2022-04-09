#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

/*Konfigurasi PIN DHT11
 * Vcc    -> 3.3V
 * out   -> D7
 * GND    -> GND
 */

/*Konfigurasi PIN mq-135
 * Vcc    -> 5V
 * A0   -> A0
 * GND    -> GND
 */

//millis define
unsigned long interval_1=1000;
unsigned long previousMillis_1=0;
 
unsigned long interval_2=10000;
unsigned long previousMillis_2=0;

//Led Define
#define LEDPWR D1
#define LEDSEND D2

//wifi
const char* ssid = "IOT"; //Enter SSID
const char* password = "12345678"; //Enter Password

//DHT11
#define DHTPIN D7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float h, t;
const float humidityCorrectionPercentage = -0.25;

//mqtt
const char* mqttBroker = "test.mosquitto.org";
WiFiClient client;
PubSubClient mqtt(client);

#define KoyaId 1

//deklarasi json document
DynamicJsonDocument doc(100);
 
// parameter sensor MQ-135
const int gasPin = A0;
float vrl, rs, ratio;
float ppm;

int rl , i;
float m, b, ro;
 
// parameter kalman filter amonia(1)
float sensorData1, kalmanFilterData1;
float xt1, xt_update1, xt_prev1;
float pt1, pt_update1, pt_prev1;
float kt1, R1, Q1;

// parameter kalman filter Suhu dan Kelembaban(2 & 3)
float sensorData2, kalmanFilterData2;
float xt2, xt_update2, xt_prev2;
float pt2, pt_update2, pt_prev2;
float kt2, R2, Q2;

float sensorData3, kalmanFilterData3;
float xt3, xt_update3, xt_prev3;
float pt3, pt_update3, pt_prev3;
float kt3;


int cases;

void wifiConnect();
void connect_mqtt();

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
    if(mqtt.connect("esp8266")) {
    }
  }
}

double round2(double value) {
   return (int)(value * 100 + 0.5) / 100.0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPWR, OUTPUT);
  pinMode(LEDSEND, OUTPUT);

  wifiConnect();
  mqtt.setServer(mqttBroker, 1883);
  dht.begin();
  
  rl = 10;
  m = -0.471;
  b = 0.425;
  ro = 17.81;
  
  R1=0.1;
  Q1=0.1;

  R2=0.1;
  Q2=0.01;
  
  
  pt_prev1=1;
  pt_prev2=1;
  pt_prev3=1;

  for (int times  = 1; times <=5; times++) {
    Serial.println();
    Serial.println("Pre Heating Sensor MQ_135");
    Serial.print("Countdown : ");
    Serial.print(times);
    Serial.println(" Seconds");
    delay(1000);
  }

  Serial.println("Go..!!");
}


  
void loop() {
  unsigned long currentTime = millis();

//Event 1
  if(currentTime - previousMillis_1 >=interval_1  ){
    // pembacaan data amonia:
    vrl = analogRead(gasPin)*(5/1023.0);
    rs = (5.0/vrl-1)*10;
    ratio = rs/ro;
    ppm = pow(10,((log10(ratio)-b)/m));
  
    while (isnan(ppm)){
    vrl = analogRead(gasPin)*(5/1023.0);
    rs = (5.0/vrl-1)*10;
    ratio = rs/ro;
    ppm = pow(10,((log10(ratio)-b)/m));
    delay(500);
    }
  
    t = dht.readTemperature();
    while(isnan(t)){
      t = dht.readTemperature();
    }
  
    h = dht.readHumidity();
    h = h + h * humidityCorrectionPercentage;
    while(isnan(h)){
    h = dht.readHumidity();
    h = h + h * humidityCorrectionPercentage;  
    }
    
    sensorData1 = ppm;
    sensorData2 = t;
    sensorData3 = h;
  
    // kalman filter case 1
    xt_update1 = xt_prev1;
    pt_update1 = pt_prev1 + Q1;
    kt1 = pt_update1/(pt_update1 + R1);
    xt1 = xt_update1 + (kt1 * (sensorData1 - xt_update1));
    pt1 = (1-kt1)*pt_update1;
   
    xt_prev1 = xt1;
    pt_prev1 = pt1;
   
    kalmanFilterData1 = xt1;
  
    // kalman filter case 2
    xt_update2 = xt_prev2;
    pt_update2 = pt_prev2 + Q2;
    kt2 = pt_update2/(pt_update2 + R2);
    xt2 = xt_update2 + (kt2 * (sensorData2 - xt_update2));
    pt2 = (1-kt2)*pt_update2;
   
    xt_prev2 = xt2;
    pt_prev2 = pt2;
   
    kalmanFilterData2 = xt2;
  
    // kalman filter case 3
    xt_update3 = xt_prev3;
    pt_update3 = pt_prev3 + Q2;
    kt3 = pt_update3/(pt_update3 + R2);
    xt3 = xt_update3 + (kt3 * (sensorData3 - xt_update3));
    pt3 = (1-kt3)*pt_update3;
  
    xt_prev3 = xt3;
    pt_prev3 = pt3;
   
    kalmanFilterData3 = xt3;
    
    Serial.println("--------------------");
    Serial.println("testing KF");
    Serial.print("Amonia : ");
    Serial.println(sensorData1,3);
    Serial.print("Amonia KF  : ");
    Serial.println(kalmanFilterData1,3);
    Serial.print("Suhu : ");
    Serial.println(sensorData2,3);
    Serial.print("Suhu KF : ");
    Serial.println(kalmanFilterData2,3);
    Serial.print("Kelembaban : ");
    Serial.println(sensorData3,3);
    Serial.print("Kelembaban KF : ");
    Serial.println(kalmanFilterData3,3);
    Serial.println();
    
    previousMillis_1 = currentTime;
  }
  
  if (currentTime-previousMillis_2 >= interval_2) {
    if(!mqtt.connected()) {
    connect_mqtt();
    Serial.println();
    Serial.println("mqtt Connected");
    }
    
    digitalWrite(LEDSEND, HIGH); // turn the LED Green on
    doc["amonia"]= round2(kalmanFilterData1);
    doc["temperature"]= round2(kalmanFilterData2);
    doc["humidity"]= round2(kalmanFilterData3);
    doc["id"]= KoyaId;
  
    char buff[100];
    
    serializeJson(doc, buff);
    mqtt.publish("KoYaApp_1", buff);
    mqtt.publish("KoYaAppSensor", buff);
    digitalWrite(LEDSEND, LOW); // turn the LED Green off  
    memset(buff, 0, sizeof(buff));

    previousMillis_2 = currentTime;
  }
  
  //delayMicroseconds(10);
  
  //Serial.print("Distance: ");
  //Serial.println(distance);
}
