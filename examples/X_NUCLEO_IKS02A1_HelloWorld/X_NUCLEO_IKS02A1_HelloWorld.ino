// Includes
#include <IIS2DLPCSensor.h>
#include <IIS2MDCSensor.h>
#include <ISM330DHCXSensor.h>

#define DEV_I2C Wire

// Components
IIS2DLPCSensor *Acc;
IIS2MDCSensor *Mag;
ISM330DHCXSensor *AccGyro;

void setup() {
  // LED
  pinMode(LED_BUILTIN,OUTPUT);

  // Serial for Output
  Serial.begin(115200);

  // Inizialize I2C bus
  DEV_I2C.begin();

  // Inizialize and Enable Components
  Acc = new IIS2DLPCSensor(&DEV_I2C);
  Acc->Enable();

  Mag = new IIS2MDCSensor(&DEV_I2C);
  Mag->Enable();

  AccGyro = new ISM330DHCXSensor(&DEV_I2C);
  AccGyro -> ACC_Enable();
  AccGyro -> GYRO_Enable();
}

void loop() {
  // Led blinking
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
  // ReadId
  uint8_t id[3];
  Acc->ReadID(&id[0]);
  Mag->ReadID(&id[1]);
  AccGyro->ReadID(&id[2]);
  
  // Read accelerometer
  int32_t accAxes[3];
  Acc->GetAxes(accAxes);

  // Read magnetometer
  int32_t magnetometer[3];
  Mag->GetAxes(magnetometer);

  // Read accelerometer and gyroscope
  int32_t acceAxes[3];
  AccGyro->ACC_GetAxes(acceAxes);

  int32_t gyroAxes[3];
  AccGyro->GYRO_GetAxes(gyroAxes);
  
  // Output  
  Serial.print("| Mag[mGauss]: ");
  Serial.print(magnetometer[0]);
  Serial.print(" ");
  Serial.print(magnetometer[1]);
  Serial.print(" ");
  Serial.print(magnetometer[2]);
  Serial.print(" ");
  Serial.print("| Acc[mg]: ");
  Serial.print(acceAxes[0]);
  Serial.print(" ");
  Serial.print(acceAxes[1]);
  Serial.print(" ");
  Serial.print(acceAxes[2]);
  Serial.print(" ");
  Serial.print("| Gyro[mdps]: ");
  Serial.print(gyroAxes[0]);
  Serial.print(" ");
  Serial.print(gyroAxes[1]);
  Serial.print(" ");
  Serial.print(gyroAxes[2]);
  Serial.print(" ");
  Serial.print("| Acc2[mg]: ");
  Serial.print(accAxes[0]);
  Serial.print(" ");
  Serial.print(accAxes[1]);
  Serial.print(" ");
  Serial.print(accAxes[2]);
  Serial.println(" |");
}
