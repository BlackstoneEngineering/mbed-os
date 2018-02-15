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
#include "mbed_toolchain.h"
#include "PeripheralPins.h"

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

// Hardare instances, #defined. Move to PinNames.h ?
// Define as number of instances. Instances start at 0, but count starts at 1. So if there are 3 instances there will be instance0-instance2, but the #define below will be 3. 
// TODO: fill in with correct defines
#define NUM_HW_PERIPHERAL_SPI 3
#define NUM_HW_PERIPHERAL_I2C 4
#define NUM_HW_PERIPHERAL_UART 2
#define NUM_HW_PERIPHERAL_PWM 5 

// Arrays to hold initialized hardware peripherals, use these if PeripheralPins.c is not implimented
MultiPinMap SPI_Blocks[NUM_HW_PERIPHERAL_SPI]		={{NC,NC,NC,NC}};
MultiPinMap I2C_Blocks[NUM_HW_PERIPHERAL_I2C] 		={{NC,NC,NC,NC}};
MultiPinMap UART_Blocks[NUM_HW_PERIPHERAL_UART]  	={{NC,NC,NC,NC}};
MultiPinMap PWM_Blocks[NUM_HW_PERIPHERAL_PWM]		={{NC,NC,NC,NC}};

// Helper Function to dissasociate pinmap from array. Probable use is in a deconstructor. 
// Input : 
// Output : True (success), False (failure) - failures only happen if pins are not in pinmap array
bool clear_block_array(const MultiPinMap * map, uint hwinstance){
	MultiPinMap blank = {NC,NC,NC,NC};
	if(map == SPI_Pinmap){
		// check that index is within bound of array
		if(hwinstance < (sizeof(SPI_Blocks))){
			SPI_Blocks[hwinstance] = blank;
			return true;
		}else{ // hwinstance is out of bounds of array, this is an error
			return false; 
		}
	}else if(map == I2C_Pinmap) {
		// check that index is within bound of array
		if(hwinstance < (sizeof(I2C_Blocks))){
			I2C_Blocks[hwinstance] = blank;
			return true;
		}else{ // hwinstance is out of bounds of array, this is an error
			return false; 
		}
	}else if(map == UART_Pinmap) {
		// check that index is within bound of array
		if(hwinstance < (sizeof(UART_Blocks))){
			UART_Blocks[hwinstance] = blank;
			return true;
		}else{ // hwinstance is out of bounds of array, this is an error
			return false; 
		}
	}else if(map == PWM_Pinmap) {
		// check that index is within bound of array
		if(hwinstance < (sizeof(PWM_Blocks))){
			PWM_Blocks[hwinstance] = blank;
			return true;
		}else{ // hwinstance is out of bounds of array, this is an error
			return false; 
		}
	}
	printf("\r\n     [ERR] The pinmap is not registered. Please expand the pinmap.c file, %s,%d", __FILE__,__LINE__);
	return false; 
}

// Helper Function to parse block array
// Input: array to parse, MultiPinMap to scan for
// Output: Hardware instance
// Error: -1 if the block array is full. 
int parse_block_array(MultiPinMap pins, MultiPinMap * array, int array_size){
	int HWInstance = 0;
	int NUM_HW_PERIPHERAL = array_size;
	printf("\r\n     [LOG] NUM_HW_Peripherals is %d, line %d",NUM_HW_PERIPHERAL, __LINE__);
	// loop through multimap peripheral array looking for blank spot.
	for(HWInstance=0; HWInstance < NUM_HW_PERIPHERAL; HWInstance++ ){
		// eq check to see if the pinmap is already recorded
		if(		pins.Pin0 ==array[HWInstance].Pin0
			 && pins.Pin1 == array[HWInstance].Pin1
			 && pins.Pin2 == array[HWInstance].Pin2
			 && pins.Pin3 == array[HWInstance].Pin3
			){
			return HWInstance;
		}

		// If spot is empty fill it with passed in value
		if(	array[HWInstance].Pin0 == 0 
			&& array[HWInstance].Pin1 == 0 
			&& array[HWInstance].Pin2 == 0 
			&& array[HWInstance].Pin3 == 0 
			){ 
				array[HWInstance] = pins; // assign to first blank spot found
				return HWInstance; // return index as hardware instance
		}
	}
	// See if buffer was full (ie no peripheral blocks available to assign to)
	// if(HWInstance == NUM_HW_PERIPHERAL){
		printf("\r\n    [ERR] There are %d blocks available and all are full. File: %s, Line %d", NUM_HW_PERIPHERAL,__FILE__,__LINE__);
		return -1;
	//}
}

