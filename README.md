# TinyNunchuck

This is a library for an ATTiny85 to use a Wii Nunchuk, over I<sup>2</sup>C.

The Wii Nunchuk is a controller with a joystick, accelerometer, and two buttons. It comunicates over I2C at 3.3V.

## Example Usage

```c
// Choose your I2C implementation before including TinyNunchuk.h
// The default is selected is Wire.h

// To use the Wire library:
//#include <Wire.h>

// To use the Adafruit's TinyWireM library:
//#include <TinyWireM.h>

// To use the TinyI2C library from https://github.com/technoblogy/tiny-i2c
//#include <TinyI2CMaster.h>

#include <TinyNunchuk.h>

void setup() {
  // Send the initialization sequence to the nunchuk.
  nunchuk.begin();
}

void loop() {
  nunchuk.update();

  // Nunchuk Joystick position:
  // nunchuk.x
  // nunchuk.y
  // Nunchuk Acceleration:
  // nunchuk.ax
  // nunchuk.ay
  // nunchuk.az
  // Nunchuk Button states:
  // nunchuk.c
  // nunchuk.z
}
```
