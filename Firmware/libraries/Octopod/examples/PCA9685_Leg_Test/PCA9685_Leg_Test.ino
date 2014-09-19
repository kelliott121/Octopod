/*************************************************** 
 * This is an example for our Adafruit 16-channel PWM & Servo driver
 * Servo test - this will drive 16 servos, one after the other
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/products/815
 * 
 * These displays use I2C to communicate, 2 pins are required to  
 * interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "/home/kelliott/Programming/Robotics/Octopod/Firmware/Servo.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm0(0x40);
Adafruit_PWMServoDriver pwm1(0x41);
// you can also call it with a different address you want

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define ANGLE_MAX 180
#define ANGLE_MIN 0

#define SERVO_HOME 90

#define JOINT(LEGNUM, JOINTNUM) (LEGNUM * 3 + JOINTNUM)

#define COXA        0  // create servo object for the coxa
#define TROCHANTER  1  // create servo object for the trochanter
#define PATELLA     2  // create servo object for the patella

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm0.begin();
  pwm1.begin();

  pwm0.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  delay(5000);
  
  Servo first(&pwm0, 0, 180, SERVOMIN, SERVOMAX, 0);
  first.sweep(5, 500);
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); 
  Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); 
  Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm0.setPWM(n, 0, pulse);
}

void loop() {
  /*
  setAngle(JOINT(0, TROCHANTER), 0);
  moveGradual(JOINT(0, PATELLA), 0, -30, 1);
  moveGradual(JOINT(0, COXA), 0, 15, 1);
  moveGradual(JOINT(0, PATELLA), -30, 0, 1);
  moveGradual(JOINT(0, COXA), 15, 0, 1);


  setAngle(JOINT(1, TROCHANTER), 0);
  moveGradual(JOINT(1, PATELLA), 0, -30, 1);
  moveGradual(JOINT(1, COXA), 0, 15, 1);
  moveGradual(JOINT(1, PATELLA), -30, 0, 1);
  moveGradual(JOINT(1, COXA), 15, 0, 1);
  */
  delay(1000);
}
/*
void homeAll()
{
  for (uint8_t servo = 0; servo < 32; servo++)
  {
    setAngle(servo, 0);
  }
}*/

/*void moveGradual(uint8_t servo, int16_t startAngle, int16_t endAngle, int16_t stepAngle)
{
  if (startAngle < endAngle)
  {
    for (int a = startAngle; a <= endAngle; a+=stepAngle)
    {
      setAngle(servo, a);
      delay(10);
    }
  }
  else
  {
    for (int a = startAngle; a >= endAngle; a-=stepAngle)
    {
      setAngle(servo, a);
      delay(10);
    }
  }
}*/

/*void setAngle(uint8_t servo, int16_t angle)
{
  uint8_t chipNum = 0;
  if (servo >= 16)
  {
    servo -= 16;
    angle *= -1;
    chipNum = 1;
  }
  unsigned int servo_range = SERVOMAX - SERVOMIN;
  unsigned int angle_range = ANGLE_MAX - ANGLE_MIN;
  unsigned int angle_set = (angle + SERVO_HOME) - ANGLE_MIN;

  float percentage = ((float)angle_set) / ((float)angle_range);
  pwm.setPWM(servo, 0, SERVOMIN + servo_range * percentage);
}*/


