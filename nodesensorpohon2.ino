#include <Wire.h>
#include <ESP8266WiFi.h>
const char* ssid     = "localhost";
const char* password = "";
const char* host = "192.168.1.9";
const int port = 80;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

int sensorPin = A0;
int nilai;
float temp = 0;
float humid = 0;

//PH Tanah Init
#define analogInPin A0
int sensorValue = 0;        
float outputValue = 0.0; 

//Humidity Library
#include <DHT.h> // sensor library using lib from https://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
#define DHTPIN D3     // DHT PIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE); //Sensor initiation

WiFiClient client;
void setup()
{
  Serial.begin(115200); 
  dht.begin();
  Serial.println("Program started");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(sensorPin, INPUT); // Kelembaban 1
}

void loop()
{
  if (!client.connect(host, port)) {
    Serial.println("Connection failed");
    return;
  }
  // Sensor PH
  sensorValue = analogRead(analogInPin);
  outputValue = ((sensorValue*(0.01388))-(-4.1388))+0.3;
   Serial.print("adc = ");
   Serial.print(sensorValue);
   Serial.print("pH = ");
   Serial.println(outputValue);
   delay(1000);
   
  //DHT22
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  temp = t;
  humid = h;
  
  //cek hasil pembacaan dan tampilkan bila ada
  if(isnan(t) || isnan(h)){
    Serial.println("Gagal membaca data dari DHT11");
    delay(200);
    }
  else{
    Serial.print("Humidity: ");//kelembapan
    Serial.print(h);
    Serial.print(" | ");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C | ");
    delay(100);
   }
   
  // Pengukuran Kelembaban Tanah
  nilai = analogRead(sensorPin); 
    Serial.print("Pohon 1 = ");
    Serial.println(nilai);
    
  kirim();
  delay(5000);
}

void kirim()   //CONNECTING WITH MYSQL
 { 
String apiUrl = "/lomba/pohon2.php?";
  apiUrl += "data0="+String(nilai);
  apiUrl += "&data1="+String(outputValue);
  apiUrl += "&data2="+String(humid);
  apiUrl += "&data3="+String(temp);
//  apiUrl += "&data4="+String(kondisi);

  // Set header Request
  client.print(String("GET ") + apiUrl + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.print(apiUrl);
  
//   Pastikan tidak berlarut-larut
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      Serial.println(">>> Operation failed !");
      client.stop();
      return;
    }
  }
  
  // Baca hasil balasan dari PHP
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }             
} 
