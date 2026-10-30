
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
#define LEDPIN 8

// Set the LCD address to 0x27 or 0x3F (common for I2C LCDs) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  float temperature = dht.readTemperature();

  lcd.clear(); // Clear the screen for new data

  if (isnan(temperature)) {
    Serial.println("Sensor error");
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
    delay(2000);
    return;
  }

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  // Print temperature on LCD Line 1
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Check threshold and update LED + LCD Line 2
  lcd.setCursor(0, 1);
  if (temperature >= 38) {
    digitalWrite(LEDPIN, HIGH);
    lcd.print("WARNING!");
  } else {
    digitalWrite(LEDPIN, LOW);
    lcd.print("Normal");
  }

  delay(2000);
}
