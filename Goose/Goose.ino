#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

const char* payload[] = {
  "GUI r",           // Win+R
  "DELAY 500",
  "powershell",
  "ENTER",
  "DELAY 800",
  "STRING Hello!",
};

void setup() {
  USB.begin();
  Keyboard.begin();
  delay(2000); // wait for enumeration
  runPayload();
}

void runPayload() {
  // parse & execute each line
  for (auto line : payload) {
    executeLine(line);
  }
}