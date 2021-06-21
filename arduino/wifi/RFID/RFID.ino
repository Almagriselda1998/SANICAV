#include <MFRC522.h>//Descargar e incluir la librería

#include <SPI.h>
#define SAD 10
#define RST 5
MFRC522 nfc(SAD, RST);


#define ledPinAbierto    2
#define ledPinCerrado  3


void setup() {
  pinMode(ledPinAbierto  , OUTPUT);   
  pinMode(ledPinCerrado, OUTPUT);   
  SPI.begin();
  Serial.begin(115200);
  Serial.println("Buscando RC522");
  nfc.begin();
  byte version = nfc.getFirmwareVersion();
  if (! version) {//Entra si no encuentra el módulo.
    Serial.print("No ha encontrado RC522");
    while(1); //detener
  }

  Serial.print("Ha encontrado RC522");
  Serial.print("Firmware version 0x");
  Serial.print(version, HEX);
  Serial.println(".");
}

#define AUTHORIZED_COUNT 1 //Para autoriazar más tarjetas ponemos el número aqui y la añadimos abajo
byte Authorized[AUTHORIZED_COUNT][6] = {

                            {0x83, 0xF4, 0x8D, 0xC6, 0x3C,}
                           //,{0x10, 0x14, 0x39, 0x2E, 0xFF, 0xFF, } ejemplo de como autorizar más tarjetas  0x83,.....
                            
                          };
                          
void printSerial(byte *serial);
boolean isSame(byte *key, byte *serial);
boolean isAuthorized(byte *serial);



void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];
  boolean Abierto = false;
  digitalWrite(ledPinAbierto, Abierto);
  digitalWrite(ledPinCerrado, !Abierto);
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    
    if(isAuthorized(serial))
    { 
      Serial.println("Autorizado");
      Abierto = true;
    }
    else
    { 
      printSerial(serial);
      Serial.println("NO autorizado");
      Abierto = false;
    }
    
    nfc.haltTag();
    digitalWrite(ledPinAbierto, Abierto);
    digitalWrite(ledPinCerrado, !Abierto);
    delay(2000);
  }//if (status == MI_OK)

  delay(500);

}//void loop()

boolean isSame(byte *key, byte *serial)
{
    for (int i = 0; i < 4; i++) {
      if (key[i] != serial[i])
      { 
        return false; 
      }
    }
    
    return true;

}

boolean isAuthorized(byte *serial)
{
    for(int i = 0; i<AUTHORIZED_COUNT; i++)
    {
      if(isSame(serial, Authorized[i]))
        return true;
    }
   return false;
}

void printSerial(byte *serial)
{
        Serial.print("Serial:");
    for (int i = 0; i < 5; i++) {// aumentar a 5 para leer el número de la tarjeta completo
      Serial.print(serial[i], HEX);
      Serial.print(" ");
    }
}
