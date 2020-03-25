const int TRAFFIC_LIGHT1_DATA_PIN = 4;
const int TRAFFIC_LIGHT2_DATA_PIN = 8;

// state of traffic lights
String trafficLight1 = "RED";
String trafficLight2 = "RED";

void stateMachineSetup() {
  buttonSetup(4);
  buttonSetup(8);
  ledControlSetup();

  // set traffic lights to red
  setTrafficLightRed("trafficLight1");
  setTrafficLightRed("trafficLight2");
}

void stateMachineLoop() {
  if (checkTrafficLightsRed()) {
    // check if a button is pressed
    if (buttonPressed(TRAFFIC_LIGHT1_DATA_PIN)) {
      setTrafficLightGreen("trafficLight1");

      // wait 5 seconds and jump to orange
      delay(5000);
      setTrafficLightOrange("trafficLight1");

      // wait 2 seconds and jump to red
      delay(2000);
      setTrafficLightRed("trafficLight1");

      //Serial.println("Button 1 pressed");
    } else if (buttonPressed(TRAFFIC_LIGHT2_DATA_PIN)) {
      if (checkTrafficLightsRed()) {
        setTrafficLightGreen("trafficLight2");
      }

      // wait 5 seconds and jump to orange
      delay(5000);
      setTrafficLightOrange("trafficLight2");

      // wait 2 seconds and jump to red
      delay(2000);
      setTrafficLightRed("trafficLight2");

      //Serial.println("Button 2 pressed");
    }
  }
}
