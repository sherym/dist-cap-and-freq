#include <LiquidCrystal.h>
 
#define trigger 13
#define echo 12
 
LiquidCrystal lcd(6,7,2,3,4,5);
 
float time=0,distance=0;
 ////////////
 int charge = 8;
int discharge = 9;
int analogPin = A0;
unsigned long start_timer=0;
unsigned long stop_timer=0;
unsigned long duration=0;
////////////////////////////////
float voltage=3;
float answer=0.0;
int measure (void);
/////////////////////////////////
const int pulsePin = 10; // Input signal connected to Pin 10 of Arduino
int pulseHigh;                           // Pulse High Time in uS
int pulseLow;                            // Pulse Low time in uS
float pulseTotal;                        // Total of high & low times
float frequency; 

///////////////////////////////
int state;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("measure project");
pinMode(discharge,INPUT);
pinMode(charge,OUTPUT);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
  pinMode(pulsePin,INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  state = Serial.read();
  if(state=='c'){
    lcd.clear();
    lcd.print("RANGE 1uF-4700uF");
    digitalWrite(charge,HIGH);
     while(measure()>=1010 && measure()<=1030)
 {
   lcd.setCursor(0,1);
    lcd.print("place capacitor ");
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("                ");  
    delay(200);
 }
 delay(2000);
 lcd.setCursor(0,1);
 lcd.print("                ");
  while(1)
  {
    //////////////////////////////////////////////discharging
    pinMode(charge,INPUT);
    pinMode(discharge,OUTPUT);
    digitalWrite(discharge,LOW);
    lcd.setCursor(0,1);
    lcd.print("Discharging-");//12
    while(voltage>2.0)
    {
    voltage=measure();
    delay(100);
    lcd.setCursor(12,1);
    answer=voltage * (99.0 / 1023.0);
    lcd.print((99-answer),0);
    lcd.setCursor(14,1);
    lcd.print("%");
    }
    
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("charging-");//9
    lcd.setCursor(13,1);
    lcd.print("%");
  
    //////////////////////////////////////////////charging 
    pinMode(discharge,INPUT);
    pinMode(charge,OUTPUT);
    digitalWrite(charge,HIGH);
    start_timer=micros();
    
    while(measure()<648)
    {
      lcd.setCursor(9,1);
      lcd.print(measure()*(100.0/1023.0),1);
    }
    
    stop_timer=micros();
    duration=stop_timer-start_timer;
    answer=duration/10000;
    lcd.clear();
   // lcd.setCursor(0,1);
   // lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("value = ");
    lcd.print(answer);
    lcd.print("uF"); 
    delay(3000);
    while(1)
    {
    lcd.setCursor(0,1);
    lcd.print("reset to measure");
    delay(200);
     lcd.setCursor(0,1);
    lcd.print("                ");  
    delay(200);
    }
   
}
  }
  if(state=='d'){
    lcd.clear();
  lcd.print(" Ultra sonic");
 lcd.setCursor(0,1);
 lcd.print("Distance Meter");
 delay(2000);
 lcd.clear();
  digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
 lcd.clear();
 lcd.print("Distance:");
 lcd.print(distance);
 lcd.print("cm");
 lcd.setCursor(0,1);
 lcd.print("Distance:");
 lcd.print(distance/100);
 lcd.print("m");
 delay(1000);
  }
  /////////////////////////
  if(state=='f'){
    lcd.clear();
        lcd.print(" Freq Counter  ");
    delay(5000);
     lcd.setCursor(0,0);                   //Set cursor to top line full left
    lcd.print("Frequency is    ");        //User Interface
    lcd.setCursor(0,1);                   //drop down one line
    lcd.print("                ");        //clear from previous
    
    pulseHigh = pulseIn(pulsePin,HIGH);   //get the high
    pulseLow = pulseIn(pulsePin,LOW);     //get the low
    
    pulseTotal = pulseHigh + pulseLow;    // add em up
    frequency=1000000/pulseTotal;         // convert to Hz with MATH!
    
    lcd.setCursor(0,1);                   //second line
    lcd.print(frequency);                 //print the freq to LCD
    lcd.print(" Hz");                     //print units
    delay(500); 

    
    }
}}
int measure (void)
{
  int value;
  value=analogRead(analogPin);
  return value;
}
