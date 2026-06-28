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

#include "endpoints.h"
#include <stddef.h>

// BABECAFE12345678BABECAFE12345678
#define DEFAULT_NWKSKEY 	{0xBA,0xBE,0xCA,0xFE,0x12,0x34,0x56,0x78,0xBA,0xBE,0xCA,0xFE,0x12,0x34,0x56,0x78}
// CAFEBABE12345678CAFEBABE12345678
#define DEFAULT_APPSKEY 	{0xCA,0xFE,0xBA,0xBE,0x12,0x34,0x56,0x78,0xCA,0xFE,0xBA,0xBE,0x12,0x34,0x56,0x78}


// 44024241ed4ce9a68c6a8bc055233fd3
#define POC_NWKSKEY			{0x44, 0x02, 0x42, 0x41, 0xed, 0x4c, 0xe9, 0xa6, 0x8c, 0x6a, 0x8b, 0xc0, 0x55, 0x23, 0x3f, 0xd3}
// ec925802ae430ca77fd3dd73cb2cc588
#define POC_APPSKEY			{0xec, 0x92, 0x58, 0x02, 0xae, 0x43, 0x0c, 0xa7, 0x7f, 0xd3, 0xdd, 0x73, 0xcb, 0x2c, 0xc5, 0x88}

/*
 * Me and list of my friends
 */
lorawan_endpoint_t lorawan_endpoints[] = {
		{
				.label = "SEED_THINGSAT_051075",
				.module = WM1302_SPI,
				.devaddr = 0xfc00aec0U,
				.deveui = 0x0016C001F1051075U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_THINGSAT_050C9A",
				.module = WM1302_SPI,
				.devaddr = 0xfc00ae48U,
				.deveui = 0x0016C001F1050C9AU,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_THINGSAT_22974C",
				.module = WM1302_SPI,
				.devaddr = 0xfc00ad58U,
				.deveui = 0x0016C001F122974CU,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_THINGSAT_0503CC",
				.module = WM1302_SPI,
				.devaddr = 0xfc00adcaU,
				.deveui = 0x0016C001F10503CCU,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_THINGSAT_151A45",
				.module = WM1302_SPI,
				.devaddr = 0xfc00af17U,
				.deveui = 0x0016C001F1151A45U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_THINGSAT_15282B",
				.module = WM1302_SPI,
				.devaddr = 0xfc00ae5bU,
				.deveui = 0x0016C001F115282BU,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50001",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00af94U,
				.deveui = 0xcafebabe00050001U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50002",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00ad10U,
				.deveui = 0xcafebabe00050002U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50003",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00afaeU,
				.deveui = 0xcafebabe00050003U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50004",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00aef7U,
				.deveui = 0xcafebabe00050004U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50005",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00afb3U,
				.deveui = 0xcafebabe00050005U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_WIOE5_50005",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00afb3U,
				.deveui = 0xcafebabe00050005U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_MICROBIT_40001",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00ad5bU,
				.deveui = 0xcafebabe00040001U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_MICROBIT_40002",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00acfcU,
				.deveui = 0xcafebabe00040002U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_MICROBIT_40003",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00ae67U,
				.deveui = 0xcafebabe00040003U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_MICROBIT_40004",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00ad30U,
				.deveui = 0xcafebabe00040004U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		{
				.label = "SEED_MICROBIT_40005",
				.module = ENDPOINT_SX12xx,
				.devaddr = 0xfc00ad0aU,
				.deveui = 0xcafebabe00040005U,
				.nwkskey = DEFAULT_NWKSKEY,
				.appskey = DEFAULT_APPSKEY,
				.fcntup = 0,
		},

		// Entries of gateways sending ranging1 messages
		{
				.label = "LORIX_LAB_420",
				.module = FIX_GATEWAY,
				.devaddr = 0xfc00ac45,
				.deveui = 0x0016c001ff10d6bb,
				.nwkskey = POC_NWKSKEY,
				.appskey = POC_APPSKEY,
				.fcntup = 10000,
		},
/*

		{
				.label = "ISTATION_0DA1_AIGUILLE_MIDI",
				.module = FIX_GATEWAY,
				.devaddr = 0xfc00acfd,
				.deveui = 0x7076ff0056080da1,
				.nwkskey = POC_NWKSKEY,
				.appskey = POC_APPSKEY,
				.fcntup = 10000,
		},

		{
				.label = "KER110_LAUTARET",
				.module = FIX_GATEWAY,
				.devaddr = 0xfc00ae69,
				.deveui = 0x0000024b080602d9,
				.nwkskey = POC_NWKSKEY,
				.appskey = POC_APPSKEY,
				.fcntup = 10000,
		},
		{
				.label = "MTCDTIP67_0001DBB_AIGOUAL",
				.module = FIX_GATEWAY,
				.devaddr = 0xfc00ad32,
				.deveui = 0x00800000d0001dbb,
				.nwkskey = POC_NWKSKEY,
				.appskey = POC_APPSKEY,
				.fcntup = 10000,
		},
*/
};

lorawan_endpoint_t* lgw_sx130x_endpoint = NULL;

