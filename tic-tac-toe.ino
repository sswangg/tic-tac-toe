#include <Keypad.h>

const byte ROWS = 3;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','4','7'},
  {'2','5','8'},
  {'3','6','9'},
};
byte rowPins[ROWS] = {A0, A1, A2};
byte colPins[COLS] = {A3, A4, A5};
int turn = 0;
int pin;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
  for (int i = 34; i <= 53; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  digitalWrite(35, LOW);
  digitalWrite(34, HIGH);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    pin = 34+String(key).toInt()*2+turn%2;
    if (digitalRead(pin) == 0 && !(turn%2 == 1 && digitalRead(pin-1) == 1) && !(turn%2 == 0 && digitalRead(pin+1) == 1)) {
      digitalWrite(pin, HIGH);
      turn++;
      delay(40);
      if (turn%2 == 0) {
        digitalWrite(34, HIGH);
        digitalWrite(35, LOW);
      } else {
        digitalWrite(34, LOW);
        digitalWrite(35, HIGH);
      }
    }
    if (win() > -1) {
      int w = win();
      for (int t = 0; t < 3; t++) {
        delay(300);
        for (int i = 34; i <= 53; i++) {
          digitalWrite(i, LOW);
        }
        delay(300);
        for (int i = 34; i <= 53; i+=2) {
          if (w == 0 || w == 2) digitalWrite(i, HIGH);
          if (w == 1 || w == 2) digitalWrite(i+1, HIGH);
        }
      }
    }
  }
}

int win(){
  for (int i = 36; i <= 40; i+=2) {
    if (digitalRead(i) && digitalRead(i+6) && digitalRead(i+12)) return 0;
  }
  for (int i = 36; i <= 48; i+=6) {
    if (digitalRead(i) && digitalRead(i+2) && digitalRead(i+4)) return 0;
  }
  if (digitalRead(36) && digitalRead(44) && digitalRead(52)) return 0;
  if (digitalRead(48) && digitalRead(44) && digitalRead(40)) return 0;
 
  for (int i = 37; i <= 41; i+=2) {
    if (digitalRead(i) && digitalRead(i+6) && digitalRead(i+12)) return 1;
  }
  for (int i = 37; i <= 49; i+=6) {
    if (digitalRead(i) && digitalRead(i+2) && digitalRead(i+4)) return 1;
  }
  if (digitalRead(37) && digitalRead(45) && digitalRead(53)) return 1;
  if (digitalRead(49) && digitalRead(45) && digitalRead(41)) return 1;

  if ((digitalRead(36)||digitalRead(37)) && (digitalRead(38)||digitalRead(39)) && (digitalRead(40)||digitalRead(41))
  && (digitalRead(42)||digitalRead(43)) && (digitalRead(44)||digitalRead(45)) && (digitalRead(46)||digitalRead(47))
  && (digitalRead(48)||digitalRead(49)) && (digitalRead(50)||digitalRead(51)) && (digitalRead(52)||digitalRead(53))) return 2;

  return -1;
}
