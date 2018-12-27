/* ---------------------------------------------------------------------
 *  Original sources are:
 *    https://randomnerdtutorials.com/complete-guide-for--sensor-hc-sr04/
 *    https://programmingelectronics.com/an-easy-way-to-make-noise-with-arduino-using-tone/
 */

int piezoPin = 8;
/*
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int triggerPin = 11;    // Trigger
int echoPin = 12;    // Echo

void setup() {
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(piezoPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

static void readToneSensor(int&& cm, int&& inches)
{ 
  long duration;
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
}


void loop() {
  long cm, inches;
  
  readToneSensor(cm, inches);
  if (cm > 10 && cm < 40) {
    tone(piezoPin, cm*100);
  } else {
    noTone(piezoPin);
  }
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
