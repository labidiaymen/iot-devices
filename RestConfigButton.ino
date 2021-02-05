const int buttonPin = D2;        

int resetButtonState = 0;     // current state of the button
int resetLastButtonState = 0; // previous state of the button
int resetStartPressed = 0;    // the moment the button was pressed
int resetEndPressed = 0;      // the moment the button was released
int resetHoldTime = 0;        // how long the button was hold
int resetIdleTime = 0;        // how long the button was idle


  // resetButtonState = digitalRead(buttonPin);
  // Show the state of pushbutton on serial monitor
  // Serial.println(resetButtonState);

void resetButtonConfigLoop(){

  resetButtonState = digitalRead(buttonPin);
  //Serial.println(resetButtonState);
  resetButtonState = digitalRead(buttonPin); // read the button input

  if (resetButtonState != resetLastButtonState) { // button state changed
     updateResetButtonState();
  }

  resetLastButtonState = resetButtonState;   
}

void updateResetButtonState() {
  // the button has been just pressed
  if (resetButtonState == HIGH) {
      resetStartPressed = millis();
      resetIdleTime = resetStartPressed - resetEndPressed;

      if (resetIdleTime >= 500 && resetIdleTime < 1000) {
          // Serial.println("Button was idle for half a second");
      }

      if (resetIdleTime >= 1000) {
          // Serial.println("Button was idle for one second or more"); 
      }

  // the button has been just released
  } else {
      resetEndPressed = millis();
      resetHoldTime = resetEndPressed - resetStartPressed;
      smartConfig();
      if (resetHoldTime >= 100 && resetHoldTime <= 3000) {
          Serial.println("Button was hold for half a second"); 
      }

      if (resetHoldTime > 3000) {
          Serial.println("Button was hold for one second or more"); 
      }

  }
}
