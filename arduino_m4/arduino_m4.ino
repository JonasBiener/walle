#include <RPC.h>

#define LED_GREEN_PIN 2
#define LED_RED_PIN 3
#define LED_BLUE_PIN 4


#define BTSTATE_ADVERTISING 1
#define BTSTATE_PAIRING 2
#define BTSTATE_CONNECTED 3

uint8_t led_state = 0;
uint8_t bt_state = BTSTATE_ADVERTISING;

void setup() {
  RPC.begin();
  RPC.bind("setLEDState", setLEDState);
  RPC.bind("setBTState", setBTState);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_RED_PIN, 0);
  digitalWrite(LED_GREEN_PIN, 0);
  digitalWrite(LED_BLUE_PIN, 0);
}
digi
void loop() { 
  runLEDThread();
  runBTThread();
}

void setLEDState(uint8_t state) {
  led_state = state;
}

void setBTState(uint8_t state) {
  bt_state = state;
}

inline void runLEDThread() {
  digitalWrite(LED_GREEN_PIN, led_state);
  digitalWrite(LED_RED_PIN, !led_state);
}

inline void runBTThread() {
  if (bt_state == BTSTATE_ADVERTISING) digitalWrite(LED_BLUE_PIN, (millis() % 1000) < 500);
  else if (bt_state == BTSTATE_PAIRING) digitalWrite(LED_BLUE_PIN, (millis() % 250) < 125);
  else if (bt_state == BTSTATE_CONNECTED) digitalWrite(LED_BLUE_PIN, 1);
}