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
  noTone(piezoPin);

}

static void readToneSensor(long* cm, long* inches)
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
 
  duration = pulseIn(echoPin, HIGH);
  Serial.print(duration);
  Serial.println();
  // Convert the time into a distance
  *cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  *inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  Serial.print(*cm);
  Serial.println();
}


void loop() {
  static long prevCm = 0;
  long cm, inches;
  double fc = 0.05;
  static double prevVal = 0.0;
  
  readToneSensor(&cm, &inches);
  if (cm > 10 && cm < 140) {
    //tone(piezoPin, cm*25);
    double freq = cm*15;
    freq = freq * fc + (1.0-fc)*prevVal;
    prevVal = freq;
    tone(piezoPin, long(freq));
    Serial.print(freq);
    Serial.println();
  } else {
    noTone(piezoPin);
  }
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //delay(250);

}
