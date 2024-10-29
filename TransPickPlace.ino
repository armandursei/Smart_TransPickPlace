#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Servo.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); 


Servo myservo;
Servo so;
Servo sv;
Servo sb;


int pos=0;
// TCS230 or TCS3200 pins wiring to Arduino
#define S0 8
#define S1 9
#define S2 7
#define S3 11
#define sensorOut 12


// Stores frequency read by the photodiodes
int red = 0;
int green = 0;
int blue = 0;
int contor_verde=0;
int contor_rosu=0;
int contor_albastru=0;

int ok;
int last=0;
int centru=169;
int down=22;
int plasat=35;
int transpv=55;
int incr=19;
int claw=95;


void setup() {

  lcd.init();                  // Initialize the lcd 
  lcd.backlight();

  pinMode(13,INPUT);

  myservo.attach(6);
  so.attach(3);
  sv.attach(5);
  sb.attach(10);


  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);

  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void initi(){
  so.write(centru);
  sv.write(60);
  sb.write(16);
}

void loop() {

  
  initi();

  // delay(1000);

  // sv.write(25);
  // delay(200);
  // sb.write(45);

  int temp=digitalRead(13); //assign value of LDR sensor to a temporary variable
  Serial.print("Intensity="); //print on serial monitor using ""
  Serial.println(temp); //display output on serial monitor
  delay(20);
  ok=0;
  digitalWrite(2, LOW);   
  digitalWrite(4, LOW); 
  if(temp==HIGH) { //HIGH means,light got blocked
      Serial.println("Obiect prezent in fata");
      myservo.write(90);
      ok=1;
     
      // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(red);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(green);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blue);
  delay(100);


  lcd.setCursor(0,0);
   delay(500);
   lcd.print("Culoarea este: ");
   

   if(red < blue && red < green){
      lcd.print("R");//rosu
       digitalWrite(4, HIGH);   
       digitalWrite(0, LOW);   
       digitalWrite(2, LOW);  
      lcd.setCursor(0,1);
      if(last==0){
      contor_rosu=contor_rosu+1;
      ok=0;
      lcd.print("R: ");
      lcd.print(contor_rosu );
      lcd.print(" A: ");
      lcd.print(contor_albastru );
      lcd.print(" V: ");
      lcd.print(contor_verde);
      delay(1000);
        grab();
        mover();
        last=1;

    } 
   }
   else if(blue < red && blue < green) {
    lcd.print("A");//albastru//
       digitalWrite(2, HIGH);
       digitalWrite(0, LOW);  
       digitalWrite(4, LOW);  
    if(last==0){
    contor_albastru=contor_albastru+1;
    ok=0;
    lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(contor_rosu );
      lcd.print(" A: ");
      lcd.print(contor_albastru );
      lcd.print(" V: ");
      lcd.print(contor_verde);
      delay(1000);
      grab();
      moveb();
      last=1;
    } 
   }
   else if (green < red && green < blue) {
    lcd.print("V"); 
       digitalWrite(0, HIGH);   
       digitalWrite(4, HIGH); 
      digitalWrite(2, HIGH);   
    if(last==0)
    {contor_verde=contor_verde+1;//galben
    ok=0;
    lcd.setCursor(0,1);
    lcd.print("R: ");
      lcd.print(contor_rosu );
      lcd.print(" A: ");
      lcd.print(contor_albastru );
      lcd.print(" V: ");
      lcd.print(contor_verde);
      delay(1000);
    grab();
    moveg();
    last=1;
    } 
   }  
   else {
      lcd.clear(); // Clears the LCD
      lcd.setCursor(0,0);
      lcd.print("   NO COLOR  ");
      lcd.setCursor(0,1); 
      lcd.print("   DETECTED  ");
      delay(5000);
  }
   last=1;
    }
  else{ 
    Serial.println("Obiect absent");
    myservo.write(80);
    ok=0;
    last=0;
   }

  // // Setting RED (R) filtered photodiodes to be read
  // digitalWrite(S2,LOW);
  // digitalWrite(S3,LOW);
  
  // // Reading the output frequency
  // redFrequency = pulseIn(sensorOut, LOW);
  
  //  // Printing the RED (R) value
  // Serial.print("R = ");
  // Serial.print(redFrequency);
  // delay(100);
  
  // // Setting GREEN (G) filtered photodiodes to be read
  // digitalWrite(S2,HIGH);
  // digitalWrite(S3,HIGH);
  
  // // Reading the output frequency
  // greenFrequency = pulseIn(sensorOut, LOW);
  
  // // Printing the GREEN (G) value  
  // Serial.print(" G = ");
  // Serial.print(greenFrequency);
  // delay(100);
 
  // // Setting BLUE (B) filtered photodiodes to be read
  // digitalWrite(S2,LOW);
  // digitalWrite(S3,HIGH);
  
  // // Reading the output frequency
  // blueFrequency = pulseIn(sensorOut, LOW);
  
  // // Printing the BLUE (B) value 
  // Serial.print(" B = ");
  // Serial.println(blueFrequency);
  // delay(100);
}

void grab()
{
  for (pos = transpv; pos >= down; pos -= 1) { 
    sv.write(pos);              
    delay(45);                    
  }  
  delay(1000);
  sb.write(claw);
  delay(1000);
for (pos = down; pos <= transpv; pos += 1) { 
    sv.write(pos);             
    delay(45);                      
  }  
}

void plasare()
{
for (pos = transpv; pos >= plasat; pos -= 1) { 
    sv.write(pos);              
    delay(45);                    
  }  
  delay(1000);
  sb.write(16);  
  delay(1000);

  for (pos = plasat; pos <= transpv; pos += 1) {
    sv.write(pos);             
    delay(45);                       
  }  

  delay(500);
}


void moveb()
{
  delay(1000);
  for (pos = centru; pos >= 102-(contor_albastru-1)*incr; pos -= 1) { 
    so.write(pos);              
    delay(45);                      
  }
  delay(1000);
  plasare();
  initi();
}


void mover()
{
  delay(1000);
  for (pos = centru; pos >= 60-(contor_rosu-1)*incr; pos -= 1) { 
    so.write(pos);             
    delay(45);                       
  }
  delay(1000);
  plasare();
  initi();
}

void moveg()
{
  delay(1000);
  for (pos = centru; pos >= 19-(contor_verde-1)*incr; pos -= 1) {
    so.write(pos);             
    delay(45);                      
  }
  delay(1000);
  plasare();
  initi();
}

