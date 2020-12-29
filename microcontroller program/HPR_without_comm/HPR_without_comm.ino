#include <Servo.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

SFE_BMP180 pressure;

double baseline; // baseline pressure

Servo myservo; 
//int Buzzer=3; //buzzer indication upon landing, Altitude= 0 mts
int a1=0;
int a2=0;
int i=0;
int pos=0;

void setup() {
  Serial.begin(9600);
  Serial.println("REBOOT");

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }
 
  baseline = getPressure();
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");
  
  myservo.attach(5);  // servo on pin 5 (pwm)
  delay(15);
//  pinMode(Buzzer, OUTPUT);

  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
  double P,a;
  String dataString = "";

  P = getPressure();
  Serial.print(" Absolute Pressure: ");
  Serial.print(P,2);
  Serial.print(" mb, ");
  dataString += "Absolute Pressure: " + String(P) + " mb, ";
          
  a = pressure.altitude(P,baseline);
  Serial.print("Altitude: ");
  Serial.print(a,0);
  Serial.println(" meters");
  dataString += "Altitude: " + String(a) + " meters";
  
  a2=a;
  if(a1-a2>0){
    i++;  
  }
  
  if(i==3){   
      for (pos = 0; pos <= 180; pos += 1) { 
        myservo.write(pos);              
        delay(15);
      }
      Serial.println(" Parachute Deployed!!!");
      dataString += " Parachute Deployed!!!";
    }
    
   if(i>3 && a2==10){
      Serial.println(" Nosecone retracting...");
      dataString += " Nosecone retracting...";
      for (pos = 180; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        delay(1000);
       }
      Serial.println(" Nosecone retracted.");
      dataString += " Nosecone retracted.";
    //while (1);
      }
    
    //Serial.print(a1);
    //Serial.print(a2);
    //Serial.print(i);

  a1=a2;

  File dataFile = SD.open("DataLog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    //Serial.println(dataString);
  }
  else {
    Serial.println("error opening DataLog.txt");
  }
  
}


double getPressure()
{
  char status;
  double T,P;

  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n"); 
}
