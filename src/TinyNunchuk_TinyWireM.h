/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 * This file adds support for the I2C implementation from https://github.com/adafruit/TinyWireM
 * Adafruit's version has a buffer overrun bugfix.
 *
 */
#ifndef TINYNUNCHUK_TINYWIREM_H
#define TINYNUNCHUK_TINYWIREM_H

#include <TinyWireM.h>
#include "TinyNunchuk_common.h"

#ifndef DATACUTE_I2C_TINYWIREM
#define DATACUTE_I2C_TINYWIREM

static bool datacute_write_tinywirem(uint8_t byte) {
	return TinyWireM.write(byte);
}

static uint8_t datacute_read_tinywirem(void) {
	return TinyWireM.read();
}

static void datacute_end_read_tinywirem(void) {}

static uint8_t datacute_endTransmission_tinywirem(void) {
	return TinyWireM.endTransmission();
}

#endif

static bool nunchuk_beginTransmission_tinywirem(void) {
	TinyWireM.beginTransmission(NUNCHUK_ADDRESS);
	return true;
}

#ifndef TINYNUNCHUK_QUICK_BEGIN
static bool nunchuk_check_tinywirem(void) {
	const uint8_t noError = 0x00;
	nunchuk_beginTransmission_tinywirem();
	return (datacute_endTransmission_tinywirem()==noError);
}
#endif

static void nunchuk_begin_tinywirem(void) {
	TinyWireM.begin();
#ifndef TINYNUNCHUK_QUICK_BEGIN
	while (!nunchuk_check_tinywirem()) {
		delay(10);
	}
#endif
}

static uint8_t nunchuk_request_tinywirem(uint8_t length) {
	const uint8_t noError = 0x00;
	if (TinyWireM.requestFrom(NUNCHUK_ADDRESS, length)==noError) return length;
	return 0;
}

NunchukDevice nunchuk(&nunchuk_begin_tinywirem,
	&nunchuk_beginTransmission_tinywirem,
	&datacute_write_tinywirem,
	&datacute_endTransmission_tinywirem,
	&nunchuk_request_tinywirem,
	&datacute_read_tinywirem,
	&datacute_end_read_tinywirem);

#endif