// Helper function to parse predefined pinmaps
// Input : pins to look for in the predefined pinmap
// Output: hardware instance
// Error: -1 if the pins are not in the pinmap
int parse_pinmap_array(MultiPinMap pins, const MultiPinMap * pinmap, int array_size){
	int HWInstance = 0;
	int NUM_HW_PERIPHERAL = array_size;
	printf("\r\n     [LOG] NUM_HW_Peripherals is %d, line %d",NUM_HW_PERIPHERAL,__LINE__);
	for(HWInstance = 0; HWInstance < NUM_HW_PERIPHERAL; HWInstance++){
		if(		pins.Pin0 == pinmap[HWInstance].Pin0
			 && pins.Pin1 == pinmap[HWInstance].Pin1
			 && pins.Pin2 == pinmap[HWInstance].Pin2
			 && pins.Pin3 == pinmap[HWInstance].Pin3
			){
			return HWInstance;
		}
	}
	// Searched entire array, no matches found, return error
	printf("\r\n     [ERR] MultiPinMap {%d,%d,%d,%d} not found in pre-defined list. File: %s, Line %d", pins.Pin0, pins.Pin1, pins.Pin2, pins.Pin3,__FILE__,__LINE__);
	return -1;
}

// Input: multiplexed pin enum, multiplexed pin enum array to determine type
// Output: Hardware Instance, positive number. Negative number is error.
// Function:
// 1) Pinmaps are defined, return hardware instance from PeripheralPins.h
// 2) Pinmaps are not defined, do best effort to allocate to hardware instance
// 3) Pinmaps are defineed, but input is not in them. This is a user error and should not happen.
int multi_peripheral(MultiPinMap pins, const MultiPinMap * map ){
	int size = -1;
	printf("\r\n     [LOG] map address = %d, SPI = %d, I2C = %d", map, SPI_Pinmap, I2C_Pinmap);
	if(map == SPI_Pinmap){
		printf("\r\n     [LOG] SPI Detected");
		// size = sizeof(SPI_Pinmap);
		size = spi_pinmap_size;
	} else if(map == I2C_Pinmap){
		printf("\r\n     [LOG] I2C Detected");
		// size = sizeof(I2C_Pinmap);
		size = i2c_pinmap_size;
	} else if(map == UART_Pinmap){
		printf("\r\n     [LOG] UART Detected");
		// size = sizeof(UART_Pinmap);
		size = uart_pinmap_size;
	} else if(map == PWM_Pinmap){
		printf("\r\n     [LOG] PWM Detected");
		// size = sizeof(PWM_Pinmap);
		size = pwm_pinmap_size;
	} 
	printf("\r\n     [LOG] size of map %d = %d",map, size);

	if(size == 0){ // no custom pinmap found, keep track in the <Peripheral>_Blocks arrays
		if(map == SPI_Pinmap){
			return parse_block_array(pins, SPI_Blocks, spi_pinmap_size);
		}else if(map == I2C_Pinmap) {
			return parse_block_array(pins, I2C_Blocks, i2c_pinmap_size);
		}else if(map == UART_Pinmap) {
			return parse_block_array(pins, UART_Blocks, uart_pinmap_size);
		}else if(map == PWM_Pinmap) {
			return parse_block_array(pins, PWM_Blocks, pwm_pinmap_size);
		}

	}else{ // Pinmap defined, return instance from pinmap or error as approrpiate
		if(map == SPI_Pinmap){
			return parse_pinmap_array(pins, SPI_Pinmap, spi_pinmap_size);
		}else if(map == I2C_Pinmap){
			return parse_pinmap_array(pins, I2C_Pinmap, i2c_pinmap_size);
		}else if(map == UART_Pinmap){
			return parse_pinmap_array(pins, UART_Pinmap, uart_pinmap_size);
		}else if(map == PWM_Pinmap){
			return parse_pinmap_array(pins, PWM_Pinmap, pwm_pinmap_size);
		}
	}
	printf("\r\n     [ERR] Something has gone terribly wrong. %s %d", __FILE__, __LINE__);
	return -1; // you only get here if there has been an error
}
