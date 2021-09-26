#include <Wire.h> //LCD Library
#include <LiquidCrystal_I2C.h> // LCD library using from  https://www.ardumotive.com/i2clcden.html for the i2c LCD library 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 after finding it from serial monitor (see comment above) for a 16 chars and 2 line display

String pohon1;
String ph1;
String humi1;
String tempe1;
String pohon2;
String ph2;

void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
lcd.init(); // initialize the lcd 
lcd.backlight();
lcd.setBacklight(HIGH);
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
    Serial.print("Pohon 2: ");
    Serial.println(pohon2); 

    ph2 = String(getValue(line,' ',5));
    Serial.print("pH Tanah:");
    Serial.println(ph2); 
    }

//Kelembapan Pohon 1
if(pohon1 >= String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Kering");
  delay(1000);
}
else if(pohon1 >= String(350) && pohon1 <= String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Normal");
  delay(1000);
}
else if(pohon1 <= String(350)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Lembab");
  delay(1000);
}
  
//Kelembapan Pohon 2
if(pohon2 >= String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Kering");
  delay(1000);
}
else if(pohon2 >= String(350) && pohon2 <= String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Normal");
  delay(1000);
}
else if(pohon2 <= String(350)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Lembab");
  delay(1000);
}

//DHT22
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(tempe1);
  lcd.print(" *C\t");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humi1);
  lcd.println(" %");
  delay(1000);
  
//PH Tanah dari Pohon 2    
  if(ph2 < String(6.5)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("pH = ");
    lcd.print(ph2);
    lcd.setCursor(0,1);
    lcd.print("SIRAM PUPUK CUK");
    delay(1000);
   }
   else if(ph2 > String(6,6)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("pH = ");
    lcd.print(ph2);
    lcd.setCursor(0,1);
    lcd.print("PUPUK CUKUP CUK");
    delay(1000);
   } 

delay(2000);   
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
