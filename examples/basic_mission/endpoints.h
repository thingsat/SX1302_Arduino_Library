/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

/*
 * Author : Didier Donsez, Université Grenoble Alpes
 */

 /*
 * LoRaWAN Networks constants for the Thingsat LoRa experiments
 *
 * Used for the configuration of Network_t.
 * See https://www.thethingsnetwork.org/docs/lorawan/prefix-assignments/
 */


#ifndef _BASIC_MISSION_ENDPOINTS_H_
#define _BASIC_MISSION_ENDPOINTS_H_

/*
 * Endpoint information for transmitting and repeating LoRa frames
 */

/*
 * @see https://github.com/csu-grenoble/flatsat/tree/main/Hardware/sx1302_modules
 */

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	RAK5146_SPI_GNSS, // + PPS
	RAK5146_USB_GNSS, // + PPS
	RAK5146_SPI_NO_GNSS,
	RAK5146_USB_NO_GNSS,
	WM1302_SPI,
	WM1302_SX1262_SPI,
	WM1303_SPI,
	NEBRA1303_SPI,
	HT1303_SPI,
	WAVESHARE_SX1302_SPI,
	WAVESHARE_SX1303_SPI,
	THINGSAT_SX1302_BOARD,
	THINGSAT_SX1303_BOARD,
	UNKNOWN_SX130X_MODULE,
	UNKNOWN_SX1388_GATEWAY,
	FIX_GATEWAY,
	ENDPOINT_SX12xx,
	ENDPOINT_LR11xx,
	ENDPOINT_LR2021,
	SDR,
	OTHER,
} lgw_sx130x_module_t;

typedef struct  {
	char* label;
	uint32_t devaddr;
	uint64_t deveui;
	uint8_t nwkskey[16];
	uint8_t appskey[16];
	uint32_t fcntup; // initial frame counter for data up
	lgw_sx130x_module_t module;
	// NB: module can be used for configuring GNSS and PPS

} lorawan_endpoint_t;

bool endpoints_set_myself(const uint64_t deveui);

const lorawan_endpoint_t* endpoints_get_myself();

const lorawan_endpoint_t* endpoints_get_endpoint(const uint32_t devaddr);

void endpoints_print_all(void);

#endif