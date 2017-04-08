/* This file uses an IR receiver and LCD to dispaly the code used 
 * for each button on random remote controls.
 * 
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <LiquidCrystal.h>


int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // initialise library with these pins

decode_results results;

void setup()
{
  Serial.begin(9600); // start serial monitor
  
  lcd.begin(16, 2); // our lcd has 16 columns and 2 rows
  
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // place the cursor at column 0, line 0 of lcd display (remember: line 1 is 0, line 2 is 1)
  lcd.setCursor(0, 0);
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
     lcd.clear();
    lcd.print(results.value, HEX);
    delay(5000); // change this if the value is disappearing too quickly

    lcd.clear();
    lcd.print("next button");
    
    irrecv.resume(); // Receive the next value
  }
    
  delay(100);
}
