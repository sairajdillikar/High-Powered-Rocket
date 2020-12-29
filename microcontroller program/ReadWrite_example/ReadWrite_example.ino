#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("DataLog.txt", FILE_WRITE);
  
  if (myFile) {
    Serial.print("Writing to DataLog.txt...");
    myFile.println("new info on text file yea bro this is cool..!!!");
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening DataLog");
  }

  myFile = SD.open("DataLog.txt");
  
  if (myFile) {
    Serial.println("DataLog.txt:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening DataLog.txt");
  }
}

void loop() {
  
}
