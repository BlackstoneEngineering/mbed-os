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

extern const int spi_pinmap_size;
extern const int i2c_pinmap_size;
extern const int uart_pinmap_size;
extern const int pwm_pinmap_size;

extern const MultiPinMap SPI_Pinmap[];
extern const MultiPinMap I2C_Pinmap[];
extern const MultiPinMap UART_Pinmap[];
extern const MultiPinMap PWM_Pinmap[];

int multi_peripheral(MultiPinMap pins, const MultiPinMap * map );

#ifdef __cplusplus
}
#endif

#endif //MBED_PERIPHERALPINS_H
