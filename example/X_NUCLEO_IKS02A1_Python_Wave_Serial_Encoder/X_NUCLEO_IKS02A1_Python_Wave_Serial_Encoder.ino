/* This example was developed for Nucleo F401RE or L476RG only. If you want to use other Nucleo or Architecture 
 * you have to implement the dedicated file to manage the low level PDM part
 */
#if !defined(ARDUINO_NUCLEO_L476RG) && !defined(ARDUINO_NUCLEO_F401RE)
#error "This example is only for STM32 Nucleo-F401RE or Nucleo-L476RG!"
#endif

#include "Arduino.h"
#include "PDM.h"
#include "pdm2pcm.h"
#include <CMSIS_DSP.h>

/* PDM */
uint16_t sampleBuffer[(((AUDIO_IN_FREQ / 8) * MAX_AUDIO_IN_CHANNEL_NBR_PER_IF * N_MS_PER_INTERRUPT)/2)] = {0};
uint32_t counter = 0;

bool recording = false;
byte inByte = 0;

/* PDM2PCM */
#define PCM_BUFLEN    (AUDIO_IN_FREQ/AUDIO_IN_DECIMATOR_FACTOR) //1280/80 = 16
int16_t pcmSamples[PCM_BUFLEN*N_MS_PER_INTERRUPT];

void setup() {

  pinMode(D13, OUTPUT);

  /* Serial */
  Serial.begin(921600);
  Serial.flush();
  while(Serial.available() > 0){
    Serial.read();
  }
  
  /* Enable and Start */
  if (PDM.Begin() != PDM_OK)
  {
    while(1)
    {
      digitalWrite(D13, HIGH);
      delay(100);
      digitalWrite(D13, LOW);
      delay(100);
    }
  }

  /* Function to execute with data */
  PDM.onReceive(foo);

  /* Initialize PDM2PCM */
  pdm2pcm_init(BYTE_LEFT_MSB, PDM_ENDIANNESS_BE, SINC4);
  if(pdm2pcm_volume(5)){  //set volume (0-6)  
    while(1)
    {
      digitalWrite(D13, HIGH);
      delay(100);
      digitalWrite(D13, LOW);
      delay(100);
    }
  }
}

void loop() {
  while(Serial.available() > 0){
    inByte = Serial.read();
  }

  if(inByte == 0x00){
    recording = 0;
    PDM.Stop();
    digitalWrite(LED_BUILTIN,LOW);
  }  

  if(inByte == 0x01 && recording == 0){
    PDM.Record(sampleBuffer);
    recording = 1;
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

extern "C" void foo()
{
  for (int i = 0; i < N_MS_PER_INTERRUPT; i++)
  {
    pdm2pcm((uint8_t *) & (sampleBuffer[i * ((BLOCK_SIZE/8)/2)]), &pcmSamples[i * PCM_BUFLEN], BLOCK_SIZE);
  }

  Serial.write((const char *)pcmSamples, sizeof(pcmSamples));
  Serial.flush();
}
