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
boolean pressed = false;
int sw_state;            // nextstate system
int sw_laststate = LOW;
int counter = 0;

int signal;

unsigned long start;
unsigned long passed_time;

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

    dotOrDash();


} // end void loop






// function returns a dot or dash value
void dotOrDash()
{
  
  if (sw_state == HIGH && sw_laststate == LOW)
  {  // for button pressing
    start_hold = millis();                       // mark the time
    allow = true;    // allow LED state changes
    pressed = true;
  } // end if
  
  // dash
  if( allow == true && sw_state == HIGH && sw_laststate == HIGH)
  {  // if button remains pressed
      if ((millis() - start_hold) >= HOLD_DELAY)
      {                   // for longer than x/1000 sec(s)
         allow = false;         // prevent multiple state changes
         Serial.println("Dash");
         counter++;
         Serial.println(counter);
         start = millis();

      } // end inner if
  } // end outer if
  
  // dot
  if( allow == true && sw_state == LOW && sw_laststate == HIGH)
  {
    
    if( (millis() - start_hold) < HOLD_DELAY && ((millis()-start_hold) > CLICK_DELAY))
    {
      allow = false;
      Serial.println("Dot");
      counter++;
      Serial.println(counter);
      start = millis();
    }
  } // end outer if
  
  if( sw_state == HIGH && sw_laststate == HIGH)
  {
    start = millis();
  }
  

  
  
   if( pressed == true && sw_state == LOW && sw_laststate == LOW)
   {
     passed_time = millis()-start;
     if(passed_time > 5000)
     {
       pressed = false;
       Serial.println("5 seconds passed");
     }
   }
     

  
  
  sw_laststate = sw_state;
  
  
  
  
  
} // end dotOrDash

