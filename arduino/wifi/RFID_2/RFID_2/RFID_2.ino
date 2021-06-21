#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
const int ledOk =  6;      // the number of the LED pin
const int ledError =  7;  // the number of the LED pin
int pinBuzzer = 5;
LiquidCrystal_I2C lcd(0x27,16,2);
 void setup() 
{
  pinMode(ledError, OUTPUT);
  pinMode(ledOk, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("APROXIMA TU TARJETA AL LECTOR...");
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("APROXIMA TU TARJETA AL LECTOR...");
  lcd.setCursor(7, 1);
  lcd.print("SANICAV");
}

void loop() 
{   lcd.scrollDisplayLeft(); 
     delay(500);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("ID:");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensaje: ");
  content.toUpperCase();
  if (content.substring(1) == "79 92 F5 4E") //change here the UID of the card/cards that you want to give access
  { tone(pinBuzzer, 600);
    Serial.println("ACCESSO AUTORIZADO");
    Serial.println();
    Serial.println("BIENVENIDO JOEL");
    digitalWrite(ledOk, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ID: 79 92 F5 4E");
    lcd.setCursor(0, 1);
    lcd.print("BIENVENIDO JOEL");
    delay(5000);
    digitalWrite(ledOk, LOW);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("APROXIMA TU TARJETA AL LECTOR...");
    lcd.setCursor(7, 1);
    lcd.print("SANICAV");
  }
  else if (content.substring(1) == "26 55 F3 F8") //change here the UID of the card/cards that you want to give access
  { tone(pinBuzzer, 600);
    Serial.println("ACCESSO AUTORIZADO");
    Serial.println();
    Serial.println("BIENVENIDA GRIS");
    digitalWrite(ledOk, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ID: 26 55 F3 F8");
    lcd.setCursor(0, 1);
    lcd.print("BIENVENIDA GRIS");
    delay(5000);
    digitalWrite(ledOk, LOW);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("APROXIMA TU TARJETA AL LECTOR...");
    lcd.setCursor(7, 1);
    lcd.print("SANICAV");
  }
  else if (content.substring(1) == "F6 07 B0 F8") //change here the UID of the card/cards that you want to give access
  { tone(pinBuzzer, 600);
    Serial.println("ACCESSO AUTORIZADO");
    Serial.println();
    Serial.println("BIENVENIDO");
    digitalWrite(ledOk, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ID: F6 07 B0 F8");
    lcd.setCursor(0, 1);
    lcd.print("BIENVENIDO ADAL");
    delay(5000);
    digitalWrite(ledOk, LOW);
    noTone(pinBuzzer);
    lcd.clear()
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("APROXIMA TU TARJETA AL LECTOR...");
    lcd.setCursor(7, 1);
    lcd.print("SANICAV");
  }
 
 else   {
    Serial.println(" ACCESO DENEGADO");
    digitalWrite(ledError, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("ERROR TARJETA");
    lcd.setCursor(0,1);
    lcd.print("ACCESO DENEGADO");
    tone(pinBuzzer, 600); 
    delay (450);  
    digitalWrite(ledError, LOW); 
    digitalWrite(ledError, HIGH);
    tone(pinBuzzer, 294); 
    delay (450);  
    digitalWrite(ledError, LOW); 
    digitalWrite(ledError, HIGH);
    tone(pinBuzzer, 494); 
    delay (450);  
    digitalWrite(ledError, LOW); 
    noTone(pinBuzzer);
    lcd.clear();
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("APROXIMA TU TARJETA AL LECTOR...");
    lcd.setCursor(7, 1);
    lcd.print("SANICAV");
  }
} 
