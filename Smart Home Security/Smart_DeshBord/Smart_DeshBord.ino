#define BLYNK_TEMPLATE_ID "TMPL6qdyrR8eM"
#define BLYNK_TEMPLATE_NAME "Smart Dashboard"
#include <DHT22.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

char auth[] = "y1YEYDW04CrJ3a0arZ-cSB4q428EvfnM";  // Enter your Blynk auth token here
char ssid[] = "Neehal";   // Enter your WiFi SSID here
char pass[] = "@84398371#";   // Enter your WiFi password here
int x = 0; int Rain, Air, Tree, Sun, Water, Gas; int k=0, S=0;
int Pin_D3  = D3;
int Pin_D4  = D4;
int Pin_D5  = D5;
int Pin_D6  = D6;
int Pin_D7  = D7;
int Pin_D8  = D8;

DHT22 dht22(D0); 
WidgetTerminal terminal(V0);	

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  lcd.begin();
  lcd.backlight();
  pinMode(0, INPUT);
  pinMode(Pin_D3, INPUT);
  pinMode(Pin_D4, OUTPUT);
  pinMode(Pin_D5, OUTPUT);
  pinMode(Pin_D6, OUTPUT);
  pinMode(Pin_D7, OUTPUT);
  pinMode(Pin_D8, OUTPUT);
}

int analogRead1() {
    digitalWrite(Pin_D4, LOW);
    digitalWrite(Pin_D5, HIGH); // Turn D1 On
    digitalWrite(Pin_D6, LOW); // Turn D2 Off
    digitalWrite(Pin_D7, LOW);
    digitalWrite(Pin_D8, LOW);
    return analogRead(0);
}
 
int analogRead2() {
    digitalWrite(Pin_D4, LOW);
    digitalWrite(Pin_D5, LOW); // Turn D1 On
    digitalWrite(Pin_D6, HIGH); // Turn D2 Off
    digitalWrite(Pin_D7, LOW);
    digitalWrite(Pin_D8, LOW);
    return analogRead(0);
}

int analogRead3() {
    digitalWrite(Pin_D4, LOW);
    digitalWrite(Pin_D5, LOW); // Turn D1 On
    digitalWrite(Pin_D6, LOW); // Turn D2 Off
    digitalWrite(Pin_D7, HIGH);
    digitalWrite(Pin_D8, LOW);
    return analogRead(0);
}
 
int analogRead4() {
    digitalWrite(Pin_D4, LOW);
    digitalWrite(Pin_D5, LOW); // Turn D1 On
    digitalWrite(Pin_D6, LOW); // Turn D2 Off
    digitalWrite(Pin_D7, LOW);
    digitalWrite(Pin_D8, HIGH);
    return analogRead(0);
}
int analogRead5() {
    digitalWrite(Pin_D4, HIGH);
    digitalWrite(Pin_D5, LOW); // Turn D1 On
    digitalWrite(Pin_D6, LOW); // Turn D2 Off
    digitalWrite(Pin_D7, LOW);
    digitalWrite(Pin_D8, LOW);
    return analogRead(0);
}

void loop() {
  Rain = analogRead1() / 10; // Read Analog value of first sensor
  delay(20);
  Tree = analogRead2() / 10; // Read Analog value of second sensor
  delay(20);
  Air = analogRead3() / 10;
  delay(20);
  Sun = analogRead4() / 10;
  delay(20);
  Water = analogRead5() / 10;
  delay(20);
  Gas = digitalRead(Pin_D3);
  delay(20);

  Blynk.run();
  float temperature = dht22.getTemperature();
  float humidity = dht22.getHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  /*Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println(Rain);
  Serial.println(Tree);
  Serial.println(Air);
  Serial.println(Sun);*/
  
  Blynk.virtualWrite(V1, temperature);  // Send temperature value to Blynk App
  Blynk.virtualWrite(V2, humidity);     // Send humidity value to Blynk App
  Blynk.virtualWrite(V3, Rain);
  Blynk.virtualWrite(V4, Tree);
  Blynk.virtualWrite(V5, Air);
  Blynk.virtualWrite(V6, Sun);
  Blynk.virtualWrite(V7, Water);
  if(Gas)
  Blynk.virtualWrite(V8, 0);
  if(!Gas)
  Blynk.virtualWrite(V8, 1);


  if((millis()-S) > 4500)
    {
      S=millis();
      if(k%3==0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Assalamu Alaikum  ");
        lcd.setCursor(0, 1);
        lcd.print(" How are you Today? ");
        lcd.setCursor(0, 2);
        lcd.print(" Smart Home Project ");
        lcd.setCursor(0, 3);
        lcd.print(" <<Smart Control>>  ");
      }
      if(k%3==1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temperature: ");
        lcd.print(temperature, 1);
        lcd.print("C ");
        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity, 1);
        lcd.print("%");
        lcd.setCursor(0, 2);
        lcd.print("Rain: ");
        lcd.print(Rain);
        lcd.print("%     ");
        lcd.setCursor(0, 3);
        lcd.print("Gardent Moisture: ");
        lcd.print(Tree, 1);
        lcd.print("%");
      }
      if(k%3==2)
      {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Air Flow is: ");
        lcd.print(Air);
        lcd.print("%  ");
        lcd.setCursor(2, 1);
        lcd.print("SunLight: ");
        lcd.print(Sun);
        lcd.print("%  ");
        lcd.setCursor(2, 2);
        lcd.print("Water Level: ");
        lcd.print(Water);
        lcd.print("%  ");
        lcd.setCursor(0, 3);
        lcd.print("     Thank You!");
      }
      k++;
    }
    
  delay(1000);   // Wait for 2 seconds
}
