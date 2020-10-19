#include <ISM330DHCXSensor.h>

#define DEV_I2C Wire

#define INT_2 D5
#define INT_1 D6

//Components
ISM330DHCXSensor *AccGyro;

//Interrupts
volatile int mems_event = 0;

void INT1Event_cb();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

  DEV_I2C.begin();

   //Interrupts.
  attachInterrupt(INT_2, INT1Event_cb, RISING);
  
  AccGyro = new ISM330DHCXSensor(&DEV_I2C);
  AccGyro->ACC_Enable();

  AccGyro->ACC_EnableFreeFallDetection(ISM330DHCX_INT2_PIN);
}

void loop() {
    ISM330DHCX_Event_Status_t status; 

    if (mems_event)
    {      
          
      AccGyro->ACC_GetEventStatus(&status);
      if (status.FreeFallStatus)
      {
        // Led blinking.
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        
        // Output data.
        Serial.println("Free Fall Detected!");  
      }
      
      mems_event=0; 
    }
}

void INT1Event_cb()
{
  mems_event = 1;
}
