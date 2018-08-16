// 1-channel LoRa Gateway for ESP8266
// Copyright (c) 2016, 2017, 2018 Maarten Westenberg version for ESP8266
// Version 5.3.2
// Date: 2018-07-07
//
// based on work done by Thomas Telkamp for Raspberry PI 1ch gateway
// and many others.
//
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the MIT License
// which accompanies this distribution, and is available at
// https://opensource.org/licenses/mit-license.php
//
// NO WARRANTY OF ANY KIND IS PROVIDED
//
// Author: Maarten Westenberg (mw12554@hotmail.com)
//
// This file contains a number of compile-time settings and definitions for OLED support.
//
// ----------------------------------------------------------------------------------------

// OLEDs dupported by this program must be I2C.
// This is because we do not want any diisturbance in the SPI area
// which is also interfacing the LORA tranceiver.
//
// The following OLDs are supported:
// 0. No OLED connected
// 1. 0.9" OLED (cheap)
// 2. 1.3" OLED with much better display

#if OLED>=1										// If OLED is used

// --------------------------------------------------------	
// Define the different PIN's used for SCL/SDA for each arch.
//
#if _PIN_OUT==1									// HALLARD
#define OLED_SCL 5								// GPIO5 / D1
#define OLED_SDA 4								// GPIO4 / D2

#elif _PIN_OUT==2								// COMRESULT				
#define OLED_SCL 0								// GPIO0 / D3
#define OLED_SDA 2								// GPIO2 / D4

#elif _PIN_OUT==4								// TTGO (onboard version used, also for DIY)
#define OLED_SCL 15								// GPIO15 / 
#define OLED_SDA 4								// GPIO4 / 
#define OLED_RST 16

#endif


// --------------------------------------------------------	
// Define the different OLED versions
//
#if OLED==1
#include "SSD1306.h"
#define OLED_ADDR 0x3C							// Default 0x3C for 0.9", for 1.3" it is 0x78
SSD1306  display(OLED_ADDR, OLED_SDA, OLED_SCL);// i2c ADDR & SDA, SCL on wemos
#endif

// This is an 1.3" OLED display which is running on I2C
#if OLED==2
#include "SH1106.h"
#define OLED_ADDR 0x3C							// Default 0x3C for 1.3" SH1106
SH1106  display(OLED_ADDR, OLED_SDA, OLED_SCL);	// i2c ADDR & SDA, SCL on wemos
#endif


#if OLED==3
#include <U8x8lib.h>
#ifdef BOARD_TTGO
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 22, /* data=*/ 21);

#endif
#ifdef BOARD_HELTEC
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
#endif
#endif


#endif//OLED>=1
