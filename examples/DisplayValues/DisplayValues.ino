/*
 * This example shows how to read the nunchuk values.
 * The values are displayed graphically on a 64x48 SSD1306 OLED
 * using the Tiny4kOLED library
 */

// Choose your I2C implementation before including TinyNunchuk.h
// The default if none is selected is Wire.h

// To use the Wire library:
//#include <Wire.h>

// To use the Adafruit's TinyWireM library:
//#include <TinyWireM.h>

// To use the TinyI2C library from https://github.com/technoblogy/tiny-i2c
//#include <TinyI2CMaster.h>

#include <TinyNunchuk.h>
#include <Tiny4kOLED.h>

bool waitingForZ = true;

uint8_t xMin;
uint8_t xMax;
uint8_t yMin;
uint8_t yMax;
uint16_t axMin;
uint16_t axMax;
uint16_t ayMin;
uint16_t ayMax;
uint16_t azMin;
uint16_t azMax;

void setup() {
  oled.begin(64, 48, sizeof(tiny4koled_init_64x48br), tiny4koled_init_64x48br);
  oled.setFont(FONT6X8);
  oled.clear();
  oled.setCursor(0,0);
  oled.print(F("Starting"));
  oled.setCursor(0,1);
  oled.print(readVcc());
  oled.print(" mV");
  oled.on();

  nunchuk.begin();

  oled.setCursor(0,0);
  oled.print(F("Press Z "));
}

void loop() {
  nunchuk.update();
  if (waitingForZ) {
    if (nunchuk.z) {
      waitingForZ = false;
      oled.clear();
    } else {
      delay(50);
      return;
    }
  } else {
    if (nunchuk.x < xMin) {
      xMin = nunchuk.x;
    }
    if (nunchuk.x > xMax) {
      xMax = nunchuk.x;
    }
    if (nunchuk.y < yMin) {
      yMin = nunchuk.y;
    }
    if (nunchuk.y > yMax) {
      yMax = nunchuk.y;
    }
    if (nunchuk.ax < axMin) {
      axMin = nunchuk.ax;
    }
    if (nunchuk.ax > axMax) {
      axMax = nunchuk.ax;
    }
    if (nunchuk.ay < ayMin) {
      ayMin = nunchuk.ay;
    }
    if (nunchuk.ay > ayMax) {
      ayMax = nunchuk.ay;
    }
    if (nunchuk.az < azMin) {
      azMin = nunchuk.az;
    }
    if (nunchuk.az > azMax) {
      azMax = nunchuk.az;
    }
  }

  if (nunchuk.z) {
    xMin = nunchuk.x;
    xMax = nunchuk.x;
    yMin = nunchuk.y;
    yMax = nunchuk.y;
    axMin = nunchuk.ax;
    axMax = nunchuk.ax;
    ayMin = nunchuk.ay;
    ayMax = nunchuk.ay;
    azMin = nunchuk.az;
    azMax = nunchuk.az;
  }

  oled.setCursor(57,0);
  oled.startData();
  oled.sendData(0x3C);
  if (nunchuk.c) {
    oled.sendData(0x7E);
    oled.sendData(0x7E);
    oled.sendData(0x7E);
    oled.sendData(0x7E);
  } else {
    oled.sendData(0x42);
    oled.sendData(0x42);
    oled.sendData(0x42);
    oled.sendData(0x42);
  }
  oled.sendData(0x3C);
  oled.endData();

  oled.setCursor(57,5);
  oled.startData();
  oled.sendData(0x3C);
  if (nunchuk.z) {
    oled.sendData(0x7E);
    oled.sendData(0x7E);
    oled.sendData(0x7E);
    oled.sendData(0x7E);
  } else {
    oled.sendData(0x42);
    oled.sendData(0x42);
    oled.sendData(0x42);
    oled.sendData(0x42);
  }
  oled.sendData(0x3C);
  oled.endData();

  uint8_t ax5 = nunchuk.ax >> 5;
  uint8_t axMin5 = axMin >> 5;
  uint8_t axMax5 = axMax >> 5;

  oled.setCursor(0,0);
  oled.startData();
  oled.sendData(0xE0);
  oled.sendData(0x18);
  oled.sendData(0x04);
  oled.sendData(0xE2);
  oled.sendData(0x12);
  oled.sendData(0x09);
  oled.sendData(0x09);
  oled.sendData(0x09);
  oled.endData();

  showHorizontalGauge(8, 0, ax5, axMin5, axMax5, 0x0F, 0x70, 0x01);

  oled.setCursor(40,0);
  oled.startData();
  oled.sendData(0x09);
  oled.sendData(0x09);
  oled.sendData(0x09);
  oled.sendData(0x12);
  oled.sendData(0xE2);
  oled.sendData(0x04);
  oled.sendData(0x18);
  oled.sendData(0xE0);
  oled.endData();

  oled.setCursor(0,5);
  oled.startData();
  oled.sendData(0x07);
  oled.sendData(0x18);
  oled.sendData(0x20);
  oled.sendData(0x47);
  oled.sendData(0x48);
  oled.sendData(0x90);
  oled.sendData(0x90);
  oled.sendData(0x90);
  oled.endData();

  showHorizontalGauge(8, 5, ax5, axMin5, axMax5, 0xF0, 0x0E, 0x80);

  oled.setCursor(40,5);
  oled.startData();
  oled.sendData(0x90);
  oled.sendData(0x90);
  oled.sendData(0x90);
  oled.sendData(0x48);
  oled.sendData(0x47);
  oled.sendData(0x20);
  oled.sendData(0x18);
  oled.sendData(0x07);
  oled.endData();

  uint8_t ay5 = nunchuk.ay >> 5;
  uint8_t ayMin5 = ayMin >> 5;
  uint8_t ayMax5 = ayMax >> 5;

  showVerticalGauge(0, 1, ay5, ayMin5, ayMax5, 0x0F, 0x70, 0x01);
  showVerticalGauge(40, 1, ay5, ayMin5, ayMax5, 0xF0, 0x0E, 0x80);

  uint8_t az5 = nunchuk.az >> 5;
  uint8_t azMin5 = azMin >> 5;
  uint8_t azMax5 = azMax >> 5;

  showVerticalGauge(56, 1, az5, azMin5, azMax5, 0xFF, 0xBD, 0x81);

  uint8_t x3 = nunchuk.x >> 3;
  uint8_t xMin3 = xMin >> 3;
  uint8_t xMax3 = xMax >> 3;
  uint8_t y3 = (255 - nunchuk.y) >> 3;
  uint8_t yMin3 = (255 - yMax) >> 3;
  uint8_t yMax3 = (255 - yMin) >> 3;
  
  showPositionGauge(8, 1, x3, y3, xMin3, xMax3, yMin3, yMax3);
}

