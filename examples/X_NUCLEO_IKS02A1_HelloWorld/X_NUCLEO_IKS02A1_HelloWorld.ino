// Includes
#include <IIS2DLPCSensor.h>
#include <IIS2MDCSensor.h>
#include <ISM330DHCXSensor.h>

#define DEV_I2C Wire

// Components
IIS2MDCSensor Mag(&DEV_I2C);
ISM330DHCXSensor AccGyro(&DEV_I2C);
IIS2DLPCSensor Acc(&DEV_I2C);

void setup() {
  // LED
  pinMode(LED_BUILTIN,OUTPUT);

  // Serial for Output
  Serial.begin(115200);

  // Initialize I2C bus
  DEV_I2C.begin();

  // Initialize and Enable Components
  Mag.begin();
  Mag.Enable();

  AccGyro.begin();
  AccGyro.ACC_Enable();
  AccGyro.GYRO_Enable();

  Acc.begin();
  Acc.Enable();
}

void loop() {
  // Led blinking
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  // Read magnetometer
  int32_t magnetometer[3];
  Mag.GetAxes(magnetometer);

  // Read accelerometer and gyroscope
  int32_t accelerometer[3];
  AccGyro.ACC_GetAxes(accelerometer);

  int32_t gyroscope[3];
  AccGyro.GYRO_GetAxes(gyroscope);

  // Read accelerometer
  int32_t accelerometer2[3];
  Acc.GetAxes(accelerometer2);
  
  // Output  
  Serial.print("| Mag[mGauss]: ");
  Serial.print(magnetometer[0]);
  Serial.print(" ");
  Serial.print(magnetometer[1]);
  Serial.print(" ");
  Serial.print(magnetometer[2]);
  Serial.print(" ");
  Serial.print("| Acc[mg]: ");
  Serial.print(accelerometer[0]);
  Serial.print(" ");
  Serial.print(accelerometer[1]);
  Serial.print(" ");
  Serial.print(accelerometer[2]);
  Serial.print(" ");
  Serial.print("| Gyro[mdps]: ");
  Serial.print(gyroscope[0]);
  Serial.print(" ");
  Serial.print(gyroscope[1]);
  Serial.print(" ");
  Serial.print(gyroscope[2]);
  Serial.print(" ");
  Serial.print("| Acc2[mg]: ");
  Serial.print(accelerometer2[0]);
  Serial.print(" ");
  Serial.print(accelerometer2[1]);
  Serial.print(" ");
  Serial.print(accelerometer2[2]);
  Serial.println(" |");
}
