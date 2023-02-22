
const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 12;
const int motorPin = 9;

int farest = 190;
int maximum = 100;
int nearest = 50;

// defines variables
long duration;
int distance;

void setup() {
 pinMode(motorPin, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034027/2;
// Prints the distance on the Serial Monitor
int motorSpeed = 427-(distance*1.7);
   if (distance >= farest)
     {
      Serial.print("Distance: ");
      Serial.println(distance);
      analogWrite(motorPin, 100); 
      delay (500);
      }
    if 
    (distance < farest && distance >= maximum)
    {  
       analogWrite(motorPin, motorSpeed);
       Serial.print("Distance: ");
       Serial.println(distance);
       Serial.print("MotorSpeed: ");
       Serial.println(motorSpeed);
       delay (500);
    }
    if
    (distance < maximum && distance >= nearest)
    {  
       analogWrite(motorPin, 255);
       Serial.print("Distance: ");
       Serial.println(distance);
       delay (500);
    }
    if (distance < nearest)
    {
      digitalWrite (motorPin, LOW); 
      Serial.print("Distance: ");
      Serial.println(distance);
      tone(buzzerPin, 1397, 400); 
      delay (500);
     }
     noTone(buzzerPin);
}
