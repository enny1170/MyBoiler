#include <Arduino.h>

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

/**************************
Boiler Sensor

The following sketch controls a latching relay connected to a boiler. A latching relay (requiring only a pulse to switch) 
has been chosen to minimize the power consumption required by a traditional relay to stay on. This relay has normally 
two pins, one for closing and the other for opening the controlled circuit, connected to pin 6 (off) and 7 (on) of the 
arduino board. Since using a SensorLatchingRelay2Pins type of sensor, NodeManager will automatically consider the 
provided pin as the ON pin and the one just after as the OFF pin and will take care of just sending out a single 
pulse only when a SET command of type V_STATUS is sent to the child id. The appropriate pin will be then used.

In this example, the board also runs at 1Mhz so it can go down to 1.8V: by setting setMinVoltage() and setMaxVoltage(), 
the battery percentage will be calculated and reported (by default, automatically every hour) based on these custom 
boundaries.
The board will be put to sleep just after startup and will report back to the controller every 5 minutes. It is 
the controller's responsability to catch when the board reports its heartbeat (using smart sleep behind the scene) 
and send a command back if needed.
*/


/**********************************
* MySensors node configuration
*/

// General settings
#define SKETCH_NAME "MyBoiler"
#define SKETCH_VERSION "1.0"
#define MY_BAUD_RATE 115200
#define MY_NODE_ID 99

// NRF24 radio settings
#define MY_RADIO_NRF24

// for NRF24DUINO you have to specify a different CE-Pin for NRF24L01+
#ifdef NRF24DUINO
    #define MY_RF24_CE_PIN 7
#endif
/***********************************
* NodeManager configuration
*/

// #define NODEMANAGER_SLEEP ON

// import NodeManager library (a nodeManager object will be then made available)
#include <MySensors_NodeManager.h>

/***********************************
* Add your sensors
*/

// Add a battery sensor
// #include <sensors/SensorBattery.h>
// SensorBattery battery;

// Add a latching relay sensor attached to pin 6 (off) and 7 (on)
// #include <sensors/SensorLatchingRelay2Pins.h>
// SensorLatchingRelay2Pins latching2pins(6,7);

// Add MaxM31855 Sensor
#include <sensors/SensorM31855k.h>
SensorM31855k vorlauf(3,4,5);

/***********************************
* Main Sketch
*/

// before
void before() {

/***********************************
* Configure your sensors
*/

	// set sleep interval to 5 minutes. Since smart sleep is enabled, the sensor will check in with the controller and pick up any outstanding command, if any
	// nodeManager.setSleepMinutes(5);

  nodeManager.setReportIntervalSeconds(30);
	// set battery minimum and maximum voltage so to calculate an accurate percentage
	// battery.setMinVoltage(1.8);
	// battery.setMaxVoltage(3.2);

	// call NodeManager before routine
	nodeManager.before();
}

// presentation
void presentation() {
	// call NodeManager presentation routine
	nodeManager.presentation();
}

// setup
void setup() {
	// call NodeManager setup routine
	nodeManager.setup();
}

// loop
void loop() {
	// call NodeManager loop routine
	nodeManager.loop();
}

#if NODEMANAGER_RECEIVE == ON
// receive
void receive(const MyMessage &message) {
	// call NodeManager receive routine
	nodeManager.receive(message);
}
#endif

#if NODEMANAGER_TIME == ON
// receiveTime
void receiveTime(unsigned long ts) {
	// call NodeManager receiveTime routine
	nodeManager.receiveTime(ts);
}
#endif