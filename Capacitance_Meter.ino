#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define analogPin 0
#define chargePin 13
#define dischargePin 8
#define resistorValue 10000.0F // Since we've used a 10K resistor to charge the capacitor
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;

void setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(19, 0);
    pinMode(chargePin, OUTPUT);
    digitalWrite(chargePin, LOW);
    lcd.print("Capacitance");
    lcd.setCursor(23, 1);
    lcd.print("meter");
    delay(500);

    for (int positionCounter = 0; positionCounter < 17; positionCounter++)
    { // Animation for Loops
        lcd.scrollDisplayLeft();
        delay(150);
    }
    delay(1000);
    for (int positionCounter = 16; positionCounter < 32; positionCounter++)
    {
        lcd.scrollDisplayLeft();
        delay(150);
    }
    lcd.clear();
}

void loop()
{
    digitalWrite(chargePin, HIGH);
    startTime = micros();
    while (analogRead(analogPin) < 648)
    {
    }
    elapsedTime = micros() - startTime;
    microFarads = ((float)elapsedTime / resistorValue);

    if (microFarads > 1)
    {
        lcd.setCursor(0, 0);
        lcd.print("SCALE:  0.1uF-4F");
        lcd.setCursor(0, 1);
        lcd.print(microFarads - 0.0116);
        lcd.setCursor(14, 1);
        lcd.print("uF");
        delay(500);
    }
    else
    {
        nanoFarads = microFarads * 1000.0;
        lcd.setCursor(0, 0);
        lcd.print("SCALE: 1nF-0.1uF");
        lcd.setCursor(0, 1);
        lcd.print(nanoFarads - 11.2);
        lcd.setCursor(14, 1);
        lcd.print("nF");
        delay(500);
    }
    digitalWrite(chargePin, LOW);
    pinMode(dischargePin, OUTPUT);
    digitalWrite(dischargePin, LOW); // discharging the capacitor
    while (analogRead(analogPin) > 0)
    {
    }                             // This while waits till the capacitor is discharged
    pinMode(dischargePin, INPUT); // this sets the pin to high impedance
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISCHARGING.....");
    lcd.setCursor(0, 1);
}