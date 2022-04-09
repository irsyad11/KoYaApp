#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

/*Konfigurasi PIN
 * DHT11 - ESP8266
 * Vcc    -> 3.3V
 * out   -> D7
 * GND    -> GND
 */

#define DHTPIN D7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float t;

//wifi
const char* ssid = "IOT"; //Enter SSID
const char* password = "12345678"; //Enter Password

//mqtt
const char* mqttBroker = "test.mosquitto.org";
WiFiClient client;
PubSubClient mqtt(client);

//deklarasi json document
DynamicJsonDocument doc(100);
 
// parameter kalman filter case 1
float sensorData, kalmanFilterData1;
float xt1, xt_update1, xt_prev1;
float pt1, pt_update1, pt_prev1;
float kt1, R1, Q1;

// parameter kalman filter case 2
float kalmanFilterData2;
float xt2, xt_update2, xt_prev2;
float pt2, pt_update2, pt_prev2;
float kt2, R2, Q2;

// parameter kalman filter case 3
float kalmanFilterData3;
float xt3, xt_update3, xt_prev3;
float pt3, pt_update3, pt_prev3;
float kt3, R3, Q3;

// parameter kalman filter case 4
float kalmanFilterData4;
float xt4, xt_update4, xt_prev4;
float pt4, pt_update4, pt_prev4;
float kt4, R4, Q4;

// parameter kalman filter case 4
float kalmanFilterData5;
float xt5, xt_update5, xt_prev5;
float pt5, pt_update5, pt_prev5;
float kt5, R5, Q5;


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

  wifiConnect();
  mqtt.setServer(mqttBroker, 1883);
  dht.begin();
  
  R1=0.00001;
  Q1=0.00000001;

  R2=0.1;
  Q2=0.01;
  
  R3=1;
  Q3=0.01;

  R4=0.01;
  Q4=0.01;

  R5=0.1;
  Q5=0.1;
  
  pt_prev1=1;
  pt_prev2=1;
  pt_prev3=1;
  pt_prev4=1;
  pt_prev5=1;
}


  
void loop() {
  if(!mqtt.connected()) {
    connect_mqtt();
    Serial.println();
    Serial.println("mqtt Connected");
  }
  // put your main code here, to run repeatedly:
  t = dht.readTemperature();

  while (isnan(t)){
  t=dht.readTemperature();
  delay(500);
  }
 
  sensorData = t;

  // kalman filter case 1
  xt_update1 = xt_prev1;
  pt_update1 = pt_prev1 + Q1;
  kt1 = pt_update1/(pt_update1 + R1);
  xt1 = xt_update1 + (kt1 * (sensorData - xt_update1));
  pt1 = (1-kt1)*pt_update1;
 
  xt_prev1 = xt1;
  pt_prev1 = pt1;
 
  kalmanFilterData1 = xt1;

  // kalman filter case 2
  xt_update2 = xt_prev2;
  pt_update2 = pt_prev2 + Q2;
  kt2 = pt_update2/(pt_update2 + R2);
  xt2 = xt_update2 + (kt2 * (sensorData - xt_update2));
  pt2 = (1-kt2)*pt_update2;
 
  xt_prev2 = xt2;
  pt_prev2 = pt2;
 
  kalmanFilterData2 = xt2;

  // kalman filter case 3
  xt_update3 = xt_prev3;
  pt_update3 = pt_prev3 + Q3;
  kt3 = pt_update3/(pt_update3 + R3);
  xt3 = xt_update3 + (kt3 * (sensorData - xt_update3));
  pt3 = (1-kt3)*pt_update3;

  xt_prev3 = xt3;
  pt_prev3 = pt3;
 
  kalmanFilterData3 = xt3;

  // kalman filter case 4
  xt_update4 = xt_prev4;
  pt_update4 = pt_prev4 + Q4;
  kt4 = pt_update4/(pt_update4 + R4);
  xt4 = xt_update4 + (kt4 * (sensorData - xt_update4));
  pt4 = (1-kt4)*pt_update4;
 
  xt_prev4 = xt4;
  pt_prev4 = pt4;
 
  kalmanFilterData4 = xt4;

  // kalman filter case 5
  xt_update5 = xt_prev5;
  pt_update5 = pt_prev5 + Q5;
  kt5 = pt_update5/(pt_update5 + R5);
  xt5 = xt_update5 + (kt5 * (sensorData - xt_update5));
  pt5 = (1-kt5)*pt_update5;
 
  xt_prev5 = xt5;
  pt_prev5 = pt5;
 
  kalmanFilterData5 = xt5;
  
  Serial.println("--------------------");
  Serial.println("testing KF");
  Serial.println(sensorData,3);
  Serial.print("KF 1 : ");
  Serial.print(kalmanFilterData1,3);
  Serial.println();
  Serial.print("KF 2 : ");
  Serial.print(kalmanFilterData2,3);
  Serial.println();
  Serial.print("KF 3 : ");
  Serial.print(kalmanFilterData3,3);
  Serial.println();
  Serial.print("KF 4 : ");
  Serial.print(kalmanFilterData4,3);
  Serial.println();
  Serial.print("KF 5 : ");
  Serial.print(kalmanFilterData5,3);
  Serial.println();

  doc["kd1"]= round2(kalmanFilterData1);
  doc["kd2"]= round2(kalmanFilterData2);
  doc["kd3"]= round2(kalmanFilterData3);
  doc["kd4"]= round2(kalmanFilterData4);
  doc["kd5"]= round2(kalmanFilterData5);
  doc["rd"]= round2(sensorData);

  char buff[100];
  serializeJson(doc, buff);
  mqtt.publish("KoyaAppKalmanTest", buff);
  memset(buff, 0, sizeof(buff));

  delay(5000);
  //delayMicroseconds(10);
  
  //Serial.print("Distance: ");
  //Serial.println(distance);
}
