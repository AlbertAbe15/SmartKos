#define BLYNK_TEMPLATE_ID "TMPLxxx32Xe_"
#define BLYNK_DEVICE_NAME "Mobile Dashboard"
#define BLYNK_AUTH_TOKEN "rdPFHby7lwASBL25n_ZElKWmdxj66mJa"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Babi Guling";
char password[] ="00000000";

#include <DHT.h>
#include <DHT_U.h>
#include <HCSR04.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h> // include library
#include <BlynkSimpleEsp32.h>
#define relay 23
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define BLYNK_PRINT Serial
#define DHTPIN 5
#define trigPin 2
#define echoPin 4
#define buzzer 18
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
long duration;
float jarak;
HCSR04 hc(trigPin,echoPin);
#define SCREEN_ADDRESS 0x3C 

void SmartDoor(){
jarak = hc.dist();
  if(jarak < 7){ 
  //digitalWrite(buzzer,HIGH);
  display.clearDisplay();
  display.setTextSize(2); 
  display.setCursor(0,25);
  display.print("Ada Maling!!!");
  tone(buzzer, 880, 500);

}
  else if(jarak > 7){ 
  //digitalWrite(buzzer,LOW); 
  display.setTextSize(1); 
  display.setCursor(0,35);
  display.print("Aman");
  noTone(buzzer); 

}
  Blynk.virtualWrite(V8,jarak);
  display.setTextSize(1); 
  display.setCursor(0,0); 
  display.print ("Jarak(cm) "); 
  display.setTextSize(2); 
  display.setCursor(0,10); 
  display.print(jarak); 
  delay(1000); 
  display.display(); 
  display.clearDisplay();
}

void SmartEnvirontment(){
  float h = dht.readHumidity(); // pengukuran kelembaban
  float t = dht.readTemperature(); // pengukuran tempperature
    if ( t >= 27 ){
    digitalWrite(relay,LOW);
  } 
    else {
    digitalWrite(relay,HIGH);
  }
    Blynk.virtualWrite(V3,t);
    Blynk.virtualWrite(V4,h);
}

void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); 
}
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  Blynk.begin(auth,ssid,password); 
  dht.begin();
}

void loop() {
  
// Smart Door 
SmartDoor();
//Smart Environment
SmartEnvirontment();
//kontrol Smart door
   //int Kontrol_Smartdoor = analogRead(buzzer);
  // Blynk.virtualWrite(V6, Kontrol_Smartdoor);
   
//kontrol Smart Environtment
  // int Kontrol_SmartEnvirontment = analogRead(relay);
  // Blynk.virtualWrite(V5, Kontrol_SmartEnvirontment);
}
