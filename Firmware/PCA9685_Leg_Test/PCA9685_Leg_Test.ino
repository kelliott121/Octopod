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
#include <Octopod.h>

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

Servo one(&pwm0, 0, 180, SERVOMIN, SERVOMAX, 0);
Servo two(&pwm0, 1, 180, SERVOMIN, SERVOMAX, 1);
Servo three(&pwm0, 2, 180, SERVOMIN, SERVOMAX, 0);
Servo four(&pwm0, 3, 180, SERVOMIN, SERVOMAX, 0);
Servo five(&pwm0, 4, 180, SERVOMIN, SERVOMAX, 1);
Servo six(&pwm0, 5, 180, SERVOMIN, SERVOMAX, 0);

Joint oneJoint(&one, 0);
Joint twoJoint(&two, 0);
Joint threeJoint(&three, 0);
Joint fourJoint(&four, 0);
Joint fiveJoint(&five, 0);
Joint sixJoint(&six, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm0.begin();
  pwm1.begin();

  pwm0.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(1000);

  oneJoint.home();
  twoJoint.home();
  threeJoint.home();
  fourJoint.home();
  fiveJoint.home();
  sixJoint.home();
}

void loop()
{
  delay(500);

  threeJoint.setAngle(30);
  
  delay(500);
  
  oneJoint.setAngle(15);

  delay(500);

  threeJoint.home();

  delay(500);

  oneJoint.home();
  
  delay(500);

  sixJoint.setAngle(30);
  
  delay(500);
  
  fourJoint.setAngle(15);

  delay(500);

  sixJoint.home();

  delay(500);

  fourJoint.home();
}

