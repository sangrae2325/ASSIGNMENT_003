#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A0

#define PIN_IR 0
#define PIN_LED 9
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 2026 // servo neutral position (90 degree)
#define _DUTY_MAX 3500 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)
#define _DIST_MIN 100.0
#define _DIST_MAX 250
#define _EMA_ALPHA 0.6

float  dist_ema, dist_prev = _DIST_MAX;

Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  pinMode(PIN_LED,OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;
 
  float dist;
  // Remove Next line !!!
  a_value = analogRead(PIN_IR);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
   dist = (6762.0/(a_value-9)-4.0)*10.0;
  // we need distance range filter here !!!
   if (dist <= _DIST_MIN) {
    dist = dist_prev;           // cut lower than minimum
    digitalWrite(PIN_LED,0);
  } else if (dist >= _DIST_MAX) {
    dist = dist_prev;           // Cut higher than maximum
    digitalWrite(PIN_LED,0);
  } else {    // In desired Range       
    dist_prev = dist;
    digitalWrite(PIN_LED,1);
  }
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist + (1-_EMA_ALPHA)* dist_ema;
  // map distance into duty
  //duty = map(a_value,0,1023, _DUTY_MIN, _DUTY_MAX);
  duty = (dist_ema - 100) / 150 * (_DUTY_MAX - _DUTY_MIN) + _DUTY_MIN;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN:");       Serial.print(_DIST_MIN);
  Serial.print(",IR:");       Serial.print(a_value);
  Serial.print(",dist:");     Serial.print(dist);
  Serial.print(",ema:");      Serial.print(dist_ema);
  Serial.print(",servo:");    Serial.print(duty);
  Serial.print(",MAX:");      Serial.print(_DIST_MIN);
  Serial.println(""); 

  
}
