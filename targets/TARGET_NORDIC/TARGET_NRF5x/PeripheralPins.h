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
#ifndef MBED_PERIPHERALPINS_H
#define MBED_PERIPHERALPINS_H

#include "pinmap.h"
#include "PeripheralNames.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: move to pinmap.h, put here temporarily 
// multiplexed pinmap, based on PinMap, add assigned HW Instance
typedef struct{
	PinName Pin0;
	PinName Pin1;
	PinName Pin2;
	PinName Pin3;
} MultiPinMap;

typedef enum {
	multipinmaptype_spi,
	multipinmaptype_i2c,
	multipinmaptype_uart,
	multipinmaptype_pwm
}MultiPinMapType ;

extern const int spi_pinmap_size;
extern const int i2c_pinmap_size;
extern const int uart_pinmap_size;
extern const int pwm_pinmap_size;

extern const MultiPinMap SPI_Pinmap[];
extern const MultiPinMap I2C_Pinmap[];
extern const MultiPinMap UART_Pinmap[];
extern const MultiPinMap PWM_Pinmap[];

// Hardare instances, #defined. Move to PinNames.h ?
// Define as number of instances. Instances start at 0, but count starts at 1. So if there are 3 instances there will be instance0-instance2, but the #define below will be 3. 
// TODO: fill in with correct defines
#define NUM_HW_PERIPHERAL_SPI 3
#define NUM_HW_PERIPHERAL_I2C 4
#define NUM_HW_PERIPHERAL_UART 2
#define NUM_HW_PERIPHERAL_PWM 5 

extern MultiPinMap SPI_Blocks[];
extern MultiPinMap I2C_Blocks[];
extern MultiPinMap UART_Blocks[];
extern MultiPinMap PWM_Blocks[];


int multi_peripheral(MultiPinMap pins, const MultiPinMap * map, MultiPinMapType type);

#ifdef __cplusplus
}
#endif

#endif //MBED_PERIPHERALPINS_H