void showHorizontalGauge(uint8_t x, uint8_t p, uint8_t gx, uint8_t gxMin, uint8_t gxMax, uint8_t endBits, uint8_t xBits, uint8_t emptyBits) {
  oled.setCursor(x, p);
  oled.startData();
  
  uint8_t pixelskip = gxMin; // Range 0 to 31
  oled.repeatData(0, pixelskip);
  if (gx == gxMin) {
    oled.sendData(endBits | xBits | emptyBits);
    if (gxMax > gxMin) {
      pixelskip = (gxMax - gxMin) - 1;
      oled.repeatData(emptyBits, pixelskip);
      oled.sendData(endBits | emptyBits);
    }
  } else {
    oled.sendData(endBits | emptyBits);
    pixelskip = (gx - gxMin) - 1;
    oled.repeatData(emptyBits, pixelskip);
    if (gx == gxMax) {
      oled.sendData(endBits | xBits | emptyBits);
    } else {
      oled.sendData(xBits | emptyBits);
      pixelskip = (gxMax - gx) - 1;
      oled.repeatData(emptyBits, pixelskip);
      oled.sendData(endBits | emptyBits);
    }
  }
  pixelskip = (31 - gxMax);
  oled.repeatData(0, pixelskip);

  oled.endData();
}

void showVerticalGauge(uint8_t xoffset, uint8_t p, uint8_t gy, uint8_t gyMin, uint8_t gyMax, uint8_t endBits, uint8_t yBits, uint8_t emptyBits) {
  uint8_t gyPage = gy >> 3;
  uint8_t gyBit = gy & 0x07;
  uint8_t gyMinPage = gyMin >> 3;
  uint8_t gyMinBit = gyMin & 0x07;
  uint8_t gyMaxPage = gyMax >> 3;
  uint8_t gyMaxBit = gyMax & 0x07;

  verticalGaugeSkip(xoffset, p, 0, gyMinPage, 0);

  oled.setCursor(xoffset,gyMinPage+p);
  if (gyPage == gyMinPage) {
    if (gyPage == gyMaxPage) {
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = (0xFF >> (7 - gyMaxBit)) & (0xFF << gyMinBit);
        }
        bits |= (((endBits >> b) & 0x01) << gyMinBit) | 
                (((yBits >> b) & 0x01) << gyBit) |
                (((endBits >> b) & 0x01) << gyMaxBit);
        oled.sendData(bits);
      }
      oled.endData();
    } else {
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = 0xFF << gyMinBit;
        }
        bits |= (((endBits >> b) & 0x01) << gyMinBit) | 
                (((yBits >> b) & 0x01) << gyBit);
        oled.sendData(bits);
      }
      oled.endData();

      verticalGaugeSkip(xoffset, p, gyPage + 1, gyMaxPage, emptyBits);

      oled.setCursor(xoffset,gyMaxPage+p);
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = 0xFF >> (7 - gyMaxBit);
        }
        bits |= (((endBits >> b) & 0x01) << gyMaxBit);
        oled.sendData(bits);
      }
      oled.endData();
    }
  } else {
    oled.startData();
    for (uint8_t b = 0; b<8; b++) {
      uint8_t bits = 0x00;
      if (((emptyBits >> b) & 0x01) == 0x01) {
        bits = 0xFF << gyMinBit;
      }
      bits |= (((endBits >> b) & 0x01) << gyMinBit);
      oled.sendData(bits);
    }
    oled.endData();

    verticalGaugeSkip(xoffset, p, gyMinPage + 1, gyPage, emptyBits);

    oled.setCursor(xoffset,gyPage+p);
    if (gyPage == gyMaxPage) {
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = 0xFF >> (7 - gyMaxBit);
        }
        bits |= (((yBits >> b) & 0x01) << gyBit) |
                (((endBits >> b) & 0x01) << gyMaxBit);
        oled.sendData(bits);
      }
      oled.endData();
    } else {
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = 0xFF;
        }
        bits |= (((yBits >> b) & 0x01) << gyBit);
        oled.sendData(bits);
      }
      oled.endData();

      verticalGaugeSkip(xoffset, p, gyPage + 1, gyMaxPage, emptyBits);

      oled.setCursor(xoffset,gyMaxPage+p);
      oled.startData();
      for (uint8_t b = 0; b<8; b++) {
        uint8_t bits = 0x00;
        if (((emptyBits >> b) & 0x01) == 0x01) {
          bits = 0xFF >> (7 - gyMaxBit);
        }
        bits |= (((endBits >> b) & 0x01) << gyMaxBit);
        oled.sendData(bits);
      }
      oled.endData();
    }
  }

  verticalGaugeSkip(xoffset, p, gyMaxPage + 1, 4, 0x00);
}

