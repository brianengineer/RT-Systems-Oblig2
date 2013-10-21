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
int signals[4] = {0,0,0,0};



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

// store morse signals in array signal
void setSignals(int count, int value )
{
  signals[count-1] = value;
} // end setSignal





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
         //Serial.println("Dash");
         counter++;
         setSignals(counter, 2);
         //Serial.println(counter);
         start = millis();

      } // end inner if
  } // end outer if
  
  // dot
  if( allow == true && sw_state == LOW && sw_laststate == HIGH)
  {
    
    if( (millis() - start_hold) < HOLD_DELAY && ((millis()-start_hold) > CLICK_DELAY))
    {
      allow = false;
      //Serial.println("Dot");
      counter++;
      setSignals(counter, 1);
      //Serial.println(counter);
      start = millis();
    }
  } // end outer if
  
  if( sw_state == HIGH && sw_laststate == HIGH)
  {
    start = millis();
  }
  

  
   // reset data and call function interpret to display character equivalent to morse code
   if( pressed == true && sw_state == LOW && sw_laststate == LOW)
   {
     passed_time = millis()-start;
     if(passed_time > 5000)
     {
       pressed = false;
       //Serial.println("5 seconds passed");
       displayChar(counter);
       counter = 0;
     } // end inner if
   } // end if

  sw_laststate = sw_state;
} // end dotOrDash

// display char equal to signs input
void displayChar(int count)
{
  switch (count)
  {
    case 1:
      if(signals[0] == 1)
        Serial.print("E");
      else if(signals[0]==2)
        Serial.print("T");
      break;
    case 2:
      
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      break;
        Serial.print("Invalid Combination Found!");
  } // end switch
  
  for(int i = 0; i < 4; i++)
  {
    signals[i] = 0;
  } // end for loop
} // end display char    
  
  
  
  
  
  
