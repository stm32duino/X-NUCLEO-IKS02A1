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
  
  //ReadId
  uint8_t id[3];
  Acc->ReadID(&id[0]);
  Mag->ReadID(&id[1]);
  AccGyro->ReadID(&id[2]);
  
  // Read accelerometer
  IIS2DLPC_Axes_t accAxes;
  Acc->GetAxes(&accAxes);

  // Read magnetometer
  int32_t magnetometer[3];
  Mag->GetAxes(magnetometer);

  // Read accelerometer and gyroscope
  ISM330DHCX_Axes_t acceAxes;
  AccGyro->ACC_GetAxes(&acceAxes);

  ISM330DHCX_Axes_t gyroAxes;
  AccGyro->GYRO_GetAxes(&gyroAxes);
  
  //Output  
  Serial.print("| Mag[mGauss]: ");
  Serial.print(magnetometer[0]);
  Serial.print(" ");
  Serial.print(magnetometer[1]);
  Serial.print(" ");
  Serial.print(magnetometer[2]);
  Serial.print(" ");
  Serial.print("| Acc[mg]: ");
  Serial.print(acceAxes.x);
  Serial.print(" ");
  Serial.print(acceAxes.y);
  Serial.print(" ");
  Serial.print(acceAxes.z);
  Serial.print(" ");
  Serial.print("| Gyro[mdps]: ");
  Serial.print(gyroAxes.x);
  Serial.print(" ");
  Serial.print(gyroAxes.y);
  Serial.print(" ");
  Serial.print(gyroAxes.z);
  Serial.print(" ");
  Serial.print("| Acc2[mg]: ");
  Serial.print(accAxes.x);
  Serial.print(" ");
  Serial.print(accAxes.y);
  Serial.print(" ");
  Serial.print(accAxes.z);
  Serial.println(" |");
}
