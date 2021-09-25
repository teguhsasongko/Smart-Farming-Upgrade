String pohon1;
String ph1;
String humi1;
String tempe1;
String pohon2;
String ph2;
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over
if (Serial.available()) {
//Serial.write(Serial.read());
String line = Serial.readString();
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
