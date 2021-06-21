# define led 13
 int trigger = 10;           // declaramos la palabra trigger como un tipo entero y al mismo tiempo reemplaza al pin 9
 int echo = 9;           // declaramos la palabra echo como un tipo entero y al mismo tiempo reemplaza al pin 8
 float tiempo_de_espera,distancia; // creamos una variable de fotante; es decir, nos puede dar resultados en decimales.
 float A;
 float porcentaje;
void setup() {
  Serial.begin (9600);   // establemos la comucicacion serial
  pinMode (trigger, OUTPUT); // declarmos el pin 9 como salida
  pinMode (echo, INPUT);   // declaramos el 8 como entrada
  pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
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
distancia =(tiempo_de_espera/2)/29.15; // formula para hallar la distancia
Serial.print (distancia);    // imprimimos la distancia en cm
Serial.print ("cm");
delay (1000);
 A=(distancia)*(3.125);
 porcentaje =(100)-(A);
Serial.print("   ");
Serial.print (porcentaje);
Serial.println ("%");
delay (1000);
if (distancia>=28 && distancia <=32){
  digitalWrite (2,1);
  digitalWrite (3,0);
  digitalWrite (4,0);
}
if (distancia>=15 && distancia <=27){
  digitalWrite (2,0);
  digitalWrite (3,1);
  digitalWrite (4,0);
}
if (distancia>=2 && distancia <=14){
  digitalWrite (2,0);
  digitalWrite (3,0);
  digitalWrite (4,1);
}

}
