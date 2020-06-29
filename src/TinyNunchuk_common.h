/*
 * TinyNunchuk - Drivers for Wii Nunchuk
 *
 * By Stephen Denne
 * https://github.com/datacute/TinyNunchuk
 *
 * Based on information from http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
 *
 */
#include <stdint.h>
#include <Arduino.h>

#ifndef TINYNUNCHUKCOMMON_H
#define TINYNUNCHUKCOMMON_H

// ----------------------------------------------------------------------------

#ifndef NUNCHUK_ADDRESS
#define NUNCHUK_ADDRESS		0x52	// Slave address
#endif

// ----------------------------------------------------------------------------

class NunchukDevice {

	public:
		NunchukDevice(
			void (*wireBeginFunc)(void), 
			bool (*wireBeginTransmissionFunc)(void), 
			bool (*wireWriteFunc)(uint8_t byte), 
			uint8_t (*wireEndTransmissionFunc)(void),
			uint8_t (*wireRequestFunc)(uint8_t length), 
			uint8_t (*wireReadFunc)(void),
			void (*wireEndReadFunc)(void));

		void begin(void);
		void update(void);
		void readCalibration(void);
		void writeCalibration(void);

		uint8_t x; // Positive is to the left
		uint8_t y; // Positive is down
		uint16_t ax; // Positive burst is "right", turning the left side down increases the value, as gravity pulls "left".
		uint16_t ay; // Positive burst is "forward", turning the front side up increases the value, as gravity pulls "backward".
		uint16_t az; // Positive burst is "up", holding the nunchuk upside down, up is down, and gravity pulls "up", giving highest stationary reading.
		bool c; // C Button pressed
		bool z; // A Button pressed
		uint8_t calibration[16];
		// The calibration data records centers and some limits.
		// The first four bytes are 0G acceleration values. X[9:2], Y[9:2], Z[9:2], {0, 0, X1, X0, Y1, Y0, Z1, Z0 }
		// These are "centers" when held normally for the left/right and forward/back axes, and when held sideways for the Z axis.
		//            X                     Y                       Z
		// Red:   512 + 0               512 + 3                 512 + 140 (+80)
		// Black: 512 - 180             512 + 80                512 + 80 (+48)
		// The next four bytes are the 1G acceleration values.
		// These are "centers" when held sideways for the left/right and forward/back axes (pointing the controller at the floor), and when held normally for the Z axis.
		// Red:   512 + 295 (-192)      512 + 300 (-217)        512 + 311 (-144)
		// Black: 512 + 44 (-441)       512 + 352 (-112)        512 + 330 (-201)
		// The negative 1G value should be the 0G value minus the 1G value
		// The next six values are the joystick maximum, minimum, and center values in the X then Y direction.
		// 255, 0, 127    255, 0, 128
		// The last two values are checksum values.

		// The holder's idea of a comfortable "center" position might not be half way between the minimum and maximum stationary readings.
		// So knowing the range of readings is useful.

		// Ranges from some example nunchuk clones:
		// Red:   -192 to +295 = 487    -217 to +300 = 517      -144 to +311 = 455
		// Black: -441 to  +44 = 485    -112 to +352 = 464      -201 to +330 = 531
};

#endif
