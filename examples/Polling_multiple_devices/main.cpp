/*
 * Copyright (c) 2019 Branilson Luiz
 * main.hpp - INA226: polling multiple devices example using the ina226
 * Mbed Library.
 * 
 * branilson (at) gmail dot com
 * Github: https://github.com/branilson/ina226_mbed_library
 * 
 * This program is free software: you can redistribute it and/or modify it un-
 * der the terms of the version 3 GNU General Public License as published by
 * the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FIT-
 * NESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mbed.h"
#include "ina226_mbed_library/ina226.hpp" 

Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);
I2C i2c(PB_7, PB_6);
unsigned const int I2C_FREQ = 400000;
unsigned const int NUM_DEVICES = 4;
const int ina_addr[NUM_DEVICES] = {0x80, 0x82, 0x8a, 0x88};
const float current_limits[NUM_DEVICES] = {0.01, 0.02, 0.02, 1.0};
ina226 ina[NUM_DEVICES] = {ina226(i2c, ina_addr[0], I2C_FREQ),
 ina226(i2c, ina_addr[1], I2C_FREQ),
 ina226(i2c, ina_addr[2], I2C_FREQ),
 ina226(i2c, ina_addr[3], I2C_FREQ)};

int main() {
  pc.printf("INA226 TEST Program. (BUILD:[" __DATE__ "/" __TIME__ "])\n");
  int count = 1;
  unsigned int i;
  for (i=0; i < NUM_DEVICES; i++) {  // setConfig/setCalibration batch
    pc.printf("INA226 Address %xh Config return: %d\n",
     ina_addr[i],
     ina[i].setConfig(AVERAGES_64,
     BUS_CONV_TIME_1100US,
     SHUNT_CONV_TIME_1100US,
     MODE_SHUNT_BUS_CONT));
    pc.printf("INA226 Address %xh Calibration return: %d\n",
     ina_addr[i],
     ina[i].setCalibration(0.01, 1.0));
     ina[i].enableShuntOverVoltageAlert();
     ina[i].setOverCurrentLimit(current_limits[i]);
  }

  while (1)  {
    pc.printf("\n%d:\n", count);

    for (i=0; i < NUM_DEVICES; i++) {
      pc.printf("Device %xh: ManID %d, DieID %d, Cal %d, ShuntV %+2.6fV, %+2.6fV, %+2.6fA, %+2.6fW\n",
       ina_addr[i],
       ina[i].readManufacturerID(),
       ina[i].readDieID(),
       ina[i].readCalibration(),
       ina[i].readShuntVoltage(),
       ina[i].readBusVoltage(),
       ina[i].readCurrent(),
       ina[i].readPower());
      if (ina[i].isAlert()) {
        pc.printf("Overcurrent detected on device %xh\n", ina_addr[i]);
      }
    }

    myled = !myled;
    wait_us(1000000);  // Wait one second.
    count++;
  }
}
