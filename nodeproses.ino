#include <Wire.h> //LCD Library
#include <SoftwareSerial.h>
SoftwareSerial espSerial(9, 10);
#include <LiquidCrystal_I2C.h> // LCD library using from  https://www.ardumotive.com/i2clcden.html for the i2c LCD library 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 after finding it from serial monitor (see comment above) for a 16 chars and 2 line display

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

//RELAY
int pumpair = 3; //relay pompa air
int pumppupuk = 4; //relay pompa pupuk

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  espSerial.begin(9600);
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.setBacklight(HIGH);
  while (!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
    }
  
  pinMode(pumpair, OUTPUT); // Pompa Kelembaban
  pinMode(pumppupuk, OUTPUT); // Pompa pH
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
    
  air = String(getValue(line,' ',6));
  Serial.print("Ketersediaan Air: ");
  Serial.println(air); 

  pupuk = String(getValue(line,' ',7));
  Serial.print("Ketersediaan Pupuk:");
  Serial.println(pupuk); 
    
  pompaair = String(getValue(line,' ',8));
  Serial.print("Pompa Air: ");
  Serial.println(pompaair); 
    
  pompapupuk = String(getValue(line,' ',9));
  Serial.print("Pompa Pupuk: ");
  Serial.println(pompapupuk); 
  }

///////////////////////////////////////////////////////////////////////////
//Kelembapan Pohon 1
if(pohon1 > String(700) && humi1 < String(31)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Kering");
  delay(1000);
  digitalWrite(pumpair, LOW);
  pompaair = "ON";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("ON");
  delay(1000);
}
else if(pohon1 > String(350) && pohon1 < String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Normal");
  delay(1000);
  digitalWrite(pumpair, LOW);
  pompaair = "OFF";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("OFF");
  delay(1000);
}
else if(pohon1 < String(350)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 1 = ");
  lcd.print(pohon1);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Lembab");
  delay(1000);
  digitalWrite(pumpair, HIGH);
  pompaair = "OFF";
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("OFF");
  delay(1000);
}
  
//Kelembapan Pohon 2
if(pohon2 > String(700) && pohon1 < String(700)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Kering");
  delay(1000);
  digitalWrite(pumpair, LOW);
  pompaair = "ON";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("ON");
  delay(1000);
}
else if(pohon2 > String(350) && humi1 < String(31)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Normal");
  delay(1000);
  digitalWrite(pumpair, LOW);
  pompaair = "OFF";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("OFF");
  delay(1000);
}
else if(pohon2 < String(350)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pohon 2 = ");
  lcd.print(pohon2);
  lcd.setCursor(0, 1);
  lcd.print("Tanah Lembab");
  delay(1000);
  digitalWrite(pumpair, HIGH);
  pompaair = "OFF";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompa Air");
  lcd.setCursor(0, 1);
  lcd.print("OFF");
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
  lcd.print(" %");
  delay(1000);
  
//PH Tanah dari Pohon 2    
  if(ph1 < String(6.6) && humi1 < String(31)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("pH = ");
    lcd.print(ph1);
    lcd.setCursor(0,1);
    lcd.print("Tanah Perlu Pupuk");
    delay(1000);
    digitalWrite(pumppupuk,HIGH);
    pompapupuk = "ON";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pompa Pupuk");
    lcd.setCursor(0, 1);
    lcd.print("ON");
    delay(1000);
   }
   else if(ph1 > String(6,6)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("pH = ");
    lcd.print(ph1);
    lcd.setCursor(0,1);
    lcd.print("Pupuk Cukup");
    delay(1000);
    digitalWrite(pumppupuk,LOW);
    pompapupuk = "OFF";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pompa Pupuk");
    lcd.setCursor(0, 1);
    lcd.print("OFF");
    delay(1000);
   } 

//Ketinggian Air
 if(air > String(70)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Air = ");
    lcd.print(air);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Air Masih Penuh");
    delay(1000);
 }
 else if(air > String(50)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Air = ");
    lcd.print(air);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Tersisa Setengah");
    delay(1000);
 }
 else if(air > String(35)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Air = ");
    lcd.print(air);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Tersisa Sedikit");
    delay(1000);
 }
//Ketinggian Pupuk
 if(pupuk > String(70)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Pupuk = ");
    lcd.print(pupuk);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Masih Penuh");
    delay(1000);
 }
 else if(pupuk > String(50)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Pupuk = ");
    lcd.print(pupuk);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Tersisa Setengah");
    delay(1000);
 }
 else if(pupuk > String(35)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Level Pupuk = ");
    lcd.print(pupuk);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Tersisa Sedikit");
    delay(1000);
 }
espSerial.println(String(pompaair)+" "+String(pompapupuk));

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
