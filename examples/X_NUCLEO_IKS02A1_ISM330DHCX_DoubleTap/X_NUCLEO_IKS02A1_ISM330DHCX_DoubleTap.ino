// Includes
#include <ISM330DHCXSensor.h>

#define DEV_I2C Wire

#define INT_2 D5
#define INT_1 D6

// Components
ISM330DHCXSensor *AccGyro;

// Interrupts.
volatile int mems_event = 0;

void INT1Event_cb();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

  DEV_I2C.begin();

  // Interrupts.
  attachInterrupt(INT_1, INT1Event_cb, RISING);
  
  AccGyro = new ISM330DHCXSensor(&DEV_I2C);
  AccGyro->ACC_Enable();

  AccGyro->ACC_EnableDoubleTapDetection(ISM330DHCX_INT1_PIN);
}

void loop() {
  ISM330DHCX_Event_Status_t status; 

  if (mems_event)
  {      
    AccGyro->ACC_GetEventStatus(&status);
    if (status.DoubleTapStatus)
    {
      // Led blinking.
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);

      // Output data.
      Serial.println("Double Tap Detected!");  
    }

    mems_event=0; 
  }
}

void INT1Event_cb()
{
  mems_event = 1;
}
