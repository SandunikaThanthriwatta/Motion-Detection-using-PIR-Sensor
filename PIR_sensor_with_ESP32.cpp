//ESP32 with PIR Motion Sensor using Interrupts and Timers

#define timeSeconds 1

// Set GPIOs for PIR Motion Sensor

const int motionSensor = 27;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected and starts a timer
void IRAM_ATTR detectsMovement() {
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);


}

void loop() {
  // Current time
  now = millis();

  //print message in serial monitor when motion is detected
  if((startTimer == true)&&(motion == false)) {
    Serial.println("MOTION DETECTED!!!");
    motion = true;
  }
  // Print message 'motion stopped' in serial monitor after the number of seconds defined in the timeSeconds variable
  if((motion == true)&& ((now - lastTrigger) > (timeSeconds*1000))) {
    Serial.println("Motion stopped...");
    startTimer = false;
    motion = false;
  }
}