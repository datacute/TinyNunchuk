/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 */
#ifndef TINYNUNCHUK_H
#define TINYNUNCHUK_H

#if defined(TwoWire_h) || defined (USIWire_h)
#include "TinyNunchuk_Wire.h"
#elif defined(TinyWireM_h)
#include "TinyNunchuk_TinyWireM.h"
#elif defined(TinyI2CMaster_h)
#include "TinyNunchuk_tiny-i2c.h"
#else
#include <Wire.h>
#include "TinyNunchuk_Wire.h"
#endif

#endif
