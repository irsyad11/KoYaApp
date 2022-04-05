
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#define DHTPIN D7
#define DHTTYPE DHT11

#define LEDPWR D1
#define LEDSEND D2


#define KoyaId 1

DHT dht(DHTPIN, DHTTYPE);


//MQ135 stuff
#define rl 10 //nilai RL pada sensor 10K
#define m -0.471 //hasil perhitungan gradien
#define b 0.425 //hasil perhitungan perpotongan
#define ro 17.81 // hasil Pengukuran RO
#define mqSensor A0 //mendefinisikan mqSensor sebagai pin a0

//variabel Global
float h,
      t;


//variabel for kf Amonia
float x_med_g, 
      x_prev_g, 
      x_now_g, 
      p_med_g, 
      p_prev_g, 
      p_now_g, 
      kt_g;
      
//variabel for kf temprature
float x_med_t, 
      x_prev_t, 
      x_now_t, 
      p_med_t, 
      p_prev_t, 
      p_now_t, 
      kt_t;

//variabel for kf humadity
float x_med_h, 
      x_prev_h, 
      x_now_h, 
      p_med_h, 
      p_prev_h, 
      p_now_h, 
      kt_h;



//variable untuk KF
float qt = 0.00000001;
float rt = 0.00001;

//wifi
const char* ssid = "IOT"; //Enter SSID
const char* password = "12345678"; //Enter Password

//mqtt
const char* mqttBroker = "test.mosquitto.org";
WiFiClient client;
PubSubClient mqtt(client);

//deklarasi json document
DynamicJsonDocument doc(100);

unsigned long lastMsg = 0;

void wifiConnect();
void connect_mqtt();

void setup() {
  Serial.begin(115200);
  pinMode(LEDPWR, OUTPUT);
  pinMode(LEDSEND, OUTPUT);
  digitalWrite(LEDPWR, HIGH); // turn the LED on
  dht.begin();
  wifiConnect();
  mqtt.setServer(mqttBroker, 1883);

  for (int times  = 1; times <=3; times++) {
    Serial.println();
    Serial.println("Pre Heating Sensor MQ_135");
    Serial.print("Countdown : ");
    Serial.print(times);
    Serial.println(" Seconds");
    delay(1000);
  }

  Serial.println("Go..!!");
}

// the loop function runs over and over again forever
void loop() {
  //variable for mq135
  float vrl, rs, ratio, ppm;

//  connect dengan broker
  if(!mqtt.connected()) {
    connect_mqtt();
    Serial.println();
    Serial.println("mqtt Connected");
  }
  
//Pembacaan data PPM sensor mq135
  vrl = analogRead(mqSensor) * (5/1023.0); //konversi analog ke tegangan
  rs = (5.0/vrl - 1) * 10; //rumus untuk mencari nilai RS
  ratio = rs/ro; //rumus untuk mencari Ratio
  ppm = pow(10, ((log10(ratio)-b)/m)); //rumus mencari ppm

  

//pembacaan data sensor DHT11
  h = dht.readHumidity();
  t = dht.readTemperature();
  int i = 0;


  if(i == 0){
    x_prev_t = t;
    p_prev_t = 0;
    x_prev_h = h;
    p_prev_h = 0;
    x_prev_g = ppm;
    p_prev_g = 0;
  }
//  Kalman Filter for Amonia
  //  predict State Amonia
  x_med_g = x_prev_g;
  p_med_g = p_prev_g + qt;

  // Update State
  kt_g    = p_med_g / (p_med_g + rt);
  x_now_g = x_med_g + (kt_g * (ppm + x_med_g));
  p_now_g = (1 - kt_g) * p_med_g;

  // previous variable update
  x_prev_g = x_now_g;
  p_prev_g = x_now_g;
  
//  Kalman Filter for temprature  
  //  predict State temprature
  x_med_t = x_prev_t;
  p_med_t = p_prev_t + qt;
  
  //  Update State
  kt_t    = p_med_t / (p_med_t + rt);
  x_now_t = x_med_t + (kt_t * (t + x_med_t));
  p_now_t = (1 - kt_t) * p_med_t;

  //  previous variabel update
  x_prev_t = x_now_t;
  p_prev_t = p_now_t; 

//  Kalman Filter for humadity
  //  predict State temprature
  x_med_h = x_prev_h;
  p_med_h = p_prev_h + qt;
  
  //  Update State
  kt_h    = p_med_h / (p_med_h + rt);
  x_now_h = x_med_h + (kt_h * (h + x_med_h));
  p_now_h = (1 - kt_h) * p_med_h;

  //  previous variabel update
  x_prev_h = x_now_h;
  p_prev_h = p_now_h; 
  
  i=1;



//Print result measurement without kalman
  Serial.println("------------- Real Sensor Data ------------");
  Serial.print("Temprature  : ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Humadity    : ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Amonia      : ");
  Serial.print(ppm);
  Serial.println(" PPM");
  Serial.println("---------------------------------------------------------------------------------------");

//Print Result Measurement with Kalman Filter
  Serial.println("------------- Data Sensor with Kalman Filter  ------------");
  Serial.print("Temprature  : ");
  Serial.print(x_now_t);
  Serial.println("°C");
  Serial.print("Humadity    : ");
  Serial.print(x_now_h);
  Serial.println("%");
  Serial.print("Amonia      : ");
  Serial.print(x_now_g);
  Serial.println(" PPM");
  Serial.println("---------------------------------------------------------------------------------------");

//memasukkan variabel kedalam json
  doc["temperature"] = x_now_t;
  doc["humidity"] = x_now_h;
  doc["amonia"] = x_now_g;
  doc["id"] = KoyaId;
  
  char buffer[100];
  
  serializeJson(doc, buffer);
  digitalWrite(LEDSEND, HIGH); // turn the LED Green on
  mqtt.publish("KoYaApp_1", buffer);
  mqtt.publish("KoYaAppSensor", buffer);
  delay(1000);
  digitalWrite(LEDSEND, LOW); // turn the LED Green off

  delay(9000);
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
    if(mqtt.connect("esp8266")) {
    }
  }
}
