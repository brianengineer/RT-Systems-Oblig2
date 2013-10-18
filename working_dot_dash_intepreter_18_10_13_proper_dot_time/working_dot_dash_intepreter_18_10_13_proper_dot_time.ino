/*
 *  Dot and Dash Separation Program
 */

// Parameters
int HOLD_DELAY = 500;    // Sets the hold delay for the signal to be interpreted as a dash
int CLICK_DELAY = 20;    // singal minimum length to be a dot - avoid debounce
 
int switchPin  = 3;      // Switch is connected to pin 3
 
// In-Program Variables 
unsigned long start_hold;
boolean allow = false;
int sw_state;            // nextstate system
int sw_laststate = LOW;

// Setup
void setup() 
{
  Serial.begin(115200);
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
     
  if( allow == true && sw_state == HIGH && sw_laststate == HIGH)
  {  // if button remains pressed
    

      
      if ((millis() - start_hold) >= HOLD_DELAY)
      {                   // for longer than x/1000 sec(s)
         allow = false;         // prevent multiple state changes
         Serial.println("Dash");
      } // end inner if
  } // end outer if
  if( allow == true && sw_state == LOW && sw_laststate == HIGH)
  {
    if( (millis() - start_hold) < HOLD_DELAY && ((millis()-start_hold) > CLICK_DELAY))
    {
      allow = false;
      Serial.println("Dot");
    }
  }
 
  sw_laststate = sw_state;   
} // end void loop

