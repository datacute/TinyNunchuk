/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 * Based on information from http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
 * 
 */

// ----------------------------------------------------------------------------

#include "TinyNunchuk_common.h"

// ----------------------------------------------------------------------------

static void (*wireBeginFn)(void);
static bool (*wireBeginTransmissionFn)(void);
static bool (*wireWriteFn)(uint8_t byte);
static uint8_t (*wireEndTransmissionFn)(void);
static uint8_t (*wireRequestFn)(uint8_t length);
static uint8_t (*wireReadFn)(void);
static void (*wireEndReadFn)(void);

static void nunchuk_begin(void) {
	wireBeginFn();
}

static void nunchuk_send_start(void) {
	wireBeginTransmissionFn();
}

static bool nunchuk_send_byte(uint8_t byte) {
	return wireWriteFn(byte);
}

static uint8_t nunchuk_send_stop(void) {
	return wireEndTransmissionFn();
}

static void nunchuk_set_data(uint8_t location, uint8_t data) {
	nunchuk_send_start();
	nunchuk_send_byte(location);
	nunchuk_send_byte(data);
	nunchuk_send_stop();
	// Can this be removed?
	//delay(10);
}

static uint8_t nunchuk_start_read(uint8_t location, int8_t bytesToRead) {
	nunchuk_send_start();
	nunchuk_send_byte(location);
	nunchuk_send_stop();
	//delayMicroseconds(275);
	return wireRequestFn(bytesToRead);
}

static uint8_t nunchuk_read(void) {
	return wireReadFn();
}

static void nunchuk_end_read(void) {
	return wireEndReadFn();
}

NunchukDevice::NunchukDevice(
			void (*wireBeginFunc)(void), 
			bool (*wireBeginTransmissionFunc)(void), 
			bool (*wireWriteFunc)(uint8_t byte), 
			uint8_t (*wireEndTransmissionFunc)(void),
			uint8_t (*wireRequestFunc)(uint8_t length), 
			uint8_t (*wireReadFunc)(void),
			void (*wireEndReadFunc)(void)) {
	wireBeginFn = wireBeginFunc;
	wireBeginTransmissionFn = wireBeginTransmissionFunc;
	wireWriteFn = wireWriteFunc;
	wireEndTransmissionFn = wireEndTransmissionFunc;
	wireRequestFn = wireRequestFunc;
	wireReadFn = wireReadFunc;
	wireEndReadFn = wireEndReadFunc;
}

void NunchukDevice::begin(void) {
	nunchuk_begin();
	nunchuk_set_data(0xF0, 0x55);
	nunchuk_set_data(0xFB, 0x00);

	//delay(100);

	nunchuk_start_read(0xfa, 6);
	//delayMicroseconds(100);
	for (uint8_t i = 0; i < 6; i++) {
		nunchuk_read();
	}
	nunchuk_end_read();
	//delay(100);
/*
	nunchuk_start_read(0xfa, 6);
	delayMicroseconds(100);
	for (uint8_t i = 0; i < 6; i++) {
		nunchuk_read();
	}
	nunchuk_end_read();
	delay(100);

	update();
	delay(100);
	update();
*/
	nunchuk_send_start();
	nunchuk_send_byte(0x00);
	nunchuk_send_stop();
	delay(100);
}

void NunchukDevice::update(void) {
	nunchuk_start_read(0x00, 6);

	uint8_t p0 = nunchuk_read();
	uint8_t p1 = nunchuk_read();
	uint8_t p2 = nunchuk_read();
	uint8_t p3 = nunchuk_read();
	uint8_t p4 = nunchuk_read();
	uint8_t p5 = nunchuk_read();
	nunchuk_end_read();

	nunchuk_send_start();
	nunchuk_send_byte(0x00);
	nunchuk_send_stop();

	if((p0 & p1 & p2 & p3 & p4 & p5) != 255) {
		NunchukDevice::x = p0;
		NunchukDevice::y = p1;
		NunchukDevice::ax = p2 << 2;
		NunchukDevice::ay = p3 << 2;
		NunchukDevice::az = p4 << 2;
		NunchukDevice::ax |= ((p5 >> 2) & 0x03);
		NunchukDevice::ay |= ((p5 >> 4) & 0x03);
		NunchukDevice::az |= ((p5 >> 6) & 0x03);
		NunchukDevice::c = !((p5 >> 1) & 0x01);
		NunchukDevice::z = !(p5 & 0x01);
	}
}

void NunchukDevice::readCalibration(void) {
	nunchuk_start_read(0x20, 16);
	for (uint8_t i = 0; i < 16; i++) {
		NunchukDevice::calibration[i] = nunchuk_read();
	}
	nunchuk_end_read();
}

void NunchukDevice::writeCalibration(void) {
	nunchuk_send_start();
	nunchuk_send_byte(0x20);
	for (uint8_t i = 0; i < 16; i++) {
		nunchuk_send_byte(NunchukDevice::calibration[i]);
	}
	nunchuk_send_stop();
}

// ----------------------------------------------------------------------------
