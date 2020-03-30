const int TRAFFIC_LIGHT1_DATA_PIN = A5;
const int TRAFFIC_LIGHT2_DATA_PIN = A4;
const int PEDESTRIAN_CROSSING_DATA_PIN = A3;

int currentStateTrafficLight1 = 3;
int currentStateTrafficLight2 = 3;
int currentStatePedestrianCrossing = 3;
int currentState = 3;

int ledState = LOW;

// timers
unsigned long trafficTimer;
const unsigned long ORANGE_TIMER_INTERVAL = 5000;
const unsigned long RED_TIMER_INTERVAL = 2000;
const unsigned long NIGHT_TIMER_INTERVAL = 750;

// font
const byte FONTS[] = {
  B10010010, //3 stripes
  B11111010, //6
  B11011010, //5
  B11001001, //4
  B10011011, //3
  B10110011, //2
  B00001001, //1
};

void stateMachineSetup() {
  buttonSetup(TRAFFIC_LIGHT1_DATA_PIN);
  buttonSetup(TRAFFIC_LIGHT2_DATA_PIN);
  buttonSetup(PEDESTRIAN_CROSSING_DATA_PIN);

  ledControlSetup();
  buzzerSetup();
  servoSetup();
  shiftSetup();
  ldrSetup();
}

void stateMachineLoop() {
  switch (currentState) {
    case 1:
      servoWrite(180);
      noTone(BUZZER);
      shiftSetPattern(B01110010);

      // blinking orange lights
      if (timerIsPassed(trafficTimer, NIGHT_TIMER_INTERVAL)) {
        trafficTimer = timerReset();

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(9, ledState);
        digitalWrite(12, ledState);
      }

      if (ldrGetValue() < 200) {
        currentState = 2;
      }
      break;
    case 2:
      servoWrite(180);
      buzzerSlowSound();
      setTrafficLightOrange("trafficLight1");
      setTrafficLightOrange("trafficLight2");

      currentState = 3;
      break;
    case 3:
      pedestrianCrossing();
      trafficLight1();
      trafficLight2();

      if (ldrGetValue() > 300) {
        currentState = 1;
        ledControlSetAllLedsOff();
      }
  }
}

void pedestrianCrossing() {
  switch (currentStatePedestrianCrossing) {
    case 1:
      servoWrite(180);
      buzzerFastSound();

      // show walk sign
      // count down from 6 to 1
      countdownDisplay();
      break;
    case 2:

      break;
    case 3:
      servoWrite(0);
      buzzerSlowSound();
      shiftSetPattern(B11101001);
  }

  if (buttonPressed(PEDESTRIAN_CROSSING_DATA_PIN) && checkTrafficLightsRed()) {
    currentStatePedestrianCrossing = 1;
  }
}

void trafficLight1() {
  switch (currentStateTrafficLight1) {
    case 1:
      setTrafficLightGreen("trafficLight1");

      // Wait 5 seconds and switch to orange
      if (timerIsPassed(trafficTimer, ORANGE_TIMER_INTERVAL)) {
        trafficTimer = timerReset();

        currentStateTrafficLight1 = 2;
      }
      break;
    case 2:
      setTrafficLightOrange("trafficLight1");

      // Wait 2 seconds and switch to orange
      if (timerIsPassed(trafficTimer, RED_TIMER_INTERVAL)) {
        currentStateTrafficLight1 = 3;
      }
      break;
    case 3:
      setTrafficLightRed("trafficLight1");

      // Check if button is pressed and all lights are red
      // then switch to green
      if (buttonPressed(TRAFFIC_LIGHT1_DATA_PIN) && checkTrafficLightsRed()) {
        trafficTimer = timerReset();

        currentStateTrafficLight1 = 1;
      }
      break;
  }
}

void trafficLight2() {
  switch (currentStateTrafficLight2) {
    case 1:
      setTrafficLightGreen("trafficLight2");

      // Wait 5 seconds and switch to orange
      if (timerIsPassed(trafficTimer, ORANGE_TIMER_INTERVAL)) {
        trafficTimer = timerReset();

        currentStateTrafficLight2 = 2;
      }
      break;
    case 2:
      setTrafficLightOrange("trafficLight2");

      // Wait 2 seconds and switch to orange
      if (timerIsPassed(trafficTimer, RED_TIMER_INTERVAL)) {
        currentStateTrafficLight2 = 3;
      }
      break;
    case 3:
      setTrafficLightRed("trafficLight2");

      // Check if button is pressed and all lights are red
      // then switch to green
      if (buttonPressed(TRAFFIC_LIGHT2_DATA_PIN) && checkTrafficLightsRed()) {
        trafficTimer = timerReset();

        currentStateTrafficLight2 = 1;
      }
      break;
  }
}
