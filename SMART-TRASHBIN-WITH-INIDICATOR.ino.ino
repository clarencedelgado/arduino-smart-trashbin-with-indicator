#include <Servo.h>   //servo library
#include <HCSR04.h>
#include <LiquidCrystal_I2C.h> // LCD I2C library


Servo servo;    
int trigPin = 5;   
int echoPin = 6; 

int trigPin1 = 9;   
int echoPin1 = 10;  

int servoPin = 7;



long duration, dist, average, duration1, dist1;  
long aver[3];   //array for average

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address 0x27, 16 column and 2 rows

void setup() {      
    servo.attach(servoPin); 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    pinMode(trigPin1, OUTPUT); 
    pinMode(echoPin1, INPUT); 

    servo.write(0);         //close cap on power on
    delay(50);
    servo.detach();

    lcd.init();      // initialize the lcd
    lcd.backlight(); // open the backlight
}
void measure() { 
 digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance

digitalWrite(10,HIGH);
digitalWrite(trigPin1, LOW);
delayMicroseconds(5);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin1, LOW);
pinMode(echoPin1, INPUT);
duration1 = pulseIn(echoPin1, HIGH);
dist1 = (duration1/2) / 29.1;    //obtain distance
}
void loop() {
  
  
  for (int i=0;i<=2;i++) {   //average distance
    measure();              
   aver[i]=dist;           
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;   


if ( dist<=30 ) {
//Change distance as per your need
  lcd.setCursor(0, 0);
  lcd.print("TRASHBIN :  OPEN");
 
 servo.attach(servoPin);
delay(1);
 servo.write(0); 
 delay(3000);      
 servo.write(150);   
 delay(1000);
 servo.detach(); 
 
   
  } else {
  lcd.setCursor(0, 0);
  lcd.print("TRASHBIN : CLOSE");
  
  }


if (dist1 <= 5) {
  
  lcd.setCursor(0, 1);
  lcd.print("STATUS :   FULL");
  

} else {
 
  lcd.setCursor(0, 1);
  lcd.print("STATUS : NORMAL");

}


}