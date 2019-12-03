#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Servo.h>

Servo myservo;

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int valX;
int previous_val = 0;

void setup() {

  pinMode(10, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initialize MPU");
  mpu.initialize();
  myservo.attach(9);
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");

}
void loop() {

  digitalWrite(10, LOW);
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //valY = map(ay, -17000, 17000, 0, 179);
  valX = map(ax, -17000, 17000, 170, 10);

  if (valX > (previous_val+10) || valX < (previous_val-10)) {
    digitalWrite(10, HIGH);
    delay(50);
  } else {
    digitalWrite(10, LOW);
  }
  
  Serial.print(valX);
  Serial.println(previous_val);
  previous_val = valX;
  myservo.write(valX);
  delay(1000);

}
