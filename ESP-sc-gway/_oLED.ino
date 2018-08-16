// 1-channel LoRa Gateway for ESP8266
// Copyright (c) 2016, 2017, 2018 Maarten Westenberg version for ESP8266
// Version 5.2.0
// Date: 2018-05-30
//
// 	based on work done by Thomas Telkamp for Raspberry PI 1ch gateway
//	and many others.
//
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the MIT License
// which accompanies this distribution, and is available at
// https://opensource.org/licenses/mit-license.php
//
// Author: Maarten Westenberg (mw12554@hotmail.com)
//
// This file contains the state machine code enabling to receive
// and transmit packages/messages.
// ========================================================================================
//

#if OLED>=1



void init_oLED() 
{
#if OLED==3
    // 16 x 8 char
    u8x8.begin();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    u8x8.drawString(0, 1, "LoRaWAN 1CH GW");
    u8x8.drawString(0, 3, "Starting...");

#else
	// Initialising the UI will init the display too.
	display.init();
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.drawString(0, 24, "STARTING");
	display.display();
#endif
}

// Activate the OLED
//
void acti_oLED() 
{
	// Initialising the UI will init the display too.
#if OLED==1
  display.clear();
	display.setFont(ArialMT_Plain_10);
	display.drawString(0, 0, "READY");
  display.display();
#elif OLED==2
  display.clear();
	display.setFont(ArialMT_Plain_16);
	display.drawString(0, 24, "READY");
  display.display();
#elif OLED==3
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "LoRaWAN 1CH GW");
  u8x8.drawString(0, 3, "Ready...");
#endif

}

// Print a message on the OLED.
// Note: The whole message must fit in the buffer
//
void msg_oLED(String tim, String sf) {
#if OLED==3
    u8x8.setCursor(0, 4);
    u8x8.printf("RX Msg Len: %d");
#else
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
	
  	display.drawString(0, 48, "LEN: " );
//    display.drawString(40, 48, String((int)messageLength) );
    display.display();
#endif
	yield();
}

void oled_stats()
{
#ifdef OLED == 3
  u8x8.setCursor(0, 7);
  u8x8.printf("Stat RX:%d TX:%d", cp_nb_rx_rcv, cp_up_pkt_fwd);
#endif
}

// Print the OLED address in use
//
void addr_oLED() 
{
#if OLED!=3
	Serial.print(F("OLED_ADDR=0x"));
	Serial.println(OLED_ADDR, HEX);
#endif
}

void display_time()
{
  static uint32_t lasttime = 0;
  uint32_t nowSeconds = now();

  if (lasttime == nowSeconds) return;
  
  u8x8.setCursor(0,1);
  u8x8.printf("%02d:%02d:%02d", hour(), minute(), second());
  lasttime = nowSeconds;
}



#endif
