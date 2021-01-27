#include <ISM330DHCXSensor.h>

#define DEV_I2C Wire

#define INT_2 D5
#define INT_1 D6

// Components
ISM330DHCXSensor AccGyro(&DEV_I2C);

// Interrupts.
volatile int mems_event = 0;

char displays[256];

void INT1Event_cb();
void sendOrientation();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

  DEV_I2C.begin();

  // Interrupts.
  attachInterrupt(INT_1, INT1Event_cb, RISING);
  
  AccGyro.begin();
  AccGyro.ACC_Enable();

  AccGyro.ACC_Enable6DOrientation(ISM330DHCX_INT1_PIN);
}

void loop() {
  ISM330DHCX_Event_Status_t status; 

  if (mems_event)
  {      
    AccGyro.ACC_GetEventStatus(&status);

    if (status.D6DOrientationStatus)
    {
      // Send D6D Orientation
      sendOrientation();

      // Led blinking.
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
    }
    mems_event=0; 
  }
}

void INT1Event_cb()
{
  mems_event = 1;
}


void sendOrientation()
{
  uint8_t xl,xh,yl,yh,zl,zh;

  AccGyro.ACC_Get6DOrientationXL(&xl);
  AccGyro.ACC_Get6DOrientationXH(&xh);
  AccGyro.ACC_Get6DOrientationYL(&yl);
  AccGyro.ACC_Get6DOrientationYH(&yh);  
  AccGyro.ACC_Get6DOrientationZL(&zl);
  AccGyro.ACC_Get6DOrientationZH(&zh);

  if ( xl == 0 && yl == 0 && zl == 0 && xh == 0 && yh == 1 && zh == 0 )
  {
    Serial.println("\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |  *             | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |________________| \r\n" );
  }    
  else if ( xl == 1 && yl == 0 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
  {
    Serial.println("\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |             *  | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |________________| \r\n" );
  }    
  else if ( xl == 0 && yl == 0 && zl == 0 && xh == 1 && yh == 0 && zh == 0 )
  {
    Serial.println("\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |  *             | " \
                      "\r\n |________________| \r\n" );
  }    
  else if ( xl == 0 && yl == 1 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
  {
    Serial.println("\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |             *  | " \
                      "\r\n |________________| \r\n" );
  }    
  else if ( xl == 0 && yl == 0 && zl == 0 && xh == 0 && yh == 0 && zh == 1 )
  {
    Serial.println( "\r\n  __*_____________  " \
                      "\r\n |________________| \r\n" );
  }    
  else if ( xl == 0 && yl == 0 && zl == 1 && xh == 0 && yh == 0 && zh == 0 )
  {
    Serial.println( "\r\n  ________________  " \
                      "\r\n |________________| " \
                      "\r\n    *               \r\n" );
  }  
  else
  {
    Serial.println("None of the 6D orientation axes is set in IIS2DLPC - accelerometer.\r\n" );
  }
}
