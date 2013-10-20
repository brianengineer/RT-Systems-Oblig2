// should print on screen the time the button was pressed

const int buttonPin = 2; // number of input pin
long durationPressed;
long startTime = 0; // value returned from millis when the button is pressed
long duration = 0; // value to store duration of button press time

void setup()
{
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, LOW); // turn on pull-up resistor
  Serial.begin(115200);
}

void loop()
{
  
  if(digitalRead(buttonPin) == LOW)
    durationPressed = dotOrDash();
     
} // end loop







long dotOrDash()
{
  
  
  // here if the switch is pressed
    startTime = millis();
  while(digitalRead(buttonPin) == LOW);
  // wait while the button is still pressed
  duration = millis() - startTime;
  Serial.println(durationPressed);
} // end function dotOrDash
