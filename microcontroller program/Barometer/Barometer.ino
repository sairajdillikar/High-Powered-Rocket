#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;

double baseline; // baseline pressure

void setup()
{
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
}

void loop()
{
  double P,a;
  
  P = getPressure();
  Serial.print("Absolute Pressure: ");
  Serial.print(P,2);
  Serial.print(" mb, ");
          
  a = pressure.altitude(P,baseline);
  Serial.print("Altitude: ");
  Serial.print(a,1);
  Serial.println(" meters");

  delay(1000);  // Pause for 2 seconds.*/
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
