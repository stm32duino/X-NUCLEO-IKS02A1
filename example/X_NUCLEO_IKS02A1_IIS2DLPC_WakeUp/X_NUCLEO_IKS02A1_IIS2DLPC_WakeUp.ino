#include <IIS2DLPCSensor.h>

#define DEV_I2C Wire
#define SerialPort Serial

/*INT1 not enable by default, to enable INT1 change the pin setup on the board.*/
#define INT1 A2
#define INT2 A4

//Components
IIS2DLPCSensor *Acc;

//Interrupts.
volatile int mems_event = 0;

void INTEvent();

void setup() {
  // LED
  pinMode(LED_BUILTIN,OUTPUT);

  // Serial for Output
  Serial.begin(115200);

  //Inizialize I2C bus
  DEV_I2C.begin();

  // Interrupts
  attachInterrupt(INT1, INTEvent, RISING);
  
  // Inizialize and Enable Components
  Acc = new IIS2DLPCSensor(&DEV_I2C);
  Acc->Enable();

  // Enable Free Fall Detection
  Acc->EnableWakeUpDetection();
}

void loop() {
 IIS2DLPC_Event_Status_t status;
 if (mems_event) {
    Acc->GetEventStatus(&status);
    if (status.WakeUpStatus)
    {
      // Led blinking
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);

      // Output data
      SerialPort.println("Wake Up Detected!");
    }
    mems_event = 0;
  }
}

void INTEvent()
{
  mems_event = 1;
}
