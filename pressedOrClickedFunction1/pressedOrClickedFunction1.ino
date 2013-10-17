// should print on screen the time the button was pressed

const int buttonPin = 2; // number of input pin
long durationPressed;

void setup()
{
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // turn on pull-up resistor
  Serial.begin(115200);
}

void loop()
{
  if(digitalRead(buttonPin) == LOW)
    durationPressed = dotOrDash();
    Serial.println(durationPressed + " ms");
     
} // end loop







long dotOrDash()
{
  long startTime; // value returned from millis when the button is pressed
  long duration; // value to store duration of button press time
  
  // here if the switch is pressed
    startTime = millis();
  while(digitalRead(buttonPin) == LOW);
  // wait while the button is still pressed
  duration = millis() - startTime;
  
} // end function dotOrDash
