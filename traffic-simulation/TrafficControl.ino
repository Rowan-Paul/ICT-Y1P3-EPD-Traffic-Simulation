const int GREEN_LIGHT1_PIN = 5;
const int ORANGE_LIGHT1_PIN = 6;
const int RED_LIGHT1_PIN = 7;

const int GREEN_LIGHT2_PIN = 9;
const int ORANGE_LIGHT2_PIN = 10;
const int RED_LIGHT2_PIN = 11;

boolean checkTrafficLightsRed() {
  if (trafficLight1 == "RED" && trafficLight2 == "RED") {
    return true;
  } else {
    return false;
  }
}

void setTrafficLightGreen(String trafficLight) {
  if (checkTrafficLightsRed()) {
    // set light to green
    if (trafficLight == "trafficLight1") {
      ledControlSetLedOff(RED_LIGHT1_PIN);
      ledControlSetLedOff(ORANGE_LIGHT1_PIN);

      ledControlSetLedOn(GREEN_LIGHT1_PIN);
      trafficLight1 = "GREEN";
    } else if (trafficLight == "trafficLight2") {
      ledControlSetLedOff(RED_LIGHT2_PIN);
      ledControlSetLedOff(ORANGE_LIGHT2_PIN);

      ledControlSetLedOn(GREEN_LIGHT2_PIN);
      trafficLight2 = "GREEN";
    }
  }
}

void setTrafficLightOrange(String trafficLight) {
  if (trafficLight == "trafficLight1") {
    ledControlSetLedOff(RED_LIGHT1_PIN);
    ledControlSetLedOff(GREEN_LIGHT1_PIN);

    ledControlSetLedOn(ORANGE_LIGHT1_PIN);
    trafficLight1 = "ORANGE";
  } else if (trafficLight == "trafficLight2") {
    ledControlSetLedOff(RED_LIGHT2_PIN);
    ledControlSetLedOff(GREEN_LIGHT2_PIN);

    ledControlSetLedOn(ORANGE_LIGHT2_PIN);
    trafficLight2 = "ORANGE";
  }
}

void setTrafficLightRed(String trafficLight) {
  if (trafficLight == "trafficLight1") {
    ledControlSetLedOff(ORANGE_LIGHT1_PIN);
    ledControlSetLedOff(GREEN_LIGHT1_PIN);

    ledControlSetLedOn(RED_LIGHT1_PIN);
    trafficLight1 = "RED";
  } else if (trafficLight == "trafficLight2") {
    ledControlSetLedOff(ORANGE_LIGHT2_PIN);
    ledControlSetLedOff(GREEN_LIGHT2_PIN);

    ledControlSetLedOn(RED_LIGHT2_PIN);
    trafficLight2 = "RED";
  }
}
