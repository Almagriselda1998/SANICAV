#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 LiquidCrystal_I2C lcd(0x27,16,2);
 int trigger = 10;           // declaramos la palabra trigger como un tipo entero y al mismo tiempo reemplaza al pin 9
 int echo = 9;           // declaramos la palabra echo como un tipo entero y al mismo tiempo reemplaza al pin 8
 int pinBuzzer = 8;
 const int verde = 7;
 const int amarillo = 6;
 const int rojo = 5;
 float tiempo_de_espera,distancia; // creamos una variable de fotante; es decir, nos puede dar resultados en decimales.
 float A, B, C, D, E;
 float promedio;
 
 void setup() { 
  mlx.begin(); 
  Serial.begin (9600);   // establemos la comucicacion serial
  pinMode (trigger, OUTPUT); // declarmos el pin 9 como salida
  pinMode (echo, INPUT);   // declaramos el 8 como entrada
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("APROXIMA TU MANO...");
  lcd.setCursor(3, 1);
  lcd.print("SANICAV");

}
void loop() {
digitalWrite (trigger,LOW); // ponemos en bajo el pin 8 durante 2 microsegundos
delayMicroseconds(2);
digitalWrite (trigger, HIGH);// ahora ponemos en alto pin 8 durante 10 microsegundos;
delayMicroseconds (10);     // pues este el momento en que emite el sonido durante 10 segungos
digitalWrite (trigger, LOW); // ahora ponemos en bajo pin 8 
tiempo_de_espera = pulseIn (echo,HIGH); // pulseIn, recoge la señal del sonido que emite el trigger
/*La función pulseIn espera la aparición de un pulso en una entrada y mide su duración, dando como resultado la duración medida                   
 El primer parámetro (ECHO) es el pin sobre el que se realizará la medición.
Y el segundo parámetro (HIGH) indica si el pulso a esperar será un 1 (HIGH) o un 0 (LOW).
 */
  Serial.println("APROXIMA TU MANO...");
  Serial.println("   ");
  distancia =(tiempo_de_espera/2)/29.15; // formula para hallar la distancia
  Serial.print (distancia);    // imprimimos la distancia en cm
  Serial.println ("cm");
  delay(1000);
  lcd.scrollDisplayLeft(); 
  delay(100);
if (distancia>=0 && distancia <=10){
 A=(mlx.readObjectTempC()); 
 delay(1000);
 B=(mlx.readObjectTempC()); 
 delay(1000);
 C=(mlx.readObjectTempC()); 
 delay(1000);
 D=(mlx.readObjectTempC()); 
 E=(mlx.readAmbientTempC()); 
 delay(1000);
 tone(pinBuzzer, 650);
 delay(1000);
 noTone(pinBuzzer);
 promedio=(A+B+C+D)/(4);
  if (promedio>=30 && promedio<=37.4){
  digitalWrite (verde,HIGH);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AMBIENTE ");
  lcd.print(E);
  lcd.setCursor(0, 1);
  lcd.print("CORPORAL ");
  lcd.print(promedio);
  delay(3000);
  digitalWrite (verde,LOW);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("APROXIMA TU MANO...");
  lcd.setCursor(3, 1);
  lcd.print("SANICAV");
 }
   if (promedio>=37.5 && promedio<=37.9){
  digitalWrite (amarillo,HIGH);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AMBIENTE ");
  lcd.print(E);
  lcd.setCursor(0, 1);
  lcd.print("CORPORAL ");
  lcd.print(promedio);
  delay(3000);
  digitalWrite (amarillo,LOW);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("APROXIMA TU MANO...");
  lcd.setCursor(3, 1);
  lcd.print("SANICAV");
 }
   if (promedio>=38 && promedio<=42.9){
  digitalWrite (rojo,HIGH);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESPERA 3 MIN.");
  lcd.setCursor(0, 1);
  lcd.print("CORPORAL ");
  lcd.print(promedio);
  delay(3000);
  digitalWrite (rojo,LOW);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("APROXIMA TU MANO...");
  lcd.setCursor(3, 1);
  lcd.print("SANICAV");
 }
}
}
