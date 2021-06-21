#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup() {
  Serial.begin(9600);
  mlx.begin();  
}
void loop() {
  Serial.print("Ambiente= ");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AMBIENTE=");
  lcd.setCursor(9, 0);
  lcd.print(mlx.readAmbientTempC());
  lcd.setCursor(15, 0);
  lcd.print("C");
  Serial.print(mlx.readAmbientTempC()); 
  lcd.setCursor(0, 1);
  lcd.print("CORPORAL=");
  lcd.setCursor(9, 1);
  lcd.print(mlx.readObjectTempC());
  lcd.setCursor(15, 1);
  lcd.print("C");
  Serial.print("ºC\tcorporal = "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("ºC");
  delay(1000);
}
