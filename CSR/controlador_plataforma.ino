#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Servo
Servo myservo;
Servo myservo2;
const unsigned int servo_zero = 90;
const unsigned int servo_zero2 = 90;

// IMU
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
unsigned long last_micros = 0;
unsigned long current_micros = 0;
unsigned long deltat_micros = 10000;
float deltat_seconds = (1.0*deltat_micros) / 1000000;
float roll_gyro = 0;
float pitch_gyro = 0;
float roll_acc = 0;
float pitch_acc = 0;
float roll_fused = 0;
float pitch_fused = 0;
float alpha = 0.005;

// PID_1
float kP = 0.055132;
float kI = 7.9199;
float kD = 0;
float ref = 0;
float error = 0;
float error_old = 0;
float error_accum = 0;
float eD = 0;
float control = 0;


// PID_2
float kP2 = 0.055132;
float kI2 = 7.9199;
float kD2 = 0;
float ref2 = 0;
float error2 = 0;
float error_old2 = 0;
float error_accum2 = 0;
float eD2 = 0;
float control2 = 0;


void setup() 
{
  myservo.attach(11);
  myservo2.attach(12);
  myservo.write(servo_zero);
  myservo2.write(servo_zero2);
  //myservo.write(40);

  Serial.begin(115200);
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
  
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}


void loop()
{
  current_micros = micros();

  // Obtenemos los datos y hacemos control sólo si han pasado deltat segundos
  if(current_micros - last_micros > deltat_micros)
  {
    last_micros = micros();

    // TODO lo procesamos aquí
    mpu.getEvent(&a, &g, &temp);

    // Calculamos los ángulos con el gyro
    roll_gyro = roll_gyro + g.gyro.x * deltat_seconds;
    //Serial.print("Roll Giroscopio:  ");
    //Serial.println(roll_gyro*180/M_PI);
    pitch_gyro = pitch_gyro + g.gyro.y * deltat_seconds;
    //Serial.print("Pitch Giroscopio:  ");
    //Serial.println(pitch_gyro*180/M_PI);

    // Calculamos los ángulos con el acc
    roll_acc = atan2(-a.acceleration.y, -a.acceleration.z);
    //Serial.print("Roll Acelerometro:  ");
    //Serial.println(roll_acc*180/M_PI);
    pitch_acc = asin(a.acceleration.x / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)) );    
    //Serial.print("Pitch Acelerometro:  ");
    //Serial.println(pitch_acc*180/M_PI);



    // Fusionamos las mediciones del acc y del gyro
    roll_fused = alpha * (roll_fused + roll_gyro) + (1 - alpha) * roll_acc;
    //Serial.print("Roll Fused:  ");
    //Serial.println(roll_fused*180/M_PI);
    pitch_fused = alpha * (pitch_fused + pitch_gyro) + (1 - alpha) * pitch_acc;
    //Serial.print("Pitch Fused:  ");
    //Serial.println(pitch_fused*180/M_PI);   

    // Controlador No.1 - Roll
    error = ref - ((roll_fused * 180) / M_PI);
    
    if(abs(error-error_old)>1){
      error_accum = error_accum + error;
      eD = error - error_old;
      control = kP * error + kI * error_accum * deltat_seconds + kD * (eD / deltat_seconds);
      error_old = error;
      control = servo_zero + control;

      //Valor absoluto entre error y erro old' > 2

      if(control > 140)
      {
        control = 140;      
      } 
      else if(control <0)
      {
        control = 0;
      } 
      myservo.write(control);
  }

    // Controlador No.2 - Pitch
    error2 = ref2 - ((pitch_fused * 180) / M_PI);

    if(abs(error2-error_old2)>1){
      error_accum2 = error_accum2 + error2;
      eD2 = error2 - error_old2;     
      control2 = kP2 * error2 + kI2 * error_accum2 * deltat_seconds + kD2 * (eD2 / deltat_seconds);
      error_old2 = error2;
      control2 = servo_zero2 + control2;
      if(control2 > 180)
      {
        control2 = 180;      
      } 
      else if(control2 <0)
      {
        control2 = 0;
      } 
      myservo2.write(control2);
    }


    //Serial.println((roll_fused * 180) / M_PI);
    //myservo.write(140);
  }

}
