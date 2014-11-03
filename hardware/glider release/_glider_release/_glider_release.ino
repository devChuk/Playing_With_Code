const int swPin = 2; // pin 2 connected via switch to ground
const int acPin = 3; // pin 3 connected to gate of n-channel FET
const int LEDPin = 13; // pin 4 drives LED to indicate countdown active

int countdown = 240;//60; //countdown in seconds

void setup() {
  Serial.begin(9600);
  Serial.write("Powered up!\n"); // log stuff to serial for debugging purposes
  pinMode(swPin, INPUT_PULLUP); // no external pullup resistor required for switch
  pinMode(acPin, OUTPUT);
  digitalWrite(acPin, LOW); // don't actuate the actuator yet!
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
}

void loop() {
  if (!digitalRead(swPin)) {
    digitalWrite(LEDPin, HIGH);
    Serial.write("Beginning countdown!\n"); // log stuff to serial for debugging purposes
    digitalWrite(acPin, LOW);
    for(int n1 = countdown; n1 > 0; n1--) {
      digitalWrite(LEDPin, HIGH);
      delay(1000); // wait 1 second
      Serial.println(n1); // print countdown to serial, for debugging purposes
    }
    digitalWrite(acPin, HIGH); // actuate the actuator!
    digitalWrite(LEDPin, LOW);
  }
}