void verticalGaugeSkip(uint8_t xoffset, uint8_t p, uint8_t fromPage, uint8_t toPage, uint8_t emptyBits) {
  for (uint8_t ps = fromPage; ps < toPage; ps++) {
    oled.setCursor(xoffset,ps+p);
    oled.startData();
    for (uint8_t b = 0; b<8; b++) {
      uint8_t bits = 0x00;
      if (((emptyBits >> b) & 0x01) == 0x01) {
        bits = 0xFF;
      }
      oled.sendData(bits);
    }
    oled.endData();
  }
}

void showPositionGauge(uint8_t xoffset, uint8_t p, uint8_t gx, uint8_t gy, uint8_t gxMin, uint8_t gxMax, uint8_t gyMin, uint8_t gyMax) {
  uint8_t gyPage = gy >> 3;
  uint8_t gyBit = gy & 0x07;
  uint8_t gyMinPage = gyMin >> 3;
  uint8_t gyMinBit = gyMin & 0x07;
  uint8_t gyMaxPage = gyMax >> 3;
  uint8_t gyMaxBit = gyMax & 0x07;

  uint8_t top = 0x01 << gyMinBit;
  uint8_t marker = 0x01 << gyBit;
  uint8_t bottom = 0x01 << gyMaxBit;
  uint8_t topedge = 0xFF << gyMinBit;
  uint8_t bottomedge = 0xFF >> (7 - gyMaxBit);

  for (uint8_t ps = 0; ps < gyMinPage; ps++) {
    showHorizontalGauge(xoffset, ps + p, gx, gxMin, gxMax, 0x00, 0x00, 0x00);
  }
  if (gyPage == gyMinPage) {
    if (gyPage == gyMaxPage) {
      showHorizontalGauge(xoffset, gyPage + p, gx, gxMin, gxMax, topedge & bottomedge, top | marker | bottom, top | bottom);
    } else {
      showHorizontalGauge(xoffset, gyPage + p, gx, gxMin, gxMax, topedge, top | marker, top);

      for (uint8_t ps = gyPage + 1; ps < gyMaxPage; ps++) {
        showHorizontalGauge(xoffset, ps + p, gx, gxMin, gxMax, 0xFF, 0x00, 0x00);
      }

      showHorizontalGauge(xoffset, gyMaxPage + p, gx, gxMin, gxMax, bottomedge, bottom, bottom);
    }
  } else {
    showHorizontalGauge(xoffset, gyMinPage + p, gx, gxMin, gxMax, topedge, top, top);

    for (uint8_t ps = gyMinPage + 1; ps < gyPage; ps++) {
      showHorizontalGauge(xoffset, ps + p, gx, gxMin, gxMax, 0xFF, 0x00, 0x00);
    }

    if (gyPage == gyMaxPage) {
      showHorizontalGauge(xoffset, gyPage + p, gx, gxMin, gxMax, bottomedge, marker | bottom, bottom);
    } else {
      showHorizontalGauge(xoffset, gyPage + p, gx, gxMin, gxMax, 0xFF, marker, 0x00);

      for (uint8_t ps = gyPage + 1; ps < gyMaxPage; ps++) {
        showHorizontalGauge(xoffset, ps + p, gx, gxMin, gxMax, 0xFF, 0x00, 0x00);
      }

      showHorizontalGauge(xoffset, gyMaxPage + p, gx, gxMin, gxMax, bottomedge, bottom, bottom);
    }
  }
  for (uint8_t ps = gyMaxPage + 1; ps < 4; ps++) {
    showHorizontalGauge(xoffset, ps + p, gx, gxMin, gxMax, 0x00, 0x00, 0x00);
  }
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  ADMUX = _BV(MUX3) | _BV(MUX2);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH 
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1126400L / result; // Calculate Vcc (in mV); 1126400 = 1.1*1024*1000
  return result; // Vcc in millivolts
}
