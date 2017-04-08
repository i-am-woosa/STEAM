#include <AFMotor.h>
#include <IRremote.h>

AF_DCMotor motorLEFT(3); //AF_DCMotor motor(motor#,frequency)
AF_DCMotor motorRIGHT(4);

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  motorLEFT.setSpeed(200); // set the speed between 200 - 255)
  motorRIGHT.setSpeed(200); // set the speed between 200 - 255)
}

void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?
  Serial.println(results.value, HEX); // show the code in the serial monitor
  {
    
    switch(results.value)

    {

    // place 0x in front of your IR codes

    case 0xE0E006F9: // forward button pressed
    Serial.println("Forward");
    motorLEFT.run(FORWARD);      // turn the left motor on to go forward
    motorRIGHT.run(FORWARD);     // turn the right motor on to go forward
    delay(1000);
    break;

    case 0xE0E08679: // backward button pressed
    Serial.println("Backward");
    motorLEFT.run(BACKWARD);    // turn the left motor on to go backward
    motorRIGHT.run(BACKWARD);   // turn the right motor on to go backward
    delay(1000);

    case 0xE0E0629D: // stop button pressed
    Serial.println("Stop");
    motorLEFT.run(RELEASE);   // turn the left motor off
    motorRIGHT.run(RELEASE);  // turn the right motor off
    delay(1000);

    case 0xE0E046B9: // right button pressed
    Serial.println("Right");
    motorLEFT.run(FORWARD);   // turn the left motor on to go forward
    motorRIGHT.run(RELEASE);  // turn the right motor off
    delay(1000);
    
    case 0xE0E0A659: // left button pressed
    Serial.println("Left");
    motorLEFT.run(RELEASE);   // turn the left motor off
    motorRIGHT.run(FORWARD);  // turn the right motor on to go forward
    delay(1000);
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
}
