                                                #include "DHT.h"
#include<LiquidCrystal.h>
String words;
LiquidCrystal lcd(12,13,5,4,3,2);
#define DHTPIN 7     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
   Serial.println(F("DHTxx test!"));
  dht.begin();
  lcd.begin(16,1);
    lcd.setCursor(0,0);
    lcd.print("Initialising.");
    delay(1000);
    lcd.clear();
    lcd.print("Initialising..");
    delay(1000);
    lcd.clear();
    lcd.print("Initialising...");
    delay(1000);
    lcd.clear();
    lcd.print("Maker : Techduino");
    delay(2000);
}

void loop() {
  lcd.clear();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance<10)
  {
    digitalWrite(8,HIGH);
    lcd.clear();
     lcd.setCursor(2,2);
     lcd.print(" OVER FLOW ");
     delay(3000);
  }
  else
  {
   digitalWrite(8,LOW);
  }
  
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  lcd.setCursor(0,0);
    lcd.print("Temp ");
    lcd.print(t);
   lcd.print(" Dis ");
   lcd.print(distance);
   delay(1200);
}
