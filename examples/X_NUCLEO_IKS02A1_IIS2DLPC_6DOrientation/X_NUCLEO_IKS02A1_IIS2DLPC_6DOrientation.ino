#include <IIS2DLPCSensor.h>

#define DEV_I2C Wire
#define SerialPort Serial

/* INT1 unusable by default, in order to use INT1 you need to */
/* close the pins 1 and 2 of JP2 and the pins 1 and 2 of JP9  */
#define INT1 A2

// Components
IIS2DLPCSensor Acc(&DEV_I2C);

// Interrupts
volatile int mems_event = 0;

char displays[256];

void INTEvent();
void sendOrientation();

void setup() {
  // LED
  pinMode(LED_BUILTIN,OUTPUT);

  // Serial for Output
  Serial.begin(115200);

  // Initialize I2C bus
  DEV_I2C.begin();

  // Interrupts
  attachInterrupt(INT1, INTEvent, RISING);
  
  // Initialize and Enable Components
  Acc.begin();
  Acc.Enable();

  // Enable 6D Orientation Detection
  Acc.Enable6DOrientation();
}

void loop() {
  IIS2DLPC_Event_Status_t status;

  if (mems_event) {
    Acc.GetEventStatus(&status);
    if (status.D6DOrientationStatus)
    {
      // Send D6D Orientation
      sendOrientation();
      
      // Led blinking
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      
    }
    mems_event = 0;
  }
}

void INTEvent()
{
  mems_event = 1;
}

void sendOrientation()
{
  uint8_t xl,xh,yl,yh,zl,zh;

  Acc.Get6DOrientationXL(&xl);
  Acc.Get6DOrientationXH(&xh);
  Acc.Get6DOrientationYL(&yl);
  Acc.Get6DOrientationYH(&yh);  
  Acc.Get6DOrientationZL(&zl);
  Acc.Get6DOrientationZH(&zh);

  if ( xl == 1 && yl == 0 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
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
  else if ( xl == 0 && yl == 1 && zl == 0 && xh == 0 && yh == 0 && zh == 0 )
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
  else if ( xl == 0 && yl == 0 && zl == 0 && xh == 0 && yh == 1 && zh == 0 )
  {
    Serial.println( "\r\n  ________________  " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |                | " \
                      "\r\n |  *             | " \
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
