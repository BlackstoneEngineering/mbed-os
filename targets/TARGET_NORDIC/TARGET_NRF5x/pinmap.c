/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed_assert.h"
#include "mbed_error.h"
#include "pinmap.h"
#include "nrf_gpio.h"

void pin_function(PinName pin, int function)
{
    /* Avoid compiler warnings */
    (void) pin;
    (void) function;
}

void pin_mode(PinName pin, PinMode mode)
{
    MBED_ASSERT(pin != (PinName)NC);

    uint32_t pin_number = (uint32_t)pin;
    
#ifdef TARGET_SDK11
    NRF_GPIO_Type * reg = NRF_GPIO;
#else
    NRF_GPIO_Type * reg = nrf_gpio_pin_port_decode(&pin_number);
#endif
    reg->PIN_CNF[pin_number] &= ~GPIO_PIN_CNF_PULL_Msk;
    reg->PIN_CNF[pin_number] |= (mode << GPIO_PIN_CNF_PULL_Pos);
}

// ------------------ Multiplexed Additions -------------------//

// TODO: move to pinmap.h
// multiplexed pinmap, based on PinMap, add assigned HW Instance
typedef struct{
	PinName Pin0;
	int HardwareInstance;
} MultiPinMap1;

typedef struct{
	PinName Pin0;
	PinName Pin1;
	int HardwareInstance;
} MultiPinMap2;

typedef struct{
	PinName Pin0;
	PinName Pin1;
	PinName Pin2;
	int HardwareInstance;
} MultiPinMap3;

typedef struct{
	PinName Pin0;
	PinName Pin1;
	PinName Pin2;
	PinName Pin3;
	int HardwareInstance;
} MultiPinMap4;


// TODO : Move to PeripheralPins.h 
// Optional defines of pinmaps. User can impliment them or not. 
// If user impliments these then they will be used, otherwise runtime configuration will be used
MBED_WEAK const MultiPinMap4 SPI[] 	{ };
MBED_WEAK const MultiPinMap2 I2C[] 	{ };
MBED_WEAK const MultiPinMap2 UART[] { };
MBED_WEAK const MultiPinMap1 PWM[]	{ };

// Add additional peripherals here

// TODO: move this to PeripheralPins.c
// Optional: Add Peripherals here
/*
/************SPI***************
const MultiPinMap4 SPI[]= {
	{SPI1_MOSI, SPI1_MISO, SPI1_SS, SPI1_SCLK, 0},// SPI1 on Hardware Instance 0
	{SPI2_MOSI, SPI2_MISO, SPI2_SS, SPI2_SCLK, 1}
}

/************I2C***************
const MultiPinMap2 I2C[]={
	{I2C1_SDA, I2C1_SDL, 1}, // I2C1 on Hardware Instance 1
	{I2C2_SDA, I2C2_SDL, 4}  // I2C2 on Hardware Instance 4

}
*/

// Hardare instances, #defined. Move to PinNames.h ?
// Define as number of instances. Instances start at 0, but count starts at 1. So if there are 3 instances there will be instance0-instance2, but the #define below will be 3. 
// TODO: fill in with correct defines
#define NUM_HW_PERIPHERAL_SPI 3
#define NUM_HW_PERIPHERAL_I2C 4
#define NUM_HW_PERIPHERAL_UART 2
#define NUM_HW_PERIPHERAL_PWM 5 

// Arrays to hold initialized hardware peripherals, use these if PeripheralPins.c is not implimented
const MultiPinMap4 SPI_Blocks[NUM_HW_PERIPHERAL_SPI]	={ 0 };
const MultiPinMap2 I2C_Blocks[NUM_HW_PERIPHERAL_I2C] 	={ 0 };
const MultiPinMap2 UART_Blocks[NUM_HW_PERIPHERAL_UART]  ={ 0 };
const MultiPinMap1 PWM_Blocks[NUM_HW_PERIPHERAL_PWM]	={ 0 };


// Input: multiplexed pin enum, multiplexed pin enum array to determine type
// Output: Hardware Instance, positive number. Negative number is error.
// Function:
// 1) Pinmaps are defined, return hardware instance from PeripheralPins.h
// 2) Pinmaps are not defined, do best effort to allocate to hardware instance
// 3) Pinmaps are defineed, but input is not in them. This is a user error and should not happen.
int multi_peripheral1(MultiPinMap1 pins, const MultiPinMap1 * map ){
	const int size_pinmap = 1;
	if(sizeof(map) == 0){ // no custom pinmap found, keep track
		// TODO: impliment method to keep track of pins
		if(map == SPI){
			int x = 0;
			// loop through multimap peripheral array looking for blank spot.
			for(x=0;(x<NUM_HW_PERIPHERAL_SPI) && (SPI_Blocks[x]!={0});x++){
				if(SPI_Blocks[x] == {0}){
					SPI_Blocks[x] = pins; // assign to first blank spot found
				}
			}
			// See if buffer was full (ie no peripheral blocks available to assign to)
			if(x == NUM_HW_PERIPHERAL_SPI){
				printf("[ERR] There are %d blocks available and all are full. File: %s, Line %d", NUM_HW_PERIPHERAL_SPI,__FILE__,__LINE__);
				return -1;
			}

		}else if(map == I2C) {

		}else if(map == UART) {

		}else if(map == PWM) {

		}

	}else{ // Pinmap defined, return instance as approrpiate
		// TODO: search array for matches of input instance, return match or return error if not found. 
		if(map == SPI){
			int x = 0;
			for(x=0;x<NUM_HW_PERIPHERAL_SPI;x++){
				// TODO: impliment equals like check
			}
		}else if(map == I2C) {

		}else if(map == UART) {

		}else if(map == PWM) {

		}

	}
}


int multi_peripheral2(MultiPinMap2 pins, const MultiPinMap2 * map ){

	// TODO: add logic here to track multiplexed_pins structures and pair them to number of hardware instances. 
}

int multi_peripheral3(MultiPinMap3 pins, const MultiPinMap3 * map ){

	// TODO: add logic here to track multiplexed_pins structures and pair them to number of hardware instances. 
}

int multi_peripheral4(MultiPinMap4 pins, const MultiPinMap4 * map ){

	// TODO: add logic here to track multiplexed_pins structures and pair them to number of hardware instances. 
}






