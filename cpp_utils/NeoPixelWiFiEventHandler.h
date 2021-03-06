/*
 * NeoPixelWiFiEventHandler.h
 *
 *  Created on: Mar 1, 2017
 *      Author: kolban
 */

#ifndef MAIN_NEOPIXELWIFIEVENTHANDLER_H_
#define MAIN_NEOPIXELWIFIEVENTHANDLER_H_
#include "WiFiEventHandler.h"
#include <WS2812.h>

/**
 * @brief Color a neopixel as a function of the WiFi state.
 *
 * When an ESP32 runs, we can't tell by looking at it the state of the WiFi connection.
 * This class provides a WiFi event handler that colors a NeoPixel as a function of the
 * state of the WiFi.
 */
class NeoPixelWiFiEventHandler: public WiFiEventHandler {
public:
	NeoPixelWiFiEventHandler();
	virtual ~NeoPixelWiFiEventHandler();

	esp_err_t apStart() override;
	esp_err_t staConnected() override;
	esp_err_t staGotIp(system_event_sta_got_ip_t event_sta_got_ip) override;
	esp_err_t staDisconnected() override;
	esp_err_t wifiReady() override;
	esp_err_t staStart() override;
private:
	WS2812 ws2812 = WS2812(GPIO_NUM_16, 8);
};

#endif /* MAIN_NEOPIXELWIFIEVENTHANDLER_H_ */
