# X-NUCLEO-IKS02A1
The X-NUCLEO-IKS02A1 is a motion MEMS and audio sensor expansion board for the STM32 Nucleo.

It is equipped with Arduino UNO R3 connector layout, and is designed around the ISM330DHCX 3D accelerometer and 3D gyroscope,
the IIS2DLPC 3D accelerometer, the IIS2MDC 3D magnetometer, the IMP34DT05 digital microphone.

The X-NUCLEO-IKS02A1 interfaces with the STM32 microcontroller via the I²C pin.

# Examples

There are several examples with the X-NUCLEO-IKS02A1 library.
* X_NUCLEO_IKS02A1_HelloWorld: This application provides a simple example of usage of the X-NUCLEO-IKS02A1 Expansion Board. 
It shows how to display on a hyperterminal the values of all on-board MEMS inertial sensors.
* X_NUCLEO_IKS02A1_IIS2DLPC_6DOrientation: This application shows how to use X-NUCLEO-IKS02A1 IIS2DLPC accelerometer to find out the 6D orientation and display data on a hyperterminal. 
* X_NUCLEO_IKS02A1_IIS2DLPC_WakeUp: This application shows how to detect the wake-up event using the X-NUCLEO-IKS02A1 IIS2DLPC accelerometer.
* X_NUCLEO_IKS02A1_IIS2DLPC_FreeFallDetection: This application shows how to detect the free fall event using the X-NUCLEO-IKS02A1 IIS2DLPC accelerometer.
* X_NUCLEO_IKS02A1_IIS2DLPC_SingleTap: This application shows how to detect the single tap event using the X-NUCLEO-IKS02A1 IIS2DLPC accelerometer.
* X_NUCLEO_IKS02A1_IIS2DLPC_DoubleTap: This application shows how to detect the double tap event using the X-NUCLEO-IKS02A1 IIS2DLPC accelerometer.
* X_NUCLEO_IKS02A1_ISM330DHCX_6DOrientation: This application shows how to use X-NUCLEO-IKS02A1 ISM330DHCX accelerometer to find out the 6D orientation and display data on a hyperterminal.
* X_NUCLEO_IKS02A1_ISM330DHCX_WakeUpDetection: This application shows how to detect the wake-up event using the X-NUCLEO-IKS02A1 ISM330DHCX accelerometer.
* X_NUCLEO_IKS02A1_ISM330DHCX_FreeFallDetection: This application shows how to detect the free fall event using the X-NUCLEO-IKS02A1 ISM330DHCX accelerometer.
* X_NUCLEO_IKS02A1_ISM330DHCX_SingleTap: This application shows how to detect the single tap event using the X-NUCLEO-IKS02A1 ISM330DHCX accelerometer.
* X_NUCLEO_IKS02A1_ISM330DHCX_DoubleTap: This application shows how to detect the double tap event using the X-NUCLEO-IKS02A1 ISM330DHCX accelerometer.

There is also an example based on the X-NUCLEO-IKS02A1 Audio library.
* X_NUCLEO_IKS02A1_Python_Wave_Serial_Encoder: This application shows how to record some data with [IMP34DT05](https://www.st.com/en/mems-and-sensors/imp34dt05.html)  digital microphone and send them through serial to a Python application which will write data to a wave file (Python application can be downloaded at https://github.com/stm32duino/Python-Wave-Serial-Encoder)

# Dependencies

The X-NUCLEO-IKS02A1 library requires the following STM32duino libraries:

* STM32duino ISM330DHCX: https://github.com/stm32duino/ISM330DHCX
* STM32duino IIS2MDC: https://github.com/stm32duino/IIS2MDC
* STM32duino IIS2DLPC: https://github.com/stm32duino/IIS2DLPC
* STM32duino X-NUCLEO-IKS02A1-Audio: https://github.com/stm32duino/X-NUCLEO-IKS02A1-Audio

## Documentation

You can find the source files at  
https://github.com/stm32duino/X-NUCLEO-IKS02A1

The X-NUCLEO-IKS02A1 datasheet is available at   
https://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment/stm32-nucleo-expansion-boards/stm32-ode-sense-hw/x-nucleo-iks02a1.html#
