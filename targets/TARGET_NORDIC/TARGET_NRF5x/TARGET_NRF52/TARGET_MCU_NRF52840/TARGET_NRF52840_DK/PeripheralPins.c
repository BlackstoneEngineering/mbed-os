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

#include "pinmap.h"
#include "PeripheralPins.h"
#include <mbed_toolchain.h>

// Optional: Add Peripherals like below to your application

// //************SPI***************
// const MultiPinMap SPI_Pinmap[]= {
// 	{SPI1_MOSI, SPI1_MISO, SPI1_SS, SPI1_SCLK},// SPI1 on Hardware Instance 0
// 	{SPI2_MOSI, SPI2_MISO, SPI2_SS, SPI2_SCLK}
// };

// //************I2C***************
// const MultiPinMap I2C_Pinmap[]={
// 	{I2C1_SDA, I2C1_SDL, NC, NC}, // I2C1 on Hardware Instance 1
// 	{I2C2_SDA, I2C2_SDL, NC, NC}  // I2C2 on Hardware Instance 4

// };

MBED_WEAK const MultiPinMap SPI_Pinmap[] = {};
MBED_WEAK const MultiPinMap I2C_Pinmap[] = {};
MBED_WEAK const MultiPinMap UART_Pinmap[] = {};
MBED_WEAK const MultiPinMap PWM_Pinmap[] = {};

// calculate size of arrays,
MBED_WEAK const int spi_pinmap_size = sizeof(SPI_Pinmap)/sizeof(MultiPinMap);
MBED_WEAK const int i2c_pinmap_size = sizeof(I2C_Pinmap)/sizeof(MultiPinMap);
MBED_WEAK const int uart_pinmap_size = sizeof(UART_Pinmap)/sizeof(MultiPinMap);
MBED_WEAK const int pwm_pinmap_size = sizeof(PWM_Pinmap)/sizeof(MultiPinMap);
