// Use an old TV remote to control 
// a vehicle remotely using an IR sensor

// The IR decoder file (seperate to this file)
// will tell you which codes the buttons on 
// your remote produce. Replace the areas commented
// in the code below with your codes.

// Make sure to put the 0x in front of your code!

// by woosa for 2017 STEAM students

#include <IRremote.h>
#include <AFMotor.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

int go = 50;

AF_DCMotor motorLEFT(4); /* motor is connected to 
                            number 4 on motor shield */
AF_DCMotor motorRIGHT(3);

void setup() {
 Serial.begin(9600); /* set up Serial library at 9600 bps */
 irrecv.enableIRIn(); /* Start the receiver */
 
 /* tell motors what speed to start when the first button is pushed */
 
 motorRIGHT.setSpeed(go); /* motors won't work below 50 very well */
 motorRIGHT.run(RELEASE);  /* tells the motor to wait for user */
 motorLEFT.setSpeed(go);
 motorLEFT.run(RELEASE);
}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    if (results.value==0xE0E006F9){ // move forward
      
      motorRIGHT.run(FORWARD);
      motorLEFT.run(FORWARD);
    
      Serial.print("move forward \n");
      
    }

    if (results.value==0xE0E08679){ // move backward

      motorRIGHT.run(BACKWARD);
      motorLEFT.run(BACKWARD);
    
      Serial.print("move backward \n");
      
    }

    if (results.value==0xE0E046B9) { // turn left
      
      motorRIGHT.run(FORWARD);
      motorLEFT.run(RELEASE);
    
      Serial.print("turn left \n");
      
    }

    if (results.value==0xE0E0A659) { // trun right
      
      motorRIGHT.run(RELEASE);
      motorLEFT.run(FORWARD);
    
      Serial.print("turn right \n");
     
    }

    if (results.value==0xE0E0629D) { // stop
      
      motorRIGHT.run(RELEASE);
      motorLEFT.run(RELEASE);
    
      Serial.print("stop \n");
      int go = 50;
    }

      if ((results.value==0xE0E0629F) && (go >= 100)) { // slower
      
      motorRIGHT.setSpeed(go -= 50);
      motorLEFT.setSpeed(go -= 50);
      
      Serial.print("SLOWER \n");
      
    } 

    if ((results.value==0xE0E0629E) && (go <= 255)) { // faster
      
      motorRIGHT.setSpeed(go += 50);
      motorLEFT.setSpeed(go += 50);
      
      Serial.print("FASTER \n");
      
    }       
  }
}
