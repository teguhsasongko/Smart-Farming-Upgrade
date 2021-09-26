#include <Wire.h>
#include <ESP8266WiFi.h>
const char* ssid     = "localhost";
const char* password = "27BF7F16";
const char* host = "192.168.1.9";
const int port = 80;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Pengukuran Air
const int trigPin = D12;
const int echoPin = D11;
const int buzzer = D4;
long duration;
int distance;

//pengukuran Pupuk
const int trig2Pin = D10;
const int echo2Pin = D9;
const int buzzer2 = D5;
long duration2;
int distance2;

WiFiClient client;
void setup()
{
  Serial.begin(9600); 
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
  
  pinMode(trigPin, OUTPUT); //Pengukuran Air
  pinMode(echoPin, INPUT);// Pengukuran Air
  pinMode(trig2Pin, OUTPUT); //Pengukuran Air
  pinMode(echo2Pin, INPUT);// Pengukuran Air
  pinMode(buzzer, OUTPUT); // buzzer Air
  pinMode(buzzer2, OUTPUT); // buzzer pupuk
}

void loop()
{
  if (!client.connect(host, port)) {
    Serial.println("Connection failed");
    return;
  }
  // Sensor Ultrasonik Air
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration*0.034/2;
  Serial.print("Jarak Air: "); 
  Serial.println(distance);
  
  // Sensor Ultrasonik Pupuk
  digitalWrite(trig2Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2Pin, LOW);
  duration2 = pulseIn(echo2Pin, HIGH); 
  distance2 = duration2*0.034/2; 
  Serial.print("Jarak Pupuk: "); 
  Serial.println(distance2); 

  kirim();
  delay(3000);
}

void kirim()   //CONNECTING WITH MYSQL
 { 
String apiUrl = "/lomba/airpupuk.php?";
  apiUrl += "data0="+String(distance);
  apiUrl += "&data1="+String(distance2);

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
