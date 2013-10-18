/*
 *  Press & Hold Switch LED program
 */

// Parameters
int HOLD_DELAY = 500;    // Sets the hold delay of switch for LED state change
int HOLD_CLICK = 70;
 
int ledPin     = 9;      // LED is connected to pin x
int switchPin  = 3;      // Switch is connected to pin x
 
// In-Program Variables 
unsigned long start_hold;
boolean allow = false;
int sw_state;
int sw_laststate = LOW;
int led_state = LOW;
 
// Setup
void setup() 
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);      // Set the LED pin as output
  pinMode(switchPin, INPUT);    // Set the switch pin as input
}
 
// Loop
void loop()
{
  sw_state = digitalRead(switchPin);             // read input value
  
  if (sw_state == HIGH && sw_laststate == LOW)
  {  // for button pressing
    start_hold = millis();                       // mark the time
    allow = true;                                // allow LED state changes
  } // end if
     
  if (allow == true && sw_state == HIGH && sw_laststate == HIGH)
  {  // if button remains pressed
      if ((millis() - start_hold) >= HOLD_DELAY)
      {                   // for longer than x/1000 sec(s)
         led_state = !led_state;                                   // change state of LED
         allow = false;         // prevent multiple state changes
         Serial.println("Dash");
      } // end inner if
      else if( (millis() - start_hold) < HOLD_DELAY && ( (millis() - start_hold) >= HOLD_CLICK) )
      {
        
          Serial.println("Dot"); // :) dot dot dot dash dash dash dot dot dot
      }
      
  } // end outer if
 
  sw_laststate = sw_state;   
  digitalWrite(ledPin, led_state);
} // end void loop

