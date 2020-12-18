#include <IIS2DLPCSensor.h>

#define DEV_I2C Wire
#define SerialPort Serial

/* INT1 unusable by default, in order to use INT1 you need to */
/* close the pins 1 and 2 of JP2 and the pins 1 and 2 of JP9  */
#define INT1 A2

// Components
IIS2DLPCSensor *Acc;

// Interrupts.
volatile int mems_event = 0;

void INTEvent();

void setup() {
  // LED
  pinMode(LED_BUILTIN,OUTPUT);

  // Serial for Output
  Serial.begin(115200);

  // Inizialize I2C bus
  DEV_I2C.begin();

  // Interrupts
  attachInterrupt(INT1, INTEvent, RISING);
  
  // Inizialize and Enable Components
  Acc = new IIS2DLPCSensor(&DEV_I2C);
  Acc->Enable();

  // Enable Single Tap Detection  
  Acc->EnableSingleTapDetection();
}

void loop() {
  IIS2DLPC_Event_Status_t status;
  if (mems_event) {
    Acc->GetEventStatus(&status);
    if (status.TapStatus)
    {
      // Led blinking
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);

      // Output data
      SerialPort.println("Single Tap Detected!");
    }
    mems_event = 0;
  }
}

void INTEvent()
{
  mems_event = 1;
}
