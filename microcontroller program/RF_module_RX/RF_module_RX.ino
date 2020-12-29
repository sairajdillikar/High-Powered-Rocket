#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup()
{
    Serial.begin(9600);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) 
    {
	    //int i;
	    //driver.printBuffer("Got:", buf, buflen);
      Serial.println((char*)buf);
    }
}
