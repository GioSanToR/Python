// MIDI Shield
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator
int  instrument;

int Notes0[] = {69,81,93};
int Notes1[] = {72,84,96};
int Notes2[] = {80,92,104};

// End MIDI Shield
//Conductivity

int inputPin0 = A0;
int inputPin1 = A1;
int inputPin2 = A2;


const float closedVoltage = 5.00;                //assumed value of voltage (replace with vcc)

const float voltageRange = closedVoltage/1023;   //Used to map the analog reading to the voltage of the circuit.

const float resistor = 10000.00;                  //size of resistor on the ground line

int conductReading0 = 0;                        //reading from A0 pin
int conductReading1 = 0;                        //reading from A1 pin
int conductReading2 = 0;                        //reading from A2 pin

float conductVoltage0 = 0.00;                  //calculated voltage from reading
float conductVoltage1 = 0.00; 
float conductVoltage2 = 0.00; 

float resistance0 = 0.00;                    //calculated resistance of water (ohms)
float resistance1 = 0.00; 
float resistance2 = 0.00; 

float area = 0.0002;                          //area of the all four sides of the electrodes in square meters

float length = 0.01;                        //distance between the electrodes in meters

float resistivity0 = 0.0;                    //resistivity of fluid
float resistivity1 = 0.0; 
float resistivity2 = 0.0; 

float conductivity0 = 0.00;                  //calculated conductivity of water (micro-siemens/m)
float conductivity1 = 0.00;
float conductivity2 = 0.00;

// End Conductivity

void setup(){

 pinMode(inputPin0, INPUT);
 pinMode(inputPin1, INPUT);
 pinMode(inputPin2, INPUT);
 
Serial.begin(57600);

//Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); //0xB0 is channel message, set channel volume to near max (127)
 


}


void loop(){

talkMIDI(0xB0, 0, 0x00);  //Default bank GM1

talkMIDI(0xC0, instrument, 0); //Set instrument number. 0xC0 is a 1 data byte command
 
 instrument = 100; //Pedal Atmospheres Re2
 noteOn(0,38,50);

//Conductivity
 conductReading0 = analogRead(inputPin0);
 conductReading1 = analogRead(inputPin1);
 conductReading2 = analogRead(inputPin2);

 conductVoltage0 = conductReading0 * voltageRange;
 conductVoltage1 = conductReading1 * voltageRange;
 conductVoltage2 = conductReading2 * voltageRange;

 resistance0 = ((closedVoltage * resistor)/conductVoltage0) - resistor;
 resistance1 = ((closedVoltage * resistor)/conductVoltage1) - resistor;
 resistance2 = ((closedVoltage * resistor)/conductVoltage2) - resistor;

 resistivity0 = resistance0 * area / length;
 resistivity1 = resistance1 * area / length;
 resistivity2 = resistance2 * area / length;

 conductivity0 = (1 / resistivity0)*1000;
 conductivity1 = (1 / resistivity1)*1000;
 conductivity2 = (1 / resistivity2)*1000;
 
Serial.print(", Conductivity A0 (milliSiemens/m) =");
Serial.println(conductivity0);
Serial.print(", Conductivity A1 (milliSiemens/m) =");
Serial.println(conductivity1);
Serial.print(", Conductivity A2 (milliSiemens/m) =");
Serial.println(conductivity2);

// End Conductivity

if (conductivity0 < 15 ) {

  instrument = 96; //Efecto Lluvia 
  noteOn(0, Notes0[0],50);
  delay(100);
  noteOff(0,Notes0[0],50); 
  delay(50);
  }

if (conductivity0 >= 15 & conductivity0 < 30) {

  instrument = 96; 
  noteOn(0, Notes0[1],50);
  delay(100);
  noteOff(0,Notes0[1],50); 
  delay(50);
}

if (conductivity0 >= 30 ) {
  
  instrument = 96;  
  noteOn(0, Notes0[2],50);
  delay(100);
  noteOff(0,Notes0[2],50); 
  delay(50);
}

if (conductivity1 < 15 ) {

  instrument = 99; //Efecto Crystal 
  noteOn(0, Notes1[0],50);
  delay(100);
  noteOff(0,Notes1[0],50); 
  delay(50);
  }

if (conductivity1 >= 15 & conductivity1 < 30) {

  instrument = 99; 
  noteOn(0, Notes1[1],50);
  delay(100);
  noteOff(0,Notes1[1],50); 
  delay(50);
}

if (conductivity1 < 15 ) {
  
  instrument = 99; 
  noteOn(0, Notes1[2],50);
  delay(100);
  noteOff(0,Notes1[2],50); 
  delay(50);
}
if (conductivity1 < 15 ) {

  instrument = 114; //Efecto Agogo 
  noteOn(0, Notes2[0],50);
  delay(100);
  noteOff(0,Notes2[0],50); 
  delay(50);
  }

if (conductivity1 >= 15 & conductivity1 < 30) {

  instrument = 114; 
  noteOn(0, Notes2[1],50);
  delay(100);
  noteOff(0,Notes2[1],50); 
  delay(50);
}

if (conductivity1 >= 30 ) {
  
  instrument = 114; 
  noteOn(0, Notes2[2],50);
  delay(100);
  noteOff(0,Notes2[2],50); 
  delay(50);
}
}

void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
