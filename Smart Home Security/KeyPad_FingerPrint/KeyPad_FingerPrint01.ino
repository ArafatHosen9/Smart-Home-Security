#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <EEPROM.h>
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(8, 9);
#else
#define mySerial Serial1
#endif
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

char password[4];
char pass[4], pass1[4];
int i = 0;
char customKey = 0;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { A3, A2, A1, A0 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 2, 3, 4, 5 };      //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led=6;
int buzzer = 10;
int k = 0, S = 0;
int pos = 0;
Servo myservo2;  // create servo object to control a servo
uint8_t id;
void setup() {
  Serial.begin(9600);
  //pinMode(11, OUTPUT);//*********************************
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(6, 0);
  myservo2.attach(12);  ///DDDDD
  myservo2.write(0);
  lcd.begin();
  lcd.backlight();
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.print("Enter Passkey:");
  lcd.setCursor(0, 1);
  finger.begin(57600);
  delay(5);

  /*for(int j=0;j<4;j++)
  EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
  pass[j]=EEPROM.read(j);*/
}



void loop() {
  getFingerprintID();
  pinMode(12, INPUT);
  //digitalWrite(12, 0);//***************************************
  //myservo2.write(0);
  customKey = customKeypad.getKey();

  if (customKey == '#')
    change();


  if (customKey == '*') {
    lcd.setCursor(0, 0);
    lcd.print("Ready to enroll");
    lcd.setCursor(0, 1);
    lcd.print("New fingerprint!");
    delay(3000);
    Enroll();
  }

  if (customKey) {
    //lcd.clear();
    password[i++] = customKey;
    lcd.print(customKey);
    Serial.print(customKey);
    beep();
  }

  if (!digitalRead(7) || i == 4 || finger.confidence > 50 && finger.confidence < 400) {
    delay(200);
    for (int j = 0; j < 4; j++)
      pass[j] = EEPROM.read(j);
    if (!digitalRead(7) || !(strncmp(password, pass, 4)) || finger.confidence > 50 && finger.confidence < 400) {
      finger.confidence = 0;
      digitalWrite(led, HIGH);
      beep();
      lcd.clear();
      lcd.print("Door is Unlocked");
      Serial.println("Passkey Accepted");
      //digitalWrite(11, LOW);//*************************************************
      myservo2.attach(12);
      for (pos = 0; pos <= 100; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo2.write(pos);  // tell servo to go to position in variable 'pos'
        delay(15);            // waits 50 ms for the servo to reach the position
      }
      delay(4000);
      /* lcd.setCursor(0,1);
 lcd.print("#.Change Passkey");
 Serial.println("#.Change Passkey");*/
      //delay(2000);
      for (pos = 100; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
        myservo2.write(pos);                 // tell servo to go to position in variable 'pos'
        delay(25);                           // waits 15 ms for the servo to reach the position
      }
      lcd.clear();
      lcd.print("Enter Passkey:");
      Serial.println("Enter Passkey:");
      lcd.setCursor(0, 1);
      i = 0;
      digitalWrite(led, LOW);
    } else {
      //digitalWrite(11, HIGH);//**************************************
      digitalWrite(buzzer, HIGH);
      lcd.clear();
      lcd.print("X Access Denied...");
      Serial.println("Access Denied...");
      lcd.setCursor(0, 1);
      lcd.print("#.Change Passkey");
      Serial.println("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      Serial.println("Enter Passkey:");
      lcd.setCursor(0, 1);
      i = 0;
      digitalWrite(buzzer, LOW);
    }
  }
}




void change() {
  int j = 0;
  lcd.clear();
  lcd.print("UR Current Passk");
  Serial.println("UR Current Passk");
  lcd.setCursor(0, 1);
  while (j < 4) {
    char key = customKeypad.getKey();
    if (key) {
      pass1[j++] = key;
      lcd.print(key);
      Serial.print(key);
      beep();
    }
    key = 0;
  }
  delay(500);
  if ((strncmp(pass1, pass, 4))) {
    lcd.clear();
    lcd.print("Wrong Passkey...");
    Serial.println("Wrong Passkey...");
    lcd.setCursor(0, 1);
    lcd.print("Better Luck Again");
    Serial.println("Better Luck Again");
    delay(1000);
  } else {
    j = 0;
    lcd.clear();
    lcd.print("Enter New Passk:");
    Serial.println("Enter New Passk:");
    lcd.setCursor(0, 1);
    while (j < 4) {
      char key = customKeypad.getKey();
      if (key) {
        pass[j] = key;
        lcd.print(key);
        Serial.print(key);
        EEPROM.write(j, key);
        j++;
        beep();
      }
    }
    lcd.print(" Done......");
    Serial.println(" Done......");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Enter Ur Passk:");
  Serial.println("Enter Ur Passk:");
  lcd.setCursor(0, 1);
  customKey = 0;
}


void beep() {
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}


void Enroll()  // run over and over again
{
  while (1) {

    lcd.setCursor(0, 0);
    lcd.print(" At First Take  ");
    lcd.setCursor(0, 1);
    lcd.print(" Admin Finger.. ");


    getFingerprintID();
    if (finger.confidence > 50 && finger.confidence < 400) {
      lcd.setCursor(0, 0);
      lcd.print("OK, Success!...");
      lcd.setCursor(0, 1);
      lcd.print("Type ID Number: ");
      delay(2000);
      break;
    }
  }

  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  id = readnumber();

  if (id == 0) {  // ID #0 not allowed, try again!
    return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  lcd.setCursor(0, 0);
  lcd.print("ID Number: ");
  lcd.print(id);
  lcd.setCursor(0, 1);
  lcd.print("Enter New Finger");

  while (!getFingerprintEnroll())
    ;
}