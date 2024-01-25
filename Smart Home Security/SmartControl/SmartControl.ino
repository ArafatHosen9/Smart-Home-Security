#define BLYNK_TEMPLATE_ID "TMPL63wrel2nD"
#define BLYNK_TEMPLATE_NAME "Smart Control"
#include <DHT22.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "ZpKwmMhnumOSbiowUjjm2NjIFVkiwvTB";  // Enter your Blynk auth token here
char ssid[] = "Neehal";   // Enter your WiFi SSID here
char pass[] = "@84398371#";   // Enter your WiFi password here
WidgetTerminal terminal(V0);	
int pos = 0;
int f = 1;
Servo myservo1;
int Pin_D0 = D0;
int Pin_D1 = D1;
int Pin_D2 = D2;
int Pin_D3 = D3;
int Pin_D4 = D4;
int Pin_D5 = D5;
int Pin_D6 = D6;
int Pin_D7 = D7;
int Pin_D8 = D8;
int L=0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  myservo1.attach(D1);
  pinMode(0, INPUT);
  pinMode(Pin_D0, OUTPUT);
  pinMode(Pin_D1, OUTPUT);
  pinMode(Pin_D2, OUTPUT);
  pinMode(Pin_D3, OUTPUT);
  pinMode(Pin_D4, OUTPUT);
  pinMode(Pin_D5, OUTPUT);
  pinMode(Pin_D6, OUTPUT);
  pinMode(Pin_D7, OUTPUT);
  pinMode(Pin_D8, INPUT);

  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
  digitalWrite(D3, 1);
  digitalWrite(D4, 1);
  digitalWrite(D5, 1);
  digitalWrite(D6, 1);
  digitalWrite(D7, 1);
}

BLYNK_WRITE(V1) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D0, LOW);
    Blynk.virtualWrite(V8, "Ok, Door Unlock");
  } else {
    digitalWrite(Pin_D0, HIGH);
    Blynk.virtualWrite(V8, "  Ok, Door Lock");
  }
}
BLYNK_WRITE(V2) {
  bool value2 = param.asInt();
  if (value2 == 1 && f==0) {
    Blynk.virtualWrite(V8, "Ok, Window Open");
    f=1;
    for (pos = 155; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15 ms for the servo to reach the position
  }
  } if (value2 == 0 && f==1) {
    Blynk.virtualWrite(V8, "Ok, Window Close");
    f=0;
    for (pos = 0; pos <= 155; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15 ms for the servo to reach the position
  }
  }
}
BLYNK_WRITE(V3) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D2, LOW);
    Blynk.virtualWrite(V8, "  Ok, Fan ON");
  } else {
    digitalWrite(Pin_D2, HIGH);
    Blynk.virtualWrite(V8, "  Ok, Fan OFF");
  }
}
BLYNK_WRITE(V4) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D3, LOW);
    Blynk.virtualWrite(V8, "  Ok, Light ON");
  } else {
    digitalWrite(Pin_D3, HIGH);
    Blynk.virtualWrite(V8, "  Ok, Light OFF");
  }
}
BLYNK_WRITE(V5) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D4, LOW);
    Blynk.virtualWrite(V8, "   Ok, AC ON");
  } else {
    digitalWrite(Pin_D4, HIGH);
    Blynk.virtualWrite(V8, "   Ok, AC OFF");
  }
}
BLYNK_WRITE(V6) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D5, LOW);
    Blynk.virtualWrite(V8, "Ok Water Pump ON");
  } else {
    digitalWrite(Pin_D5, HIGH);
    Blynk.virtualWrite(V8, " Water Pump OFF");
  }
}
BLYNK_WRITE(V7) {
  bool value2 = param.asInt();
  if (value2 == 1) {
    digitalWrite(Pin_D6, LOW);
    Blynk.virtualWrite(V8, "Gerdent Pump ON");
  } else {
    digitalWrite(Pin_D6, HIGH);
    Blynk.virtualWrite(V8, "Gerdent Pump OFF");
  }
}

void loop() {
  int Door=digitalRead(D8);
  if(Door==0)
  Blynk.virtualWrite(V0, " Door is Locked ");
  else
  Blynk.virtualWrite(V0, "Door is Unlocked");

  Blynk.run();
  delay(50);
}
