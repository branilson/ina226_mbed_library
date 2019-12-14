<a href="https://github.com/branilson"><img src="https://github.com/branilson/ina226_mbed_library/raw/master/img/INA226.jpg" title="INA226" alt="BranlsonLuiz"></a>

<!-- [![Branilson Luiz(https://github.com/branilson/ina226_mbed_library/raw/master/img/INA226.jpg](https://github.com/branilson) -->


# Ina226 Mbed Library

> INA226 High-Side or Low-Side Measurement, Bi-Directional Current and Power Monitor with I2C Compatible Interface

> C++ Library for ARM mbed framework

> Tested on ST STM32 evaluation boards Nucleo_L432KC and Nucleo_F746zg. 

> This program is free software. Licensed under the terms of the BSD License.

**Use**

<a href="https://github.com/branilson"><img src="https://github.com/branilson/ina226_mbed_library/raw/master/img/Screenshot_ina226.png" title="Branilson Luiz" alt="BranlsonLuiz"></a>

1. Instantiate an mbed I2C object:

<pre><code>I2C i2c(PB_7, PB_6);
</code></pre>

2. Instatiate the ina226 object:
The ina226 class constructor receives an mbed I2C object, the device address, and the I2C frequency value as parameters. Notice that mbed I2C implementation uses 8-bit adresses. So, the 7-bit adress of the device needs a bit left shift (&lt;&lt; 1).

<pre><code>ina226 ina(i2c, 0x80, 400000);
</code></pre>

3. Configure the device.
The first thing needed before start measuring is to configure the behavior of the device. This method requires four:
 - Averaging Mode options:
	- AVERAGES_1, for no averaging;
	- AVERAGES_4, for 4 samples averaging;
	- AVERAGES_16, for 16 samples averaging;
	- AVERAGES_64, for 64 samples averaging;
	- AVERAGES_128, for 128 samples averaging;
	- AVERAGES_256, for 256 samples averaging;
	- AVERAGES_512, for 512 samples averaging;
	- AVERAGES_1024, for 1024 samples averaging.

 - Bus Voltage ConversionTime options:
	- BUS_CONV_TIME_140US, for 140 microseconds voltage conversion time;
	- BUS_CONV_TIME_204US, for 204 microseconds voltage conversion time;
	- BUS_CONV_TIME_332US, for 332 microseconds voltage conversion time;
	- BUS_CONV_TIME_588US, for 588 microseconds voltage conversion time;
	- BUS_CONV_TIME_1100US, for 1100 microseconds voltage conversion time;
	- BUS_CONV_TIME_2116US, for 2116 microseconds voltage conversion time;
	- BUS_CONV_TIME_4156US, for 4156 microseconds voltage conversion time;
	- BUS_CONV_TIME_8244US, for 8244 microseconds voltage conversion time.

 - Shunt Voltage Conversion Time options:
	- BUS_CONV_TIME_140US, for 140 microseconds voltage conversion time;
	- BUS_CONV_TIME_204US, for 204 microseconds voltage conversion time;
	- BUS_CONV_TIME_332US, for 332 microseconds voltage conversion time;
	- BUS_CONV_TIME_588US, for 588 microseconds voltage conversion time;
	- BUS_CONV_TIME_1100US, for 1100 microseconds voltage conversion time;
	- BUS_CONV_TIME_2116US, for 2116 microseconds voltage conversion time;
	- BUS_CONV_TIME_4156US, for 4156 microseconds voltage conversion time;
	- BUS_CONV_TIME_8244US, for 8244 microseconds voltage conversion time.

 - Operating Mode options:
	- MODE_POWER_DOWN, 
	- MODE_SHUNT_TRIG, 
	- MODE_BUS_TRIG, 
	- MODE_SHUNT_BUS_TRIG, 
	- MODE_ADC_OFF, 
	- MODE_SHUNT_CONT, 
	- MODE_BUS_CONT, 
	- MODE_SHUNT_BUS_CONT,

<pre><code>ina.setConfig(AVERAGES_64, BUS_CONV_TIME_1100US, SHUNT_CONV_TIME_1100US, MODE_SHUNT_BUS_CONT);
</code></pre>

With no parameters, the default settings loaded are AVERAGES_64, BUS_CONV_TIME_1100US, SHUNT_CONV_TIME_1100US, MODE_SHUNT_BUS_CONT.

<pre><code>ina.setConfig();
</code></pre>

4. Calibrate the device:
This method do the calibration math using the supplied Shunt resistor value and maximun current expected.

<pre><code>ina.setCalibration(0.01, 5.0);
</code></pre>

With no parameters the object will adopt the default calibration parameters: rShunt = 0.01 Ohm, Imax = 8.191 A.

<pre><code>ina.setCalibration();
</code></pre>

5. Set an alert type (optional).

<pre><code>ina.enableShuntOverVoltageAlert();  //for shunt overvoltage or current limit
</code></pre>

6. Set an alert value (optional).

<pre><code>ina.setOverCurrentLimit(2.4);  // for 2.4 A current limit alert
</code></pre>

7. Start reading data:

<pre><code>ina.readManufacturerID(),
ina.readDieID(),
ina.readCalibration(),
ina.readShuntVoltage(),
ina.readBusVoltage(),
ina.readCurrent(),
ina.readPower());
</code></pre>

Many other methods for reading and writing data are available in the class. See the header file for more details.

<a href="https://github.com/branilson"><img src="https://github.com/branilson/ina226_mbed_library/raw/master/img/ina226_circuit.jpg" title="Branilson Luiz" alt="BranlsonLuiz"></a>
