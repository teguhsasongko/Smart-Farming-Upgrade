#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(14,12);

const char* ssid     = "localhost";
const char* password = "";
const char* host = "192.168.1.9";
const int httpPort = 80;

String sentence;
String pohon1;
String ph1;
String humi1;
String tempe1;
String pohon2;
String ph2;
String air;
String pupuk;
String pompaair;
String pompapupuk;

WiFiClient client;
  
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  delay(1000);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  while (!Serial) {; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
 
  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  // We now create a URI for the request
  String url = "/lomba/mainpost.php";
 
  Serial.print("Requesting URL: ");
  Serial.println(url);
 
  // This will send the request to the server
  client.print(String("GET ") + url + "\r\n");
  delay(1000);
  // Read all the lines of the reply from server and print them to Serial
  if (client.available()){
    String line = client.readString();
//    Serial.print(line);
   espSerial.println(line);

    pohon1 = String(getValue(line,' ',0));
    Serial.print("Pohon 1: ");
    Serial.println(pohon1); 

    ph1 = String(getValue(line,' ',1));
    Serial.print("pH Tanah 1:");
    Serial.println(ph1); 

    humi1 = String(getValue(line,' ',2));
    Serial.print("Humidity: ");
    Serial.println(humi1); 

    tempe1 = String(getValue(line,' ',3));
    Serial.print("Suhu:");
    Serial.println(tempe1); 
    
    pohon2 = String(getValue(line,' ',4));
    Serial.print("kelembapan 1: ");
    Serial.println(pohon2); 

    ph2 = String(getValue(line,' ',5));
    Serial.print("pH Tanah:");
    Serial.println(ph2); 
    
    air = String(getValue(line,' ',6));
    Serial.print("Ketersediaan Air: ");
    Serial.println(air); 

    pupuk = String(getValue(line,' ',7));
    Serial.print("Ketersediaan Pupuk:");
    Serial.println(pupuk); 
    
    }
//Send Data to Arduino
//espSerial.println(String(pohon1)+" "+String(ph1)+" "+String(humi1)+" "+String(tempe1)+" "+String(pohon2)+" "+String(ph2)+" "+String(air)+" "+String(pupuk));
//espSerial.println("CEK KONEKSI");

}

void kirim()   //CONNECTING WITH MYSQL
 { 
String apiUrl = "/lomba/kirim.php?";
  apiUrl += "1="+String(pohon1);
  apiUrl += "&2="+String(pohon2);
  apiUrl += "&3="+String(ph2);
  apiUrl += "&4="+String(humi1);
  apiUrl += "&5="+String(tempe1);
  apiUrl += "&6="+String(air);
  apiUrl += "&7="+String(pupuk);
  
  // Set header Request
  client.print(String("GET ") + apiUrl + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  // Pastikan tidak berlarut-larut
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

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0,-1};
  int maxIndex = data.length()-1;

  for(int i =0; i<=maxIndex && found<=index; i++ ){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]): "";
}
