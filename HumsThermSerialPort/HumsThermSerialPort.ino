// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// Rewriting this to use Pi Arduino IDE and node js
// See index.js in /home/pi/Desktop/serialportdev/
#include "DHT.h"

//#define DHTPIN 2     // what pin we're connected to
#define DHTPIN 7     // what pin we're connected to
#define DHTPIN2 2     // what pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht1(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);
#include <math.h>

double Thermistor(int RawADC) {
 double Temp;
// Temp = log(10000.0*((600.0/RawADC-1)));
 Temp = log(10000.0/(1024.0/RawADC-1)); // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup() {
 Serial.begin(9600);
   Serial.println("DHTxx test!");

  dht1.begin();
  dht2.begin();
 	pinMode(13, OUTPUT); // this is for the LED?
}

void loop() {
//	Serial.println(int(analogRead(A0)));
 Serial.print((Thermistor(analogRead(A0))));  // display Fahrenheit
 Serial.print("\t");
 delay(2000);
  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht1.readHumidity();
  // Read temperature as Celsius
  float t = dht1.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht1.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("1. Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  // float hi = dht1.computeHeatIndex(f, h);

  Serial.print("Short7.  Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  //Serial.print("Heat index: ");
  //Serial.print(hi);
  //Serial.println(" *F");

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit
  float f2 = dht2.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("2. Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Long2.  Humidity: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t2);
  Serial.print(" *C ");
  Serial.print(f2);
  Serial.println(" *F\t");
  //Serial.print("Heat index: ");
  //Serial.print(hi);
  //Serial.println(" *F");

	//Sync on board led with transmission
	//Set the LED pin to HIGH. This gives power to the LED and turns it on
	digitalWrite(13, HIGH);
	//Wait for a while
	delay(1);
	//Set the LED pin to LOW. This turns it off
	digitalWrite(13, LOW);
}

