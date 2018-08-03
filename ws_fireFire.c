#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main( ) {
    /* WS2108 - Fire controller */

  int potPin = 2; // Potentiometer pin
  int ledPin = 9; // PWM pin for LEDs

  // Program timestep
  float dt=0.1; // s

  // Fire intesity change
  int fire_flickerIntens = 40;
  float fireVal = 0;
  float fireDecay = 0.98;
  int fireMax = 255; // Maximum fire value for PWM

  // Potentiometer transimtion
  int potDir = 1; // 1 or -1 -- decide through testing
  int potVal_old = 0;

  //! pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT

  //! randomSeed(analogRead(0));
  srand(time(NULL));

  // Set up fire decay with Half life time of t_2=15s
  dt = 1;
  int n_t2 = 15/dt;

  //fireDecay = pow(0.5, (1./n_t2) ); // 0.5 - half life time
  float exp = (1./n_t2);
  printf("n_t2: %f", exp) ;
  double exp2 = 0.0667;
  fireDecay = pow(0.5, exp2 ) ;
  //fireDecay = 0.99538;
  //fireDecay = 0.5;

  // Set up potentiometer transition
  // angle of potentiometer - 60 deg/180
  // 3 cycle to pump fire up (128/3)
  float potTransmition= 2.55; // = 255./3 *60/180


  // Initialize potentiometer value
  //! potVal_old = analogRead(potPin);
  int potVal;
  printf( "\n Pot val :");
  scanf("%d", &potVal);

  int time_old=time(0);

  int n = 0; // loop counter
  while(1)
  {
    float time_new = time(0);
    int timeDiff = time_new-time_old;
    time_old = time_new;

    printf(" start loop again. N=%d", n);
    // Read potentiometer
    // ! int potVal = analogRead(potPin);
    printf( "\n New Pot val :");
    scanf("%d", &potVal);

    int deltaPot = potVal - potVal_old;
    potVal_old = potVal;

    // Update Fire PWN
    if(potDir*deltaPot<0){ deltaPot=0; }
    fireVal = fireVal + potDir*deltaPot*potTransmition; // update fire

    // Add natural fire variation
    //int fireFlickr = random(0, fire_flickerIntens); // add white noise to fire
    int fireFlickr  = rand() % fire_flickerIntens; // DO BETTER TO HAVE UNIFORMITY
    fireFlickr = 0;
    int fireVal_natural = fireFlickr + fireVal;
    if(fireVal_natural > fireMax){
        fireVal_natural=fireMax;
    }

    //! analogWrite(ledPin, min(fireVal_natural,, fireMax) ); // Set PWM
    printf( "\n Delta potVal: %d", deltaPot);
    printf( "\n Time diff: %d", timeDiff);
    printf( "\n LED strength: %d", fireVal_natural);

    //putchar( fireVal_natural );

    // Decay of fire
    fireVal = fireVal*fireDecay;
    if(fireVal > 2*fireMax){ // Let be able to save internally (2*fireMax
        fireVal = 2*fireMax;
    }
    //delay(dt); // Change to wait constant time. Maybe.. Random time might be nice too. Do something with it or remain silent forever.
    n++;
  }

  return 0;
}
