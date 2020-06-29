/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 * This file adds support for the I2C implementation from https://github.com/technoblogy/tiny-i2c
 *
 */
#ifndef TINYNUNCHUK_TINYI2C_H
#define TINYNUNCHUK_TINYI2C_H

#include <TinyI2CMaster.h>
#include "TinyNunchuk_common.h"

#ifndef DATACUTE_I2C_TINYI2C
#define DATACUTE_I2C_TINYI2C

static bool datacute_write_tinyi2c(uint8_t byte) {
	return TinyI2C.write(byte);
}

static uint8_t datacute_read_tinyi2c(void) {
	return TinyI2C.read();
}

static void datacute_end_read_tinyi2c(void) {
	TinyI2C.stop();
}

static uint8_t datacute_endTransmission_tinyi2c(void) {
	TinyI2C.stop();
	return 0;
}

#endif

static bool nunchuk_beginTransmission_tinyi2c(void) {
	return TinyI2C.start(NUNCHUK_ADDRESS, 0);
}

static void nunchuk_begin_tinyi2c(void) {
	TinyI2C.init();
#ifndef TINYNUNCHUK_QUICK_BEGIN
	while (!nunchuk_beginTransmission_tinyi2c()) {
		delay(10);
	}
	datacute_endTransmission_tinyi2c();
#endif
}

static uint8_t nunchuk_request_tinyi2c(uint8_t length) {
	if (TinyI2C.start(NUNCHUK_ADDRESS, length)) return length;
	return 0;
}

NunchukDevice nunchuk(
	&nunchuk_begin_tinyi2c,
	&nunchuk_beginTransmission_tinyi2c,
	&datacute_write_tinyi2c,
	&datacute_endTransmission_tinyi2c,
	&nunchuk_request_tinyi2c,
	&datacute_read_tinyi2c,
	&datacute_end_read_tinyi2c);

#endif
