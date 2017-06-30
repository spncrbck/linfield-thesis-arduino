#include <Arduino.h>          // Arduino library
#include <max6675.h>          // thermocouple library
#include <Wire.h>
#include <SPI.h>              // SD card library
#include <SD.h>               // SD card library

File celsiusFile;         // celsius temperature data gets put in this file
File outputFile;          // voltage output gets put in this file

const int chipSelect = 10;
int SDcsPin = 10;                // pin in which cs from SD breakout is attached
int motorPin = A3;            // motor connected to A2
int ktcSOPin = 4;
int ktcCSPin = 5;
int ktcCLKPin = 6;
MAX6675 ktc(ktcCLKPin, ktcCSPin, ktcSOPin); // map MAX667 pins

float celsius;
float fahrenheit;
float output;

int loopTime = 200; // ms
int collectionRate = 5; // ms
int n = loopTime / collectionRate;
int i;

void setup()
{
  Serial.begin(9600); // open serial communications
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB only
  }
  Serial.print("Initializing SD card...");
  delay(2000);
  //lcd.clear();

  if (!SD.begin(SDcsPin))
  {
    Serial.println("SD card initialization failed!");
    delay(2000);
    return;
  }
  Serial.println("SD initialization done.");
  delay(2000);

  celsiusFile = SD.open("celsius.txt", FILE_WRITE); // open or create celsiusData to write to on SD card
  if (celsiusFile){
    celsiusFile.println("SETUP RUN. BEGIN DATA COLLECTION.");
    celsiusFile.close(); // close the file
  } else {
    Serial.println("Error opening celsius.txt during setup.");
  }
  
  outputFile = SD.open("output.txt", FILE_WRITE); // open or create outputData to write to on SD card
  if (outputFile){
  outputFile.println("SETUP RUN. BEGIN DATA COLLECTION.");
  outputFile.close(); // close the file
  } else {
    Serial.println("Error opening output.txt during setup.");
  }
}

void loop()
{  
  float celsius = ktc.readCelsius();
  float fahrenheit = ktc.readFahrenheit();
  
  for (i = 0; i < n; i++){
    float readOutput = analogRead(motorPin) * 15.0000 / 1024;
    
    delay(collectionRate);
  }
  
  celsiusFile = SD.open("celsius.txt", FILE_WRITE); // open or create celsiusData to write to on SD card
  if (celsiusFile){
    celsiusFile.println(celsius);
    celsiusFile.close(); // close the file
  } else {
    Serial.println("Error opening celsius.txt during loop.");
  }
  
  outputFile = SD.open("output.txt", FILE_WRITE); // open or create outputData to write to on SD card
  if (outputFile){
  outputFile.println(output);
  outputFile.close(); // close the file
  } else {
    Serial.println("Error opening output.txt during loop.");
  }
  Serial.print(celsius);
  Serial.println(" C");
  Serial.print(fahrenheit);
  Serial.println(" F");
  Serial.print(output);
  Serial.println(" V");
}
