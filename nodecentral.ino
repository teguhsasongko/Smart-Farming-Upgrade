#include <ESP8266WiFi.h>

const char* ssid     = "localhost";
const char* password = "";

const char* host = "192.168.1.9";
String sentence;
String pohon1;
String ph1;
String humi1;
String tempe1;
String pohon2;
String ph2;

void setup() {
  Serial.begin(115200);
  delay(10);

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

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
 
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
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

    
    }
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
