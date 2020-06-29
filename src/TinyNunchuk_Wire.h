/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 */
#ifndef TINYNUNCHUK_WIRE_H
#define TINYNUNCHUK_WIRE_H

#include <Wire.h>
#include "TinyNunchuk_common.h"

#ifndef DATACUTE_I2C_WIRE
#define DATACUTE_I2C_WIRE

static bool datacute_write_wire(uint8_t byte) {
	return Wire.write(byte);
}

static uint8_t datacute_read_wire(void) {
	return Wire.read();
}

static void datacute_end_read_wire(void) {}

static uint8_t datacute_endTransmission_wire(void) {
	return Wire.endTransmission();
}

#endif

static bool tinynunchuk_beginTransmission_wire(void) {
	Wire.beginTransmission(NUNCHUK_ADDRESS);
	return true;
}

#ifndef TINYNUNCHUK_QUICK_BEGIN
inline static bool tinynunchuk_check_wire(void) {
	const uint8_t noError = 0x00;
	tinynunchuk_beginTransmission_wire();
	return (datacute_endTransmission_wire()==noError);
}
#endif

static void tinynunchuk_begin_wire(void) {
	Wire.begin();
#ifndef TINYNUNCHUK_QUICK_BEGIN
	while (!tinynunchuk_check_wire()) {
		delay(10);
	}
#endif
}

static uint8_t tinynunchuk_request_wire(uint8_t length) {
	return Wire.requestFrom((uint8_t)NUNCHUK_ADDRESS, length);
}

NunchukDevice nunchuk(
	&tinynunchuk_begin_wire,
	&tinynunchuk_beginTransmission_wire,
	&datacute_write_wire,
	&datacute_endTransmission_wire,
	&tinynunchuk_request_wire,
	&datacute_read_wire,
	&datacute_end_read_wire);

#endif
