/*
* The MySensors Arduino library handles the wireless radio link and protocol
* between your home built sensors/actuators and HA controller of choice.
* The sensors forms a self healing radio network with optional repeaters. Each
* repeater and gateway builds a routing tables in EEPROM which keeps track of the
* network topology allowing messages to be routed to nodes.
*
* Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
* Copyright (C) 2013-2017 Sensnology AB
* Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
*
* Documentation: http://www.mysensors.org
* Support Forum: http://forum.mysensors.org
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*/
#ifndef SensorM31855k_h
#define SensorM31855k_h

/*
SensorM31855k
*/

#include <SPI.h>
#include <Adafruit_MAX31855.h>

class SensorM31855k: public Sensor {
protected:
	Adafruit_MAX31855* _thermocouple;
	int _sensor_type;
	int _maxDo;
    int _maxCs;
    int _maxClk;

public:
	SensorM31855k(int maxDo,int maxCs,int maxClk,uint8_t child_id = 0): Sensor(-1) {
		_maxDo=maxDo;
        _maxCs=maxCs;
        _maxClk=maxClk;
        _name = "MAX31855k";
		children.allocateBlocks(1);
		new Child(this,FLOAT,nodeManager.getAvailableChildId(child_id),S_TEMP,V_TEMP,"TEMP");
	};

	// define what to do during setup
	void onSetup() {
		// initialize the library
		Serial.println("init Max Lib");
		_thermocouple = new Adafruit_MAX31855(_maxClk,_maxCs,_maxDo);
	};

	// define what to do during loop
	void onLoop(Child* child) {
		float temperature;
		temperature=_thermocouple->readCelsius();
		// the first child is the ambient temperature, the second the object temperature
		// if (children.get(1) == child) temperature = _thermocouple->readInternal();
		// else temperature = _thermocouple->readCelsius();
		// convert it
		// temperature = nodeManager.celsiusToFahrenheit(temperature);
		child->setValue(temperature);
	};
};
#endif