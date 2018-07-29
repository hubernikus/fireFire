/* WS2108 - Fire controller */

int potPin = 2; // Potentiometer pin
int ledPin = 9; // PWM pin for LEDs

// Program timestep
float dt=0.1; // s

// Fire intesity change
int fire_flickerIntens = 40;
float fireVal = 0;
float fireDecay = 0.98;

// Potentiometer transimtion 
float potTransmition= 128; // = 128./3 *60/180
int potDir = 1; // 1 or -1 -- decide through testing
int potVal_old = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  
  randomSeed(analogRead(0));
  
  // Set up fire decay with Half life time of t_2=15s
  int n_t2 = 10/dt;
  fireDecay = pow(0.5,(1./n_t2) ); // 0.5 - half life time
  
  // Set up potentiometer tranmition
  // angle of potentiometer - 60 deg/180
  // 3 cycle to pump fire up (128/3)
  potTransmition=128;
  
  // Initialize potentiometer value
  potVal_old = analogRead(potPin);
  
}

void loop()
{
  // Read potentiometer
  int potVal = analogRead(potPin);
  int deltaPot = potVal_old - potVal;
  potVal_old = potVal;
  
  // Update Fire PWN
  fireVal = min(fireVal + max(potDir*deltaPot,0)*potTransmition, 128); // update fire, limit to maximum of 128
  
  // Add natural fire variation
  int fireVal_natural = fireVal + random(0, fire_flickerIntens); // add white noise to fire
  analogWrite(ledPin, fireVal_natural); // Set PWM
  
  // Decay of fire
  fireVal = fireVal*fireDecay;
  
  delay(dt); // Change to wait constant time. Maybe.. Random time might be nice too. Do something with it or remain silent forever.
}






